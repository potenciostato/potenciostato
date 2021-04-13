/*
 * @brief FreeRTOS Blinky example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <string.h>

#include "app_usbd_cfg.h"
#include "hid_generic.h"


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
#include <setup.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
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

xSemaphoreHandle UARTSemMtx,UARTSendMtx,DACSemMtx,ADCSemMtx;
xQueueHandle xQTqueue,xACDqueue,xOPCodequeue;

#define InitMeasure "001"
#define AbortMeasurement "002"
#define SendData "003"
#define ACK "099"
#define SendDataEnd "0031"


char QTFlagSTR[] = "000000000000000000", UARTAKTSTR[] = "0000", pruebahernan[]="080";

xSemaphoreHandle slectura_ok;
xQueueHandle datoADC;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/



/*****************************************************************************
 * Interrupciones
 ****************************************************************************/

void ADC_IRQHandler(void){
	static signed portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	NVIC_DisableIRQ(ADC_IRQn);
	xSemaphoreGiveFromISR(slectura_ok, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void USB_IRQHandler(void)
{
	USBD_API->hw->ISR(g_hUsb);
}

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
}


void hostDispositivo(int id, int valor){
	int valoraux;
}

/* Initialize pin and clocks for USB port */
static void usb_pin_clk_init(void)
{
	/* enable USB PLL and clocks */
	Chip_USB_Init();
	/* enable USB 1 port on the board */
	Board_USBD_Init(1);
}


/* Find the address of interface descriptor for given class type. */
USB_INTERFACE_DESCRIPTOR *find_IntfDesc(const uint8_t *pDesc, uint32_t intfClass)
{
	USB_COMMON_DESCRIPTOR *pD;
	USB_INTERFACE_DESCRIPTOR *pIntfDesc = 0;
	uint32_t next_desc_adr;

	pD = (USB_COMMON_DESCRIPTOR *) pDesc;
	next_desc_adr = (uint32_t) pDesc;

	while (pD->bLength) {
		/* is it interface descriptor */
		if (pD->bDescriptorType == USB_INTERFACE_DESCRIPTOR_TYPE) {

			pIntfDesc = (USB_INTERFACE_DESCRIPTOR *) pD;
			/* did we find the right interface descriptor */
			if (pIntfDesc->bInterfaceClass == intfClass) {
				break;
			}
		}
		pIntfDesc = 0;
		next_desc_adr = (uint32_t) pD + pD->bLength;
		pD = (USB_COMMON_DESCRIPTOR *) next_desc_adr;
	}

	return pIntfDesc;
}


/*****************************************************************************
 * Tareas
 ****************************************************************************/

static void vInicializarUSB(void *pvParameters) {

	USBD_API_INIT_PARAM_T usb_param;
	USB_CORE_DESCS_T desc;
	ErrorCode_t ret = LPC_OK;

	/* Initialize board and chip */
	SystemCoreClockUpdate();
	Board_Init();

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

	while (1) {
		vTaskDelete(NULL);
	}
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
	int ProgState = 0;
char BufferOutSTR[] = "0000000000000000",OpCode[]="000";


	while (1) {
		DEBUGOUT("USB: Leo xOPCodequeue\n");

		xQueueReceive( xOPCodequeue, &OpCode, portMAX_DELAY);

		ProgState = atoi(OpCode);
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

			default:
				DEBUGOUT("USB: Estado invalido\r\n");
				break;
	       }

	}
}
/* DAC parpadeo cada 0.1s */
static void vDACTask(void *pvParameters) {
	bool LedState = false;
	int inDAC = 0;
	static portBASE_TYPE xHigherPriorityTaskWoken;


	while (1)	{
		Board_LED_Set(0, LedState);
		LedState = (bool) !LedState;
		inDAC++;

		/*
		 * tomo el semáforo para poder darlo
		 * lo tomo 2 veces así se bloquea hasta que la uart lo habilite
		 * cuando implementemos dma vamos a resolver de otra forma
		 * */
		DEBUGOUT("DAC: Voy a tomar el semaforo\n");
		xSemaphoreTake( DACSemMtx, portMAX_DELAY );
		DEBUGOUT("DAC: Tengo el semaforo\n");


		/* parpadeo cada 0.1s*/
//		vTaskDelay(100/portTICK_RATE_MS);

//		taskYIELD();
	}
}
/* ADC parpadeo cada 1s */
static void vADCTask(void *pvParameters) {
	char ADCBuff[] = "0000000000000666";

	static uint16_t lecturaADC;
	uint32_t timerFreq, duty;
	timerFreq = Chip_Clock_GetSystemClockRate()/4;
	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_EnableIRQ(ADC_IRQn);
	while (1) {

		DEBUGOUT("ADC: Voy a tomar el semaforo\n");
		/*
		 * tomo el semáforo para poder darlo
		 * lo tomo 2 veces así se bloquea hasta que la uart lo habilite
		 * cuando implementemos dma vamos a resolver de otra forma
		 * */
		xSemaphoreTake( ADCSemMtx, portMAX_DELAY );
		DEBUGOUT("ADC: Escribo datos en xACDqueue\n");
		xQueueSendToBack(xACDqueue,&ADCBuff,0);

		/*
		NVIC_EnableIRQ(ADC_IRQn);
		Chip_ADC_SetStartMode(LPC_ADC,ADC_START_NOW,ADC_TRIGGERMODE_RISING);
		xSemaphoreTake(slectura_ok, ( portTickType ) portMAX_DELAY);
		Chip_ADC_ReadValue(LPC_ADC,ADC_CH0,&lecturaADC);
		duty =(uint32_t)lecturaADC*100/4096;
		Chip_TIMER_SetMatch(LPC_TIMER0, 0, (uint32_t)(timerFreq-(timerFreq*duty)/100)/100);
		xQueueSend( datoADC, ( void * ) &lecturaADC, ( portTickType ) 0 );
		vTaskDelay(configTICK_RATE_HZ / 4);
		*/

		/* parpadeo cada 1s*/
//		vTaskDelay(1000/portTICK_RATE_MS);

//		taskYIELD();
	}
}


/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
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

	vSemaphoreCreateBinary(slectura_ok);
	xSemaphoreTake(slectura_ok, ( portTickType ) 10 );
	datoADC = xQueueCreate( 1, sizeof( uint16_t ) );

	 /*
	  * Busco asegurar que pueda pasar un string del tamaño definido en el protocolo, no se que
	  * tan rapido sea el adc vs a la uart, por lo que a priori creo una cola que pueda
	  * almacenar hasta 4 envios del adc
	  * */
	 xACDqueue = xQueueCreate(4, sizeof(QTFlagSTR));
	 xQTqueue = xQueueCreate(4, sizeof(QTFlagSTR));
	 xOPCodequeue = xQueueCreate(4, sizeof("000"));


	 /* Check the semaphore was created successfully. */
	 if( (UARTSendMtx != NULL) && (UARTSemMtx != NULL) && (ADCSemMtx != NULL) && (DACSemMtx != NULL) )
	 {

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


	/* Start the scheduler */
	vTaskStartScheduler();
	 }
	/* Should never arrive here */
	return 1;
}

/**
 * @}
 */
