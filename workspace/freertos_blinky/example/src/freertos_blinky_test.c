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
#define InitMeasure "001"
#define AbortMeasure "002"
#define ACK "099"
#define SendData "0030"
#define SendDataEnd "0031"

char QTFlagSTR[] = "000000000000000000", UARTAKTSTR[] = "0000", pruebahernan[]="010";
/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/


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


/* ADC parpadeo cada 1s */
static void vINTSimTask(void *pvParameters) {
	int i;
	int a = 0;

	while (1) {

		DEBUGOUT("INT: Iniciar medicion\n");
		strcpy(QTFlagSTR,"0010050001000010");
		/*
		 * uso strncpy  para quedarme con los primeros 3 caracteres
		 * reconozco la int que llamó a la uart
		 * */
		strncpy (UARTAKTSTR,QTFlagSTR,3);

		DEBUGOUT("INT: QTFlagSTR = %s\n", QTFlagSTR);
		xSemaphoreGive(UARTSemMtx);
		/* Espero 3s*/
		vTaskDelay(3000/portTICK_RATE_MS);

		DEBUGOUT("INT: Abortar medicion\n");
		strcpy(QTFlagSTR,AbortMeasure);
		strncpy (UARTAKTSTR,QTFlagSTR,3);
		DEBUGOUT("INT: QTFlagSTR = %s\n", QTFlagSTR);

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
int ProgState = 0;
char BufferOutSTR[] = "000000000000000000";

	while (1) {
		DEBUGOUT("UART: Voy a tomar semaforos\n");
		/*
		 * La UART funciona cuando la PC interrumpe o
		 * cuando debe enviar datos a la PC*/
		xSemaphoreTake( UARTSemMtx, portMAX_DELAY);


			ProgState = atoi(UARTAKTSTR);
			DEBUGOUT("UART: UARTAKTSTR = %s, ProgState = %d\n",UARTAKTSTR,ProgState);

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
		//le indico a la uart que debe mandar info
		xSemaphoreGive( UARTSemMtx);


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
