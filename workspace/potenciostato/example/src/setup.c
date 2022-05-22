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
	SystemCoreClockUpdate();
	Board_Init();
	Chip_GPIO_Init (LPC_GPIO);
	Chip_IOCON_Init(LPC_IOCON);

	// Setup ADC
	Chip_ADC_Init(LPC_ADC, &ADCSetup);
	Chip_ADC_EnableChannel(LPC_ADC, CANAL_CORRIENTE, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC, CANAL_TENSION, ENABLE);
	Chip_ADC_SetSampleRate(LPC_ADC,&ADCSetup,ADC_SAMPL_FREC);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC,CANAL_CORRIENTE,ENABLE);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC,CANAL_TENSION,ENABLE);
	Chip_IOCON_PinMux(LPC_IOCON, PUERTO(0), PIN(23), MD_PLN, IOCON_FUNC1); //ADC0
	Chip_IOCON_PinMux(LPC_IOCON, PUERTO(0), PIN(24), MD_PLN, IOCON_FUNC1); //ADC1

    // Setup DAC
	Chip_IOCON_PinMux (LPC_IOCON , PUERTO(0) , PIN(26) , MD_PLN, IOCON_FUNC2 );
	Chip_DAC_Init(LPC_DAC);
	// Punto medio DAC
	Chip_DAC_UpdateValue(LPC_DAC, 512);

	// Setup Timer0
	Chip_TIMER_Init(LPC_TIMER0);
	Chip_TIMER_Enable(LPC_TIMER0);

	// Setup Timer1
	Chip_TIMER_Init(LPC_TIMER1);
	Chip_TIMER_Enable(LPC_TIMER1);

	// Pines selectores de ganancia de corriente
    Chip_IOCON_PinMux(LPC_IOCON, PUERTO(0), PIN(8), MD_PUP, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PUERTO(0), PIN(8)); //Configuro como salida el pin
    Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(8));
    Chip_IOCON_PinMux(LPC_IOCON, PUERTO(0), PIN(7), MD_PUP, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PUERTO(0), PIN(7));
    Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(7));
    Chip_IOCON_PinMux(LPC_IOCON, PUERTO(0), PIN(6), MD_PUP, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PUERTO(0), PIN(6));
    Chip_GPIO_SetPinOutLow(LPC_GPIO, PUERTO(0), PIN(6));
    Chip_IOCON_PinMux(LPC_IOCON, PUERTO(0), PIN(0), MD_PUP, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PUERTO(0), PIN(0));
    Chip_GPIO_SetPinOutHigh(LPC_GPIO, PUERTO(0), PIN(7));
}
