/*
 * hid_generic.c
 *
 *  Created on: Feb 14, 2017
 *      Author: axellucas
 */

/*
 * @brief HID generic example's callabck routines
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include <board.h>
#include <FreeRTOS.h>
#include <task.h>
#include <chip.h>
#include <semphr.h>
#include <queue.h>

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <string.h>
#include "usbd_rom_api.h"

#include <defines.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

static uint8_t *loopback_report;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
extern bool debugging;

extern const uint8_t HID_ReportDescriptor[];
extern const uint16_t HID_ReportDescSize;

extern xQueueHandle qADCsend, qUSBin, qUSBout;
extern uint8_t midiendo;
bool medicion_iniciada=false;

struct USBmsj {
	uint16_t corriente;
	uint16_t tension;
};

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*  HID get report callback function. */
static ErrorCode_t HID_GetReport(USBD_HANDLE_T hHid, USB_SETUP_PACKET *pSetup, uint8_t * *pBuffer, uint16_t *plength)
{
	/* ReportID = SetupPacket.wValue.WB.L; */
	switch (pSetup->wValue.WB.H) {
	case HID_REPORT_INPUT:
		*pBuffer[0] = *loopback_report;
		*plength = 1;
		break;

	case HID_REPORT_OUTPUT:
		return ERR_USBD_STALL;			/* Not Supported */

	case HID_REPORT_FEATURE:
		return ERR_USBD_STALL;			/* Not Supported */
	}
	return LPC_OK;
}

/* HID set report callback function. */
static ErrorCode_t HID_SetReport(USBD_HANDLE_T hHid, USB_SETUP_PACKET *pSetup, uint8_t * *pBuffer, uint16_t length)
{
	/* we will reuse standard EP0Buf */
	if (length == 0) {
		return LPC_OK;
	}

	/* ReportID = SetupPacket.wValue.WB.L; */
	switch (pSetup->wValue.WB.H) {
	case HID_REPORT_INPUT:
		return ERR_USBD_STALL;			/* Not Supported */

	case HID_REPORT_OUTPUT:
		*loopback_report = **pBuffer;
		break;

	case HID_REPORT_FEATURE:
		return ERR_USBD_STALL;			/* Not Supported */
	}
	return LPC_OK;
}

/* HID Interrupt endpoint event handler. */
static ErrorCode_t HID_Ep_Hdlr(USBD_HANDLE_T hUsb, void *data, uint32_t event)
{
	USB_HID_CTRL_T *pHidCtrl = (USB_HID_CTRL_T *) data;
	uint8_t cantidad = 0;

	uint8_t i, mensaje[LARGO_MENSAJE_SALIDA]={0}, mensajein[LARGO_MENSAJE_SALIDA]={0};
	uint8_t respuesta[LARGO_MENSAJE_ENTRADA]={0};
	struct USBmsj medicion;
	uint8_t n_punto = 0;
	int cod_receive;

	static portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	switch (event) {
	case USB_EVT_IN:
		/* last report is successfully sent. Do something... */
		break;

	case USB_EVT_OUT:
		/* Se lee el mensaje del QT */
		cantidad = USBD_API->hw->ReadEP(hUsb, pHidCtrl->epout_adr, loopback_report);
		for (i = 0; i < cantidad; i++){
			mensaje[i] = *(loopback_report+i);
		}
		/* El mensaje sera procesado */

		// Si QT pidio datos, que el LPC envie e1 dato que
		// tiene sin tener que pasar por USBTask (para agilizar)
		// qUSBout tendra los datos a pasar

		if(mensaje[0] == OC_INITMEASUREMENTCYCLICAL)
			medicion_iniciada = true;
		if(mensaje[0] == OC_ABORTMEASUREMENT)
			medicion_iniciada = false;


		// Si el QT envia cualquier otra cosa se pasan todos los datos
		// a la tarea de USB por medio de la cola qUSBout
		switch (mensaje[0]){
			// si el codigo de operacion recibido coincide con el de recibir datos
			case OC_SENDDATA:
				if(xQueueReceiveFromISR( qUSBin, &mensajein, &xHigherPriorityTaskWoken) != pdFAIL) {
					if (mensajein[0] == OC_CYCLEEND){
						medicion_iniciada = false;
						if (debugging == ENABLED)
							DEBUGOUT("INT: CYCLE END\n");
						respuesta[0] = OC_CYCLEEND;
						for (i = 1; i < LARGO_MENSAJE_ENTRADA; i ++){
							respuesta[i] = 0x0;
						}
					}
				}else{
					// Hay que enviar datos de la medicion

					// Se inicia en 0 puntos
					n_punto = 0;

					// Se intenta recibir la primer medicion
					cod_receive = xQueueReceiveFromISR( qADCsend, &medicion, &xHigherPriorityTaskWoken);
					if(cod_receive == pdFAIL){
						if (medicion_iniciada == true){
							if (debugging == ENABLED)
								DEBUGOUT("INT: NO HAY DATOS PARA MANDAR\n");
							respuesta[0] = OC_SENDDATA_ERR;
						}
						if (medicion_iniciada == false){
							if (debugging == ENABLED)
								DEBUGOUT("INT: Termino la medicion y no hay mas datos \n");
							respuesta[0] = OC_SENDDATAEND;
						}
						for (i = 1; i < LARGO_MENSAJE_ENTRADA; i ++){
							respuesta[i] = 0x0;
						}
					} else {
						for (i = 0; i < LARGO_MENSAJE_ENTRADA; i ++){
							respuesta[i] = 0x0;
						}
						do{
							// Hay datos para enviar
							if (debugging == ENABLED)
								DEBUGOUT("INT: SEND DATA\n");

							// Si hay datos para mandar, encolar los puntos de la medicion
							respuesta[0] = OC_SENDDATA;
							respuesta[1] = n_punto+1; // representa la cantidad de puntos a enviar
							respuesta[2+3*n_punto] = (medicion.corriente & 0xFF);
							respuesta[3+3*n_punto] =  ((medicion.corriente >> 8) & 0x0F) | ((medicion.tension & 0x0F) << 4);
							respuesta[4+3*n_punto] = (((medicion.tension) >> 4) & 0xFF);

							n_punto++;
							if (n_punto < MAX_PUNTOS){
								cod_receive = xQueueReceiveFromISR( qADCsend, &medicion, &xHigherPriorityTaskWoken);
							}
						}while((cod_receive != pdFAIL) && (n_punto < MAX_PUNTOS));
					}
				}
				USBD_API->hw->WriteEP(hUsb, pHidCtrl->epin_adr, respuesta, LARGO_MENSAJE_ENTRADA);
				break;
			case OC_INITMEASUREMENTCYCLICAL:
			case OC_ABORTMEASUREMENT:
			case OC_ENDMEASUREMENT:
				xQueueSendToBackFromISR( qUSBout, &mensaje, &xHigherPriorityTaskWoken );
				respuesta[0] = mensaje[0]; //el ACK sera el codigo de operacion recibido y nada mas
				for (i = 1; i < LARGO_MENSAJE_ENTRADA; i++){
					respuesta[i] = 0;
				}
				if (debugging == ENABLED)
					DEBUGOUT("INT: INIT OR ABORT\n");
				USBD_API->hw->WriteEP(hUsb, pHidCtrl->epin_adr, respuesta, LARGO_MENSAJE_ENTRADA);
				break;
			default:
				for (i = 1; i < LARGO_MENSAJE_ENTRADA; i++){
					if (i % 2 == 0)
						respuesta[i] = 0xAA;
					else
						respuesta[i] = 0xFF;
				}

				USBD_API->hw->WriteEP(hUsb, pHidCtrl->epin_adr, respuesta, LARGO_MENSAJE_ENTRADA);
				break;
		}

		break;
	}
	return LPC_OK;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* HID init routine */
ErrorCode_t usb_hid_init(USBD_HANDLE_T hUsb,
						 USB_INTERFACE_DESCRIPTOR *pIntfDesc,
						 uint32_t *mem_base,
						 uint32_t *mem_size)
{
	USBD_HID_INIT_PARAM_T hid_param;
	USB_HID_REPORT_T reports_data[1];
	ErrorCode_t ret = LPC_OK;

	memset((void *) &hid_param, 0, sizeof(USBD_HID_INIT_PARAM_T));
	/* HID params */
	hid_param.max_reports = 1;
	/* Init reports_data */
	reports_data[0].len = HID_ReportDescSize;
	reports_data[0].idle_time = 0;
	reports_data[0].desc = (uint8_t *) &HID_ReportDescriptor[0];

	if ((pIntfDesc == 0) || (pIntfDesc->bInterfaceClass != USB_DEVICE_CLASS_HUMAN_INTERFACE)) {
		return ERR_FAILED;
	}

	hid_param.mem_base = *mem_base;
	hid_param.mem_size = *mem_size;
	hid_param.intf_desc = (uint8_t *) pIntfDesc;
	/* user defined functions */
	hid_param.HID_GetReport = HID_GetReport;
	hid_param.HID_SetReport = HID_SetReport;
	hid_param.HID_EpIn_Hdlr  = HID_Ep_Hdlr;
	hid_param.HID_EpOut_Hdlr = HID_Ep_Hdlr;
	hid_param.report_data  = reports_data;

	ret = USBD_API->hid->init(hUsb, &hid_param);
	/* allocate USB accessable memory space for report data */
	loopback_report =  (uint8_t *) hid_param.mem_base;
	hid_param.mem_base += 4;
	hid_param.mem_size += 4;
	/* update memory variables */
	*mem_base = hid_param.mem_base;
	*mem_size = hid_param.mem_size;
	return ret;
}
