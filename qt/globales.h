#ifndef GLOBALES_H
#define GLOBALES_H

#include "libusb.h"

//LPC1769
#define MY_VENDOR  ((uint16_t) 0x1FC9)
#define MY_PRODUCT ((uint16_t) 0x0081)

//CH340
//#define MY_VENDOR  ((uint16_t) 0x1a86)
//#define MY_PRODUCT ((uint16_t) 0x7523)

libusb_device **devs;
libusb_context *ctx = NULL;

libusb_device_handle *dev_handle;

libusb_device_descriptor desc;
libusb_config_descriptor *config;

const libusb_interface *inter;
const libusb_interface_descriptor *interdesc;
const libusb_endpoint_descriptor *epdesc;

uint8_t connected = 0;
int8_t Dispositivo = -1;

// Definiciones de los códigos de operación
#define OC_INITMEASUREMENTCYCLICAL 0xA1
#define OC_ABORTMEASUREMENT         0xB1
#define OC_ENDMEASUREMENT 			0xB2
#define OC_SENDDATA 0xC
#define OC_CYCLEEND 0xD1
#define OC_SENDDATAEND 0xD2
#define OC_ACK 0xE
#define OC_SENDDATA_ERR 0xF

#define ADC_TENSION_MAX 30
#define ADC_CORRIENTE_MAX 30
#define ADC_TENSION_BITS 12
#define ADC_CORRIENTE_BITS 12
#define MV_TENSION_MAXIMA 3300

#define MILISEGUNDOS_POLLING 50 //cantidad de milisegundos entre rafagas de REPORTES_A_RECIBIR

#define POS_X_MINIMA 46
#define POS_X_MAXIMA 736
#define POS_Y_MINIMA 14
#define POS_Y_MAXIMA 461

#define LARGO_MENSAJE_ENTRADA	21 //cantidad de bytes de los reports de entrada (visto desde el punto de vista de la PC)
                                   //da 21 porque no se pudo enviar mas datos desde el LPC, deberia ser 32 o hasta 64
#define LARGO_MENSAJE_SALIDA	13 //cantidad de bytes de los reports de salida (visto desde el punto de vista de la PC)

#define CANT_VALORES 1000 //cantidad maxima de puntos a representar en el grafico
#define PUNTOS_REFRESCO 10
#define REPORTES_A_RECIBIR 4 //reportes a recibir en una misma rafaga de pedido de datos

#define GEN_PTO_MEDIO 1000 //mV

// Definiciones de las ganancias de corriente(x0.1, x1, x5 y x10)
#define GAN_CORRIENTE_X01 0
#define GAN_CORRIENTE_X1 1
#define GAN_CORRIENTE_X5 2
#define GAN_CORRIENTE_X10 3

// CONSTANTES INTERNAS
#define ENABLED true
#define DISABLED false
#define BITS_EN_UN_BYTE 8
#define SIN_SELECCIONAR 0
#define SELECCIONAR_A 1
#define SELECCIONAR_B 2
#define CUR_A 1
#define CUR_B 2


#endif // GLOBALES_H
