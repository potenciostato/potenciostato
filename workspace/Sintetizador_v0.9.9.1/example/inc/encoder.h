/*
 * encoder.h
 *
 *  Created on: Nov 29, 2016
 *      Author: axellucas
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_


//hacer un vector de defines para las fases asi se llama ciclicamente
//hacer que cada encoder se maneje con 1 sola cola  de dos lugares
//Defino los pines de entrada de los encoders
#define PORT_FASEA  	PORTVOL1
#define PIN_FASEA     	PINVOL1	//Pin que sensa la fase A con una R de 10k a 3.3V
#define PORT_FASEB   	PORTVOL3
#define PIN_FASEB     	PINVOL3 	//Pin que sensa la fase B idem anterior

#define PORTS_FASEA(i) 		(i) VECTOR(0,PORTVOL1) (i) VECTOR(1,PORTFCI1) (i) VECTOR(2,PORTFCS1) \
							(i) VECTOR(3,PORTOVER1) (i) VECTOR(4,PORTATT1) (i) VECTOR(5,PORTDELAY1) \
							0
#define PINS_FASEA(i) 		(i) VECTOR(0,PINVOL1) (i) VECTOR(1,PINFCI1) (i) VECTOR(2,PINFCS1) \
							(i) VECTOR(3,PINOVER1) (i) VECTOR(4,PINATT1) (i) VECTOR(5,PINDELAY1) \
							0
#define PORTS_FASEB(i) 		(i) VECTOR(0,PORTVOL3) (i) VECTOR(1,PORTFCI3) (i) VECTOR(2,PORTFCS3) \
							(i) VECTOR(3,PORTOVER3) (i) VECTOR(4,PORTATT3) (i) VECTOR(5,PORTDELAY3) \
							0
#define PINS_FASEB(i) 		(i) VECTOR(0,PINVOL3) (i) VECTOR(1,PINFCI3) (i) VECTOR(2,PINFCS3) \
							(i) VECTOR(3,PINOVER3) (i) VECTOR(4,PINATT3) (i) VECTOR(5,PINDELAY3) \
							0

typedef struct {
	int delta[6];
	int last[6];
} encoder;

enum {
	ENC_VOLUMEN,
	ENC_FCI,
	ENC_FCS,
	ENC_OVER,
	ENC_ATT,
	ENC_DELAY,

};
#define LARGO_COLA_ENCODERS  1
xQueueHandle cola_encoders; //creamos un manejador de colas global para cada encoder


//Finalizo declaraciones de los encoders

static void prvSetupEncoder(void);


#endif /* INC_ENCODER_H_ */
