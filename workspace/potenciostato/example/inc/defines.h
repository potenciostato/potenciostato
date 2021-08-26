/*
 * defines.h
 *
 *  Created on: Nov 26, 2016
 *      Author: axellucas
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define ENABLED			1
#define DISABLED		0

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

#define CANAL_CORRIENTE		ADC_CH1
#define CANAL_TENSION		ADC_CH0

#define ADC_SAMPL_FREC      50000
#define ADC_N_COLA 			1 //se pone 1 medicion (punto) por cada mensaje de USB
#define TAMANIO_MAX_COLA	100
#define LARGO_MENSAJE		8 //igual a la cantidad de bytes de los reports de entrada y de salida de USB

#define ADC_DR_RESULT(n)        (((n) & 0xFFF))

// Definiciones de los códigos de operación
#define OC_INITMEASUREMENT 0xA
#define OC_ABORTMEASUREMENT 0xB
#define OC_SENDDATA 0xC
#define OC_SENDDATAEND 0xD
#define OC_ACK 0xE
#define OC_SENDDATA_ERR 0xF

// Defines llaves
#define SW_I_GAIN1 1
#define SW_I_GAIN2 0
#define SW_GAIN1 1
#define SW_GAIN2 0
#define SW_V_GAIN1 1
#define SW_V_GAIN2 0
#define OFF_DAC_1 1
#define OFF_DAC_2 0
#define OFF_V_1 1
#define OFF_V_2 0
#define OFF_I_1 1
#define OFF_I_2 0

#endif /* DEFINES_H_ */
