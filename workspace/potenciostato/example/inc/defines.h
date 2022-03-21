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

#define PUERTO(X)             	X
#define PIN(X)                 	X

#define NUMERO_MUESTRAS     	500 // cantidad de muestras de las señales precalculadas
//#define NUMERO_MUESTRAS     	1000 // cantidad de muestras de las señales precalculadas
//#define NUMERO_MUESTRAS     	2000 // cantidad de muestras de las señales precalculadas
//#define NUMERO_MUESTRAS     	4000 // cantidad de muestras de las señales precalculadas
#define DMA_SIZE            	NUMERO_MUESTRAS
#define VALOR_MEDIO_DAC     	512 //valor medio salida dac en cuentas (de 10 bits) de tension para 1.5V
#define REINTENTOS_MAX			3
//#define CLOCK_DAC_HZ        30000000    // CCLK divido por 4. NOTA: Clock que trae por defecto con ésta configuración: 120MHz.

// Defines ADC
#define CANAL_CORRIENTE				ADC_CH0
#define CANAL_TENSION				ADC_CH1
#define ADC_SAMPL_FREC      		200000
#define ADC_N_COLA 					1 //se pone 1 medicion (punto) por cada mensaje de USB
#define TAMANIO_MAX_COLA_ADC 		2000 //cantidad maxima de mediciones (puntos) en la cola ADC
#define TAMANIO_MAX_COLA_USB		100 //cantidad maxima de mensajes en la cola USB
#define LARGO_MENSAJE_ENTRADA		21 //cantidad de bytes de los reports de entrada (visto desde el punto de vista de la PC)
#define LARGO_PACKETSIZE_ENTRADA	21 //cantidad de bytes máxima de los reports de entrada
#define LARGO_MENSAJE_SALIDA		8 //cantidad de bytes de los reports de salida (visto desde el punto de vista de la PC)
#define LARGO_PACKETSIZE_SALIDA		8 //cantidad de bytes máxima de los reports de salida

#define PUNTOS_GRAFICA			200
#define MAX_PUNTOS 6
#define FRECUENCIA_BAJA			50000 // FREC*1000
#define FRECUENCIA_MUY_BAJA		5000 // FREC*1000

#define TICKS_MUESTREO          10 // delay entre lecturas de ADC, determina la frecuencia de muestreo (con el error propio de los ticks del sistema)

#define ADC_DR_RESULT(n)        (((n) & 0xFFF))

#define TAKE_TIMEOUT			1000


// Definiciones de los códigos de operación
#define OC_INITMEASUREMENTLINEAL 	0xA1
#define OC_INITMEASUREMENTCYCLICAL 	0xA2
#define OC_RETRYMEASUREMENT		 	0xA3
#define OC_ABORTMEASUREMENT 		0xB1
#define OC_ENDMEASUREMENT 			0xB2
#define OC_SENDDATA 				0xC
#define OC_CYCLEEND 				0xD1
#define OC_SENDDATAEND 				0xD2
#define OC_ACK 						0xE
#define OC_SENDDATA_ERR 			0xF

#define BARRIDO_CICLICO 		OC_INITMEASUREMENTCYCLICAL
#define BARRIDO_LINEAL 			OC_INITMEASUREMENTLINEAL


#endif /* DEFINES_H_ */
