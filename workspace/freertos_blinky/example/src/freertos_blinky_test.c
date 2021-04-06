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

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
xSemaphoreHandle UARTSemMtx,UARTSendMtx,DACSemMtx,ADCSemMtx;
xQueueHandle xQTqueue,xACDqueue,xOPCodequeue;
#define InitMeasure "001"
#define AbortMeasurement "002"
#define ACK "099"
#define SendData "0030"
#define SendDataEnd "0031"


<<<<<<< HEAD
char QTFlagSTR[] = "0000000000000000", UARTAKTSTR[] = "0000", pruebahernan[]="080";
=======

char QTFlagSTR[] = "000000000000000000", UARTAKTSTR[] = "0000", pruebahernan[]="080";
>>>>>>> 6e7d665b3afb58734b8e58e82216a25f8d661831

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


/*
* Tarea para simular la INT del QT
* interrumpo a la UART/USB para:
* _comenzar a medir, paso el código de operacion y los valores a usar
* _detener la medición, ppaso el código de operacion
* _pedir datos de la medición, paso el código de operacion*/
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
		 * Envio
		 * 	_código de operación
		 * 	_datos a usar
		 * Para la ISR usar
		 * xQueueSendToBackFromISR( xQTqueue, &USBBuff, pdFALSE );*/
		xQueueSendToBack(xOPCodequeue,&InitMeasure,0);
		xQueueSendToBack(xQTqueue,&USBBuff,0);
		xSemaphoreGive(UARTSemMtx);
		/* Espero 3s*/
		vTaskDelay(3000/portTICK_RATE_MS);

		/*
		 * Envio el código para parar*/
		DEBUGOUT("INT: Abortar medicion\n");
		strcpy(USBBuff,AbortMeasurement);
		xQueueSendToBack(xQTqueue,&AbortMeasurement,0);
		//strncpy (UARTAKTSTR,QTFlagSTR,3);


		xSemaphoreGive(UARTSemMtx);
		/* Espero 1s*/
		vTaskDelay(1000/portTICK_RATE_MS);
	}
}
/* UART
 * Iniciar medición 001
 * Abortar medición 002
 * Enviar datos de en curso 003 xx 0
 * Enviar datos fin 003 xx 1
 * Uso BufferOutSTR para enviarle datos a QT
 * */
static void vUARTTask(void *pvParameters) {
//char ProgState= "0000000000000000";
	int ProgState = 0;
char BufferOutSTR[] = "0000000000000000";


	while (1) {
		DEBUGOUT("UART: Voy a tomar semaforos\n");
		/*
		 * La UART funciona cuando la PC interrumpe o
		 * cuando debe enviar datos a la PC*/
		xSemaphoreTake( UARTSemMtx, portMAX_DELAY);

		xQueueReceive( xOPCodequeue, &BufferOutSTR, 0);
		/*
		 * Me quedo con el código de operación*/
		strncpy (UARTAKTSTR,BufferOutSTR,3);
		ProgState = atoi(UARTAKTSTR);
			switch(ProgState){
			case 10 :
				/*
				 * 1)Habilito int del DAC
				 * 2)Habilito int del ADC
				 * NVIC_EnableIRQ(ADC_IRQn);
				 * ADC_StartCmd(LPC_ADC,ADC_START_NOW);
				 */
				DEBUGOUT("UART: Habilito DAC & ADC\n");
				xSemaphoreGive(DACSemMtx);
				xSemaphoreGive(ADCSemMtx);
				break;

			case 20:
				// Deshabilito int del DAC & ADC
				DEBUGOUT("UART: Deshabilito DAC & ADC\r\n");
				strcpy(BufferOutSTR,ACK);
				DEBUGOUT("UART: ACKAbort = %s\r\n",BufferOutSTR);
				break;

			case 30:
				// Envio datos a PC de manera continua
				DEBUGOUT("UART: Envio datos a PC\r\n");
				//Leo el valor recibido por el adc
				xQueueReceive( xACDqueue, &BufferOutSTR, 0);

				break;

			case 31:
				// Finalizo el envio de datos a la PC
				DEBUGOUT("UART: Finalizo el envio datos a PC\r\n");
				break;

			default:
				DEBUGOUT("UART: Estado invalido\r\n");
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
<<<<<<< HEAD
char ADCBuff[] = "0000000000000666";

=======

	static uint16_t lecturaADC;
	uint32_t timerFreq, duty;
	timerFreq = Chip_Clock_GetSystemClockRate()/4;
	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_EnableIRQ(ADC_IRQn);
	char ADCBuff[] = "000000000000000666";
>>>>>>> 6e7d665b3afb58734b8e58e82216a25f8d661831
	while (1) {

		DEBUGOUT("ADC: Voy a tomar el semaforo\n");
		/*
		 * tomo el semáforo para poder darlo
		 * lo tomo 2 veces así se bloquea hasta que la uart lo habilite
		 * cuando implementemos dma vamos a resolver de otra forma
		 * */
		xSemaphoreTake( ADCSemMtx, portMAX_DELAY );
		DEBUGOUT("ADC: Doy el semaforo de la UART\n");
		strcpy(UARTAKTSTR,SendData);
		/*
		 * Envio
		 * _código de operación
		 * _datos de la medición*/
		xQueueSendToBack(xOPCodequeue,&SendData,0);
		xQueueSendToBack(xACDqueue,&ADCBuff,0);
		//le indico a la uart que debe mandar info
		xSemaphoreGive( UARTSemMtx);

		NVIC_EnableIRQ(ADC_IRQn);
		Chip_ADC_SetStartMode(LPC_ADC,ADC_START_NOW,ADC_TRIGGERMODE_RISING);
		xSemaphoreTake(slectura_ok, ( portTickType ) portMAX_DELAY);
		Chip_ADC_ReadValue(LPC_ADC,ADC_CH0,&lecturaADC);
		duty =(uint32_t)lecturaADC*100/4096;
		Chip_TIMER_SetMatch(LPC_TIMER0, 0, (uint32_t)(timerFreq-(timerFreq*duty)/100)/100);
		xQueueSend( datoADC, ( void * ) &lecturaADC, ( portTickType ) 0 );
		vTaskDelay(configTICK_RATE_HZ / 4);


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

	/* QT */
	xTaskCreate(vINTSimTask, (signed char *) "vINTSimTask",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 3UL),
						(xTaskHandle *) NULL);

	/* UART  */
	xTaskCreate(vUARTTask, (signed char *) "vUARTTask",
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
