/*
 * setup.c
 *
 *  Created on: Nov 29, 2016
 *      Author: axellucas
 */


#include <defines.h>
#include <chip.h>

// Variable necesaria para config ADC
ADC_CLOCK_SETUP_T ADCSetup;

/*****************************************************************************
 * Funcion de Setup Inicial
 ****************************************************************************/
void prvSetupHardware(void)
{
	uint32_t timerfreq;

	SystemCoreClockUpdate();
	Board_Init();
	Chip_GPIO_Init (LPC_GPIO);
	Chip_IOCON_Init(LPC_IOCON);

	timerfreq= Chip_Clock_GetSystemClockRate();

	// Setup ADC
	Chip_ADC_Init(LPC_ADC, &ADCSetup);
	Chip_ADC_EnableChannel(LPC_ADC, CANAL_CORRIENTE, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC, CANAL_TENSION, ENABLE);
	Chip_ADC_SetSampleRate(LPC_ADC,&ADCSetup,ADC_SAMPL_FREC);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC,CANAL_CORRIENTE,ENABLE);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC,CANAL_TENSION,ENABLE);
	Chip_IOCON_PinMux(LPC_IOCON, PUERTO(0), PIN(23), MD_PLN, IOCON_FUNC1); //ADC0
	Chip_IOCON_PinMux(LPC_IOCON, PUERTO(0), PIN(24), MD_PLN, IOCON_FUNC1); //ADC1

	//Chip_ADC_SetBurstCmd(LPC_ADC,DISABLE);


    // Setup DAC
	Chip_IOCON_PinMux (LPC_IOCON , PUERTO(0) , PIN(26) , MD_PLN, IOCON_FUNC2 );
	Chip_DAC_Init(LPC_DAC);
	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_DAC, SYSCTL_CLKDIV_8);
	Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DBLBUF_ENA | DAC_CNT_ENA | DAC_DMA_ENA); // Se habilita el DMA y soporte de cuenta.

}
