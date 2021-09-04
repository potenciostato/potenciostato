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
	//Chip_ADC_SetBurstCmd(LPC_ADC,DISABLE);


    // Setup DAC
	Chip_IOCON_PinMux (LPC_IOCON , PUERTO(0) , PIN(26) , MD_PLN, IOCON_FUNC2 );
	Chip_DAC_Init(LPC_DAC);
	Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DBLBUF_ENA | DAC_CNT_ENA | DAC_DMA_ENA); // Se habilita el DMA y soporte de cuenta.


    // Setup P0.2 SW_I_GAIN1
	Chip_IOCON_PinMux(LPC_IOCON, PORT0, PIN(2), MD_PUP, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT0, PIN(2));
//    Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT0, PIN(2));

    // Setup P0.3 SW_I_GAIN2
	Chip_IOCON_PinMux(LPC_IOCON, PORT0, PIN(3), MD_PUP, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT0, PIN(3));
//    Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT0, PIN(3));
//    Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT0, PIN(3));


    // Setup P0.21 OFF_I_1
	Chip_IOCON_PinMux(LPC_IOCON, PORT0, PIN(21), MD_PUP, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT0, PIN(21));
//    Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT0, PIN(21));

    // Setup P0.22 OFF_I_2
	Chip_IOCON_PinMux(LPC_IOCON, PORT0, PIN(22), MD_PUP, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT0, PIN(22));
//    Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT0, PIN(22));
//    Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT0, PIN(22));

    // Setup P2.1 SW_GAIN1 -  En el kickcad estaba al reves y era el P.2.2
	Chip_IOCON_PinMux(LPC_IOCON, PORT2, PIN(1), MD_PUP, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT2, PIN(2));
//   Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(2));

    // Setup P2.2 SW_GAIN2 -  En el kickcad estaba al reves y era el P.2.1
	Chip_IOCON_PinMux(LPC_IOCON, PORT2, PIN(2), MD_PUP, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT2, PIN(1));
//    Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(1));
//    Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(1));

    // Setup P2.3 OFF_DAC_1
	Chip_IOCON_PinMux(LPC_IOCON, PORT2, PIN(3), MD_PUP, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT2, PIN(3));
//    Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(3));

    // Setup P2.4 OFF_DAC_2
	Chip_IOCON_PinMux(LPC_IOCON, PORT2, PIN(4), MD_PUP, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT2, PIN(4));
//    Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(4));
//    Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(4));

    // Setup P2.5 SW_V_GAIN1
	Chip_IOCON_PinMux(LPC_IOCON, PORT2, PIN(5), MD_PUP, IOCON_FUNC0); //Configuro la funcion del pin P2.5,Pull up, I/O
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT2, PIN(5));	//Configuro como salida el pi
//    Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(5));

    // Setup P2.6 SW_V_GAIN2
	Chip_IOCON_PinMux(LPC_IOCON, PORT2, PIN(6), MD_PUP, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT2, PIN(6));
//    Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(6));
//    Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(6));

    // Setup P2.7 OFF_V_1
	Chip_IOCON_PinMux(LPC_IOCON, PORT2, PIN(7), MD_PUP, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT2, PIN(7));
   Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(7));

    // Setup P2.8 OFF_V_2
	Chip_IOCON_PinMux(LPC_IOCON, PORT2, PIN(8), MD_PUP, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT2, PIN(8));
//    Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(8));
    Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(8));

    /*
    if (SW_GAIN1 == 1)
    {
    	//Prendo SW_GAIN1 & OFF_DAC_1 y apago SW_GAIN2 y OFF_DAC_2
    	// P2.1 SW_GAIN1
        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(1));
        // P2.3 OFF_DAC_1
        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(3));
        // P2.2 SW_GAIN2
        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(2));
        // P2.4 OFF_DAC_2
        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(4));

    }

    if (SW_GAIN1 == 2)
    {
    	//Prendo SW_GAIN2 & OFF_DAC_2 y apago SW_GAIN1 y OFF_DAC_1
    	// P2.1 SW_GAIN1
    	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(1));
        // P2.3 OFF_DAC_1
    	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(3));
        // P2.2 SW_GAIN2
        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(2));
        // P2.4 OFF_DAC_12
        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(4));

    }

    if (SW_I_GAIN1 == 1)
    {
    	//Prendo SW_I_GAIN1 & OFF_I_1 y apago SW_I_GAIN2 y OFF_I_2
    	// P2.1 SW_I_GAIN1
        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT0, PIN(2));
        // P2.3 OFF_I_1
        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT0, PIN(21));
        // P2.2 SW_I_GAIN2
        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT0, PIN(3));
        // P2.4 OFF_I_2
        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT0, PIN(22));

    }

    if (SW_I_GAIN1 == 2)
    {
    	//Prendo SW_I_GAIN1 & OFF_I_1 y apago SW_I_GAIN2 y OFF_I_2
    	// P2.1 SW_I_GAIN1
    	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT0, PIN(2));
        // P2.3 OFF_I_1
        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT0, PIN(21));
        // P2.2 SW_I_GAIN2
        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT0, PIN(3));
        // P2.4 OFF_I_2
        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT0, PIN(22));

    }

    if (SW_v_GAIN1 == 1)
    {
    	//Prendo SW_V_GAIN1 & OFF_V_1 y apago SW_V_GAIN2 y OFF_V_2
    	// P2.1 SW_V_GAIN1
        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(5));
        // P2.3 OFF_V_1
        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(7));
        // P2.2 SW_V_GAIN2
        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(6));
        // P2.4 OFF_V_2
        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(8));

    }

    if (SW_v_GAIN1 == 2)
    {
    	//Prendo SW_V_GAIN1 & OFF_V_1 y apago SW_V_GAIN2 y OFF_V_2
    	// P2.1 SW_V_GAIN1
    	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(5));
        // P2.3 OFF_V_1
    	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(7));
        // P2.2 SW_V_GAIN2
        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(6));
        // P2.4 OFF_V_2
        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(8));

    }*/

}


/*****************************************************************************
 * Configuro las ganancias y los offsets de a pares
 ****************************************************************************/
void configGains(uint8_t SW_GAIN,uint8_t SW_I_GAIN,uint8_t SW_V_GAIN)
{

	    if (SW_GAIN == SW_GAIN1)
	    {
	    	//Prendo SW_GAIN1 & OFF_DAC_1 y apago SW_GAIN2 y OFF_DAC_2
	    	// P2.1 SW_GAIN1
	        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(1));
	        // P2.3 OFF_DAC_1
	        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(3));
	        // P2.2 SW_GAIN2
	        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(2));
	        // P2.4 OFF_DAC_2
	        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(4));

	    }

	    if (SW_GAIN == SW_GAIN2)
	    {
	    	//Apago SW_GAIN2 & OFF_DAC_2 y prendo SW_GAIN1 y OFF_DAC_1
	    	// P2.1 SW_GAIN1
	    	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(1));
	        // P2.3 OFF_DAC_1
	    	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(3));
	        // P2.2 SW_GAIN2
	        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(2));
	        // P2.4 OFF_DAC_12
	        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(4));

	    }

	    if (SW_I_GAIN == SW_I_GAIN1)
	    {
	    	//Prendo SW_I_GAIN1 & OFF_I_1 y apago SW_I_GAIN2 y OFF_I_2
	    	// P2.1 SW_I_GAIN1
	        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT0, PIN(2));
	        // P2.3 OFF_I_1
	        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT0, PIN(21));
	        // P2.2 SW_I_GAIN2
	        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT0, PIN(3));
	        // P2.4 OFF_I_2
	        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT0, PIN(22));

	    }

	    if (SW_I_GAIN == SW_I_GAIN2)
	    {
	    	//Apago SW_I_GAIN1 & OFF_I_1 y prendo SW_I_GAIN2 y OFF_I_2
	    	// P2.1 SW_I_GAIN1
	    	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT0, PIN(2));
	        // P2.3 OFF_I_1
	        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT0, PIN(21));
	        // P2.2 SW_I_GAIN2
	        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT0, PIN(3));
	        // P2.4 OFF_I_2
	        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT0, PIN(22));

	    }

	    if (SW_V_GAIN == SW_V_GAIN1)
	    {
	    	//Prendo SW_V_GAIN1 & OFF_V_1 y apago SW_V_GAIN2 y OFF_V_2
	    	// P2.1 SW_V_GAIN1
	        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(5));
	        // P2.3 OFF_V_1
	        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(7));
	        // P2.2 SW_V_GAIN2
	        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(6));
	        // P2.4 OFF_V_2
	        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(8));

	    }

	    if (SW_V_GAIN == SW_V_GAIN2)
	    {
	    	//Apago SW_V_GAIN1 & OFF_V_1 y prendo SW_V_GAIN2 y OFF_V_2
	    	// P2.1 SW_V_GAIN1
	    	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(5));
	        // P2.3 OFF_V_1
	    	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(7));
	        // P2.2 SW_V_GAIN2
	        Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT2, PIN(6));
	        // P2.4 OFF_V_2
	        Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT2, PIN(8));

	    }
}
