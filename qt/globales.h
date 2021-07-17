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
uint8_t Dispositivo = 0;

// Definiciones de los códigos de operación
#define OC_INITMEASUREMENT 0xA
#define OC_ABORTMEASUREMENT 0xB
#define OC_SENDDATA 0xC
#define OC_SENDDATAEND 0xD
#define OC_ACK 0xE

#endif // GLOBALES_H
