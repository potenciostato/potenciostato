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

xSemaphoreHandle sDACncic, sDACready, sADCready, sDACstart, sADCstart, sADCdelay, sDACdelay;
xQueueHandle qUSBin, qUSBout, qADC, qDAC, qADCmedicion, qADCsend;

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
    struct USBmsj medicion;
    int error;
    static signed portBASE_TYPE xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    NVIC_DisableIRQ(ADC_IRQn);
    Board_LED_Toggle(0);
    if (Chip_ADC_ReadStatus(LPC_ADC,CANAL_CORRIENTE,ADC_DR_ADINT_STAT) && Chip_ADC_ReadStatus(LPC_ADC,CANAL_TENSION,ADC_DR_ADINT_STAT)){
        Chip_ADC_ReadValue(LPC_ADC, CANAL_CORRIENTE, &dataADC);
        medicion.corriente = ADC_DR_RESULT(dataADC);
    	Chip_ADC_ReadValue(LPC_ADC, CANAL_TENSION, &dataADC);
    	medicion.tension = ADC_DR_RESULT(dataADC);
        error = xQueueSendToBackFromISR( qADCmedicion, &medicion, &xHigherPriorityTaskWoken );
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

void TIMER0_IRQHandler(void)
{
	static signed portBASE_TYPE xHigherPriorityTaskWoken;
	NVIC_DisableIRQ(TIMER0_IRQn);
	if (Chip_TIMER_MatchPending(LPC_TIMER0, 1)) {
		Chip_TIMER_ClearMatch(LPC_TIMER0, 1);
		xSemaphoreGiveFromISR(sADCdelay, &xHigherPriorityTaskWoken);
	}
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void TIMER1_IRQHandler(void)
{
	static signed portBASE_TYPE xHigherPriorityTaskWoken;
	NVIC_DisableIRQ(TIMER1_IRQn);
	if (Chip_TIMER_MatchPending(LPC_TIMER1, 1)) {
		Chip_TIMER_ClearMatch(LPC_TIMER1, 1);
		xSemaphoreGiveFromISR(sDACdelay, &xHigherPriorityTaskWoken);
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

    uint8_t lecturaQT[LARGO_MENSAJE_ENTRADA]={0};
    int i, error;
    struct DACmsj conf_dac = {false, BARRIDO_CICLICO, 1000, 255}; //estado del modulo, frecuencia[Hz], amplitud[V]
    struct ADCmsj conf_adc = {false,ADC_SAMPL_FREC}; //estado del modulo, frecuencia[Hz]

    int countADCsend, countUSBin, countUSBout, DAC_ready, ADC_ready;


    NVIC_SetPriority(USB_IRQn, 1);

    while (1) {
        if (debugging == ENABLED)
            DEBUGOUT("USB: Se va a leer qUSBout\n");

        // Se lee la cola, si no se recibe nada la tarea se quedará esperando
        xQueueReceive( qUSBout, &lecturaQT, portMAX_DELAY);

        if (debugging == ENABLED)
            DEBUGOUT("USB: Se obtuvo OPcode: %x\n",lecturaQT[0]);

        switch(lecturaQT[0])
        {
            case OC_INITMEASUREMENTLINEAL:
            case OC_INITMEASUREMENTCYCLICAL:

                if (debugging == ENABLED)
                    DEBUGOUT("USB: Configuro DAC & ADC\n");

                conf_dac.set = true;
                conf_dac.mode = lecturaQT[0];
                conf_dac.frec =(lecturaQT[3]<<16) | (lecturaQT[4]<<8) | lecturaQT[5]; //me parece debería ir un OR | (había un +)
                conf_dac.amp = lecturaQT[2];
                conf_dac.ncic = lecturaQT[6];

                conf_adc.set = true;
                conf_adc.frec = conf_dac.frec;

                // Envia la configuracion a las tareas y estado de medicion
                error = xQueueSendToBack(qDAC,&conf_dac,0);
                error = xQueueSendToBack(qADC,&conf_adc,0);

                // Espera a que ambas tareas esten listas para la medicion
                xSemaphoreTake(sDACready, ( portTickType ) TAKE_TIMEOUT);
                xSemaphoreTake(sADCready, ( portTickType ) TAKE_TIMEOUT);

                if (debugging == ENABLED)
                     DEBUGOUT("USB: Habilito DAC & ADC\n");

                // Inicio de la medicion
                xSemaphoreGive(sADCstart);
                xSemaphoreGive(sDACstart);

                break;

            case OC_ABORTMEASUREMENT:

                // Deshabilito int del DAC & ADC
                if (debugging == ENABLED)
                    DEBUGOUT("USB: Deshabilito DAC & ADC\n");

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
                xQueueReset( qADCmedicion );
                xQueueReset( qUSBin );
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
    uint16_t i, j, SG_OK = 0;
    uint16_t tabla_salida[ NUMERO_MUESTRAS ];
    uint16_t AMPLITUD = 0, AMPLITUD_DIV = 255, MODO = 2;
    uint32_t FREC = 0;
    uint32_t CLOCK_DAC_HZ, timerFreq, timeoutDMA, cuentas;

    uint8_t respuesta_out[LARGO_MENSAJE_SALIDA]={0};

    struct DACmsj conf;

    int error;

    timerFreq = Chip_Clock_GetSystemClockRate()/4;

    // Config DAC DMA
    CLOCK_DAC_HZ = Chip_Clock_GetSystemClockRate()/8;
    Chip_GPDMA_Init ( LPC_GPDMA );
    NVIC_EnableIRQ(DMA_IRQn);
    NVIC_SetPriority(DMA_IRQn, 3);

    while(1) {

        // Anular salida DAC
        Chip_DAC_UpdateValue(LPC_DAC, 512);

        //se lee la cola, si no se recibe nada la tarea se quedará esperando
        xQueueReceive(qDAC,&conf,portMAX_DELAY);

        if (debugging == ENABLED)
            DEBUGOUT("DAC: Conf recibida Set:%d,Frec:%d,Ncic:%d,Amp:%d\n",conf.set,conf.frec,conf.ncic,conf.amp);

        if(conf.frec != FREC){
            FREC = conf.frec; //este valor esta multiplicado por 1000 desde el Qt
            if (FREC == 0){
            	DEBUGOUT("DAC: Frecuencia incorrecta, no puede valer 0\n");
            }
            if (FREC <= FRECUENCIA_MUY_BAJA){
            	cuentas = ((timerFreq*100) / (FREC*NUMERO_MUESTRAS))*10;
    			if(cuentas <= 0) cuentas = 1;
    			Chip_TIMER_Reset(LPC_TIMER1);
    			Chip_TIMER_MatchEnableInt(LPC_TIMER1, 1);
    			Chip_TIMER_SetMatch(LPC_TIMER1, 1, cuentas);
    			Chip_TIMER_ResetOnMatchEnable(LPC_TIMER1, 1);
            }
            if (FREC > FRECUENCIA_MUY_BAJA && FREC <= 10*1000){
            	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_DAC, SYSCTL_CLKDIV_8);
                CLOCK_DAC_HZ = Chip_Clock_GetSystemClockRate()/8;
                timeoutDMA = ((((CLOCK_DAC_HZ * 100) / FREC) * 10) / NUMERO_MUESTRAS );
            }
            if (FREC > 10*1000 && FREC <= 200*1000){
            	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_DAC, SYSCTL_CLKDIV_4);
                CLOCK_DAC_HZ = Chip_Clock_GetSystemClockRate()/4;
                timeoutDMA = ((((CLOCK_DAC_HZ * 100) / FREC) * 10) / NUMERO_MUESTRAS );
            }
            if (FREC > 200*1000 && FREC <= 1000*1000){
            	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_DAC, SYSCTL_CLKDIV_2);
                CLOCK_DAC_HZ = Chip_Clock_GetSystemClockRate()/2;
                timeoutDMA = (((((CLOCK_DAC_HZ * 10) / FREC) * 10) / NUMERO_MUESTRAS ) * 10);
            }
            if (FREC > 1000*1000){
            	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_DAC, SYSCTL_CLKDIV_1);
                CLOCK_DAC_HZ = Chip_Clock_GetSystemClockRate()/1;
                timeoutDMA = (((((CLOCK_DAC_HZ * 10) / FREC) * 10) / NUMERO_MUESTRAS ) * 10);
            }

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
					tabla_salida[i]= (uint16_t) ((AMPLITUD * (tabla_tria500[i] - VALOR_MEDIO_DAC))/AMPLITUD_DIV + VALOR_MEDIO_DAC) << 6;
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
            	CanalDAC = Chip_GPDMA_GetFreeChannel ( LPC_GPDMA , 0 );
                if (conf.mode == BARRIDO_CICLICO) {
                	if(conf.set < FRECUENCIA_MUY_BAJA){
                        for(i=0;i<conf.ncic;i++) {
                        	for(j=0;j<NUMERO_MUESTRAS;j++){
                        		Chip_DAC_UpdateValue(LPC_DAC, tabla_salida[j] >> 6);

                                // Delay por timer
                            	NVIC_ClearPendingIRQ(TIMER1_IRQn);
                            	NVIC_EnableIRQ(TIMER1_IRQn);
                            	xSemaphoreTake(sDACdelay, ( portTickType ) TAKE_TIMEOUT);
                        	}
                    	}
                	} else {
						if (conf.ncic == 0){
							Chip_GPDMA_PrepareDescriptor ( LPC_GPDMA , &DMA_LLI_buffer  , (uint32_t) tabla_salida ,
															 GPDMA_CONN_DAC , DMA_SIZE , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA , &DMA_LLI_buffer);
							xSemaphoreGive(sDACready);
							xSemaphoreTake(sDACstart, ( portTickType ) TAKE_TIMEOUT);
							if (debugging == ENABLED)
								DEBUGOUT("DAC: Iniciando señal triangular infinita\n");
							SG_OK = Chip_GPDMA_SGTransfer (LPC_GPDMA , CanalDAC ,&DMA_LLI_buffer , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
							Board_LED_Set(0,false);
						} else {
							Chip_GPDMA_PrepareDescriptor ( LPC_GPDMA , &DMA_LLI_buffer  , (uint32_t) tabla_salida ,
																GPDMA_CONN_DAC , DMA_SIZE , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA , 0);
							xSemaphoreGive(sDACready);
							xSemaphoreTake(sDACstart, ( portTickType ) TAKE_TIMEOUT);
							if (debugging == ENABLED)
								DEBUGOUT("DAC: Iniciando señal triangular de %d ciclos\n", conf.ncic);
							for(i=0;i<conf.ncic;i++) {
								SG_OK = Chip_GPDMA_SGTransfer (LPC_GPDMA , CanalDAC ,&DMA_LLI_buffer , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
								error = xSemaphoreTake(sDACncic, ( portTickType ) (500000/FREC + 1000));
								if(error == pdFALSE){
									// reseteo las variables debido a error
									MODO = 2;
									AMPLITUD = 0;
									FREC = 0;
									break;
								}
							}
						}
					}
					//Se envía el término de medición a Tarea USB

					if (debugging == ENABLED)
						DEBUGOUT("DAC: ABORT\n");

					midiendo = false;

					respuesta_out[0] = OC_ABORTMEASUREMENT;
					for (i = 1; i < LARGO_MENSAJE_SALIDA; i ++){
						respuesta_out[i] = 0x0;
					}
					error = xQueueSendToBack(qUSBout,&respuesta_out,TAKE_TIMEOUT);
            	}
                if (conf.mode == BARRIDO_LINEAL) {
                	xSemaphoreGive(sDACready);
                	xSemaphoreTake(sDACstart, ( portTickType ) TAKE_TIMEOUT);
                    if (debugging == ENABLED)
                        DEBUGOUT("DAC: Iniciando señal lineal\n");
                    SG_OK = Chip_GPDMA_SGTransfer (LPC_GPDMA , CanalDAC ,&DMA_NLI_buffer , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
                    midiendo = false;
                }
            } else {
                Chip_GPDMA_Stop(LPC_GPDMA, CanalDAC);
                if (debugging == ENABLED)
                    DEBUGOUT("DAC: Deshabilitado\n");
                midiendo = false;
            }
        }
    }
}


static void vADCTask(void *pvParameters) {

    uint8_t respuesta_in[LARGO_MENSAJE_ENTRADA]={0};
    uint32_t FREC, timerFreq, cuentas, error, datos_ok, i;
    struct ADCmsj conf;
    struct USBmsj msjUSB;
    unsigned portBASE_TYPE n_mensajes;

	timerFreq = Chip_Clock_GetSystemClockRate()/4;
	NVIC_SetPriority(ADC_IRQn, 5);
	NVIC_SetPriority(TIMER0_IRQn, 4);

    while(1) {

        // Se lee la cola, si no se recibe nada la tarea se quedará esperando
        xQueueReceive(qADC,&conf,portMAX_DELAY);
        if (debugging == ENABLED)
        	DEBUGOUT("ADC: Conf recibida Set:%d,Frec:%d\n",conf.set,conf.frec);

        if(conf.frec != FREC){
        	FREC = conf.frec;
        	if(FREC < 1000){
        		cuentas = ((timerFreq*10) / (FREC*PUNTOS_GRAFICA))*100;
        	} else {
        		cuentas = timerFreq / ((FREC/1000)*PUNTOS_GRAFICA);
        	}
            if(cuentas <= 0) cuentas = 1;
        	Chip_TIMER_Reset(LPC_TIMER0);
        	Chip_TIMER_MatchEnableInt(LPC_TIMER0, 1);
        	Chip_TIMER_SetMatch(LPC_TIMER0, 1, cuentas);
        	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0, 1);
        }
        if (conf.set == true){

            xQueueReset( qADCsend );
            xQueueReset( qADCmedicion );
        	Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE);
            if (debugging == ENABLED)
                DEBUGOUT("ADC: Iniciando medición\n");
            i = 0;

            xSemaphoreGive(sADCready);
            xSemaphoreTake(sADCstart, ( portTickType ) TAKE_TIMEOUT);
            midiendo = true;
            while (conf.set && midiendo){

            	if(FREC<FRECUENCIA_BAJA){
            		NVIC_EnableIRQ(ADC_IRQn);
            		error = xQueueReceive(qADCmedicion,&msjUSB,10);
                    if (error == pdFAIL){
                    	continue;
                    }

            		error = xQueueSendToBack(qADCsend, &msjUSB, 0);

                    if (debugging == ENABLED)
                        DEBUGOUT("ADC: ADC Send\n");

                    // Se recibe la config para saber si se debera seguir midiendo o terminar
                    xQueueReceive(qADC,&conf,0);

                    // Delay por timer
                	NVIC_ClearPendingIRQ(TIMER0_IRQn);
                	NVIC_EnableIRQ(TIMER0_IRQn);
                	xSemaphoreTake(sADCdelay, ( portTickType ) TAKE_TIMEOUT);
            	} else {

            		NVIC_EnableIRQ(ADC_IRQn);
            		// Se encuesta la cola cada 50 mediciones

                    // Delay por timer
                	NVIC_ClearPendingIRQ(TIMER0_IRQn);
                	NVIC_EnableIRQ(TIMER0_IRQn);
                	xSemaphoreTake(sADCdelay, ( portTickType ) TAKE_TIMEOUT);
                	i++;
            		if(i>=PUNTOS_GRAFICA){
                    	xQueueReceive(qADC,&conf,10);
                    	i=0;
                    }
            	}
            }
            if (debugging == ENABLED)
                DEBUGOUT("ADC: Deshabilita medicion ADC\n");
            Chip_ADC_SetBurstCmd(LPC_ADC, DISABLE);
            if(FREC>=FRECUENCIA_BAJA){
            	datos_ok = 1;
            	n_mensajes = uxQueueMessagesWaiting(qADCmedicion);
            	while(datos_ok){
            		datos_ok = xQueueReceive(qADCmedicion,&msjUSB, 1);
                    error = xQueueSendToBack(qADCsend, &msjUSB, 0);
            	}
            }
            // Se da aviso de fin de lectura de datos
			if (debugging == ENABLED)
				DEBUGOUT("ADC: CYCLE END\n");

			respuesta_in[0] = OC_CYCLEEND;
			for (i = 1; i < LARGO_MENSAJE_ENTRADA; i ++){
				respuesta_in[i] = 0x0;
			}
			error = xQueueSendToBack(qUSBin,&respuesta_in,TAKE_TIMEOUT);
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
    vSemaphoreCreateBinary(sADCdelay);
    xSemaphoreTake(sADCdelay, ( portTickType ) 10 );
    vSemaphoreCreateBinary(sDACdelay);
    xSemaphoreTake(sDACdelay, ( portTickType ) 10 );

    qUSBin = xQueueCreate( TAMANIO_MAX_COLA_USB, sizeof( uint8_t )* LARGO_MENSAJE_ENTRADA);
    qUSBout = xQueueCreate( TAMANIO_MAX_COLA_USB, sizeof( uint8_t ) * LARGO_MENSAJE_SALIDA);
    qDAC = xQueueCreate( 1, sizeof( struct DACmsj ));
    qADC = xQueueCreate( 1, sizeof( struct ADCmsj ));
    qADCmedicion = xQueueCreate(PUNTOS_GRAFICA*2, sizeof( struct USBmsj ));
    qADCsend = xQueueCreate(TAMANIO_MAX_COLA_ADC, sizeof( struct USBmsj ) * ADC_N_COLA);

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
                configMINIMAL_STACK_SIZE * 1, NULL, (tskIDLE_PRIORITY + 1UL),
                (xTaskHandle *) NULL);

    /* Empieza el Scheduler */
    vTaskStartScheduler();

    /* Nunca deberá llegar hasta acá */
    return 1;
}

/**
 * @}
 */
