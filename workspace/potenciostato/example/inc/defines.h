/*
 * defines.h
 *
 *  Created on: Nov 26, 2016
 *      Author: axellucas
 */

#ifndef DEFINES_H_
#define DEFINES_H_



#define SALIDA			1
#define ENTRADA			0

#define PORT0			0
#define PORT1			1
#define PORT2			2
#define PORT3			3
#define PORT4			4



// Defines DAC

#define pi    3.14159265358979

#define PUERTO(X)             X
#define PIN(X)                 X

#define NUMERO_MUESTRAS     120
#define DMA_SIZE            120
#define FMAX                880

#define PRIMER_CUADRANTE 	15
#define SEGUNDO_CUADRANTE 	30
#define TERCER_CUADRANTE 	45
#define CUARTO_CUADRANTE 	60

//#define CLOCK_DAC_HZ        30000000    // CCLK divido por 4. NOTA: Clock que trae por defecto con ésta configuración: 120MHz.

#define CANT_DELAY 			100

#define NUM_TAPS            29
#define BLOCK_SIZE          30

#define TECLAS				32
#define cantTECLAS_MAX		6
#define SILENCIO			50

#define FREC_TIMER          80

// Defines ADC

#define ADC_SAMPL_FREC      50000
#define ADC_N_LECTURAS		30
#define ADC_N_COLA 			50

#define ADC_DR_RESULT(n)        (((n) & 0xFFF))


#endif /* DEFINES_H_ */
