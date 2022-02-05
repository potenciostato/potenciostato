/*
 * Potenciostato Grupo 1
 *
 */
// 1.0
//TODO: - Todo lo que dice en Minutas al día de la fecha

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

//Para habilitar (o no) imprimir por consola
bool debugging = DISABLED;
//bool debugging = ENABLED;

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
  uint16_t mode;
  uint32_t frec;
  uint16_t amp;
  uint8_t ncic;
};

struct ADCmsj {
  bool set;
  uint32_t frec;
};

struct USBmsj {
    uint16_t corriente;
    uint16_t tension;
};


uint8_t midiendo=false;

// OBJETOS FreeRTOS

xSemaphoreHandle sDACncic, sDACready, sADCready, sDACstart, sADCstart;
xQueueHandle qUSBin, qUSBout, qADC, qDAC, qADCcorriente, qADCtension, qADCsend;

DMA_TransferDescriptor_t DMA_LLI_buffer;
DMA_TransferDescriptor_t DMA_NLI_buffer;

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


/*****************************************************************************
 * Interrupciones
 ****************************************************************************/
void USB_IRQHandler(void){
    USBD_API->hw->ISR(g_hUsb);

    //Todo: poner un mensaje cuando se logra conectar correctamente

    // Conteos para debugging
    //int countADCsend = uxQueueMessagesWaiting( qADCsend );
    //int countUSBin = uxQueueMessagesWaiting( qUSBin );
    //int countUSBout = uxQueueMessagesWaiting( qUSBout );

}

void ADC_IRQHandler(void){
    uint32_t dataADC;
    uint16_t valorADC;
    int error;
    static signed portBASE_TYPE xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    NVIC_DisableIRQ(ADC_IRQn);
    Board_LED_Toggle(0);
    if (Chip_ADC_ReadStatus(LPC_ADC,CANAL_CORRIENTE,ADC_DR_ADINT_STAT)){
        Chip_ADC_ReadValue(LPC_ADC, CANAL_CORRIENTE, &dataADC);
        valorADC = ADC_DR_RESULT(dataADC);
        error = xQueueSendToBackFromISR( qADCcorriente, &valorADC, &xHigherPriorityTaskWoken );
    }
    if (Chip_ADC_ReadStatus(LPC_ADC,CANAL_TENSION,ADC_DR_ADINT_STAT)){
        Chip_ADC_ReadValue(LPC_ADC, CANAL_TENSION, &dataADC);
        valorADC = ADC_DR_RESULT(dataADC);
        error = xQueueSendToBackFromISR( qADCtension, &valorADC, &xHigherPriorityTaskWoken );
    }
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void DMA_IRQHandler(void)
{
    static signed portBASE_TYPE xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    if (Chip_GPDMA_Interrupt(LPC_GPDMA, CanalDAC) == SUCCESS) {
        xSemaphoreGiveFromISR(sDACncic, &xHigherPriorityTaskWoken);
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
 * USB
 * Es únicamente interrumpida por el QT para
 *  _Iniciar medición
 *  _Abortar medición
 *  _Solicitar el envio de datos => esto lo hace el handler de USB directamente
 *  _A DEFINIR
 * */
static void vUSBTask(void *pvParameters) {

    uint8_t lecturaQT[8]={0};
    int i, error;
    struct DACmsj conf_dac = {false, BARRIDO_CICLICO, 1000, 255}; //estado del modulo, frecuencia[Hz], amplitud[V]
    struct ADCmsj conf_adc = {false,10}; //estado del modulo, frecuencia[Hz], amplitud[V]

    int countADCsend, countUSBin, countUSBout;

    //Solo para pruebas
    //  xQueueSendToBack(qDAC,&conf_dac,0);
    //  xQueueSendToBack(qADC,&conf_adc,0);


    while (1) {
        if (debugging == ENABLED)
            DEBUGOUT("USB: Se va a leer xOPCodequeue\n");

        // Se lee la cola, si no se recibe nada la tarea se quedará esperando
        xQueueReceive( qUSBout, &lecturaQT, portMAX_DELAY);

        if (debugging == ENABLED)
            DEBUGOUT("USB: Se obtuvo xOPCodequeue\n");

        switch(lecturaQT[0])
        {
            case OC_INITMEASUREMENTLINEAL:
                //if (midiendo == true){
                //    break;
                //}
            	midiendo = true;

                //midiendo = true; //se setea en true, pero esto primero se hace desde hid_generic.c
                /*
                 * 1)Habilito int del DAC
                 * 2)Habilito int del ADC
                 * NVIC_EnableIRQ(ADC_IRQn);
                 * ADC_StartCmd(LPC_ADC,ADC_START_NOW);
                 */
                if (debugging == ENABLED)
                    DEBUGOUT("USB: Habilito DAC & ADC\n");

                // Se habilitan DAC y ADC

                /*struct DACmsj {
                  bool set;
                  uint16_t mode;
                  uint32_t frec;
                  uint16_t amp;*/


                conf_dac.set = true;
                conf_dac.mode = BARRIDO_LINEAL;
                conf_dac.frec = (lecturaQT[3]<<16) | (lecturaQT[4]<<8) | lecturaQT[5]; //me parece debería ir un OR | (había un +)
                conf_dac.amp = lecturaQT[2];

                conf_adc.set = true;

                // Envia la configuracion a las tareas y estado de medicion
                error = xQueueSendToBack(qDAC,&conf_dac,0);
                error = xQueueSendToBack(qADC,&conf_adc,0);

                // Espera a que ambas tareas esten listas para la medicion
                xSemaphoreTake(sDACready, ( portTickType ) portMAX_DELAY);
                xSemaphoreTake(sADCready, ( portTickType ) portMAX_DELAY);

                // Inicio de la medicion
                xSemaphoreGive(sDACstart);
                xSemaphoreGive(sADCstart);

                break;

            case OC_INITMEASUREMENTCYCLICAL:
                //if (midiendo == true){
                //    break;
                //}

                midiendo = true;

                /*
                 * 1)Habilito int del DAC
                 * 2)Habilito int del ADC
                 * NVIC_EnableIRQ(ADC_IRQn);
                 * ADC_StartCmd(LPC_ADC,ADC_START_NOW);
                 */
                if (debugging == ENABLED)
                    DEBUGOUT("USB: Habilito DAC & ADC\n");

                //Todo tomar la config del init del QT
                // Se habilitan DAC y ADC

                conf_dac.set = true;
                conf_dac.mode = BARRIDO_CICLICO;
                conf_dac.frec =(lecturaQT[3]<<16) | (lecturaQT[4]<<8) | lecturaQT[5]; //me parece debería ir un OR | (había un +)
                conf_dac.amp = lecturaQT[2];
                conf_dac.ncic = lecturaQT[6];

                conf_adc.set = true;

                // Envia la configuracion a las tareas y estado de medicion
                error = xQueueSendToBack(qDAC,&conf_dac,0);
                error = xQueueSendToBack(qADC,&conf_adc,0);

                // Espera a que ambas tareas esten listas para la medicion
                xSemaphoreTake(sDACready, ( portTickType ) portMAX_DELAY);
                xSemaphoreTake(sADCready, ( portTickType ) portMAX_DELAY);

                // Inicio de la medicion
                xSemaphoreGive(sDACstart);
                xSemaphoreGive(sADCstart);

                break;

            case OC_ABORTMEASUREMENT:
                //if (midiendo == false){
                //    break;
                //}

            	midiendo = false;

                // Deshabilito int del DAC & ADC
                if (debugging == ENABLED)
                    DEBUGOUT("USB: Deshabilito DAC & ADC\n");
                //midiendo = false; //esto se hace desde el handler de USB en hid_generic.c

                // Se limpian las configuraciones
                //conf_dac.mode = BARRIDO_CICLICO;
                //conf_dac.frec = 1000;
				//conf_dac.amp = 255;
                //conf_adc.frec = 10;

                // Se deshabilitan DAC y ADC
                conf_dac.set = false;
                conf_adc.set = false;
                error = xQueueSendToBack(qDAC,&conf_dac,0);
                error = xQueueSendToBack(qADC,&conf_adc,0);

                break;

            case OC_ENDMEASUREMENT:
                // Se limpian las colas de las mediciones
                if (debugging == ENABLED)
                    DEBUGOUT("USB: Se limpian las colas\n");
                xQueueReset( qADCsend );
                xQueueReset( qADCcorriente );
                xQueueReset( qADCtension );
                xQueueReset( qUSBin );
                break;

            case 30:
                // Envio datos a PC de manera continua
                //if (debugging == ENABLED)
                //  DEBUGOUT("USB: Envio datos a QT\r\n");
                //Leo el valor recibido por el adc
                //xQueueReceive( xACDqueue, &BufferOutSTR, 0);

                break;

            case 31:
                // Finalizo el envio de datos a la PC
                if (debugging == ENABLED)
                    DEBUGOUT("USB: Finalizo el envio datos a PC\r\n");
                break;

            case 32:
                if (debugging == ENABLED)
                    DEBUGOUT("DATOS ADC");
                break;

            default:
                if (debugging == ENABLED)
                    DEBUGOUT("USB: Estado invalido\r\n");
                break;
        }
    }
}

/* DAC parpadeo cada 0.1s */
static void vDACTask(void *pvParameters) {
    bool DACset = false;
    uint16_t tabla_salida[ NUMERO_MUESTRAS ], i, SG_OK = 0;
    uint16_t AMPLITUD = 0, AMPLITUD_DIV = 255, MODO = 2;
    uint32_t FREC = 0;
    uint32_t CLOCK_DAC_HZ, timeoutDMA;

    uint8_t respuesta[8]={0};

    struct DACmsj conf;

    int error;

    // Config DAC DMA
    CLOCK_DAC_HZ = Chip_Clock_GetSystemClockRate()/8;
    CanalDAC = Chip_GPDMA_GetFreeChannel ( LPC_GPDMA , 0 );
    Chip_GPDMA_Init ( LPC_GPDMA );
    NVIC_EnableIRQ(DMA_IRQn);




    while(1) {

        // Anular salida DAC
        Chip_DAC_UpdateValue(LPC_DAC, 512);

        //se lee la cola, si no se recibe nada la tarea se quedará esperando
        xQueueReceive(qDAC,&conf,portMAX_DELAY);

        if (debugging == ENABLED)
            DEBUGOUT("DAC: Entre DAC\n");

        if(conf.frec != FREC){
            FREC = conf.frec; //este valor esta multiplicado por 1000 desde el Qt
            if (FREC == 0){
            	DEBUGOUT("DAC: Frecuencia incorrecta, no puede valer 0\n");
            }
            timeoutDMA = (((((CLOCK_DAC_HZ * 10) / FREC) * 10) / NUMERO_MUESTRAS ) * 10);
            // Nota:
            // el multiplicar 3 veces por 10 se debe a que la frecuencia desde QT se envia multiplicada
            // por 1000 para pasar 0,001 a 1 y tener todo en unsigned int en 24 (32) bits
            if (timeoutDMA > 65535){
            	timeoutDMA = 65535; //esto soluciona el problema del envío del Qt que,
            	// a veces, le resta 1 a 1000 * frecuencia a enviar.
            	// => timeoutDMA resultaría mayor al máximo
            }
            if (timeoutDMA == 0){
            	DEBUGOUT("DAC: El timeoutDMA no puede valer 0\n");
            }else{
            	Chip_DAC_SetDMATimeOut(LPC_DAC, timeoutDMA);
            }
            timeoutDMA = 50;
        }
        if (conf.mode != MODO){
        	MODO = conf.mode;
            Chip_GPDMA_Stop(LPC_GPDMA, CanalDAC);
            AMPLITUD = 0; // fuerza a que cuando cambie el modo verifique la tabla de salida
            DACset = false;
            if (conf.mode == BARRIDO_LINEAL){
                Chip_GPDMA_PrepareDescriptor ( LPC_GPDMA , &DMA_NLI_buffer  , (uint32_t) tabla_salida ,
                                                GPDMA_CONN_DAC , DMA_SIZE , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA , 0 );
            }
        }
        if (conf.amp != AMPLITUD ){
        	AMPLITUD = conf.amp;
			if (conf.mode == BARRIDO_CICLICO){
				for ( i = 0 ; i < NUMERO_MUESTRAS ; i++ ) {
					tabla_salida[i]= (uint16_t) ((AMPLITUD * (tabla_tria[i] - VALOR_MEDIO_DAC))/AMPLITUD_DIV + VALOR_MEDIO_DAC) << 6;
				}
			}
			if (conf.mode == BARRIDO_LINEAL){
				for ( i = 0 ; i < NUMERO_MUESTRAS ; i++ ) {
					tabla_salida[i]= (uint16_t) (AMPLITUD * tabla_sier[i] / AMPLITUD_DIV ) << 6;
				}
			}
		}

        if(conf.set != DACset){
            DACset = conf.set;
            if(DACset){
                if (conf.mode == BARRIDO_CICLICO) {
                	if (conf.ncic == 0){
                        Chip_GPDMA_PrepareDescriptor ( LPC_GPDMA , &DMA_LLI_buffer  , (uint32_t) tabla_salida ,
                                                         GPDMA_CONN_DAC , DMA_SIZE , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA , &DMA_LLI_buffer);

                        xSemaphoreGive(sDACready);
                        xSemaphoreTake(sDACstart, ( portTickType ) portMAX_DELAY);
                        SG_OK = Chip_GPDMA_SGTransfer (LPC_GPDMA , CanalDAC ,&DMA_LLI_buffer , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
                		Board_LED_Set(0,false);
                	}else{
                        Chip_GPDMA_PrepareDescriptor ( LPC_GPDMA , &DMA_LLI_buffer  , (uint32_t) tabla_salida ,
                                                            GPDMA_CONN_DAC , DMA_SIZE , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA , 0);
                        xSemaphoreGive(sDACready);
                        xSemaphoreTake(sDACstart, ( portTickType ) portMAX_DELAY);
                        for(i=0;i<conf.ncic;i++) {
                    		//Board_LED_Toggle(0);
                    		SG_OK = Chip_GPDMA_SGTransfer (LPC_GPDMA , CanalDAC ,&DMA_LLI_buffer , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
                    		xSemaphoreTake(sDACncic, ( portTickType ) portMAX_DELAY);
                    	}

                    	//Se envía el término de medición

    					if (debugging == ENABLED)
    						DEBUGOUT("INT: CYCLE END\n");
    					respuesta[0] = OC_CYCLEEND;
    					respuesta[1] = 0x0;
    					respuesta[2] = 0x0;
    					respuesta[3] = 0x0;
    					respuesta[4] = 0x0;
    					respuesta[5] = 0x0;
    					respuesta[6] = 0x0;
    					respuesta[7] = 0x0;
    					error = xQueueSendToBack(qUSBin,&respuesta,portMAX_DELAY);

    					respuesta[0] = OC_ABORTMEASUREMENT;
    					respuesta[1] = 0x0;
    					respuesta[2] = 0x0;
    					respuesta[3] = 0x0;
    					respuesta[4] = 0x0;
    					respuesta[5] = 0x0;
    					respuesta[6] = 0x0;
    					respuesta[7] = 0x0;
    					error = xQueueSendToBack(qUSBout,&respuesta,portMAX_DELAY);

                    	// Aquí el Qt debera enviar un Abort


                	}
                }
                if (conf.mode == BARRIDO_LINEAL) {
                	xSemaphoreGive(sDACready);
                	xSemaphoreTake(sDACstart, ( portTickType ) portMAX_DELAY);
                    SG_OK = Chip_GPDMA_SGTransfer (LPC_GPDMA , CanalDAC ,&DMA_NLI_buffer , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
                }

                if (debugging == ENABLED)
                    DEBUGOUT("DAC: Habilite DAC\n");
            } else {
                Chip_GPDMA_Stop(LPC_GPDMA, CanalDAC);
                if (debugging == ENABLED)
                    DEBUGOUT("DAC: Deshabilite DAC\n");
            }
        }
    }
}

/* ADC parpadeo cada 1s */
static void vADCTask(void *pvParameters) {

    uint16_t FREC = ADC_SAMPL_FREC, i, corrienteADC, tensionADC;
    struct ADCmsj conf;
    //uint16_t ADCbuffer[ADC_N_COLA];
    struct USBmsj msjUSB;
    int error;

    NVIC_EnableIRQ(ADC_IRQn);

    while(1) {

        // Se lee la cola, si no se recibe nada la tarea se quedará esperando
        xQueueReceive(qADC,&conf,portMAX_DELAY);
        if (debugging == ENABLED)
            DEBUGOUT("ADC: Entre ADC\n");

        if(conf.frec != FREC){
            FREC = conf.frec;
            Chip_ADC_SetSampleRate(LPC_ADC,&ADCSetup,FREC);
        }
        if (conf.set == true){
            if (debugging == ENABLED)
                DEBUGOUT("ADC: Habilita medicion ADC\n");

            xQueueReset( qADCsend );
            xQueueReset( qADCcorriente );
            xQueueReset( qADCtension );

            xSemaphoreGive(sADCready);
            xSemaphoreTake(sADCstart, ( portTickType ) portMAX_DELAY);
            NVIC_EnableIRQ(ADC_IRQn);
        	Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE);

            i = 0;
            while (conf.set){


                xQueueReceive(qADCcorriente,&corrienteADC,portMAX_DELAY);
                NVIC_EnableIRQ(ADC_IRQn);
                xQueueReceive(qADCtension,&tensionADC,portMAX_DELAY);
                NVIC_EnableIRQ(ADC_IRQn);

                msjUSB.corriente = corrienteADC;
                msjUSB.tension = tensionADC;
                error = xQueueSendToBack(qADCsend, &msjUSB, 10); // pdTRUE (1) if the item was successfully posted, otherwise errQUEUE_FULL (0)

                if(error == 0){
                	error = 0;
                }
                // Conteos para debugging
                //int countADCsend = uxQueueMessagesWaiting( qADCsend );

                if (debugging == ENABLED)
                    DEBUGOUT("ADC: ADC Send\n");

                // Se recibe la config para saber si se debera
                // seguir midiendo o terminar
                xQueueReceive(qADC,&conf,( portTickType ) TICKS_MUESTREO);
            }
            if (debugging == ENABLED)
                DEBUGOUT("ADC: Deshabilita medicion ADC\n");
            Chip_ADC_SetBurstCmd(LPC_ADC, DISABLE);
        }
        else {
            if (debugging == ENABLED)
                DEBUGOUT("ADC: Esta deshabilitado ADC\n");
        }
    }
}


/*****************************************************************************
 * Main
 ****************************************************************************/

/**
 * @brief   Main
 * @return  Nada, la funcion no deberá salir
 */
int main(void)
{
    prvSetupHardware();
    //ADC conf
    //DAC conf
    Board_LED_Set(0, false);
    if (debugging == ENABLED)
        DEBUGOUT("Potenciostato UTN FRA\r\n");

    vSemaphoreCreateBinary(sDACncic);
    xSemaphoreTake(sDACncic, ( portTickType ) 10 );
    vSemaphoreCreateBinary(sDACready);
    xSemaphoreTake(sDACready, ( portTickType ) 10 );
    vSemaphoreCreateBinary(sDACstart);
    xSemaphoreTake(sDACstart, ( portTickType ) 10 );
    vSemaphoreCreateBinary(sADCready);
    xSemaphoreTake(sADCready, ( portTickType ) 10 );
    vSemaphoreCreateBinary(sADCstart);
    xSemaphoreTake(sADCstart, ( portTickType ) 10 );

    qUSBin = xQueueCreate( TAMANIO_MAX_COLA_USB, sizeof( uint8_t )* LARGO_MENSAJE);
    qUSBout = xQueueCreate( TAMANIO_MAX_COLA_USB, sizeof( uint8_t ) * LARGO_MENSAJE);
    qDAC = xQueueCreate( 1, sizeof( struct DACmsj ));
    qADC = xQueueCreate( 1, sizeof( struct ADCmsj ));
    qADCcorriente = xQueueCreate(ADC_N_COLA, sizeof( uint16_t ));
    qADCtension = xQueueCreate(ADC_N_COLA, sizeof( uint16_t ));
    qADCsend = xQueueCreate(TAMANIO_MAX_COLA_ADC, sizeof( struct USBmsj ) * ADC_N_COLA);

    prvSetupHardware();

    xTaskCreate(vInicializarUSB, (signed char *) "InicializarUSB",
                        configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 3UL),
                        (xTaskHandle *) NULL);

    /* USB  */
    xTaskCreate(vUSBTask, (signed char *) "vUSBTask",
                configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
                (xTaskHandle *) NULL);

    /* DAC  */
    xTaskCreate(vDACTask, (signed char *) "vDACTask",
                configMINIMAL_STACK_SIZE * 5, NULL, (tskIDLE_PRIORITY + 1UL),
                (xTaskHandle *) NULL);

    /* ADC  */
    xTaskCreate(vADCTask, (signed char *) "vADCTask",
                configMINIMAL_STACK_SIZE * 5, NULL, (tskIDLE_PRIORITY + 1UL),
                (xTaskHandle *) NULL);
    // verificar si es * 5 o si se puede dejar * 1

    /* Empieza el Scheduler */
    vTaskStartScheduler();

    /* Nunca deberá llegar hasta acá */
    return 1;
}

/**
 * @}
 */
