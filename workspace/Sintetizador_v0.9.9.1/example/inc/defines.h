/*
 * defines.h
 *
 *  Created on: Nov 26, 2016
 *      Author: axellucas
 */

#ifndef DEFINES_H_
#define DEFINES_H_


#define VOLUMEN_INICIAL	7
#define FCI_INICIAL	4 //estos dos no estan activos
#define FCS_INICIAL	4 //estos dos no estan activos
#define ATTACK_INICIAL	0
#define DELAY_INICIAL	0
#define OVER_INICIAL	0

#define SALIDA			1
#define ENTRADA			0

#define PORT0			0
#define PORT1			1
#define PORT2			2
#define PORT3			3
#define PORT4			4

//TECLADO EL BOTON 5 NO ANDA, el 13 presenta dificultades, el 21 tampoco anda bien, el 28 tampoco y entre la 21 y 32 andan mas o menos
#define PORT0A8TECLADO	PORT2
#define PIN1TECLADO		7 //pin 49
#define PIN2TECLADO		6 //pin 48
#define PIN3TECLADO		5 //pin 47
#define PIN4TECLADO		4 //pin 46
#define PIN5TECLADO		3 //pin 45
#define PIN6TECLADO		2 //pin 44
#define PIN7TECLADO		1 //pin 43
#define PIN8TECLADO		0 //pin 42

#define PORT9A12TECLADO	PORT0
#define PIN9TECLADO		11 //pin 41
#define PIN10TECLADO	10 //pin 40
#define PIN11TECLADO	5 //pin 39
#define PIN12TECLADO	4 //pin 38


//Defino los pines de entradas de la matriz del teclado
#define PORT_SENS1   	PORT0A8TECLADO
#define PIN_SENS1     	PIN6TECLADO		//Pin que sensa las teclas 1 a la 8 TIENEN QUE ESTAR CON UNA R de 10 K A 3.3V!!!!!
#define PORT_SENS2   	PORT0A8TECLADO
#define PIN_SENS2     	PIN7TECLADO 	//Pin que sensa las teclas 9 a la 16
#define PORT_SENS3   	PORT0A8TECLADO
#define PIN_SENS3     	PIN8TECLADO 	//Pin que sensa las teclas 17 a la 24
#define PORT_SENS4   	PORT9A12TECLADO
#define PIN_SENS4     	PIN9TECLADO 	//Pin que sensa las teclas 25 a la 32

//Defino los pines de excitación por los que inyectaré un 0 para habilitar cada columna de nuestra matriz del teclado
#define PORT_EXCT1   	PORT0A8TECLADO
#define PIN_EXCT1     	PIN1TECLADO		//Excitacion para habilitar botones 1, 9, 17 y 25
#define PORT_EXCT2   	PORT0A8TECLADO
#define PIN_EXCT2     	PIN2TECLADO 	//Excitacion para habilitar botones 2, 10, 18 y 26
#define PORT_EXCT3   	PORT0A8TECLADO
#define PIN_EXCT3     	PIN3TECLADO 	//Excitacion para habilitar botones 3, 11, 19 y 27
#define PORT_EXCT4   	PORT0A8TECLADO
#define PIN_EXCT4     	PIN4TECLADO		//Excitacion para habilitar botones 4, 12, 20 y 28
#define PORT_EXCT5   	PORT0A8TECLADO
#define PIN_EXCT5     	PIN5TECLADO 	//Excitacion para habilitar botones 5, 13, 21 y 29
#define PORT_EXCT6   	PORT9A12TECLADO
#define PIN_EXCT6     	PIN11TECLADO 	//Excitacion para habilitar botones 6, 14, 22 y 30
#define PORT_EXCT7   	PORT9A12TECLADO
#define PIN_EXCT7     	PIN12TECLADO	//Excitacion para habilitar botones 7, 15, 23 y 31
#define PORT_EXCT8   	PORT9A12TECLADO
#define PIN_EXCT8     	PIN10TECLADO 	//Excitacion para habilitar botones 8, 16, 24 y 32

//----------INICIO UN VECTOR DE CONSTANTES DEFINIDAS ANTERIORMENTE
#define VECTOR(n,d) ==(n) ? d :

#define PORTS_EXCT(i) 		(i) VECTOR(0,PORT_EXCT1) (i) VECTOR(1,PORT_EXCT2) (i) VECTOR(2,PORT_EXCT3) (i) VECTOR(3,PORT_EXCT4)\
							(i) VECTOR(4,PORT_EXCT5) (i) VECTOR(5,PORT_EXCT6) (i) VECTOR(6,PORT_EXCT7) (i) VECTOR(7,PORT_EXCT8)\
							0
#define PINS_EXCT(i) 		(i) VECTOR(0,PIN_EXCT1) (i) VECTOR(1,PIN_EXCT2) (i) VECTOR(2,PIN_EXCT3) (i) VECTOR(3,PIN_EXCT4)\
							(i) VECTOR(4,PIN_EXCT5) (i) VECTOR(5,PIN_EXCT6) (i) VECTOR(6,PIN_EXCT7) (i) VECTOR(7,PIN_EXCT8)\
							0
//----------FIN DE VECTOR DE CONSTANTES

#define PORT_BOT_VOL	PORT0
#define PIN_BOT_VOL		17
#define PORT_BOT_FCI	PORT0
#define PIN_BOT_FCI		15

#define PORTVOL1		PORT1
#define PINVOL1			31
#define PORTVOL3 		PORT2
#define PINVOL3			13

#define PORTFCI1		PORT0
#define PINFCI1			27 //damos vuelta tambien al igual que el FCS
#define PORTFCI3		PORT0
#define PINFCI3			28

#define PORTFCS1		PORT0
#define PINFCS1			22 // lo dimos vuelta con el 22 por un intercambio de conexion en la placa
#define PORTFCS3		PORT0
#define PINFCS3			21

#define PORTOVER1		PORT0
#define PINOVER1		2 //tambien hubo que dar vuelta
#define PORTOVER3		PORT0
#define PINOVER3		3

#define PORTATT1		PORT2
#define PINATT1			11 //tambien hubo que dar vuelta
#define PORTATT3		PORT2
#define PINATT3			12

#define PORTDELAY1		PORT2
#define PINDELAY1		8 //idem anterior
#define PORTDELAY3		PORT2
#define PINDELAY3		10

#define PORTBOTONES	PORT0

#define PINSENO			8
#define PINCUAD			18
#define PINTRIA			9
#define PINSIER			1
#define PINHP			7
#define PINLP			0
#define PINBP			6

// Defines DAC

#define pi    3.14159265358979

#define PUERTO(X)             X
#define PIN(X)                 X

#define NUMERO_MUESTRAS     60
#define DMA_SIZE            60
#define FMAX                880

#define PRIMER_CUADRANTE 	15
#define SEGUNDO_CUADRANTE 	30
#define TERCER_CUADRANTE 	45
#define CUARTO_CUADRANTE 	60

//#define CLOCK_DAC_HZ        30000000    // CCLK divido por 4. NOTA: Clock que trae por defecto con ésta configuración: 120MHz.

#define CUADRADA            1
#define SENOIDAL            2
#define TRIANGULAR          3
#define SIERRA              4

#define LP					1
#define BP					2
#define HP					3
#define CANT_FCI 			8
#define CANT_FCI_PB 		2
#define CANT_FCS 			8
#define CANT_FCS_PB 		2
#define CANT_BP				9

#define CANT_DELAY 			100

#define NUM_TAPS            29
#define BLOCK_SIZE          30

#define TECLAS				32
#define cantTECLAS_MAX		6
#define SILENCIO			50

#define FREC_TIMER          80




#endif /* DEFINES_H_ */
