/*
 * setup.c
 *
 *  Created on: Nov 29, 2016
 *      Author: axellucas
 */

#include <board.h>
#include <FreeRTOS.h>
#include <task.h>
#include <chip.h>
#include <semphr.h>
#include <queue.h>

#include <defines.h>

#include <encoder.h>
#include <display.h>


/*****************************************************************************
 * Funcion de Setup Inicial
 ****************************************************************************/
void prvSetupHardware(void)
{
	uint32_t timerfreq;

	SystemCoreClockUpdate();
	//Board_Init();
	Chip_GPIO_Init (LPC_GPIO);
	Chip_IOCON_Init(LPC_IOCON);

	timerfreq= Chip_Clock_GetSystemClockRate();

	Chip_IOCON_PinMux(LPC_IOCON, PORT_BOT_VOL, PIN_BOT_VOL, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORT_BOT_VOL, PIN_BOT_VOL); //Configuro como entrada el pin
	Chip_IOCON_PinMux(LPC_IOCON, PORT_BOT_FCI, PIN_BOT_FCI, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORT_BOT_FCI, PIN_BOT_FCI); //Configuro como entrada el pin

    Chip_IOCON_PinMux(LPC_IOCON, PORTVOL1, PINVOL1, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTVOL1, PINVOL1); //Configuro como salida el pin
    Chip_IOCON_PinMux(LPC_IOCON, PORTVOL3, PINVOL3, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTVOL3, PINVOL3); //Configuro como salida el pin

    Chip_IOCON_PinMux(LPC_IOCON, PORTFCI1, PINFCI1, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTFCI1, PINFCI1); //Configuro como salida el pin
    Chip_IOCON_PinMux(LPC_IOCON, PORTFCI3, PINFCI3, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTFCI3, PINFCI3); //Configuro como salida el pin

    Chip_IOCON_PinMux(LPC_IOCON, PORTFCS1, PINFCS1, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTFCS1, PINFCS1); //Configuro como entrada el pin
    Chip_IOCON_PinMux(LPC_IOCON, PORTFCS3, PINFCS3, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTFCS3, PINFCS3); //Configuro como entrada el pin

    Chip_IOCON_PinMux(LPC_IOCON, PORTOVER1, PINOVER1, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTOVER1, PINOVER1); //Configuro como salida el pin
    Chip_IOCON_PinMux(LPC_IOCON, PORTOVER3, PINOVER3, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTOVER3, PINOVER3); //Configuro como salida el pin

    Chip_IOCON_PinMux(LPC_IOCON, PORTATT1, PINATT1, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTATT1, PINATT1); //Configuro como salida el pin
    Chip_IOCON_PinMux(LPC_IOCON, PORTATT3, PINATT3, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTATT3, PINATT3); //Configuro como salida el pin

    Chip_IOCON_PinMux(LPC_IOCON, PORTDELAY1, PINDELAY1, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTDELAY1, PINDELAY1); //Configuro como salida el pin
    Chip_IOCON_PinMux(LPC_IOCON, PORTDELAY3, PINDELAY3, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTDELAY3, PINDELAY3); //Configuro como salida el pin

    Chip_IOCON_PinMux(LPC_IOCON, PORTBOTONES, PINSENO, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTBOTONES, PINSENO); //Configuro como salida el pin
    Chip_IOCON_PinMux(LPC_IOCON, PORTBOTONES, PINTRIA, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTBOTONES, PINTRIA); //Configuro como salida el pin
    Chip_IOCON_PinMux(LPC_IOCON, PORTBOTONES, PINCUAD, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTBOTONES, PINCUAD); //Configuro como salida el pin
    Chip_IOCON_PinMux(LPC_IOCON, PORTBOTONES, PINSIER, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTBOTONES, PINSIER); //Configuro como salida el pin

    Chip_IOCON_PinMux(LPC_IOCON, PORTBOTONES, PINHP, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTBOTONES, PINHP); //Configuro como salida el pin
    Chip_IOCON_PinMux(LPC_IOCON, PORTBOTONES, PINLP, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTBOTONES, PINLP); //Configuro como salida el pin
    Chip_IOCON_PinMux(LPC_IOCON, PORTBOTONES, PINBP, MD_PLN, IOCON_FUNC0); //Configuro la funcion del pin
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTBOTONES, PINBP); //Configuro como salida el pin

    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_EXCT1, PIN_EXCT1, 		MD_PLN, IOCON_FUNC0);	//Configuramos la funcion del los pines de excitacion
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT_EXCT1, PIN_EXCT1);							//Configuramos los pines como salida
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_EXCT2, PIN_EXCT2, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT_EXCT2, PIN_EXCT2);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_EXCT3, PIN_EXCT3, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT_EXCT3, PIN_EXCT3);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_EXCT4, PIN_EXCT4, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT_EXCT4, PIN_EXCT4);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_EXCT5, PIN_EXCT5, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT_EXCT5, PIN_EXCT5);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_EXCT6, PIN_EXCT6, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT_EXCT6, PIN_EXCT6);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_EXCT7, PIN_EXCT7, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT_EXCT7, PIN_EXCT7);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_EXCT8, PIN_EXCT8, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT_EXCT8, PIN_EXCT8);

    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_SENS1, PIN_SENS1, 		MD_PLN, IOCON_FUNC0);		//Configuramos la funcion de los pines del teclado
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, 	PORT_SENS1, PIN_SENS1);								//Configuramos los pines como entrada
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_SENS2, PIN_SENS2, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, 	PORT_SENS2, PIN_SENS2);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_SENS3, PIN_SENS3, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, 	PORT_SENS3, PIN_SENS3);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_SENS4, PIN_SENS4, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, 	PORT_SENS4, PIN_SENS4);


    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_DISPLAY_D_I, PIN_DISPLAY_D_I, 		MD_PLN, IOCON_FUNC0);	//Configuramos la funcion del los pines de control del display
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT_DISPLAY_D_I, PIN_DISPLAY_D_I);							//Configuramos los pines como salida
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_DISPLAY_R_W, PIN_DISPLAY_R_W, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT_DISPLAY_R_W, PIN_DISPLAY_R_W);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_DISPLAY_EN, PIN_DISPLAY_EN, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT_DISPLAY_EN, PIN_DISPLAY_EN);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_DISPLAY_CSEL1, PIN_DISPLAY_CSEL1, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT_DISPLAY_CSEL1, PIN_DISPLAY_CSEL1);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_DISPLAY_CSEL2, PIN_DISPLAY_CSEL2, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT_DISPLAY_CSEL2, PIN_DISPLAY_CSEL2);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_DISPLAY_RESET, PIN_DISPLAY_RESET, 		MD_PLN, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORT_DISPLAY_RESET, PIN_DISPLAY_RESET);

    Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT_DISPLAY_RESET, PIN_DISPLAY_RESET);

    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_DISPLAY_D0, PIN_DISPLAY_D0, 		MD_PLN, IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_DISPLAY_D1, PIN_DISPLAY_D1, 		MD_PLN, IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_DISPLAY_D2, PIN_DISPLAY_D2, 		MD_PLN, IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_DISPLAY_D3, PIN_DISPLAY_D3, 		MD_PLN, IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_DISPLAY_D4, PIN_DISPLAY_D4, 		MD_PLN, IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_DISPLAY_D5, PIN_DISPLAY_D5, 		MD_PLN, IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_DISPLAY_D6, PIN_DISPLAY_D6, 		MD_PLN, IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, 		PORT_DISPLAY_D7, PIN_DISPLAY_D7, 		MD_PLN, IOCON_FUNC0);


    // Setup DAC
	Chip_IOCON_PinMux (LPC_IOCON , PUERTO(0) , PIN(26) , MD_PLN, IOCON_FUNC2 );
	Chip_DAC_Init(LPC_DAC);

	Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DBLBUF_ENA | DAC_CNT_ENA | DAC_DMA_ENA); // Se habilita el DMA y soporte de cuenta.

}
