/*
 * Potenciostate Grupo 1
 *
 */
// 1.0
//TODO: -buferear salida para que no haga ruido ->listo
//      -mejorar amplitud de onda segun las potencias
//      -chequear el bug de que se cuelga, creo que tiene que ver con el hardware

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
};

struct ADCmsj {
  bool set;
  uint32_t frec;
};

struct USBmsj {
    uint16_t corriente;
    uint16_t tension;
};


// OBJETOS FreeRTOS

xSemaphoreHandle DACSemMtx,ADCSemMtx;
xSemaphoreHandle sBufferADC;
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

void hostDispositivo(uint32_t id, uint32_t valor){
    int valoraux;
}

/*****************************************************************************
 * Interrupciones
 ****************************************************************************/
void USB_IRQHandler(void){
    USBD_API->hw->ISR(g_hUsb);

    //Todo: poner un mensaje cuando se logra conectar correctamente

    // Conteos para debugging
    int countADCsend = uxQueueMessagesWaiting( qADCsend );
    int countUSBin = uxQueueMessagesWaiting( qUSBin );
    int countUSBout = uxQueueMessagesWaiting( qUSBout );
}

void ADC_IRQHandler(void){
    uint32_t dataADC;
    uint16_t valorADC;
    static signed portBASE_TYPE xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    NVIC_DisableIRQ(ADC_IRQn);
    if (Chip_ADC_ReadStatus(LPC_ADC,CANAL_CORRIENTE,ADC_DR_ADINT_STAT)){
        Chip_ADC_ReadValue(LPC_ADC, CANAL_CORRIENTE, &dataADC);
        valorADC = ADC_DR_RESULT(dataADC);
        xQueueSendToBackFromISR( qADCcorriente, &valorADC, &xHigherPriorityTaskWoken );
    }
    if (Chip_ADC_ReadStatus(LPC_ADC,CANAL_TENSION,ADC_DR_ADINT_STAT)){
        Chip_ADC_ReadValue(LPC_ADC, CANAL_TENSION, &dataADC);
        valorADC = ADC_DR_RESULT(dataADC);
        xQueueSendToBackFromISR( qADCtension, &valorADC, &xHigherPriorityTaskWoken );
    }
    //Chip_ADC_ReadValue(LPC_ADC, ADC_CH0, &dataADC);
    //valorADC = ADC_DR_RESULT(dataADC);
    //xQueueSendToBackFromISR( qADCdata, &valorADC, &xHigherPriorityTaskWoken );
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void DMA_IRQHandler(void)
{
    static signed portBASE_TYPE xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    if (Chip_GPDMA_Interrupt(LPC_GPDMA, CanalDAC) == SUCCESS) {
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
 * USB
 * Es únicamente interrumpida por el QT para
 *  _Iniciar medición
 *  _Abortar medición
 *  _Solicitar el envio de datos => esto lo hace el handler de USB directamente
 *  _A DEFINIR
 * */
static void vUSBTask(void *pvParameters) {

    uint8_t lecturaQT[8]={0};
    int i;
    struct DACmsj conf_dac = {true, BARRIDO_CICLICO, 1000, 1}; //estado del modulo, frecuencia[Hz], amplitud[V]
    struct ADCmsj conf_adc = {true,10}; //estado del modulo, frecuencia[Hz], amplitud[V]
    uint8_t midiendo=false;

    int countADCsend, countUSBin, countUSBout;

    //Solo para pruebas
        configGains(SW_GAIN2,SW_I_GAIN2,SW_V_GAIN2);
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
                if (midiendo == true){
                    break;
                }
                /*
                 * 1)Habilito int del DAC
                 * 2)Habilito int del ADC
                 * NVIC_EnableIRQ(ADC_IRQn);
                 * ADC_StartCmd(LPC_ADC,ADC_START_NOW);
                 */
                if (debugging == ENABLED)
                    DEBUGOUT("USB: Habilito DAC & ADC\n");


                //Configuro los gains y los offsets
                configGains(SW_GAIN1,SW_I_GAIN1,SW_V_GAIN1);

                //Todo tomar la config del init del QT
                // Se habilitan DAC y ADC

                /*struct DACmsj {
                  bool set;
                  uint16_t mode;
                  uint32_t frec;
                  uint16_t amp;*/


                conf_dac.set = true;
                conf_dac.mode = BARRIDO_LINEAL;
                conf_dac.frec =(lecturaQT[3]<<8)+lecturaQT[4];
                conf_dac.amp =lecturaQT[2]/100;

                if(lecturaQT[2]<30)
                    //>1v
                    configGains(SW_GAIN2,SW_I_GAIN2,SW_V_GAIN2);
                else
                    //<1v
                    configGains(SW_GAIN1,SW_I_GAIN1,SW_V_GAIN1);




                conf_adc.set = true;
                xQueueSendToBack(qDAC,&conf_dac,0);
                xQueueSendToBack(qADC,&conf_adc,0);

                midiendo = true;
                break;

            case OC_INITMEASUREMENTCYCLICAL:
                if (midiendo == true){
                    break;
                }
                /*
                 * 1)Habilito int del DAC
                 * 2)Habilito int del ADC
                 * NVIC_EnableIRQ(ADC_IRQn);
                 * ADC_StartCmd(LPC_ADC,ADC_START_NOW);
                 */
                if (debugging == ENABLED)
                    DEBUGOUT("USB: Habilito DAC & ADC\n");


                //Configuro los gains y los offsets
                configGains(SW_GAIN1,SW_I_GAIN1,SW_V_GAIN1);

                //Todo tomar la config del init del QT
                // Se habilitan DAC y ADC

                conf_dac.set = true;
                conf_dac.mode = BARRIDO_LINEAL;
                conf_dac.frec =(lecturaQT[3]<<8)+lecturaQT[4];
                conf_dac.amp =lecturaQT[2]/100;

                if(lecturaQT[2]<30)
                    //>1v
                    configGains(SW_GAIN2,SW_I_GAIN2,SW_V_GAIN2);
                else
                    //<1v
                    configGains(SW_GAIN1,SW_I_GAIN1,SW_V_GAIN1);

                conf_adc.set = true;
                xQueueSendToBack(qDAC,&conf_dac,0);
                xQueueSendToBack(qADC,&conf_adc,0);

                midiendo = true;
                break;

            case OC_ABORTMEASUREMENT:
                if (midiendo == false){
                    break;
                }

                // Deshabilito int del DAC & ADC
                if (debugging == ENABLED)
                    DEBUGOUT("USB: Deshabilito DAC & ADC\n");
                midiendo = false;

                // Se deshabilitan DAC y ADC
                conf_dac.set = false;
                conf_adc.set = false;
                xQueueSendToBack(qDAC,&conf_dac,0);
                xQueueSendToBack(qADC,&conf_adc,0);

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
/* DAC parpadeo cada 0.1s */
static void vDACTask(void *pvParameters) {
    bool DACset = false;
    uint16_t tabla_salida[ NUMERO_MUESTRAS ], i, SG_OK = 0;
    uint16_t FREC = 0, AMPLITUD = 0, AMPLITUD_DIV = 10, MODO = 2;
    uint32_t CLOCK_DAC_HZ, timeoutDMA;
    struct DACmsj conf;

    // Config DAC DMA
    CLOCK_DAC_HZ = Chip_Clock_GetSystemClockRate()/4;
    CanalDAC = Chip_GPDMA_GetFreeChannel ( LPC_GPDMA , 0 );
    Chip_GPDMA_Init ( LPC_GPDMA );
    NVIC_EnableIRQ(DMA_IRQn);



    while(1) {

        //se lee la cola, si no se recibe nada la tarea se quedará esperando
        xQueueReceive(qDAC,&conf,portMAX_DELAY);

        if (debugging == ENABLED)
            DEBUGOUT("DAC: Entre DAC\n");

        if(conf.frec != FREC){
            FREC = conf.frec;
            timeoutDMA = CLOCK_DAC_HZ / ( FREC * NUMERO_MUESTRAS );
            Chip_DAC_SetDMATimeOut(LPC_DAC, timeoutDMA);
            timeoutDMA = 50;
        }
        if (conf.mode != MODO){
            Chip_GPDMA_Stop(LPC_GPDMA, CanalDAC);
            AMPLITUD = 0; // fuerza a que cuando cambie el modo verifique la tabla de salida
            DACset = false;
            if (conf.mode == BARRIDO_CICLICO){
                Chip_GPDMA_PrepareDescriptor ( LPC_GPDMA , &DMA_LLI_buffer  , (uint32_t) tabla_salida ,
                                                GPDMA_CONN_DAC , DMA_SIZE , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA , &DMA_LLI_buffer );
            }
            if (conf.mode == BARRIDO_LINEAL){
                Chip_GPDMA_PrepareDescriptor ( LPC_GPDMA , &DMA_NLI_buffer  , (uint32_t) tabla_salida ,
                                                GPDMA_CONN_DAC , DMA_SIZE , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA , 0 );
            }
        }
        if (conf.amp != AMPLITUD){
                    AMPLITUD = conf.amp;
                    if (conf.mode == BARRIDO_CICLICO){
                        for ( i = 0 ; i < NUMERO_MUESTRAS ; i++ ) {
                            if (tabla_salida[i] > VALOR_MEDIO_DAC){
                                tabla_salida[i]= (uint16_t) ((AMPLITUD * (tabla_tria[i] - VALOR_MEDIO_DAC)) + VALOR_MEDIO_DAC) << 6;
                            } else {
                                tabla_salida[i]= (uint16_t) ((AMPLITUD * (VALOR_MEDIO_DAC - tabla_tria[i])) + VALOR_MEDIO_DAC) << 6;
                            }
                        }
                    }
                    if (conf.mode == BARRIDO_LINEAL){
                        for ( i = 0 ; i < NUMERO_MUESTRAS ; i++ ) {
                            tabla_salida[i]= (uint16_t) (AMPLITUD * tabla_sier[i]) << 6;
                        }
                    }
                }

        if(conf.set != DACset){
            DACset = conf.set;
            if(DACset){
                if (conf.mode == BARRIDO_CICLICO){
                    Board_LED_Set(0, true);
                    SG_OK = Chip_GPDMA_SGTransfer (LPC_GPDMA , CanalDAC ,&DMA_LLI_buffer , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
                }
                if (conf.mode == BARRIDO_LINEAL) {
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
                xQueueSendToBack(qADCsend, &msjUSB, 10);

                if (debugging == ENABLED)
                    DEBUGOUT("ADC: ADC Send\n");

                // Se recibe la config para saber si se debera
                // seguir midiendo o terminar
                xQueueReceive(qADC,&conf,( portTickType ) 0);
            }
            if (debugging == ENABLED)
                DEBUGOUT("ADC: Deshabilita medicion ADC\n");
            Chip_ADC_SetBurstCmd(LPC_ADC, DISABLE);
        }else{
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

    ADCSemMtx = xSemaphoreCreateMutex();
    DACSemMtx = xSemaphoreCreateMutex();

    vSemaphoreCreateBinary(sBufferADC);
    xSemaphoreTake(sBufferADC, ( portTickType ) 10 );

    qUSBin = xQueueCreate( TAMANIO_MAX_COLA, sizeof( uint8_t )* LARGO_MENSAJE);
    qUSBout = xQueueCreate( TAMANIO_MAX_COLA, sizeof( uint8_t ) * LARGO_MENSAJE);
    qDAC = xQueueCreate( 1, sizeof( struct DACmsj ));
    qADC = xQueueCreate( 1, sizeof( struct ADCmsj ));
    qADCcorriente = xQueueCreate(ADC_N_COLA, sizeof( uint16_t ));
    qADCtension = xQueueCreate(ADC_N_COLA, sizeof( uint16_t ));
    qADCsend = xQueueCreate(1, sizeof( struct USBmsj ) * ADC_N_COLA);

    prvSetupHardware();

    xTaskCreate(vInicializarUSB, (signed char *) "InicializarUSB",
                        configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 3UL),
                        (xTaskHandle *) NULL);

    /* USB  */
    xTaskCreate(vUSBTask, (signed char *) "vUSBTask",
                configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2UL),
                (xTaskHandle *) NULL);

    /* DAC  */
    xTaskCreate(vDACTask, (signed char *) "vDACTask",
                configMINIMAL_STACK_SIZE * 5, NULL, (tskIDLE_PRIORITY + 1UL),
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
