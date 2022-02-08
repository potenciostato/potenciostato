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
#define OC_INITMEASUREMENTLINEAL 0xA1
#define OC_INITMEASUREMENTCYCLICAL 0xA2
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

#define MILISEGUNDOS_POLLING 200

#define CANT_VALORES 500
#define PUNTOS_REFRESCO 10
#define PUNTOS_A_RECIBIR 5

#define MAX_PUNTOS 2

// CONSTANTES INTERNAS
#define FRECUENCIA 0
#define PERIODO 1
#define ENABLED true
#define DISABLED false


#endif // GLOBALES_H
