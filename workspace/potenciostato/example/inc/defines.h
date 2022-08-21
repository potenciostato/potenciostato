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
#define LARGO_MENSAJE_SALIDA		13 //cantidad de bytes de los reports de salida (visto desde el punto de vista de la PC)
#define LARGO_PACKETSIZE_SALIDA		13 //cantidad de bytes máxima de los reports de salida

#define PUNTOS_GRAFICA			500
#define MAX_PUNTOS_RETENCION	50
#define MAX_PUNTOS 6
#define FRECUENCIA_BAJA			50000 // FREC*1000
#define FRECUENCIA_MUY_BAJA		5000 // FREC*1000

#define TICKS_MUESTREO          10 // delay entre lecturas de ADC, determina la frecuencia de muestreo (con el error propio de los ticks del sistema)

#define ADC_DR_RESULT(n)        (((n) & 0xFFF))

#define TAKE_TIMEOUT			1000


// Definiciones de los códigos de operación
#define OC_INITMEASUREMENTCYCLICAL  0xA1
#define OC_RETRYMEASUREMENT		 	0xA3
#define OC_ABORTMEASUREMENT 		0xB1
#define OC_ENDMEASUREMENT 			0xB2
#define OC_SENDDATA 				0xC
#define OC_CYCLEEND 				0xD1
#define OC_SENDDATAEND 				0xD2
#define OC_ACK 						0xE
#define OC_SENDDATA_ERR 			0xF

#define BARRIDO_CICLICO 		OC_INITMEASUREMENTCYCLICAL

// Definiciones del codigo generador de señales
#define GEN_GAN_AT 165 //100*3300mV/2000 se multiplica por 100 para no utilizar punto flotante
#define GEN_CANT_MUESTRAS_MAX 1000
#define GEN_CANT_BITS_DAC 10
#define GEN_PTO_MEDIO 1000 //mV

// Definiciones de los flancos
#define PRIMER_FLANCO 	1
#define SEGUNDO_FLANCO 	2

// Definiciones de las ganancias de corriente(x0.1, x1, x5 y x10)
#define GAN_CORRIENTE_X01 	0
#define GAN_CORRIENTE_X1 	1
#define GAN_CORRIENTE_X5 	2
#define GAN_CORRIENTE_X10 	3

#define PIN_GAN_CORR_X01 	PIN(7)
#define PIN_GAN_CORR_X1 	PIN(0)
#define PIN_GAN_CORR_X5 	PIN(6)
#define PIN_GAN_CORR_X10 	PIN(8)

#endif /* DEFINES_H_ */
