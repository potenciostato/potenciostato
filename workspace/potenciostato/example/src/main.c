/*
 * Potenciostato
 * Proyecto Final
 * UTN Facultad Regional Avellaneda
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
#include <setup.h>

/*****************************************************************************
 * Variables Globales
 ****************************************************************************/

//Para habilitar (o no) imprimir por consola
//bool debugging = ENABLED;
bool debugging = DISABLED;

extern ADC_CLOCK_SETUP_T ADCSetup;

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
  uint8_t mode;
  uint16_t v_pto1;
  uint16_t v_pto2;
  uint16_t v_pto3;
  uint16_t v_retencion;
  uint8_t velocidad;
  uint8_t s_retencion;
  uint8_t ncic;
};

struct ADCmsj {
  bool set;
  uint8_t velocidad;
};

struct USBmsj {
    uint16_t corriente;
    uint16_t tension;
};

uint8_t midiendo=false;

// OBJETOS FreeRTOS
xSemaphoreHandle sDACready, sADCready, sDACstart, sADCstart, sADCdelay, sDACdelay;
xQueueHandle qUSBin, qUSBout, qADC, qDAC, qADCmedicion, qADCsend;

static void vDACTask(struct DACmsj *pvParameters);
static void vADCTask(struct ADCmsj *pvParameters);

/*****************************************************************************
 * Declaración de funciones
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
 * */
static void vUSBTask(void *pvParameters) {

    uint8_t lecturaQT[LARGO_MENSAJE_SALIDA] = {0};
    uint8_t ganancia_corriente = GAN_CORRIENTE_X1;

    int error, retry_cnt = 0;
    struct DACmsj conf_dac = {false, BARRIDO_CICLICO}; //estado del modulo, modo Cíclico
    struct ADCmsj conf_adc = {false, 100}; //estado del modulo, velocidad[mV/s]

    xTaskHandle xADCTask, xDACTask;

    NVIC_DisableIRQ(USB_IRQn);
    NVIC_SetPriority(USB_IRQn, 1);
    NVIC_EnableIRQ(USB_IRQn);

    while (1) {
        if (debugging == ENABLED)
            DEBUGOUT("USB: Se va a leer qUSBout\n");

        // Se lee la cola, si no se recibe nada la tarea se quedará esperando
        xQueueReceive( qUSBout, &lecturaQT, portMAX_DELAY);

        if (debugging == ENABLED)
            DEBUGOUT("USB: Se obtuvo OPcode: %x\n",lecturaQT[0]);

        // Si se supera el numero maximo de reintentos de medicion se aborta
        if(lecturaQT[0] != OC_RETRYMEASUREMENT && retry_cnt >= REINTENTOS_MAX)
        	lecturaQT[0] = OC_ABORTMEASUREMENT;

        switch(lecturaQT[0])
        {
            case OC_INITMEASUREMENTCYCLICAL:
            case OC_RETRYMEASUREMENT:

            	// Se reinician las colas de control de ADC Y DAC
        		xQueueReset( qADC );
        		xQueueReset( qDAC );

        		// Se configura ADC y DAC, si es un reintento se saltea
                if(lecturaQT[0] != OC_RETRYMEASUREMENT){
                	if (debugging == ENABLED)
						DEBUGOUT("USB: Configuro DAC & ADC\n");

					conf_dac.set = true;
					conf_dac.mode = (uint8_t) (lecturaQT[0] & 0xFF);

					conf_dac.v_pto1 = (uint16_t) (((lecturaQT[2] & 0xFF) << 6) | ((lecturaQT[3] & 0xFC) >> 2));
					conf_dac.v_pto2 = (uint16_t) (((lecturaQT[3] & 0x03) << 12) | ((lecturaQT[4] & 0xFF) << 4) | ((lecturaQT[5] & 0xF0) >> 4));
					conf_dac.v_pto3 = (uint16_t) (((lecturaQT[5] & 0x0F) << 10) | ((lecturaQT[6] & 0xFF) << 2) | ((lecturaQT[7] & 0xC0) >> 6));
					conf_dac.v_retencion = (uint16_t) (((lecturaQT[7] & 0x3F) << 8) | (lecturaQT[8] & 0xFF));
					conf_dac.velocidad = (uint8_t) (lecturaQT[9] & 0xFF);
					conf_dac.s_retencion = (uint8_t) (lecturaQT[10] & 0xFF);
					conf_dac.ncic = (uint8_t) (lecturaQT[11] & 0xFF);

					conf_adc.set = true;
					conf_adc.velocidad = conf_dac.velocidad;

					// Se configura la ganancia en funcion a lo recibido desde la PC
					ganancia_corriente = (uint8_t) (lecturaQT[12] & 0xFF);
					switch (ganancia_corriente){
						case GAN_CORRIENTE_X10:
							Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(0));
							Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(6));
							Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(7));
							Chip_GPIO_SetPinOutHigh(LPC_GPIO, PUERTO(0), PIN(8));
							break;
						case GAN_CORRIENTE_X5:
							Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(0));
							Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(6));
							Chip_GPIO_SetPinOutHigh(LPC_GPIO, PUERTO(0), PIN(7));
							Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(8));
							break;
						case GAN_CORRIENTE_X2:
							Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(0));
							Chip_GPIO_SetPinOutHigh(LPC_GPIO, PUERTO(0), PIN(6));
							Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(7));
							Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(8));
							break;
						case GAN_CORRIENTE_X1:
						default:
							Chip_GPIO_SetPinOutHigh(LPC_GPIO, PUERTO(0), PIN(0));
							Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(6));
							Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(7));
							Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(8));
							break;
					}
                } else {
                	retry_cnt++;
                }

                 xTaskCreate(vDACTask, (signed char *) "vDACTask",
                            configMINIMAL_STACK_SIZE * 12, &conf_dac, (tskIDLE_PRIORITY + 1UL), &xDACTask);

                 xTaskCreate(vADCTask, (signed char *) "vADCTask",
                            configMINIMAL_STACK_SIZE * 1, &conf_adc, (tskIDLE_PRIORITY + 1UL), &xADCTask);

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
static void vDACTask(struct DACmsj *pvParameters) {
    bool DACset = false, DACfail = false;
    uint16_t i, j, SG_OK = 0;
    uint16_t gen_cant_valores_dac = 1, gen_ms_entrepuntos_subida, gen_ms_entrepuntos_bajada;
    int32_t gen_pto_inicial, gen_pto_picomax, gen_pto_final, gen_pto_retencion;
    int16_t gen_velocidad;
    int32_t gen_dif_subida, gen_dif_bajada;
    uint16_t gen_mul_subida, gen_mul_bajada, gen_inicial_subida, gen_inicial_bajada;
    uint16_t gen_vector_valores_subida[GEN_CANT_MUESTRAS_MAX] = {0}, gen_vector_valores_bajada[GEN_CANT_MUESTRAS_MAX] = {0};
    uint16_t gen_valor_retencion;
    uint8_t flanco;
    uint32_t timerFreq, cuentas;

    uint8_t respuesta_out[LARGO_MENSAJE_SALIDA]={0};

    struct DACmsj conf;

    int error;

    timerFreq = Chip_Clock_GetSystemClockRate()/4;

    // Config DAC DMA
    Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DBLBUF_ENA | DAC_CNT_ENA); // Se habilita el soporte de cuenta.

    conf = *pvParameters;

	if (debugging == ENABLED)
		DEBUGOUT("DAC: Conf recibida \nSet:%d, v_pto1:%d, v_pto2:%d, v_pto3:%d, v_retencion:%d, velocidad:%d, s_retencion:%d, Ncic:%d\n",conf.set,conf.v_pto1,conf.v_pto2,conf.v_pto3,conf.v_retencion,conf.velocidad,conf.s_retencion,conf.ncic);

	if (conf.velocidad == 0){
		DEBUGOUT("DAC: Velocidad incorrecta, no puede valer 0\n");
	}

	// Se genera la señal a transferir por el DAC
	gen_pto_inicial = (int32_t) (conf.v_pto1 - GEN_PTO_MEDIO); //mV
	gen_pto_picomax = (int32_t) (conf.v_pto2 - GEN_PTO_MEDIO); //mV
	gen_pto_final = (int32_t) (conf.v_pto3 - GEN_PTO_MEDIO); //mV
	gen_pto_retencion = (int32_t) (conf.v_retencion - GEN_PTO_MEDIO); //mV

	gen_velocidad = (int16_t) (conf.velocidad);

	// se calcula la potencia
	for (i = 0; i < GEN_CANT_BITS_DAC; i++){
		gen_cant_valores_dac *= 2;
	}
	gen_cant_valores_dac -= 1;

	// se le quita el signo a la diferencia para calcular ms entre puntos en flanco de "subida"
	if (gen_pto_picomax > gen_pto_inicial){
		gen_dif_subida = (uint16_t) (gen_pto_picomax - gen_pto_inicial);
	}
	else{
		gen_dif_subida = (uint16_t) (- gen_pto_picomax + gen_pto_inicial);
	}

	// se le quita el signo a la diferencia para calcular ms entre puntos en flanco de "bajada"
	if (gen_pto_picomax > gen_pto_final){
		gen_dif_bajada = (uint16_t) (gen_pto_picomax - gen_pto_final);
	}
	else{
		gen_dif_bajada = (uint16_t) (- gen_pto_picomax + gen_pto_final);
	}

	// se obtiene el vector de valores del primer flanco ya escalado para mV (con la ganancia tenida en cuenta)
	for (i = 0; i < GEN_CANT_MUESTRAS_MAX; i++){
		gen_mul_subida = i;
		gen_inicial_subida = 512 + ((gen_pto_inicial*1023) / (2*GEN_PTO_MEDIO));

		gen_vector_valores_subida[i] = (uint16_t) (gen_inicial_subida+
				((((gen_pto_picomax - gen_pto_inicial)*gen_mul_subida+GEN_PTO_MEDIO)*gen_cant_valores_dac)/(2*GEN_PTO_MEDIO)/GEN_CANT_MUESTRAS_MAX));
	}

	// se obtiene el vector de valores del segundo flanco ya escalado para mV (con la ganancia tenida en cuenta)
	for (i = 0; i < GEN_CANT_MUESTRAS_MAX; i++){
		gen_mul_bajada = i;
		gen_inicial_bajada = gen_vector_valores_subida[GEN_CANT_MUESTRAS_MAX-1];
		gen_vector_valores_bajada[i] = (uint16_t) (gen_inicial_bajada+
				((((gen_pto_final - gen_pto_picomax)*gen_mul_bajada+GEN_PTO_MEDIO)*gen_cant_valores_dac)/(2*GEN_PTO_MEDIO)/GEN_CANT_MUESTRAS_MAX));
	}

	// se obtiene el valor digital (10 bits) de la tensión de retención
	gen_valor_retencion = (((gen_pto_retencion+GEN_PTO_MEDIO)*gen_cant_valores_dac)/(2*GEN_PTO_MEDIO));

	// se calculan los milisegundos que deberan trascurrir entre puntos para cada flanco
	/*
	 * Amplitud subida/bajada en tensión [mV] * 1000 [mSeg]
	 * --------------------------------------------------------------- = [mSeg/muestra]
	 * Cant Max muestras [muestra] * velocidad [mV/Seg] * 1000 [mSeg]
	 */
	gen_ms_entrepuntos_subida = (uint16_t) ((gen_dif_subida*1000)
			/ (GEN_CANT_MUESTRAS_MAX * gen_velocidad));
	gen_ms_entrepuntos_bajada = (uint16_t) ((gen_dif_bajada*1000)
			/ (GEN_CANT_MUESTRAS_MAX * gen_velocidad));

	// Se da comienzo al período de retención
	cuentas = (timerFreq)*conf.s_retencion;
	if(cuentas <= 0) cuentas = 1;
	Chip_TIMER_Reset(LPC_TIMER1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER1, 1);
	Chip_TIMER_SetMatch(LPC_TIMER1, 1, cuentas);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER1, 1);
	if (conf.mode == BARRIDO_CICLICO) {
		if(conf.s_retencion > 0){
			if (conf.ncic == 0) conf.ncic = 255;
			xSemaphoreGive(sDACready);
			xSemaphoreTake(sDACstart, ( portTickType ) TAKE_TIMEOUT);

			Chip_DAC_UpdateValue(LPC_DAC, gen_valor_retencion);

			// Delay por timer
			xSemaphoreTake(sDACdelay, ( portTickType ) TAKE_TIMEOUT); // parche para empezar a contar a partir de aca los conf.s_retencion segundos
			NVIC_ClearPendingIRQ(TIMER1_IRQn);
			NVIC_EnableIRQ(TIMER1_IRQn);
			xQueueReceive(qDAC, &conf, 0);
			if(conf.set == false){
				// finaliza la tarea
				Chip_DAC_UpdateValue(LPC_DAC, gen_valor_retencion);

				if (debugging == ENABLED)
					DEBUGOUT("DAC: Deshabilitado\n");

				vTaskDelete(NULL);
			}
			xSemaphoreTake(sDACdelay, ( portTickType ) portMAX_DELAY);
		}
	}

	// Se da comienzo a la inyección de los flancos de la señal
	cuentas = (timerFreq/1000)*gen_ms_entrepuntos_subida;
	if(cuentas <= 0) cuentas = 1;
	Chip_TIMER_Reset(LPC_TIMER1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER1, 1);
	Chip_TIMER_SetMatch(LPC_TIMER1, 1, cuentas);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER1, 1);

	DACset = conf.set;

	if (conf.mode == BARRIDO_CICLICO) {
		if(conf.velocidad > 0){
			if (conf.ncic == 0) conf.ncic = 255;
			xSemaphoreGive(sDACready);
			xSemaphoreTake(sDACstart, ( portTickType ) TAKE_TIMEOUT);
			for(i=0;i<conf.ncic;i++) {
				for(flanco = PRIMER_FLANCO; flanco <= SEGUNDO_FLANCO; flanco++){
					if (flanco == SEGUNDO_FLANCO){
						cuentas = (timerFreq/1000)*gen_ms_entrepuntos_bajada;
						if(cuentas <= 0) cuentas = 1;
						Chip_TIMER_Reset(LPC_TIMER1);
						Chip_TIMER_MatchEnableInt(LPC_TIMER1, 1);
						Chip_TIMER_SetMatch(LPC_TIMER1, 1, cuentas);
						Chip_TIMER_ResetOnMatchEnable(LPC_TIMER1, 1);
					}
					for(j=0;j<GEN_CANT_MUESTRAS_MAX;j++){
					if (flanco == PRIMER_FLANCO)
						Chip_DAC_UpdateValue(LPC_DAC, gen_vector_valores_subida[j]);
					if (flanco == SEGUNDO_FLANCO)
						Chip_DAC_UpdateValue(LPC_DAC, gen_vector_valores_bajada[j]);

					// Delay por timer
					NVIC_ClearPendingIRQ(TIMER1_IRQn);
					NVIC_EnableIRQ(TIMER1_IRQn);
					xQueueReceive(qDAC, &conf, 0);
					if(conf.set == false){
						// Finaliza la tarea
						Chip_DAC_UpdateValue(LPC_DAC, gen_valor_retencion);

						if (debugging == ENABLED)
							DEBUGOUT("DAC: Deshabilitado\n");
						midiendo = false;

						NVIC_DisableIRQ(TIMER1_IRQn);
						NVIC_ClearPendingIRQ(TIMER1_IRQn);
						xSemaphoreTake(sDACdelay, ( portTickType ) TAKE_TIMEOUT);
						vTaskDelete(NULL);
					}
					xSemaphoreTake(sDACdelay, ( portTickType ) TAKE_TIMEOUT);
					}
				}
			}
		}
		//Se envía el término de medición a Tarea USB
		if (debugging == ENABLED)
			DEBUGOUT("DAC: ABORT\n");

		midiendo = false;

		// Si algo falla se reintenta TODO: no implementado todavia
		if(DACfail)
			respuesta_out[0] = OC_RETRYMEASUREMENT;
		else
			respuesta_out[0] = OC_ABORTMEASUREMENT;

		for (i = 1; i < LARGO_MENSAJE_SALIDA; i ++){
			respuesta_out[i] = 0x0;
		}
		error = xQueueSendToBack(qUSBout,&respuesta_out,TAKE_TIMEOUT);
	}

	Chip_DAC_UpdateValue(LPC_DAC, gen_valor_retencion);

	if (debugging == ENABLED)
		DEBUGOUT("DAC: Deshabilitado\n");
	midiendo = false;

	// Finaliza la tarea
	NVIC_DisableIRQ(TIMER1_IRQn);
	NVIC_ClearPendingIRQ(TIMER1_IRQn);
	xSemaphoreTake(sDACdelay, ( portTickType ) TAKE_TIMEOUT);
	vTaskDelete(NULL);
}


static void vADCTask(struct ADCmsj *pvParameters) {
    uint8_t respuesta_in[LARGO_MENSAJE_ENTRADA]={0};
    uint32_t timerFreq, cuentas, error, datos_ok, i;
    struct ADCmsj conf;
    struct USBmsj msjUSB;
    uint32_t n_mensajes;

	timerFreq = Chip_Clock_GetSystemClockRate()/4;
	NVIC_SetPriority(ADC_IRQn, 5);
	NVIC_SetPriority(TIMER0_IRQn, 4);

    conf = *pvParameters;

	if (debugging == ENABLED)
		DEBUGOUT("ADC: Conf recibida Set:%d,Velocidad:%d\n",conf.set,conf.velocidad);

	// TODO: escalar esto al mejor valor posible en funcion de la velocidad (8 bits)
	if(conf.velocidad < 1000){
		cuentas = ((timerFreq*10) / (conf.velocidad*PUNTOS_GRAFICA))*100;
	} else {
		cuentas = timerFreq / ((conf.velocidad/1000)*PUNTOS_GRAFICA);
	}
	if(cuentas <= 0) cuentas = 1;
	Chip_TIMER_Reset(LPC_TIMER0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER0, 1);
	Chip_TIMER_SetMatch(LPC_TIMER0, 1, cuentas);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0, 1);

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

		// TODO: Revisar comportamiento y ajustar
		if(conf.velocidad<FRECUENCIA_BAJA){
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
	// TODO: Corroborar utilidad actual
	if(conf.velocidad>=FRECUENCIA_BAJA){
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
	NVIC_DisableIRQ(TIMER0_IRQn);
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	xSemaphoreTake(sADCdelay, ( portTickType ) TAKE_TIMEOUT);
	vTaskDelete(NULL);
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
    Board_LED_Set(0, false);
    if (debugging == ENABLED)
        DEBUGOUT("Potenciostato UTN FRA\r\n");

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

    /* DAC
    xTaskCreate(vDACTask, (signed char *) "vDACTask",
                configMINIMAL_STACK_SIZE * 5, NULL, (tskIDLE_PRIORITY + 1UL),
                (xTaskHandle *) NULL);

    /* ADC
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
