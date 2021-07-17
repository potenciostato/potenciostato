/*
 * Sintetizador Grupo 1
 *
 */
// 1.0
//TODO: -buferear salida para que no haga ruido ->listo
//      -mejorar amplitud de onda segun las potencias
//		-chequear el bug de que se cuelga, creo que tiene que ver con el hardware

#include <board.h>
#include <FreeRTOS.h>
#include <task.h>
#include <chip.h>
#include <semphr.h>
#include <queue.h>


#include <stdio.h>
#include <string.h>
#include "app_usbd_cfg.h"
#include "hid_generic.h"

#include <defines.h>
#include <constantes.h>
#include <setup.h>

/*****************************************************************************
 * Variables Globales
 ****************************************************************************/
extern ADC_CLOCK_SETUP_T ADCSetup;

uint32_t CanalDAC, CanalADC;

static USBD_HANDLE_T g_hUsb;

extern const  USBD_HW_API_T hw_api;
extern const  USBD_CORE_API_T core_api;
extern const  USBD_HID_API_T hid_api;
/* Since this example only uses HID class link functions for that class only */

static const  USBD_API_T g_usbApi = {
	&hw_api,
	&core_api,
	0,
	0,
	&hid_api,
	0,
	0,
	0x02221101,
};

const  USBD_API_T *g_pUsbApi = &g_usbApi;

struct DACmsj {
  bool set;
  uint32_t frec;
  uint16_t amp;
};

struct ADCmsj {
  bool set;
  uint32_t frec;
};


// OBJETOS FreeRTOS

xSemaphoreHandle UARTSemMtx,UARTSendMtx,DACSemMtx,ADCSemMtx;
xQueueHandle xQTqueue,xACDqueue,xOPCodequeue;
xSemaphoreHandle sBufferADC;
xQueueHandle qUSBin, qUSBout, qADC, qDAC, qADCdata, qADCsend;

DMA_TransferDescriptor_t DMA_LLI_buffer;
DMA_TransferDescriptor_t DMA_LLI_buffer_ADC;

#define InitMeasure "001"
#define AbortMeasurement "002"
#define SendData "003"
#define ACK "099"
#define SendDataEnd "0031"


char QTFlagSTR[] = "000000000000000000", UARTAKTSTR[] = "0000", pruebahernan[]="080";

static uint8_t Burst_Mode_Flag = 0, Interrupt_Continue_Flag;
static uint8_t ADC_Interrupt_Done_Flag, channelTC, dmaChannelNum;

/*****************************************************************************
 * Declaracion de funciones
 ****************************************************************************/
static void usb_pin_clk_init(void)
{
	/* enable USB PLL and clocks */
	Chip_USB_Init();
	/* enable USB 1 port on the board */
	Board_USBD_Init(1);
}

void hostDispositivo(uint32_t id, uint32_t valor){
	int valoraux;
}

/*****************************************************************************
 * Interrupciones
 ****************************************************************************/
void USB_IRQHandler(void){
	USBD_API->hw->ISR(g_hUsb);
}

void ADC_IRQHandler(void){
	uint32_t dataADC;
	uint16_t valorADC;
	static signed portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	NVIC_DisableIRQ(ADC_IRQn);
	Chip_ADC_ReadValue(LPC_ADC, ADC_CH0, &dataADC);
	valorADC = ADC_DR_RESULT(dataADC);
	xQueueSendToBackFromISR( qADCdata, &valorADC, &xHigherPriorityTaskWoken );
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void DMA_IRQHandler(void)
{
	static signed portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	if (Chip_GPDMA_Interrupt(LPC_GPDMA, CanalADC) == SUCCESS) {
		xSemaphoreGiveFromISR(sBufferADC, &xHigherPriorityTaskWoken);
	}
	else {
		/* Process error here */
	}
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*****************************************************************************
 * Tareas
 ****************************************************************************/
static void vInicializarUSB(void *pvParameters) {

	USBD_API_INIT_PARAM_T usb_param;
	USB_CORE_DESCS_T desc;
	ErrorCode_t ret = LPC_OK;

	/* enable clocks and pinmux */
	usb_pin_clk_init();

	/* initialize call back structures */
	memset((void *) &usb_param, 0, sizeof(USBD_API_INIT_PARAM_T));
	usb_param.usb_reg_base = LPC_USB_BASE + 0x200;
	usb_param.max_num_ep = 2;
	usb_param.mem_base = USB_STACK_MEM_BASE;
	usb_param.mem_size = USB_STACK_MEM_SIZE;

	/* Set the USB descriptors */
	desc.device_desc = (uint8_t *) USB_DeviceDescriptor;
	desc.string_desc = (uint8_t *) USB_StringDescriptor;

	/* Note, to pass USBCV test full-speed only devices should have both
	 * descriptor arrays point to same location and device_qualifier set
	 * to 0.
	 */
	desc.high_speed_desc = USB_FsConfigDescriptor;
	desc.full_speed_desc = USB_FsConfigDescriptor;
	desc.device_qualifier = 0;

	/* USB Initialization */
	ret = USBD_API->hw->Init(&g_hUsb, &desc, &usb_param);
	if (ret == LPC_OK) {

		ret = usb_hid_init(g_hUsb,
			(USB_INTERFACE_DESCRIPTOR *) &USB_FsConfigDescriptor[sizeof(USB_CONFIGURATION_DESCRIPTOR)],
			&usb_param.mem_base, &usb_param.mem_size);
		if (ret == LPC_OK) {
			/*  enable USB interrupts */
			NVIC_EnableIRQ(USB_IRQn);
			/* now connect */
			USBD_API->hw->Connect(g_hUsb, 1);
		}
	}
	vTaskDelete(NULL);
}

/*
* Tarea para simular la INT del QT
* Interrumpo a la UART/USB para:
* _comenzar a medir, paso el código de operacion y los valores a usar
* _pedir datos de la medición, paso el código de operacion
* _detener la medición, paso el código de operacion
* El órden de envio de datos es
* 1) datos de la medición, si estoy iniciando una medición, uso xQTqueue
* 2) código de operación, uso xOPCodequeue
*
* */
static void vINTSimTask(void *pvParameters) {
	int i;
	int a = 0;
	char USBBuff[] = "0000000000000777";


	while (1) {

		/*
		 * Envio el código para iniciar la medición*/
		DEBUGOUT("INT: Iniciar medicion\n");
		strcpy(USBBuff,"0010050001000010");
		/*
		 * Para la ISR usar
		 * xQueueSendToBackFromISR( xQTqueue, &USBBuff, pdFALSE );*/
		xQueueSendToBack(xQTqueue,&USBBuff,0);
		xQueueSendToBack(xOPCodequeue,&InitMeasure,0);
		/* Espero 3s*/
		vTaskDelay(3000/portTICK_RATE_MS);

		/* Envío el código para pedir datos*/
		DEBUGOUT("INT: Pedir datos\n");
		xQueueSendToBack(xOPCodequeue,&SendData,0);
		/* Espero 3s*/
		vTaskDelay(3000/portTICK_RATE_MS);

		/* Envio el código para abortar la medición*/
		DEBUGOUT("INT: Abortar medicion\n");
		xQueueSendToBack(xQTqueue,&AbortMeasurement,0);
		/* Espero 1s*/
		vTaskDelay(1000/portTICK_RATE_MS);
	}
}
/*
 * USB
 * Es únicamente interrumpida por el QT para
 * 	_Iniciar medición 001
 * 	_Solicitar el envio de datos 003
 * 	_Abortar medición 002
 * Uso BufferOutSTR para enviarle datos a QT
 * */
static void vUSBTask(void *pvParameters) {
//char ProgState= "0000000000000000";
	int ProgState = 0, i;
	char BufferOutSTR[] = "0000000000000000",OpCode[]="000";
	struct DACmsj conf = {true,1000,1};
	struct ADCmsj conf2 = {true,10};
	uint32_t ADCbuffer[ADC_N_LECTURAS], valoresADC[ADC_N_LECTURAS];

	xQueueSendToBack(qDAC,&conf,0);
	xQueueSendToBack(qADC,&conf2,0);
	while (1) {
		DEBUGOUT("USB: Leo xOPCodequeue\n");

		xQueueReceive( xOPCodequeue, &OpCode, portMAX_DELAY);

		ProgState = 32;
			switch(ProgState){
			case 10 :
				/*
				 * 1)Habilito int del DAC
				 * 2)Habilito int del ADC
				 * NVIC_EnableIRQ(ADC_IRQn);
				 * ADC_StartCmd(LPC_ADC,ADC_START_NOW);
				 */
				DEBUGOUT("USB: Habilito DAC & ADC\n");
				xSemaphoreGive(DACSemMtx);
				xSemaphoreGive(ADCSemMtx);
				break;

			case 20:
				// Deshabilito int del DAC & ADC
				strcpy(BufferOutSTR,ACK);
				DEBUGOUT("USB: Deshabilito DAC & ADC\r\n");

				DEBUGOUT("USB: ACKAbort = %s\r\n",BufferOutSTR);
				break;

			case 30:
				// Envio datos a PC de manera continua
				DEBUGOUT("USB: Envio datos a QT\r\n");
				//Leo el valor recibido por el adc
				xQueueReceive( xACDqueue, &BufferOutSTR, 0);

				break;

			case 31:
				// Finalizo el envio de datos a la PC
				DEBUGOUT("USB: Finalizo el envio datos a PC\r\n");
				break;

			case 32:
				DEBUGOUT("DATOS ADC");
				break;

			default:
				DEBUGOUT("USB: Estado invalido\r\n");
				break;
	       }
	}
}
/* DAC parpadeo cada 0.1s */
static void vDACTask(void *pvParameters) {
	bool DACset = false;
	uint16_t tabla_salida[ NUMERO_MUESTRAS ], i, SG_OK = 0;
	uint16_t FREC = 0, AMPLITUD = 0;
	uint32_t CLOCK_DAC_HZ, timeoutDMA;
	struct DACmsj conf;

	// Config DAC DMA
	CLOCK_DAC_HZ = Chip_Clock_GetSystemClockRate()/4;
	Chip_GPDMA_PrepareDescriptor ( LPC_GPDMA , &DMA_LLI_buffer  , (uint32_t) tabla_salida ,
									GPDMA_CONN_DAC , DMA_SIZE , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA , &DMA_LLI_buffer );
	CanalDAC = Chip_GPDMA_GetFreeChannel ( LPC_GPDMA , 0 );
	Chip_GPDMA_Init ( LPC_GPDMA );

	while (1)	{

		xQueueReceive(qDAC,&conf,portMAX_DELAY);

		if(conf.frec != FREC){
			FREC = conf.frec;
			timeoutDMA = CLOCK_DAC_HZ / ( FREC * NUMERO_MUESTRAS );
			Chip_DAC_SetDMATimeOut(LPC_DAC, timeoutDMA);
		}
		if (conf.amp != AMPLITUD){
			AMPLITUD = conf.amp;
			for ( i = 0 ; i < NUMERO_MUESTRAS ; i++ ) {
				tabla_salida[i]= AMPLITUD * tabla_tria[i];
			}
		}
		if(conf.set != DACset){
			DACset = conf.set;
			if(DACset){
				SG_OK = Chip_GPDMA_SGTransfer (LPC_GPDMA , CanalDAC ,&DMA_LLI_buffer , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
				Board_LED_Set(0, true);
			} else {
				Chip_GPDMA_Stop(LPC_GPDMA, CanalDAC);
				Board_LED_Set(0, false);
			}
		}
	}
}

/* ADC parpadeo cada 1s */
static void vADCTask(void *pvParameters) {

	uint16_t FREC = ADC_SAMPL_FREC, i, dataADC;
	struct ADCmsj conf;
	uint16_t ADCbuffer[ADC_N_COLA], ADCbuffer2[ADC_N_LECTURAS];

	Chip_ADC_Int_SetChannelCmd(LPC_ADC, ADC_CH0, ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);

	while (1){
		xQueueReceive(qADC,&conf,portMAX_DELAY);

		if(conf.frec != FREC){
			FREC = conf.frec;
			Chip_ADC_SetSampleRate(LPC_ADC,&ADCSetup,FREC);
		}
		if (conf.set){
			Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE);
			i = 0;
			while (conf.set){
				xQueueReceive(qADC,&conf,( portTickType ) 0);
				xQueueReceive(qADCdata,&dataADC,portMAX_DELAY);
				NVIC_EnableIRQ(ADC_IRQn);
				ADCbuffer[i] = dataADC;
				i++;
				if(i>=ADC_N_COLA){
					i = 0;
					xQueueSendToBack(qADCsend,ADCbuffer,10);
				}
			}
			Chip_ADC_SetBurstCmd(LPC_ADC, DISABLE);
		}
	}
}


/*****************************************************************************
 * Main
 ****************************************************************************/

/**
 * @brief	Main
 * @return	Nada, la funcion no deberá salir
 */
int main(void)
{
	prvSetupHardware();
	//ADC conf
	//DAC conf

	DEBUGOUT("Hello code\r\n");

	UARTSendMtx = xSemaphoreCreateMutex();
	UARTSemMtx = xSemaphoreCreateMutex();
	ADCSemMtx = xSemaphoreCreateMutex();
	DACSemMtx = xSemaphoreCreateMutex();

	vSemaphoreCreateBinary(sBufferADC);
	xSemaphoreTake(sBufferADC, ( portTickType ) 10 );

	qUSBin = xQueueCreate( 10, sizeof( uint8_t )* 6);
	qUSBout = xQueueCreate( 10, sizeof( uint8_t )* 6);
	qDAC = xQueueCreate( 1, sizeof( struct DACmsj ));
	qADC = xQueueCreate( 1, sizeof( struct ADCmsj ));
	qADCdata = xQueueCreate(ADC_N_COLA, sizeof( uint16_t ));
	qADCsend = xQueueCreate(1, sizeof( uint16_t ) * ADC_N_COLA);

	 /*
	  * Busco asegurar que pueda pasar un string del tamaño definido en el protocolo, no se que
	  * tan rapido sea el adc vs a la uart, por lo que a priori creo una cola que pueda
	  * almacenar hasta 4 envios del adc
	  * */
	 xACDqueue = xQueueCreate(4, sizeof(QTFlagSTR));
	 xQTqueue = xQueueCreate(4, sizeof(QTFlagSTR));
	 xOPCodequeue = xQueueCreate(4, sizeof("000"));

	prvSetupHardware();

	xTaskCreate(vInicializarUSB, (signed char *) "InicializarUSB",
						configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 3UL),
						(xTaskHandle *) NULL);
	/* QT */
	xTaskCreate(vINTSimTask, (signed char *) "vINTSimTask",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2UL),
						(xTaskHandle *) NULL);

	/* USB ex UART  */
	xTaskCreate(vUSBTask, (signed char *) "vUSBTask",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2UL),
				(xTaskHandle *) NULL);

	/* DAC  */
	xTaskCreate(vDACTask, (signed char *) "vDACTask",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	/* ADC  */
	xTaskCreate(vADCTask, (signed char *) "vADCTask",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	/* Empieza el Scheduler */
	vTaskStartScheduler();

	/* Nunca deberá llegar hasta acá */
	return 1;
}

/**
 * @}
 */
