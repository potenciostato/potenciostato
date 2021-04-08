/*
 * Sintetizador Grupo 1
 *
 */
// 1.0
//TODO: -buferear salida para que no haga ruido ->listo
//      -mejorar amplitud de onda segun las potencias
//		-chequear el bug de que se cuelga, creo que tiene que ver con el hardware

#include <board.h>
#include <FreeRTOS.h>
#include <task.h>
#include <chip.h>
#include <semphr.h>
#include <queue.h>
#include <arm_math.h>
#include <math_helper.h>

#include <stdio.h>
#include <string.h>
#include "app_usbd_cfg.h"
#include "hid_generic.h"

#include <defines.h>
#include <constantes.h>

#include <setup.h>
#include <encoder.h>
#include <display.h>
#include <arial_bold_14.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

static USBD_HANDLE_T g_hUsb;

extern const  USBD_HW_API_T hw_api;
extern const  USBD_CORE_API_T core_api;
extern const  USBD_HID_API_T hid_api;
/* Since this example only uses HID class link functions for that class only */
static const  USBD_API_T g_usbApi = {
	&hw_api,
	&core_api,
	0,
	0,
	&hid_api,
	0,
	0,
	0x02221101,
};

const  USBD_API_T *g_pUsbApi = &g_usbApi;

DMA_TransferDescriptor_t DMA_LLI_buffer;

xSemaphoreHandle recurso_volumen; //semaforo que haremos de mutua exclusion para tomar un recurso
xSemaphoreHandle recurso_estadoteclado;
xSemaphoreHandle recurso_formadeonda;
xSemaphoreHandle recurso_filtro;
xSemaphoreHandle recurso_fci;
xSemaphoreHandle recurso_fcs;
xSemaphoreHandle recurso_attack;
xSemaphoreHandle recurso_delay;
xSemaphoreHandle recurso_over;

#define LARGO_COLA  1
xQueueHandle cola_estado; //creamos un manejador de colas global.
xQueueHandle cola_estadoUSB; //creamos un manejador de colas global.

xQueueHandle cola_formaDeOnda; //creamos un manejador de colas global.

xQueueHandle cola_volumen; //creamos un manejador de colas global.
xQueueHandle cola_fci; //creamos un manejador de colas global.
xQueueHandle cola_fcs; //creamos un manejador de colas global.
xQueueHandle cola_over; //creamos un manejador de colas global.
xQueueHandle cola_att; //creamos un manejador de colas global.
xQueueHandle cola_delay; //creamos un manejador de colas global.

xQueueHandle cola_menu_teclado; //creamos un manejador de colas global.
xQueueHandle cola_opcion_elegida; //creamos un manejador de colas global.

xQueueHandle cola_filtro;

xTaskHandle GenOnda, Encoders, Display, Botones, Teclas;
/*****************************************************************************
 * Declaracion de funciones
 ****************************************************************************/

char * itoa_mio(int entero); char * itoa_mio_porcentual(int entero);
void my_utoa(int dataIn, char* bffr, int radix);

void hostDispositivo(uint32_t id, uint32_t valor);

void hostDispositivo(uint32_t id, uint32_t valor){
	int valoraux;

	switch (id){
	case 10:{
		if (uxQueueMessagesWaiting(cola_estadoUSB)==1){
			xQueueReceive(cola_estadoUSB, &valoraux, (portTickType) 1000 );
		}
		xQueueSendToBack(cola_estadoUSB, &valor, (portTickType) 1000 );
	}break;
	case 15:{
		if(xSemaphoreTake(recurso_volumen, (portTickType) 1000) == pdTRUE){
			if (uxQueueMessagesWaiting(cola_volumen)==1){
				xQueueReceive(cola_volumen, &valoraux, (portTickType) 0 );
			}

			xQueueSendToBack(cola_volumen, &valor, (portTickType) 0 );
			xSemaphoreGive(recurso_volumen);
		}
	}break;
	case 16:{
		if(xSemaphoreTake(recurso_formadeonda, (portTickType) 1000) == pdTRUE){
			if (uxQueueMessagesWaiting(cola_formaDeOnda)==1){
				xQueueReceive(cola_formaDeOnda, &valoraux, (portTickType) 0 );
			}

			xQueueSendToBack(cola_formaDeOnda, &valor, (portTickType) 0 );
			xSemaphoreGive(recurso_formadeonda);
		}
	}break;
	case 17:{
		if(xSemaphoreTake(recurso_filtro, (portTickType) 1000) == pdTRUE){
			if (uxQueueMessagesWaiting(cola_filtro)==1){
				xQueueReceive(cola_filtro, &valoraux, (portTickType) 0 );
			}

			xQueueSendToBack(cola_filtro, &valor, (portTickType) 0 );
			xSemaphoreGive(recurso_filtro);
		}
	}break;
	case 18:{
		if(xSemaphoreTake(recurso_fcs, (portTickType) 1000) == pdTRUE){
			if (uxQueueMessagesWaiting(cola_fcs)==1){
				xQueueReceive(cola_fcs, &valoraux, (portTickType) 0 );
			}

			xQueueSendToBack(cola_fcs, &valor, (portTickType) 0 );
			xSemaphoreGive(recurso_fcs);
		}
	}break;
	case 19:{
		if(xSemaphoreTake(recurso_fci, (portTickType) 1000) == pdTRUE){
			if (uxQueueMessagesWaiting(cola_fci)==1){
				xQueueReceive(cola_fci, &valoraux, (portTickType) 0 );
			}

			xQueueSendToBack(cola_fci, &valor, (portTickType) 0 );
			xSemaphoreGive(recurso_fci);
		}
	}break;
	case 20:{
		if(xSemaphoreTake(recurso_attack, (portTickType) 1000) == pdTRUE){
			if (uxQueueMessagesWaiting(cola_att)==1){
				xQueueReceive(cola_att, &valoraux, (portTickType) 0 );
			}

			xQueueSendToBack(cola_att, &valor, (portTickType) 0 );
			xSemaphoreGive(recurso_attack);
		}
	}break;
	case 21:{
		if(xSemaphoreTake(recurso_delay, (portTickType) 1000) == pdTRUE){
			if (uxQueueMessagesWaiting(cola_delay)==1){
				xQueueReceive(cola_delay, &valoraux, (portTickType) 0 );
			}

			xQueueSendToBack(cola_delay, &valor, (portTickType) 0 );
			xSemaphoreGive(recurso_delay);
		}
	}break;
	case 22:
	{
		if(xSemaphoreTake(recurso_over, (portTickType) 1000) == pdTRUE){
			if (uxQueueMessagesWaiting(cola_over)==1){
				xQueueReceive(cola_over, &valoraux, (portTickType) 0 );
			}

			xQueueSendToBack(cola_over, &valor, (portTickType) 0 );
			xSemaphoreGive(recurso_over);
		}
	}break;
	}
}

/* Initialize pin and clocks for USB port */
static void usb_pin_clk_init(void)
{
	/* enable USB PLL and clocks */
	Chip_USB_Init();
	/* enable USB 1 port on the board */
	Board_USBD_Init(1);
}
/**
 * @brief	Handle interrupt from USB
 * @return	Nothing
 */
void USB_IRQHandler(void)
{
	USBD_API->hw->ISR(g_hUsb);
}

/* Find the address of interface descriptor for given class type. */
USB_INTERFACE_DESCRIPTOR *find_IntfDesc(const uint8_t *pDesc, uint32_t intfClass)
{
	USB_COMMON_DESCRIPTOR *pD;
	USB_INTERFACE_DESCRIPTOR *pIntfDesc = 0;
	uint32_t next_desc_adr;

	pD = (USB_COMMON_DESCRIPTOR *) pDesc;
	next_desc_adr = (uint32_t) pDesc;

	while (pD->bLength) {
		/* is it interface descriptor */
		if (pD->bDescriptorType == USB_INTERFACE_DESCRIPTOR_TYPE) {

			pIntfDesc = (USB_INTERFACE_DESCRIPTOR *) pD;
			/* did we find the right interface descriptor */
			if (pIntfDesc->bInterfaceClass == intfClass) {
				break;
			}
		}
		pIntfDesc = 0;
		next_desc_adr = (uint32_t) pD + pD->bLength;
		pD = (USB_COMMON_DESCRIPTOR *) next_desc_adr;
	}

	return pIntfDesc;
}


void Datos_display_pines_salida(void){
	for (int i=0;i<8;i++)
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, PORTS_DISPLAY_DATO(i), PINS_DISPLAY_DATO(i));
}
void Datos_display_pines_entrada(void){
	for (int i=0;i<8;i++)
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, PORTS_DISPLAY_DATO(i), PINS_DISPLAY_DATO(i));
}
//hacer esta funcion para mapear un dato en los pines del lpc
void Ingresar_Comando_Datos(uint32_t cmd){
	int i;

	Datos_display_pines_salida(); //por las dudas

	for (i = 0; i < 8; i++)
			Chip_GPIO_SetPinState(LPC_GPIO, PORTS_DISPLAY_DATO(i), PINS_DISPLAY_DATO(i), (cmd & (0x01 << i)));

}
void ks0108Enable(void) {
	//LCD_CMD_PORT |= 0x01 << EN;						// EN high level width: min. 450ns
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT_DISPLAY_EN, PIN_DISPLAY_EN);

	asm volatile(
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			::);
	//for(i=0; i<8; i++); //este delay deberia ser mayor a 450nS

	//LCD_CMD_PORT &= ~(0x01 << EN);
	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_EN, PIN_DISPLAY_EN);

	//for(i=0; i<8; i++);			// a little delay loop (faster than reading the busy flag)
	//for(i=0; i<8; i++); //se calculo a 20 veces el anterior
	asm volatile(
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			::);


	//for (i=0;i < 30; i++);
}
void Datos_display_poner_a_cero(void){

	Datos_display_pines_salida(); //puede ser redundante, esta por las dudas

	//Ponemos un 0 en los pines de datos
	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_D0, PIN_DISPLAY_D0);
	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_D1, PIN_DISPLAY_D1);
	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_D2, PIN_DISPLAY_D2);
	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_D3, PIN_DISPLAY_D3);
	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_D4, PIN_DISPLAY_D4);
	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_D5, PIN_DISPLAY_D5);
	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_D6, PIN_DISPLAY_D6);
	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_D7, PIN_DISPLAY_D7);

}
uint32_t Leer_Datos(void){
	uint32_t dato=0;

	uint32_t dato0;
	uint32_t dato1;
	uint32_t dato2;
	uint32_t dato3;
	uint32_t dato4;
	uint32_t dato5;
	uint32_t dato6;
	uint32_t dato7;

	Datos_display_pines_entrada();

	dato0 = Chip_GPIO_GetPinState(LPC_GPIO, PORT_DISPLAY_D0, PIN_DISPLAY_D0);
	dato1 = Chip_GPIO_GetPinState(LPC_GPIO, PORT_DISPLAY_D1, PIN_DISPLAY_D1);
	dato2 = Chip_GPIO_GetPinState(LPC_GPIO, PORT_DISPLAY_D2, PIN_DISPLAY_D2);
	dato3 = Chip_GPIO_GetPinState(LPC_GPIO, PORT_DISPLAY_D3, PIN_DISPLAY_D3);
	dato4 = Chip_GPIO_GetPinState(LPC_GPIO, PORT_DISPLAY_D4, PIN_DISPLAY_D4);
	dato5 = Chip_GPIO_GetPinState(LPC_GPIO, PORT_DISPLAY_D5, PIN_DISPLAY_D5);
	dato6 = Chip_GPIO_GetPinState(LPC_GPIO, PORT_DISPLAY_D6, PIN_DISPLAY_D6);
	dato7 = Chip_GPIO_GetPinState(LPC_GPIO, PORT_DISPLAY_D7, PIN_DISPLAY_D7);

	dato |= ((dato7<<7)|(dato6<<6)|(dato5<<5)|(dato4<<4)|(dato3<<3)|(dato2<<2)|(dato1<<1)|(dato0<<0));

	return dato;
}

// Funcion mia del display
void ks0108FillImage(uint32_t x, uint32_t y, uint32_t width, uint32_t height, const uint32_t* grafico) {
	uint32_t pageOffset, i, data=0x00, displayData;

	//height++; //saco esto para fixear y hacer que pongas el height posta (si mide 9 pones 9)
	//width --; //idem anterior pero hay que restarle ahora.

	//uint32_t color;
	int ancho, alto, columna, z;
	int altoaux;
	uint32_t offset, paginas=1;

//	pageOffset = y%8;
//	y -= pageOffset;
//	mask = 0xFF;
//	if(height < 8-pageOffset) {
//		mask >>= (8-height);
//		h = height;
//	} else {
//		h = 8-pageOffset;
//	}
//	mask <<= pageOffset;

//	if (height==0)
//	{
//		ks0108GotoXY(x, y);
//		for (i=0;i<111;i++){
//			data = 0xF0;
//			InvertirEnX(data);
//			ks0108WriteData(data); //Esto escribe el dato desde el punto que esta hacia la derecha y mueve el cursor hacia abajo
//		}
//	}

	//si el grafico tiene 3x15 mi variable de repeticiones de "pagina" sera 2,
	//mientras que el offset estaria en 7 (15%8)

	//ancho=128; //estaba en 128
	ancho = width;
	//alto=64; //estaba en 64
	alto = height;

	altoaux = alto;
	while((altoaux-8) > 0){
		altoaux -= 8;
		paginas ++;
	}
	offset = alto - (paginas-1)*8;


	if (height==28){
		for(z=0;z<paginas;z++){ //z tendra el valor de la pagina
			ks0108GotoXY(x, y+(z*8));
			for(columna=0;columna<ancho;columna++){
				data=0;

				//este if es para que el offset nada mas rija en la ultima pagina de impresion
				if(z == (paginas-1)){
					for (i=0;i<offset;i++){
						data|=(grafico[columna+((i+(z*8))*ancho)]<<(7-i));
					}
				}else{
//					for (i=0;i<8;i++){
//						data|=(grafico[columna+((i+(z*8))*ancho)]<<(7-i));
//					}
					//esto lo hago para probar a ver si tarda menos en imprimir en pantalla
					data|=(grafico[columna+((0+(z*8))*ancho)]<<(7-0));
					data|=(grafico[columna+((1+(z*8))*ancho)]<<(7-1));
					data|=(grafico[columna+((2+(z*8))*ancho)]<<(7-2));
					data|=(grafico[columna+((3+(z*8))*ancho)]<<(7-3));
					data|=(grafico[columna+((4+(z*8))*ancho)]<<(7-4));
					data|=(grafico[columna+((5+(z*8))*ancho)]<<(7-5));
					data|=(grafico[columna+((6+(z*8))*ancho)]<<(7-6));
					data|=(grafico[columna+((7+(z*8))*ancho)]<<(7-7));
				}
				displayData = ks0108ReadData();
				InvertirEnX(displayData);

				data|=displayData;

				InvertirEnX(data); //esto se hace para standarizar la salida a como responde el display el comando readdata
				ks0108WriteData(data); //Esto escribe el dato desde el punto que esta hacia la derecha y mueve el cursor hacia abajo
			}
		}
	}
	if (height==0)
	{

//		data|=(ks0108ImageRead(ks0108Image+columna+(0*ancho))<<7);
//		data|=(ks0108ImageRead(ks0108Image+columna+(1*ancho))<<6);
//		data|=(ks0108ImageRead(ks0108Image+columna+(2*ancho))<<5);
//		data|=(ks0108ImageRead(ks0108Image+columna+(3*ancho))<<4);
//		data|=(ks0108ImageRead(ks0108Image+columna+(4*ancho))<<3);
//		data|=(ks0108ImageRead(ks0108Image+columna+(5*ancho))<<2);
//		data|=(ks0108ImageRead(ks0108Image+columna+(6*ancho))<<1);
//		data|=(ks0108ImageRead(ks0108Image+columna+(7*ancho))<<0);

		//InvertirEnX(data); //esto se hace para standarizar la salida a como responde el display el comando readdata
		//ks0108WriteData(data); //Esto escribe el dato desde el punto que esta hacia la derecha y mueve el cursor hacia abajo

		for(z=0;z<paginas;z++){ //z tendra el valor de la pagina
			ks0108GotoXY(x, y+(z*8));
			for(columna=0;columna<ancho;columna++){
				data=0;

				//este if es para que el offset nada mas rija en la ultima pagina de impresion
				if(z == (paginas-1)){
					for (i=0;i<offset;i++){
						data|=(grafico[columna+((i+(z*8))*ancho)]<<(7-i));
					}
				}else{
//					for (i=0;i<8;i++){
//						data|=(grafico[columna+((i+(z*8))*ancho)]<<(7-i));
//					}
					//esto lo hago para probar a ver si tarda menos en imprimir en pantalla
					data|=(grafico[columna+((0+(z*8))*ancho)]<<(7-0));
					data|=(grafico[columna+((1+(z*8))*ancho)]<<(7-1));
					data|=(grafico[columna+((2+(z*8))*ancho)]<<(7-2));
					data|=(grafico[columna+((3+(z*8))*ancho)]<<(7-3));
					data|=(grafico[columna+((4+(z*8))*ancho)]<<(7-4));
					data|=(grafico[columna+((5+(z*8))*ancho)]<<(7-5));
					data|=(grafico[columna+((6+(z*8))*ancho)]<<(7-6));
					data|=(grafico[columna+((7+(z*8))*ancho)]<<(7-7));
				}
				displayData = ks0108ReadData();
				InvertirEnX(displayData);

				data|=displayData;

				InvertirEnX(data); //esto se hace para standarizar la salida a como responde el display el comando readdata
				ks0108WriteData(data); //Esto escribe el dato desde el punto que esta hacia la derecha y mueve el cursor hacia abajo
			}
		}
	}

	if (height==1)
	{
		ks0108GotoXY(x, y);
		displayData = ks0108ReadData();
		data = 0xF0;

		//data|=displayData;

		InvertirEnX(data);
		ks0108WriteData(data);
	}
	if (height==2)
	{
		ks0108GotoXY(x, y);
		displayData = ks0108ReadData();
		//data = graf_cuadrado[0];
		columna=0;
		ancho=1;

		data = 0x00;
		data|=graf_cuadrado[columna+(0*ancho)]<<7;
		data|=graf_cuadrado[columna+(1*ancho)]<<6;
		data|=graf_cuadrado[columna+(2*ancho)]<<5;
		data|=graf_cuadrado[columna+(3*ancho)]<<4;
		data|=graf_cuadrado[columna+(4*ancho)]<<3;
		data|=graf_cuadrado[columna+(5*ancho)]<<2;
		data|=graf_cuadrado[columna+(6*ancho)]<<1;
		data|=graf_cuadrado[columna+(7*ancho)]<<0;

		//data|=displayData;

		InvertirEnX(data);
		ks0108WriteData(data);
	}
}
//FIN FUNCION MIA--------------------------




int ks0108PutChar(char c) {

	uint8_t width = 0;
	uint8_t height = Arial_Bold_14[FONT_HEIGHT];
	uint8_t bytes = (height+7)/8;

	uint8_t firstChar = Arial_Bold_14[FONT_FIRST_CHAR];
	uint8_t charCount = Arial_Bold_14[FONT_CHAR_COUNT];

	uint16_t index = 0;
	//uint32_t x = lcdCoord.x, y = lcdCoord.y;
	uint8_t x, y;
	lcdCoord lcdCoord;

	if (uxQueueMessagesWaiting(cola_lcdCoord)==1){
		xQueuePeek( cola_lcdCoord, &lcdCoord, (portTickType) 0 );
	}else{
		return 1;
	}
	x = lcdCoord.x;
	y = lcdCoord.y;

	//hay 96 letras que se imprimen con el programa (arial_bold_14.h)
	//cada una tiene su width
	if(c < firstChar || c >= (firstChar+charCount)) {
		return 1;
	}
	c-= firstChar;

	// read width data, to get the index
	for(uint8_t i=0; i<c; i++) {
		index += Arial_Bold_14[FONT_WIDTH_TABLE+i];
	}
	index = index*bytes+charCount+FONT_WIDTH_TABLE;
	width = Arial_Bold_14[FONT_WIDTH_TABLE+c];

	// last but not least, draw the character
	for(uint8_t i=0; i<bytes; i++) {
		uint8_t page = i*width;
		for(uint8_t j=0; j<width; j++) {
			uint8_t data = Arial_Bold_14[index+page+j];

			if(height < (i+1)*8) {
				data >>= (i+1)*8-height;
			}

			ks0108WriteData(data);
		}
		ks0108WriteData(0x00);
		ks0108GotoXY(x, lcdCoord.y+8);

	}
	ks0108GotoXY(x+width+1, y);

	return 0;
}

int ks0108PutChar_OLD(char c) {

	uint8_t width = 0;
	uint8_t height = Arial_Bold_14[FONT_HEIGHT];
	uint8_t bytes = (height+7)/8;

	uint8_t firstChar = Arial_Bold_14[FONT_FIRST_CHAR];
	uint8_t charCount = Arial_Bold_14[FONT_CHAR_COUNT];

	uint16_t index = 0;
	//uint32_t x = lcdCoord.x, y = lcdCoord.y;
	uint8_t x, y;
	lcdCoord lcdCoord;

	if (uxQueueMessagesWaiting(cola_lcdCoord)==1){
		xQueuePeek( cola_lcdCoord, &lcdCoord, (portTickType) 0 );
	}else{
		return 1;
	}
	x = lcdCoord.x;
	y = lcdCoord.y;

	//ks0108GotoXY(x, y-y%8);					// read data from display memory

	//hay 96 letras que se imprimen con la tabla en arial_bold_14.h
	//cada una tiene su width
	if(c < firstChar || c >= (firstChar+charCount)) {
		return 1;
	}
	c-= firstChar;

	// read width data, to get the index
	for(uint8_t i=0; i<c; i++) {
		index += Arial_Bold_14[FONT_WIDTH_TABLE+i];
	}
	index = index*bytes+charCount+FONT_WIDTH_TABLE;
	width = Arial_Bold_14[FONT_WIDTH_TABLE+c];

	// last but not least, draw the character
	/////REVISAR YA QUE PARA i=0 VA JOYA, EL TEMA ES CUANDO i=1 ya que al hacer la segunda pasada
	/////la pagina como que se queda desfasada (ver con F6 para mas detalles)
	///// y sobreescribe todo lo anterior, lo recomendable seria hacer 2 pasadas
	///// una para la primer pagina (primera parte sin el if (y%8>0)
	///// y otra para la segunda pagina siempre y cuando bytes sea 2 o haya quedado letra para imprimir
	for(uint8_t i=0; i<bytes; i++) {
		uint8_t page = i*width;
		for(uint8_t j=0; j<width; j++) {
			uint8_t data = Arial_Bold_14[index+page+j];

			if(height < (i+1)*8) {
				data >>= (i+1)*8-height;
			}
//			y = 1;
			ks0108GotoXY(x+j,y-y%8);
			data <<= y%8;
			ks0108WriteData(data);
			data = Arial_Bold_14[index+page+j];
			if (y%8 > 0){
				ks0108GotoXY(x+j,y+8-y%8);
				data >>= (8-y%8);
				ks0108WriteData(data);
			}

			//data <<= (y%8);				// set dot

//			if(ks0108FontColor == BLACK) {
//				ks0108WriteData(data);
//			} else {
//				ks0108WriteData(~data);
//			}
			//ks0108WriteData(data);
		}
		// 1px gap between chars
//		if(ks0108FontColor == BLACK) {
//			ks0108WriteData(0x00);
//		} else {
//			ks0108WriteData(0xFF);
//		}
		ks0108WriteData(0x00);
		ks0108GotoXY(x, lcdCoord.y+8);

	}
	ks0108GotoXY(x+width+1, y);

	return 0;
}
void ks0108Puts(char* str) {

	lcdCoord lcdCoord;
	int x;

	if (uxQueueMessagesWaiting(cola_lcdCoord)==1){
		xQueuePeek( cola_lcdCoord, &lcdCoord, (portTickType) 0 );
	}else{
		return;
	}
	x = lcdCoord.x;

	while(*str != 0) {
		if(*str == '\n') {
			//ks0108GotoXY(x, lcdCoord.y+Arial_Bold_14[FONT_HEIGHT]);
			ks0108GotoXY(x, lcdCoord.y+Arial_Bold_14[FONT_HEIGHT]+lcdCoord.y%8);
		} else {
			ks0108PutChar(*str);
		}
		str++;
	}
}


//hay que inicializar los pines del display (los de control como salida y los de datos dinamicamente)
void ks0108WriteCommand(uint32_t cmd, uint32_t chip) {
	if(chip == CHIP1) {
		// deselect chip 2
		Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_CSEL2, PIN_DISPLAY_CSEL2);

		// select chip 1
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT_DISPLAY_CSEL1, PIN_DISPLAY_CSEL1);
	} else if(chip == CHIP2) {
		// deselect chip 1
		Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_CSEL1, PIN_DISPLAY_CSEL1);

		// select chip 2
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT_DISPLAY_CSEL2, PIN_DISPLAY_CSEL2);
	}

	// D/I = 0
	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_D_I, PIN_DISPLAY_D_I);

	// R/W = 0
	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_R_W, PIN_DISPLAY_R_W);

	Ingresar_Comando_Datos(cmd);

	ks0108Enable();									// enable
	Datos_display_poner_a_cero();

}
void ks0108GotoXY(uint32_t x, uint32_t y) {
	uint32_t chip = CHIP1, cmd;

	lcdCoord lcdCoord, auxlcdCoord; //el aux es para recibir la cola sin importar lo que tenia, ya que despues se sobreescribira

	if(x > 127) x = 0;								// ensure that coordinates are legal
	if(y > 63)  y = 0;

	lcdCoord.x = x;								// save new coordinates
	lcdCoord.y = y;
	lcdCoord.page = y/8;

	//esto es para recibir si habia un valor y "resetear" la cola, para luego ponerle el valor que tiene que ir
	if (uxQueueMessagesWaiting(cola_lcdCoord)==1){
		xQueueReceive( cola_lcdCoord, &auxlcdCoord, (portTickType) 0 );
	}
	xQueueSendToBack( cola_lcdCoord, &lcdCoord, (portTickType) 0);

	if(x >= 64) {									// select the right chip
		x -= 64;
		chip = CHIP2;
	}
	cmd = LCD_SET_ADD | x;
	ks0108WriteCommand(cmd, chip);					// set x address on active chip

	cmd = LCD_SET_PAGE | lcdCoord.page;			// set y address on both chips
	ks0108WriteCommand(cmd, CHIP1);
	ks0108WriteCommand(cmd, CHIP2);
}
uint32_t ks0108DoReadData(uint32_t first) {
	uint32_t data;

	lcdCoord lcdCoord;

	if (uxQueueMessagesWaiting(cola_lcdCoord)==1){
		xQueueReceive( cola_lcdCoord, &lcdCoord, (portTickType) 0 );
	}else{
		return 1; //para que deje de ejecutarse si la cola no tiene valor
	}

	if(lcdCoord.x < 64) {
		Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_CSEL2, PIN_DISPLAY_CSEL2);
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT_DISPLAY_CSEL1, PIN_DISPLAY_CSEL1);
	} else if(lcdCoord.x >= 64) {
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT_DISPLAY_CSEL2, PIN_DISPLAY_CSEL2);
		Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_CSEL1, PIN_DISPLAY_CSEL1);
	}
	if(lcdCoord.x == 64 && first) {				// chip2 X-address = 0
		ks0108WriteCommand(LCD_SET_ADD, CHIP2); 	// wuff wuff
	}

	Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT_DISPLAY_D_I, PIN_DISPLAY_D_I);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT_DISPLAY_R_W, PIN_DISPLAY_R_W);


	//LCD_CMD_PORT |= 0x01 << EN;						// EN high level width: min. 450ns
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT_DISPLAY_EN, PIN_DISPLAY_EN);

	asm volatile("nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
			::);

	data = Leer_Datos();

	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_EN, PIN_DISPLAY_EN);

	Datos_display_pines_salida();

	ks0108GotoXY(lcdCoord.x, lcdCoord.y);

	return data;
}

uint32_t ks0108ReadData(void) {
	ks0108DoReadData(1);							// dummy read
	return ks0108DoReadData(0);						// "real" read
}

void ks0108WriteData(uint32_t data) {
	uint32_t displayData, yOffset;

	lcdCoord lcdCoord;

	if (uxQueueMessagesWaiting(cola_lcdCoord)==1){
		xQueueReceive( cola_lcdCoord, &lcdCoord, (portTickType) 0 );
	}else{
		return; //para que deje de ejecutarse si la cola no tiene valor
	}

	if(lcdCoord.x >= 128)
		return;

	if(lcdCoord.x < 64) {
		Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_CSEL2, PIN_DISPLAY_CSEL2);
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT_DISPLAY_CSEL1, PIN_DISPLAY_CSEL1);
	} else if(lcdCoord.x >= 64) {
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT_DISPLAY_CSEL2, PIN_DISPLAY_CSEL2);
		Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_CSEL1, PIN_DISPLAY_CSEL1);
	}
	if(lcdCoord.x == 64)							// chip2 X-address = 0
		ks0108WriteCommand(LCD_SET_ADD, CHIP2);

	Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORT_DISPLAY_D_I, PIN_DISPLAY_D_I);
	Chip_GPIO_SetPinOutLow(LPC_GPIO, PORT_DISPLAY_R_W, PIN_DISPLAY_R_W);

	Datos_display_pines_salida();

	yOffset = lcdCoord.y%8;
	if(yOffset != 0) {
		// first page
		displayData = ks0108ReadData();

		displayData |= data << yOffset;

		Ingresar_Comando_Datos(displayData);

		ks0108Enable();								// enable

		// second page
		ks0108GotoXY(lcdCoord.x, lcdCoord.y+8);

		displayData = ks0108ReadData();

		displayData |= data >> (8-yOffset);
		Ingresar_Comando_Datos(displayData);

		ks0108Enable();								// enable

		ks0108GotoXY(lcdCoord.x+1, lcdCoord.y-8);
	} else {


		////LCD_DATA_OUT = data;						// write data
		//LCD_DATA_OUT1 |= (data & 0x0F);
		//LCD_DATA_OUT1 &=~(~(data) & 0x0F);
		//LCD_DATA_OUT2 |= (data & 0xF0);
		//LCD_DATA_OUT2 &=~(~(data) & 0xF0);
		Ingresar_Comando_Datos(data);
		//Ingresar_Comando_Datos(0b00000000);

		ks0108Enable();								// enable
		lcdCoord.x++;

	}
	//envio la cola en esta etapa ya que si la enviamos justo despues del lcdCoord++ hay un "if" mediante y me puede causar problemas

	xQueueSendToBack( cola_lcdCoord, &lcdCoord, (portTickType) 0 );

	////LCD_DATA_OUT = 0x00;
	//LCD_DATA_OUT1 &=~ ((1<<0)|(1<<1)|(1<<2)|(1<<3));
	//LCD_DATA_OUT2 &=~ ((1<<4)|(1<<5)|(1<<6)|(1<<7));
	Datos_display_poner_a_cero();
}
void ks0108DrawRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color) {
	ks0108DrawHoriLine(x, y, width, color);				// top
	ks0108DrawHoriLine(x, y+height, width, color);		// bottom
	ks0108DrawVertLine(x, y, height, color);			// left
	ks0108DrawVertLine(x+width, y, height, color);		// right
}


void ks0108FillRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color) {
	uint32_t mask, pageOffset, h, i, data;
	height++;

	pageOffset = y%8;
	y -= pageOffset;
	mask = 0xFF;
	if(height < 8-pageOffset) {
		mask >>= (8-height);
		h = height;
	} else {
		h = 8-pageOffset;
	}
	mask <<= pageOffset;

	ks0108GotoXY(x, y);
	for(i=0; i<=width; i++) {
		data = ks0108ReadData();

		if(color == BLACK) {
			data |= mask;
		} else {
			data &= ~mask;
		}

		ks0108WriteData(data);
	}

	while(h+8 <= height) {
		h += 8;
		y += 8;
		ks0108GotoXY(x, y);

		for(i=0; i<=width; i++) {
			ks0108WriteData(color);
		}
	}

	if(h < height) {
		mask = ~(0xFF << (height-h));
		ks0108GotoXY(x, y+8);

		for(i=0; i<=width; i++) {
			data = ks0108ReadData();

			if(color == BLACK) {
				data |= mask;
			} else {
				data &= ~mask;
			}

			ks0108WriteData(data);
		}
	}
}
void ks0108SetDot(uint32_t x, uint32_t y, uint32_t color) {
	uint32_t data;

	ks0108GotoXY(x, y-y%8);					// read data from display memory
	data = ks0108ReadData();

	if(color == BLACK) {
		data |= 0x01 << (y%8);				// set dot
	} else {
		data &= ~(0x01 << (y%8));			// clear dot
	}

	ks0108WriteData(data);					// write data back to display
	//ks0108WriteData(0b11111111);
}



/*****************************************************************************
 * Funciones
 ****************************************************************************/

char * itoa_mio_porcentual(int entero){
	if (entero == 0){ return "  0%";}
	if (entero == 1){ return "  1%";}
	if (entero == 2){ return "  2%";}
	if (entero == 3){ return "  3%";}
	if (entero == 4){ return "  4%";}
	if (entero == 5){ return "  5%";}
	if (entero == 6){ return "  6%";}
	if (entero == 7){ return "  7%";}
	if (entero == 8){ return "  8%";}
	if (entero == 9){ return "  9%";}
	if (entero == 10){ return " 10%";}

	if (entero == 11){ return " 11%";}
	if (entero == 12){ return " 12%";}
	if (entero == 13){ return " 13%";}
	if (entero == 14){ return " 14%";}
	if (entero == 15){ return " 15%";}
	if (entero == 16){ return " 16%";}
	if (entero == 17){ return " 17%";}
	if (entero == 18){ return " 18%";}
	if (entero == 19){ return " 19%";}
	if (entero == 20){ return " 20%";}

	if (entero == 21){ return " 21%";}
	if (entero == 22){ return " 22%";}
	if (entero == 23){ return " 23%";}
	if (entero == 24){ return " 24%";}
	if (entero == 25){ return " 25%";}
	if (entero == 26){ return " 26%";}
	if (entero == 27){ return " 27%";}
	if (entero == 28){ return " 28%";}
	if (entero == 29){ return " 29%";}
	if (entero == 30){ return " 30%";}

	if (entero == 31){ return " 31%";}
	if (entero == 32){ return " 32%";}
	if (entero == 33){ return " 33%";}
	if (entero == 34){ return " 34%";}
	if (entero == 35){ return " 35%";}
	if (entero == 36){ return " 36%";}
	if (entero == 37){ return " 37%";}
	if (entero == 38){ return " 38%";}
	if (entero == 39){ return " 39%";}
	if (entero == 40){ return " 40%";}

	if (entero == 41){ return " 41%";}
	if (entero == 42){ return " 42%";}
	if (entero == 43){ return " 43%";}
	if (entero == 44){ return " 44%";}
	if (entero == 45){ return " 45%";}
	if (entero == 46){ return " 46%";}
	if (entero == 47){ return " 47%";}
	if (entero == 48){ return " 48%";}
	if (entero == 49){ return " 49%";}
	if (entero == 50){ return " 50%";}

	if (entero == 51){ return " 51%";}
	if (entero == 52){ return " 52%";}
	if (entero == 53){ return " 53%";}
	if (entero == 54){ return " 54%";}
	if (entero == 55){ return " 55%";}
	if (entero == 56){ return " 56%";}
	if (entero == 57){ return " 57%";}
	if (entero == 58){ return " 58%";}
	if (entero == 59){ return " 59%";}
	if (entero == 60){ return " 60%";}

	if (entero == 61){ return " 61%";}
	if (entero == 62){ return " 62%";}
	if (entero == 63){ return " 63%";}
	if (entero == 64){ return " 64%";}
	if (entero == 65){ return " 65%";}
	if (entero == 66){ return " 66%";}
	if (entero == 67){ return " 67%";}
	if (entero == 68){ return " 68%";}
	if (entero == 69){ return " 69%";}
	if (entero == 70){ return " 70%";}

	if (entero == 71){ return " 71%";}
	if (entero == 72){ return " 72%";}
	if (entero == 73){ return " 73%";}
	if (entero == 74){ return " 74%";}
	if (entero == 75){ return " 75%";}
	if (entero == 76){ return " 76%";}
	if (entero == 77){ return " 77%";}
	if (entero == 78){ return " 78%";}
	if (entero == 79){ return " 79%";}
	if (entero == 80){ return " 80%";}

	if (entero == 81){ return " 81%";}
	if (entero == 82){ return " 82%";}
	if (entero == 83){ return " 83%";}
	if (entero == 84){ return " 84%";}
	if (entero == 85){ return " 85%";}
	if (entero == 86){ return " 86%";}
	if (entero == 87){ return " 87%";}
	if (entero == 88){ return " 88%";}
	if (entero == 89){ return " 89%";}
	if (entero == 90){ return " 90%";}

	if (entero == 91){ return " 91%";}
	if (entero == 92){ return " 92%";}
	if (entero == 93){ return " 93%";}
	if (entero == 94){ return " 94%";}
	if (entero == 95){ return " 95%";}
	if (entero == 96){ return " 96%";}
	if (entero == 97){ return " 97%";}
	if (entero == 98){ return " 98%";}
	if (entero == 99){ return " 99%";}
	if (entero == 100){ return "100%";}
	return "  0%";
}
void my_utoa(int dataIn, char* bffr, int radix){
	int temp_dataIn;
	int stringLen=3;

	temp_dataIn = dataIn;

//	while ((int)temp_dataIn/radix != 0){
//		temp_dataIn = (int)temp_dataIn/radix;
//		stringLen++;
//	}
//	//printf("stringLen = %d\n", stringLen);
//	temp_dataIn = dataIn;
	do{
		*(bffr+stringLen-1) = (temp_dataIn%radix)+'0';
		temp_dataIn = (int) temp_dataIn / radix;
	}while(stringLen--);
}
char * itoa_mio(int entero){

	if (entero == 0){ return "  0";}
	if (entero == 1){ return "  1";}
	if (entero == 2){ return "  2";}
	if (entero == 3){ return "  3";}
	if (entero == 4){ return "  4";}
	if (entero == 5){ return "  5";}
	if (entero == 6){ return "  6";}
	if (entero == 7){ return "  7";}
	if (entero == 8){ return "  8";}
	if (entero == 9){ return "  9";}
	if (entero == 10){ return " 10";}

	if (entero == 11){ return " 11";}
	if (entero == 12){ return " 12";}
	if (entero == 13){ return " 13";}
	if (entero == 14){ return " 14";}
	if (entero == 15){ return " 15";}
	if (entero == 16){ return " 16";}
	if (entero == 17){ return " 17";}
	if (entero == 18){ return " 18";}
	if (entero == 19){ return " 19";}
	if (entero == 20){ return " 20";}

	if (entero == 21){ return " 21";}
	if (entero == 22){ return " 22";}
	if (entero == 23){ return " 23";}
	if (entero == 24){ return " 24";}
	if (entero == 25){ return " 25";}
	if (entero == 26){ return " 26";}
	if (entero == 27){ return " 27";}
	if (entero == 28){ return " 28";}
	if (entero == 29){ return " 29";}
	if (entero == 30){ return " 30";}

	if (entero == 31){ return " 31";}
	if (entero == 32){ return " 32";}
	if (entero == 33){ return " 33";}
	if (entero == 34){ return " 34";}
	if (entero == 35){ return " 35";}
	if (entero == 36){ return " 36";}
	if (entero == 37){ return " 37";}
	if (entero == 38){ return " 38";}
	if (entero == 39){ return " 39";}
	if (entero == 40){ return " 40";}

	if (entero == 41){ return " 41";}
	if (entero == 42){ return " 42";}
	if (entero == 43){ return " 43";}
	if (entero == 44){ return " 44";}
	if (entero == 45){ return " 45";}
	if (entero == 46){ return " 46";}
	if (entero == 47){ return " 47";}
	if (entero == 48){ return " 48";}
	if (entero == 49){ return " 49";}
	if (entero == 50){ return " 50";}

	if (entero == 51){ return " 51";}
	if (entero == 52){ return " 52";}
	if (entero == 53){ return " 53";}
	if (entero == 54){ return " 54";}
	if (entero == 55){ return " 55";}
	if (entero == 56){ return " 56";}
	if (entero == 57){ return " 57";}
	if (entero == 58){ return " 58";}
	if (entero == 59){ return " 59";}
	if (entero == 60){ return " 60";}

	if (entero == 61){ return " 61";}
	if (entero == 62){ return " 62";}
	if (entero == 63){ return " 63";}
	if (entero == 64){ return " 64";}
	if (entero == 65){ return " 65";}
	if (entero == 66){ return " 66";}
	if (entero == 67){ return " 67";}
	if (entero == 68){ return " 68";}
	if (entero == 69){ return " 69";}
	if (entero == 70){ return " 70";}

	if (entero == 71){ return " 71";}
	if (entero == 72){ return " 72";}
	if (entero == 73){ return " 73";}
	if (entero == 74){ return " 74";}
	if (entero == 75){ return " 75";}
	if (entero == 76){ return " 76";}
	if (entero == 77){ return " 77";}
	if (entero == 78){ return " 78";}
	if (entero == 79){ return " 79";}
	if (entero == 80){ return " 80";}

	if (entero == 81){ return " 81";}
	if (entero == 82){ return " 82";}
	if (entero == 83){ return " 83";}
	if (entero == 84){ return " 84";}
	if (entero == 85){ return " 85";}
	if (entero == 86){ return " 86";}
	if (entero == 87){ return " 87";}
	if (entero == 88){ return " 88";}
	if (entero == 89){ return " 89";}
	if (entero == 90){ return " 90";}

	if (entero == 91){ return " 91";}
	if (entero == 92){ return " 92";}
	if (entero == 93){ return " 93";}
	if (entero == 94){ return " 94";}
	if (entero == 95){ return " 95";}
	if (entero == 96){ return " 96";}
	if (entero == 97){ return " 97";}
	if (entero == 98){ return " 98";}
	if (entero == 99){ return " 99";}
	if (entero == 100){ return "100";}
	return "  0";
}
char * itoa_mio_seg(int entero){
	if (entero == 0){ return "0.0 seg";}
	if (entero == 1){ return "0.1 seg";}
	if (entero == 2){ return "0.2 seg";}
	if (entero == 3){ return "0.3 seg";}
	if (entero == 4){ return "0.4 seg";}
	if (entero == 5){ return "0.5 seg";}
	if (entero == 6){ return "0.6 seg";}
	if (entero == 7){ return "0.7 seg";}
	if (entero == 8){ return "0.8 seg";}
	if (entero == 9){ return "0.9 seg";}
	if (entero == 10){ return "1.0 seg";}

	if (entero == 11){ return "1.1 seg";}
	if (entero == 12){ return "1.2 seg";}
	if (entero == 13){ return "1.3 seg";}
	if (entero == 14){ return "1.4 seg";}
	if (entero == 15){ return "1.5 seg";}
	if (entero == 16){ return "1.6 seg";}
	if (entero == 17){ return "1.7 seg";}
	if (entero == 18){ return "1.8 seg";}
	if (entero == 19){ return "1.9 seg";}
	if (entero == 20){ return "2.0 seg";}

	if (entero == 21){ return "2.1 seg";}
	if (entero == 22){ return "2.2 seg";}
	if (entero == 23){ return "2.3 seg";}
	if (entero == 24){ return "2.4 seg";}
	if (entero == 25){ return "2.5 seg";}
	if (entero == 26){ return "2.6 seg";}
	if (entero == 27){ return "2.7 seg";}
	if (entero == 28){ return "2.8 seg";}
	if (entero == 29){ return "2.9 seg";}
	if (entero == 30){ return "3.0 seg";}

	if (entero == 31){ return "3.1 seg";}
	if (entero == 32){ return "3.2 seg";}
	if (entero == 33){ return "3.3 seg";}
	if (entero == 34){ return "3.4 seg";}
	if (entero == 35){ return "3.5 seg";}
	if (entero == 36){ return "3.6 seg";}
	if (entero == 37){ return "3.7 seg";}
	if (entero == 38){ return "3.8 seg";}
	if (entero == 39){ return "3.9 seg";}
	if (entero == 40){ return "4.0 seg";}

	if (entero == 41){ return "4.1 seg";}
	if (entero == 42){ return "4.2 seg";}
	if (entero == 43){ return "4.3 seg";}
	if (entero == 44){ return "4.4 seg";}
	if (entero == 45){ return "4.5 seg";}
	if (entero == 46){ return "4.6 seg";}
	if (entero == 47){ return "4.7 seg";}
	if (entero == 48){ return "4.8 seg";}
	if (entero == 49){ return "4.9 seg";}
	if (entero == 50){ return "5.0 seg";}
	return "0.0 seg";
}

/*****************************************************************************
 * Tareas
 ****************************************************************************/


static void vInicializarUSB(void *pvParameters) {

	USBD_API_INIT_PARAM_T usb_param;
	USB_CORE_DESCS_T desc;
	ErrorCode_t ret = LPC_OK;

	/* Initialize board and chip */
	SystemCoreClockUpdate();
	Board_Init();

	/* enable clocks and pinmux */
	usb_pin_clk_init();

	/* initialize call back structures */
	memset((void *) &usb_param, 0, sizeof(USBD_API_INIT_PARAM_T));
	usb_param.usb_reg_base = LPC_USB_BASE + 0x200;
	usb_param.max_num_ep = 2;
	usb_param.mem_base = USB_STACK_MEM_BASE;
	usb_param.mem_size = USB_STACK_MEM_SIZE;

	/* Set the USB descriptors */
	desc.device_desc = (uint8_t *) USB_DeviceDescriptor;
	desc.string_desc = (uint8_t *) USB_StringDescriptor;

	/* Note, to pass USBCV test full-speed only devices should have both
	 * descriptor arrays point to same location and device_qualifier set
	 * to 0.
	 */
	desc.high_speed_desc = USB_FsConfigDescriptor;
	desc.full_speed_desc = USB_FsConfigDescriptor;
	desc.device_qualifier = 0;

	/* USB Initialization */
	ret = USBD_API->hw->Init(&g_hUsb, &desc, &usb_param);
	if (ret == LPC_OK) {

		ret = usb_hid_init(g_hUsb,
			(USB_INTERFACE_DESCRIPTOR *) &USB_FsConfigDescriptor[sizeof(USB_CONFIGURATION_DESCRIPTOR)],
			&usb_param.mem_base, &usb_param.mem_size);
		if (ret == LPC_OK) {
			/*  enable USB interrupts */
			NVIC_EnableIRQ(USB_IRQn);
			/* now connect */
			USBD_API->hw->Connect(g_hUsb, 1);
		}
	}

	while (1) {
		vTaskDelete(NULL);
	}
}

static void vInicializarColas(void *pvParameters) {


	int auxiliar;

	if (xSemaphoreTake(recurso_volumen, (portTickType) 0) == pdTRUE){
		if (uxQueueMessagesWaiting(cola_volumen) == 1)
			xQueueReceive(cola_volumen, &auxiliar, (portTickType) 0);
		auxiliar = VOLUMEN_INICIAL;
		xQueueSendToBack(cola_volumen, &auxiliar, (portTickType) 0 );
		xSemaphoreGive(recurso_volumen);
	}

	auxiliar = 0;
	xQueueSendToBack(cola_opcion_elegida, &auxiliar, (portTickType) 0 );

	auxiliar = 0;
	xQueueSendToBack(cola_menu_teclado, &auxiliar, (portTickType) 0 );

	auxiliar = FCI_INICIAL;
	xQueueSendToBack(cola_fci, &auxiliar, (portTickType) 0 );

	auxiliar = FCI_INICIAL;
	xQueueSendToBack(cola_fci, &auxiliar, (portTickType) 0 );

	auxiliar = FCS_INICIAL;
	xQueueSendToBack(cola_fcs, &auxiliar, (portTickType) 0 );

	auxiliar = ATTACK_INICIAL;
	xQueueSendToBack(cola_att, &auxiliar, (portTickType) 0 );

	auxiliar = DELAY_INICIAL;
	xQueueSendToBack(cola_delay, &auxiliar, (portTickType) 0 );

	auxiliar = OVER_INICIAL;
	xQueueSendToBack(cola_over, &auxiliar, portMAX_DELAY );

	auxiliar = 0;
	xQueueSendToBack(cola_estadoUSB, &auxiliar, (portTickType) 0 );

	auxiliar = CUADRADA;
	xQueueSendToBack(cola_formaDeOnda, &auxiliar, (portTickType) 0 );

	auxiliar = 0;
	xQueueSendToBack(cola_filtro, &auxiliar, (portTickType) 0 );

	while (1) {
		vTaskDelete(NULL);
	}
}

static void vLeerBotones(void *pvParameters) {

	static uint32_t formaDeOnda = 0, filtro;
	uint32_t formaDeOndaaux, filtroaux;

	while(1){

		// Formas de onda
		if (!Chip_GPIO_GetPinState(LPC_GPIO, PORTBOTONES, PINSENO)==1){
			formaDeOnda=SENOIDAL;
			xQueueReceive( cola_formaDeOnda, &formaDeOndaaux, portMAX_DELAY);
			xQueueSendToBack( cola_formaDeOnda, &formaDeOnda, portMAX_DELAY);
		}
		if (!Chip_GPIO_GetPinState(LPC_GPIO, PORTBOTONES, PINCUAD)==1){
			formaDeOnda=CUADRADA;
			xQueueReceive( cola_formaDeOnda, &formaDeOndaaux, portMAX_DELAY);
			xQueueSendToBack( cola_formaDeOnda, &formaDeOnda, portMAX_DELAY);
		}
		if (!Chip_GPIO_GetPinState(LPC_GPIO, PORTBOTONES, PINTRIA)==1){
			formaDeOnda=TRIANGULAR;
			xQueueReceive( cola_formaDeOnda, &formaDeOndaaux, portMAX_DELAY);
			xQueueSendToBack( cola_formaDeOnda, &formaDeOnda, portMAX_DELAY);
		}
		if (!Chip_GPIO_GetPinState(LPC_GPIO, PORTBOTONES, PINSIER)==1){
			formaDeOnda=SIERRA;
			xQueueReceive( cola_formaDeOnda, &formaDeOndaaux, portMAX_DELAY);
			xQueueSendToBack( cola_formaDeOnda, &formaDeOnda, portMAX_DELAY);
		}

		// Filtros

		if (!Chip_GPIO_GetPinState(LPC_GPIO, PORTBOTONES, PINLP)==1){
				xQueueReceive( cola_filtro, &filtroaux, portMAX_DELAY);
			if(filtro == LP){
				filtro = 0;
				xQueueSendToBack( cola_filtro, &filtro, portMAX_DELAY);
			}
			else {
				filtro = LP;
				xQueueSendToBack( cola_filtro, &filtro, portMAX_DELAY);
			}
			while (!Chip_GPIO_GetPinState(LPC_GPIO, PORTBOTONES, PINLP)==1){
				vTaskDelay(50);
			}
		}

		if (!Chip_GPIO_GetPinState(LPC_GPIO, PORTBOTONES, PINBP)==1){

			if (uxQueueMessagesWaiting(cola_filtro)==1){
				xQueueReceive( cola_filtro, &filtroaux, (portTickType) 0 );
			}
			if(filtro == BP){
				filtro = 0;
				xQueueSendToBack( cola_filtro, &filtro, (portTickType) 0);
			}
			else {
				filtro = BP;
				xQueueSendToBack( cola_filtro, &filtro, (portTickType) 0);
			}
			while (!Chip_GPIO_GetPinState(LPC_GPIO, PORTBOTONES, PINBP)==1){
				vTaskDelay(50);
			}
		}

		if (!Chip_GPIO_GetPinState(LPC_GPIO, PORTBOTONES, PINHP)==1){

			if (uxQueueMessagesWaiting(cola_filtro)==1){
				xQueueReceive( cola_filtro, &filtroaux, (portTickType) 0 );
			}
			if(filtro == HP){
				filtro = 0;
				xQueueSendToBack( cola_filtro, &filtro, (portTickType) 0);
			}
			else {
				filtro = HP;
				xQueueSendToBack( cola_filtro, &filtro, (portTickType) 0);
			}
			while (!Chip_GPIO_GetPinState(LPC_GPIO, PORTBOTONES, PINHP)==1){
				vTaskDelay(50);
			}
		}

		taskYIELD();
	}
}

static void vLeerTeclado (void *pvParameters) {

	uint32_t boton1aux = 0, boton2aux = 0, boton3aux = 0, boton4aux = 0, i = 0, a = 0, estado_prev, estado = 0;

	// inicializo la cola_estado en 0
	xQueueSendToBack(cola_estado, &estado, portMAX_DELAY);

	while(1){

		if (uxQueueMessagesWaiting(cola_estadoUSB)==1){
			xQueuePeek(cola_estadoUSB, &estado, (portTickType) 0 );
		}else{
			estado = 0;
		}

		for (a=0;a<8;a++){
			//Deshabilito todas las "columnas"
			for(i=0;i<8;i++)
				Chip_GPIO_SetPinOutHigh(LPC_GPIO, PORTS_EXCT(i), PINS_EXCT(i));

			boton1aux = 0;
			boton2aux = 0;
			boton3aux = 0;
			boton4aux = 0;

			//habilito las mediciones para 1 columna de 4 teclas
			//para a = 0 habilita 1, 9,17,25;
			//para a = 1 habilita 2,10,18,26; y asi...
			Chip_GPIO_SetPinOutLow(LPC_GPIO, PORTS_EXCT(a), PINS_EXCT(a));


			//Leemos las teclas, chequeo el estado del pin de las teclas habilitadas
			//en la primer pasada toman las teclas 1, 9, 17 y 25, la segunda 2, 10, 18 y 26; y asi...
			boton1aux = !Chip_GPIO_GetPinState(LPC_GPIO, PORT_SENS1, PIN_SENS1);
			boton2aux = !Chip_GPIO_GetPinState(LPC_GPIO, PORT_SENS2, PIN_SENS2);
			boton3aux = !Chip_GPIO_GetPinState(LPC_GPIO, PORT_SENS3, PIN_SENS3);
			boton4aux = !Chip_GPIO_GetPinState(LPC_GPIO, PORT_SENS4, PIN_SENS4);

			estado |= ((boton4aux<<(a+24))|(boton3aux<<(a+16))|(boton2aux<<(a+8))|(boton1aux<<(a)));
		}

		xQueueReceive(cola_estado, &estado_prev, portMAX_DELAY );
		xQueueSendToBack(cola_estado, &estado, portMAX_DELAY);

		taskYIELD();
	}
}

static void vEncoders(void *pvParameters) {

	int lectura = 0, Leer_Encoder[6];
	uint32_t volumenaux=VOLUMEN_INICIAL, volumen = VOLUMEN_INICIAL, FILTRO;
	uint32_t fciaux = CANT_FCI/2, fci = CANT_FCI/2;
	uint32_t fcsaux = CANT_FCS/2, fcs = CANT_FCS/2;
	uint32_t overaux = OVER_INICIAL, over = OVER_INICIAL;
	uint32_t attaux = ATTACK_INICIAL, att = ATTACK_INICIAL;
	uint32_t delayaux = DELAY_INICIAL, delay = DELAY_INICIAL;

	uint32_t fci_o_fcs = 1; //se arranca modificando fci
	uint32_t opcion_elegida = 0;
	uint32_t menu_teclado = 0, aprete_volumen=0;

	// De leer encoders
	int new, diff, enc_delta=0, enc_last=0, val;
	int PHASE_A=0, PHASE_B=0;
	int i = 0;
	encoder encoders;

	// Inicializo poniendo en 0 a cola_encoders
	for (i = 0; i < 6; i++){
		encoders.last[i]=0;
		encoders.delta[i]=0;
	}

	while(1){

		// Lee el estado de los 6 encoders y lo guarda en la cola_encoders
		for (i = 0; i < 6; i++){
			PHASE_A = Chip_GPIO_GetPinState(LPC_GPIO, PORTS_FASEA(i), PINS_FASEA(i));
			PHASE_B = Chip_GPIO_GetPinState(LPC_GPIO, PORTS_FASEB(i), PINS_FASEB(i));

			enc_last = encoders.last[i];
			enc_delta = encoders.delta[i];

			new = 0;
			// new va desde 0b00 a 0b11
			if( PHASE_A )
				new = 3;
			if( PHASE_B )
				new ^= 1;      // convierte gray a binario
			diff = enc_last - new;
			if( diff & 1 ){       // bit 0 = valor (1)
				enc_last = new;   // guarda la nueva posicion como ultima
				// bit 1 = dirección (+/-)
				// Si 1 = gire para un lado, 0 no gire, -1 = gire para el otro lado
				enc_delta += (diff & 2) - 1;
			}

			val = enc_delta;
			// se queda con los dos bits menos significativos
			enc_delta = val & 3;

			encoders.delta[i] = enc_delta;
			encoders.last[i] = enc_last;
			// cuando val = 4, val >> 2 = 1, cuando val = -1, val >> 2 = -1
			Leer_Encoder[i] = val >> 2;
		}


		if (!Chip_GPIO_GetPinState(LPC_GPIO, PORT_BOT_VOL, PIN_BOT_VOL)==1){
			while (!Chip_GPIO_GetPinState(LPC_GPIO, PORT_BOT_VOL, PIN_BOT_VOL)==1){
				vTaskDelay(50);
			}
			aprete_volumen = 1;

			xQueueReceive( cola_menu_teclado, &menu_teclado, portMAX_DELAY);
			xQueueReceive( cola_opcion_elegida, &opcion_elegida, portMAX_DELAY);

			if (menu_teclado == 0 && aprete_volumen == 1)
			{
				aprete_volumen = 0;
				menu_teclado = 1;
			}
			if (menu_teclado == 1 && aprete_volumen == 1){
				aprete_volumen = 0;
				if (opcion_elegida == 0){
					menu_teclado = 0;
					//
				}
				if (opcion_elegida == 1){
					menu_teclado = 0;
					//
				}
			}
			xQueueSendToBack( cola_menu_teclado, &menu_teclado, portMAX_DELAY);
			xQueueSendToBack( cola_opcion_elegida, &opcion_elegida, portMAX_DELAY);

		}

		lectura = Leer_Encoder[ENC_VOLUMEN];

		// ENCODER VOLUMEN
		if(lectura == (-1)){
			xQueuePeek( cola_volumen, &volumen, 1000);
			if(volumen > 1){
				if (xSemaphoreTake(recurso_volumen, (portTickType) 0) == pdTRUE)
					xQueueReceive( cola_volumen, &volumenaux, portMAX_DELAY );
					volumen = volumenaux-1;
					xQueueSendToBack(cola_volumen, &volumen, portMAX_DELAY);
					xSemaphoreGive(recurso_volumen);
			}
		}
		if(lectura == 1){
			xQueuePeek( cola_volumen, &volumen, 1000);
			if(volumen <= 99){
				if (xSemaphoreTake(recurso_volumen, (portTickType) 0) == pdTRUE){
					xQueueReceive( cola_volumen, &volumenaux, portMAX_DELAY);
					volumen = volumenaux+1;
					xQueueSendToBack(cola_volumen, &volumen, portMAX_DELAY);
					xSemaphoreGive(recurso_volumen);
				}
			}
		}

		// Modo guardar/cargar
		if (menu_teclado == 1){
			xQueueReceive( cola_opcion_elegida, &opcion_elegida, portMAX_DELAY);

			if(lectura == (-1)){
				if(opcion_elegida == 1){
					opcion_elegida = 0;
				}
			}
			if(lectura == 1){
				if(opcion_elegida == 0){
					opcion_elegida = 1;
				}
			}
			xQueueSendToBack( cola_opcion_elegida, &opcion_elegida, portMAX_DELAY);
		}

		// ENCODER FCI y FCI (1°)
		// Si es pasa banda FCI y FCS van de 0 a 2, sino de 0 a 8
		xQueuePeek( cola_filtro, &FILTRO, (portTickType) 0 );

		// Si el segundo encoder esta apretado controla FCI
		if (!Chip_GPIO_GetPinState(LPC_GPIO, PORT_BOT_FCI, PIN_BOT_FCI)==0){
			lectura = Leer_Encoder[ENC_FCI];
			if(lectura == (-1)){
				xQueuePeek( cola_fci, &fci, 1000);
				if(fci >= 1){
					if (xSemaphoreTake(recurso_fci, (portTickType) 0) == pdTRUE){
						xQueueReceive( cola_fci, &fciaux, portMAX_DELAY);
						fci = fciaux-1;
						xQueueSendToBack(cola_fci, &fci, portMAX_DELAY);
						xSemaphoreGive(recurso_fci);
					}
				}
			}
			if(lectura == 1){
				xQueuePeek( cola_fci, &fci, 1000);
				if(FILTRO == BP){
					if(fci < (CANT_FCI_PB - 1)){
						if (xSemaphoreTake(recurso_fci, (portTickType) 0) == pdTRUE){
							xQueueReceive( cola_fci, &fciaux, portMAX_DELAY);
							fci = fciaux+1;
							xQueueSendToBack(cola_fci, &fci, portMAX_DELAY);
							xSemaphoreGive(recurso_fci);
						}
					}
				}
				else {
					if(fci < (CANT_FCI - 1)){
						if (xSemaphoreTake(recurso_fci, (portTickType) 0) == pdTRUE){
							xQueueReceive( cola_fci, &fciaux, portMAX_DELAY);
							fci = fciaux+1;
							xQueueSendToBack(cola_fci, &fci, portMAX_DELAY);
							xSemaphoreGive(recurso_fci);
						}
					}
				}
			}
		}

		// Si el segundo encoder no está apretado controla FCS
		if (!Chip_GPIO_GetPinState(LPC_GPIO, PORT_BOT_FCI, PIN_BOT_FCI)==1){
			lectura = Leer_Encoder[ENC_FCI];
			if(lectura == (-1)){
				xQueuePeek( cola_fcs, &fcs, 1000);
				if(fcs >= 1){
					if (xSemaphoreTake(recurso_fcs, (portTickType) 0) == pdTRUE){
						xQueueReceive( cola_fcs, &fcsaux, portMAX_DELAY);
						fcs = fcsaux-1;
						xQueueSendToBack(cola_fcs, &fcs, portMAX_DELAY);
						xSemaphoreGive(recurso_fcs);
					}
				}
			}
			if(lectura == 1){
				xQueuePeek( cola_fcs, &fcs, 1000);
				if(FILTRO == BP){
					if(fcs < (CANT_FCS_PB - 1)){
						if (xSemaphoreTake(recurso_fcs, (portTickType) 0) == pdTRUE){
							xQueueReceive( cola_fcs, &fciaux, portMAX_DELAY);
							fcs = fcsaux+1;
							xQueueSendToBack(cola_fcs, &fcs, portMAX_DELAY);
							xSemaphoreGive(recurso_fcs);
						}
					}
				}
				else {
					if(fcs < (CANT_FCS - 1)){
						if (xSemaphoreTake(recurso_fcs, (portTickType) 0) == pdTRUE){
							xQueueReceive( cola_fcs, &fcsaux, portMAX_DELAY);
							fcs = fcsaux+1;
							xQueueSendToBack(cola_fcs, &fcs, portMAX_DELAY);
							xSemaphoreGive(recurso_fcs);
						}
					}
				}
			}
		}

		// ENCODER OVER (3°)

		lectura = Leer_Encoder[ENC_OVER];
		if(lectura == (-1)){
			xQueuePeek( cola_over, &over, 1000);
			if(over >= 1){
				if (xSemaphoreTake(recurso_over, (portTickType) 0) == pdTRUE){
					xQueueReceive( cola_over, &overaux, portMAX_DELAY);
					over = overaux-1;
					xQueueSendToBack(cola_over, &over, portMAX_DELAY);
					xSemaphoreGive(recurso_over);
				}
			}
		}
		if(lectura == 1){
			xQueuePeek( cola_over, &over, 1000);
			if(over <= (CANT_OVER-1)){
				if (xSemaphoreTake(recurso_over, (portTickType) 0) == pdTRUE){
					xQueueReceive( cola_over, &overaux, portMAX_DELAY);
					over = overaux+1;
					xQueueSendToBack(cola_over, &over, portMAX_DELAY);
					xSemaphoreGive(recurso_over);
				}
			}
		}

		// ENCODER ATTACK (4°)

		lectura = Leer_Encoder[ENC_ATT];
		if(lectura == (-1)){
			xQueuePeek( cola_att, &att, 1000);
			if(att > 0){
				if (xSemaphoreTake(recurso_attack, (portTickType) 0) == pdTRUE){
					xQueueReceive( cola_att, &attaux, portMAX_DELAY);
					att = attaux-1;
					xQueueSendToBack(cola_att, &att, portMAX_DELAY);
					xSemaphoreGive(recurso_attack);
				}
			}
		}
		if(lectura == 1){
			xQueuePeek( cola_att, &att, 1000);
			if(att <= 49){
				if (xSemaphoreTake(recurso_attack, (portTickType) 0) == pdTRUE){
					xQueueReceive( cola_att, &attaux, portMAX_DELAY);
					att = attaux+1;
					xQueueSendToBack(cola_att, &att, portMAX_DELAY);
					xSemaphoreGive(recurso_attack);
				}
			}
		}

		// ENCODER DELAY (5°)

		lectura = Leer_Encoder[ENC_DELAY];
		if(lectura == (-1)){
			xQueuePeek( cola_delay, &delay, 1000);
			if(delay > 0){
				if (xSemaphoreTake(recurso_delay, (portTickType) 0) == pdTRUE){
					xQueueReceive( cola_delay, &delayaux, portMAX_DELAY);
					delay = delayaux-1;
					xQueueSendToBack(cola_delay, &delay, portMAX_DELAY);
					xSemaphoreGive(recurso_delay);
				}
			}
		}
		if(lectura == 1){
			xQueuePeek( cola_delay, &delay, 1000);
			if(delay <= 9){
				if (xSemaphoreTake(recurso_delay, (portTickType) 0) == pdTRUE){
					xQueueReceive( cola_delay, &delayaux, portMAX_DELAY);
					delay = delayaux+1;
					xQueueSendToBack(cola_delay, &delay, portMAX_DELAY);
					xSemaphoreGive(recurso_delay);
				}
			}
		}
		vTaskDelay(3);
	}
}
static void vControlDisplay(void *pvParameters) {

	uint32_t formaDeOnda=1, formadeonda_ant = 1, contador=0;
	int volumen, filtro, fci=4, fcs=4, over=0, att=0, att_ant=0, delay=0, delay_ant=0;
	char *string="100%", *string_fci="100", *string_fcs="100", *string_over="0";
	char *string_att="0.0 seg", *string_delay="0.0 seg";
	uint32_t data, y;
	static int menu_teclado = 0, opcion_elegida = 0, menu_ant_teclado = 0;
	int a, b, c;

	ks0108WriteCommand(LCD_ON, CHIP1);				// power on
	ks0108WriteCommand(LCD_ON, CHIP2);

	ks0108WriteCommand(LCD_DISP_START, CHIP1);		// display start line = 0
	ks0108WriteCommand(LCD_DISP_START, CHIP2);
	ks0108ClearScreen();							// display clear
	ks0108GotoXY(0,0);


	ks0108GotoXY(29,0);
	ks0108Puts("Vol:");
	ks0108GotoXY(78,0);
	ks0108Puts("Attack");
	ks0108GotoXY(76,16);
	ks0108Puts("0.0 seg");
	ks0108GotoXY(95,32);
	ks0108Puts("Over");

	ks0108GotoXY(0,0);
	ks0108FillImage(0, 0, 28, 28, grafico_cuadrada);

	while (1) {

		if (uxQueueMessagesWaiting(cola_menu_teclado)==1){
			xQueuePeek( cola_menu_teclado, &menu_teclado, (portTickType) 0 );
		}
		contador ++;
		switch (menu_teclado){
		case 0:
		{
			if (menu_ant_teclado != menu_teclado){
				menu_ant_teclado = menu_teclado;
				ks0108ClearScreen();
				//Imprimir_Pantalla_Menu_Teclado();

				ks0108GotoXY(29,0);
				ks0108Puts("Vol:");

				ks0108GotoXY(78,0);
				ks0108Puts("Attack");
				ks0108GotoXY(76,16);
				xQueuePeek( cola_att, &att, (portTickType) 10 );
				string_att = itoa_mio_seg(att);
				ks0108Puts(string_att);

				ks0108GotoXY(95,32);
				ks0108Puts("Over");

				ks0108GotoXY(0,0);
				ks0108FillImage(0, 0, 28, 28, grafico_cuadrada);
			}

			if (contador >= 1){
				contador = 0;

				if (uxQueueMessagesWaiting(cola_volumen)==1){
					xQueuePeek( cola_volumen, &volumen, (portTickType) 0 );
					string = itoa_mio_porcentual(volumen);
					ks0108GotoXY(28,16);
					ks0108Puts(string);
				}

				if (uxQueueMessagesWaiting(cola_filtro)==1){
					xQueuePeek( cola_filtro, &filtro, (portTickType) 0 );
					if (uxQueueMessagesWaiting(cola_fci)==1){
						xQueuePeek( cola_fci, &fci, (portTickType) 0 );
						string_fci = itoa_mio(fci);
					}
					if (uxQueueMessagesWaiting(cola_fcs)==1){
						xQueuePeek( cola_fcs, &fcs, (portTickType) 0 );
						string_fcs = itoa_mio(fcs);
					}

					if (filtro != 0){
						ks0108GotoXY(28,32);
						ks0108Puts("Pasa");
					}
					if (filtro == 0){
						ks0108GotoXY(28,32); //Pasa
						ks0108Puts("     ");
						ks0108GotoXY(28,48); //bajo, band, alto
						ks0108Puts("     ");

						ks0108GotoXY(0,32); //fci
						ks0108Puts("   ");
						ks0108GotoXY(0,48); //0-100 fci
						ks0108Puts("   ");

						ks0108GotoXY(65,32); //fcs
						ks0108Puts("   ");
						ks0108GotoXY(64,48); //0-100 fcs
						ks0108Puts("   ");
					}
					if (filtro == HP){
						ks0108GotoXY(28,48);
						ks0108Puts("Alto ");
						ks0108GotoXY(0,32);
						ks0108Puts("Fc ");
						ks0108GotoXY(0,48);
						ks0108Puts(string_fci);
						ks0108GotoXY(65,32); //fcs
						ks0108Puts("   ");
						ks0108GotoXY(64,48); //0-100 fcs
						ks0108Puts("   ");
					}
					if (filtro == BP){
						ks0108GotoXY(28,48);
						ks0108Puts("Band");
						ks0108GotoXY(0,32);
						ks0108Puts("Fci");
						ks0108GotoXY(0,48);
						ks0108Puts(string_fci);
						ks0108GotoXY(65,32);
						ks0108Puts("Fcs");
						ks0108GotoXY(64,48);
						ks0108Puts(string_fcs);
					}
					if (filtro == LP){
						ks0108GotoXY(28,48);
						ks0108Puts("Bajo ");
						ks0108GotoXY(0,32);
						ks0108Puts("   "); //fci
						ks0108GotoXY(0,48);
						ks0108Puts("   "); //0-100 fci
						ks0108GotoXY(65,32);
						ks0108Puts("Fc ");
						ks0108GotoXY(64,48);
						ks0108Puts(string_fcs);
					}
				}
				if (uxQueueMessagesWaiting(cola_over)==1){
					xQueuePeek( cola_over, &over, (portTickType) 0 );
					ks0108GotoXY(97,48);
					string_over = itoa_mio(over);
					ks0108Puts(string_over);
				}
				if (uxQueueMessagesWaiting(cola_att)==1){
					xQueuePeek( cola_att, &att, (portTickType) 0 );
					if (att_ant != att){
						att_ant = att;
						ks0108GotoXY(78,0);
						ks0108Puts("Attack");
						ks0108GotoXY(76,16);
						string_att = itoa_mio_seg(att);
						ks0108Puts(string_att);
					}
				}
				if (uxQueueMessagesWaiting(cola_delay)==1){
					xQueuePeek( cola_delay, &delay, (portTickType) 0 );
					if (delay_ant != delay){
						delay_ant = delay;
						ks0108GotoXY(78,0);
						ks0108Puts("Delay ");
						ks0108GotoXY(76,16);
						string_delay = itoa_mio_seg(delay);
						ks0108Puts(string_delay);
					}
				}

				if (uxQueueMessagesWaiting(cola_formaDeOnda)==1){
					xQueuePeek( cola_formaDeOnda, &formadeonda_ant, (portTickType) 0 );
					if (formaDeOnda != formadeonda_ant){
						formaDeOnda = formadeonda_ant;
						ks0108GotoXY(0,0);
						switch (formaDeOnda){
						case CUADRADA:{
							ks0108FillRect(0,0,28,28,WHITE);
							ks0108FillImage(0, 0, 28, 28, grafico_cuadrada);
						}break;
						case SENOIDAL:{
							ks0108FillRect(0,0,28,28,WHITE);
							ks0108FillImage(0, 0, 28, 28, grafico_senoidal);
						}break;
						case TRIANGULAR:{
							ks0108FillRect(0,0,28,28,WHITE);
							ks0108FillImage(0, 0, 28, 28, grafico_triangular);
						}break;
						case SIERRA:{
							ks0108FillRect(0,0,28,28,WHITE);
							ks0108FillImage(0, 0, 28, 28, grafico_sierra);
						}break;
						default:
							ks0108FillRect(0,0,28,28,WHITE);
							ks0108FillImage(0, 0, 28, 28, grafico_cuadrada);
						}
					}
				}
			}
//			if (contador == 5000){
//				data = 0xFF;
//				y = 1;
//				ks0108GotoXY(100,y-y%8);
//				data <<= y%8;
//				ks0108WriteData(data);
//
//				if (y > 0){
//					ks0108GotoXY(100,y+8-y%8);
//					data >>= (8-y%8);
//					ks0108WriteData(data);
//				}
//
//			}
//			if (contador == 10000){
//				ks0108GotoXY(29,0);
//				ks0108Puts("Vol:");
//				ks0108GotoXY(28,16);
//				ks0108Puts("100%");
//				ks0108GotoXY(28,16);
//				ks0108Puts("  1%");
//				ks0108GotoXY(28,32);
//				ks0108Puts("Pasa");
//				ks0108GotoXY(28,48);
//				ks0108Puts("Bajo");
//				ks0108GotoXY(28,48);
//				ks0108Puts("Band");
//				ks0108GotoXY(0,32);
//				ks0108Puts("Fci");
//				ks0108GotoXY(0,48);
//				ks0108Puts("  1");
//				ks0108GotoXY(0,48);
//				ks0108Puts(" 20");
//				ks0108GotoXY(65,32);
//				ks0108Puts("Fcs");
//				ks0108GotoXY(64,48);
//				ks0108Puts("100");
//				ks0108GotoXY(0,32);
//				ks0108Puts("   ");
//
//				ks0108GotoXY(78,0);
//				ks0108Puts("Attack");
//				ks0108GotoXY(76,16);
//				ks0108Puts("4.9 seg");
//				ks0108GotoXY(78,0);
//				ks0108Puts("Delay ");
//				ks0108GotoXY(76,16);
//				ks0108Puts("0.1 seg");
//
//				ks0108GotoXY(95,32);
//				ks0108Puts("Over");
//				ks0108GotoXY(97,48);
//				ks0108Puts("100");
//				ks0108GotoXY(97,48);
//				ks0108Puts(" 10");
//
//				//ks0108PutChar('A');
//
//			}
//			if (contador == 3000){
//				contador = 0;
//				ks0108ClearScreen();
//			}
		}break;
		case 1:
		{
			if (menu_ant_teclado != menu_teclado){
				menu_ant_teclado = menu_teclado;
				ks0108ClearScreen();

				ks0108GotoXY(9,16);
				ks0108Puts("Guardar");
				ks0108GotoXY(9,32);
				ks0108Puts("Config");
				ks0108GotoXY(9,48);
				ks0108Puts("Actual");

				ks0108GotoXY(72,16);
				ks0108Puts("Cargar");
				ks0108GotoXY(72,32);
				ks0108Puts("Config");
				ks0108GotoXY(72,48);
				ks0108Puts("Ant");

			}
			if (contador >= 1){
				contador = 0;

				if (uxQueueMessagesWaiting(cola_opcion_elegida)==1){
					xQueuePeek( cola_opcion_elegida, &opcion_elegida, (portTickType) 0 );
				}
				if (opcion_elegida == 0){
					ks0108DrawRect(7,14,56,46,BLACK);
					ks0108DrawRect(71,14,55,46,WHITE);
//					for (a = 7; a < 63; a ++){
//						ks0108SetDot(a,14,BLACK);
//						ks0108SetDot(a,60,BLACK);
//					}
//					for (a = 71; a < 126; a ++){
//						ks0108SetDot(a,14,WHITE);
//						ks0108SetDot(a,60,WHITE);
//					}
//					for (b = 14; b < 60; b ++){
//						ks0108SetDot(7,b,BLACK);
//						ks0108SetDot(63,b,BLACK);
//					}
//					for (b = 14; b < 60; b ++){
//						ks0108SetDot(71,b,WHITE);
//						ks0108SetDot(126,b,WHITE);
//					}
				}

				if (opcion_elegida == 1){
					ks0108DrawRect(7,14,56,46,WHITE);
					ks0108DrawRect(71,14,55,46,BLACK);
					//
//					for (a = 7; a < 63; a ++){
//						ks0108SetDot(a,14,WHITE);
//						ks0108SetDot(a,60,WHITE);
//					}
//					for (a = 71; a < 126; a ++){
//						ks0108SetDot(a,14,BLACK);
//						ks0108SetDot(a,60,BLACK);
//					}
//					for (b = 14; b < 60; b ++){
//						ks0108SetDot(7,b,WHITE);
//						ks0108SetDot(63,b,WHITE);
//					}
//					for (b = 14; b < 60; b ++){
//						ks0108SetDot(71,b,BLACK);
//						ks0108SetDot(126,b,BLACK);
//					}
				}

			}
		}break;
		default:
		{

		}break;
		}
		vTaskDelay(100);
	}

}


static void vGenFormaOnda(void *pvParameters) {

	uint16_t tabla_buffer [ NUMERO_MUESTRAS ];
	uint16_t tabla_salida [ NUMERO_MUESTRAS ];

	uint32_t estadoTeclado=0, estadoTeclado_PREV=0, FORMADEONDA=CUADRADA, i, j=0, timeoutDMA, FILTRO=0, FILTRO_PREV, SET_FILTRO=0, SET_FORMADEONDA=1,
			FORMADEONDA_PREV=0, SET_VOLUMEN=0, SET_ATTACK=0, ATTACK, ATTACK_PREV, contATTACK=0, t_ATT=0, SET_CAMBIO=0,volumen = VOLUMEN_INICIAL, CLOCK_DAC_HZ,
			FCI=CANT_FCI/2, FCI_PREV, FCS=CANT_FCS/2, FCS_PREV, OVER=0, OVER_PREV=0, SET_OVER=0, valorPICO =0;

    // Variables FILTRO
	uint32_t blockSize = BLOCK_SIZE;
	uint32_t numBlocks = NUMERO_MUESTRAS/BLOCK_SIZE;
	arm_fir_instance_f32 S;
	arm_status status;

	float32_t  *inputF32, *outputF32, *outputF32aux,  firStateF32[BLOCK_SIZE + NUM_TAPS - 1], COEF_FCI[CANT_FCI];

	// Tablas para el filtro en f32
	float32_t tabla_buffer_f32 [ NUMERO_MUESTRAS ], tabla_aux_f32 [ NUMERO_MUESTRAS ];

	float32_t *TABLA_FCI[CANT_FCI], *TABLA_FCS[CANT_FCS],  *TABLA_BP[CANT_BP];

    float32_t AMPLITUD=1, volumenfloat, overfloat=0, D_ATT;


	for(i=0;i<CANT_FCI;i++){
		switch(i){
			case 0: TABLA_FCI[i] = (float32_t *) &Coef_1k2hz_HP[0];break;
			case 1: TABLA_FCI[i] = (float32_t *) &Coef_1k6hz_HP[0];break;
			case 2: TABLA_FCI[i] = (float32_t *) &Coef_2khz_HP[0];break;
			case 3: TABLA_FCI[i] = (float32_t *) &Coef_3khz_HP[0];break;
			case 4: TABLA_FCI[i] = (float32_t *) &Coef_4khz_HP[0];break;
			case 5: TABLA_FCI[i] = (float32_t *) &Coef_6khz_HP[0];break;
			case 6: TABLA_FCI[i] = (float32_t *) &Coef_9khz_HP[0];break;
			case 7: TABLA_FCI[i] = (float32_t *) &Coef_12khz_HP[0];break;
			default: TABLA_FCI[i] = (float32_t *)&Coef_3khz_HP[0];break;
		}
	}

	for(i=0;i<CANT_FCS;i++){
		switch(i){
			case 0: TABLA_FCS[i] = (float32_t *) &Coef_1khz_LP[0];break;
			case 1: TABLA_FCS[i] = (float32_t *) &Coef_3khz_LP[0];break;
			case 2: TABLA_FCS[i] = (float32_t *) &Coef_6khz_LP[0];break;
			case 3: TABLA_FCS[i] = (float32_t *) &Coef_9khz_LP[0];break;
			case 4: TABLA_FCS[i] = (float32_t *) &Coef_12khz_LP[0];break;
			case 5: TABLA_FCS[i] = (float32_t *) &Coef_15khz_LP[0];break;
			case 6: TABLA_FCS[i] = (float32_t *) &Coef_18khz_LP[0];break;
			case 7: TABLA_FCS[i] = (float32_t *) &Coef_22khz_LP[0];break;
			default: TABLA_FCS[i] = (float32_t *)&Coef_12khz_LP[0];break;
		}
	}

	for(i=0;i<CANT_BP;i++){
		switch(i){
			case 0: TABLA_BP[i] = (float32_t *) &Coef_1a4khz_BP[0];break;
			case 1: TABLA_BP[i] = (float32_t *) &Coef_1a5khz_BP[0];break;
			case 2: TABLA_BP[i] = (float32_t *) &Coef_1a6khz_BP[0];break;
			case 3: TABLA_BP[i] = (float32_t *) &Coef_2a4khz_BP[0];break;
			case 4: TABLA_BP[i] = (float32_t *) &Coef_2a5khz_BP[0];break;
			case 5: TABLA_BP[i] = (float32_t *) &Coef_2a6khz_BP[0];break;
			case 6: TABLA_BP[i] = (float32_t *) &Coef_3a4khz_BP[0];break;
			case 7: TABLA_BP[i] = (float32_t *) &Coef_3a5khz_BP[0];break;
			case 8: TABLA_BP[i] = (float32_t *) &Coef_3a6khz_BP[0];break;
			default: TABLA_BP[i] = (float32_t *)&Coef_2a5khz_BP[0];break;
		}
	}

	/* Call FIR init function to initialize the instance structure. */
	arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&Coef_12khz_LP[0], &firStateF32[0], blockSize);
	outputF32 = &tabla_buffer_f32[0];
	outputF32aux = &tabla_aux_f32[0];
	inputF32 = &tabla_cuad_f32[0];

	Chip_GPDMA_PrepareDescriptor ( LPC_GPDMA , &DMA_LLI_buffer  , (uint32_t) tabla_salida ,
						GPDMA_CONN_DAC , DMA_SIZE , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA , &DMA_LLI_buffer );

	while (1) {

		xQueuePeek( cola_volumen, &volumen, (portTickType) 0 );
		if(volumenfloat == volumen) SET_VOLUMEN = 0;
		else {
			volumenfloat = volumen;
			AMPLITUD = volumenfloat/100;
			SET_VOLUMEN = 1;
		}

		xQueuePeek( cola_formaDeOnda, &FORMADEONDA, (portTickType) 0 );
		if(FORMADEONDA == FORMADEONDA_PREV) SET_FORMADEONDA = 0;
		else {
			switch(FORMADEONDA){
				case CUADRADA: inputF32 = &tabla_cuad_f32[0];break;
				case SENOIDAL: inputF32 = &tabla_seno_f32[0];break;
				case TRIANGULAR: inputF32 = &tabla_tria_f32[0];break;
				case SIERRA: inputF32 = &tabla_sier_f32[0];break;
			}
			SET_FORMADEONDA = 1;
		}
		FORMADEONDA_PREV = FORMADEONDA;

		xQueuePeek( cola_filtro, &FILTRO, (portTickType) 0 );
		if(FILTRO == FILTRO_PREV) SET_FILTRO = 0;
		else SET_FILTRO = 1;
		FILTRO_PREV = FILTRO;



		xQueuePeek( cola_over, &OVER, (portTickType) 0 );
		if(OVER != OVER_PREV){
			if(OVER < CANT_OVER) overfloat = (float32_t) (OVER)/CANT_OVER;
			else overfloat = (float32_t)19 /CANT_OVER;
			SET_OVER=1;
			SET_VOLUMEN=1;
		}
		OVER_PREV = OVER;

		xQueuePeek( cola_att, &ATTACK, (portTickType) 0 );
		if(ATTACK != ATTACK_PREV) {
			contATTACK=0;
			SET_ATTACK = 1;
		}
		if(ATTACK == 0) SET_ATTACK = 0;
		ATTACK_PREV = ATTACK;
		t_ATT = (ATTACK * 100)/T_FORMAONDA;
		D_ATT = (volumenfloat/100)/t_ATT;



		if(SET_ATTACK == 1){
			xQueuePeek( cola_estado, &estadoTeclado, (portTickType) 0 );
			if(estadoTeclado!=estadoTeclado_PREV){
				AMPLITUD = 0;
				SET_VOLUMEN = 1;
				contATTACK = 0;
			}
			else {
				contATTACK++;
				if((contATTACK < t_ATT) && (AMPLITUD < volumenfloat/100)){
					AMPLITUD+= D_ATT;
					SET_VOLUMEN = 1;
				}
			}
			estadoTeclado_PREV = estadoTeclado;
		}

		if(FILTRO == HP){
			// Si cambia el encoder de FCI reinicia con otros coeficientes el fitro
			xQueuePeek( cola_fci, &FCI, (portTickType) 0 );
			if(FCI == FCI_PREV && SET_FILTRO==0) SET_FILTRO = 0;
			else {
				arm_fir_init_f32(&S, NUM_TAPS, (float32_t *) TABLA_FCI[FCI] , &firStateF32[0], blockSize);
				SET_FILTRO=1;
			}
			FCI_PREV = FCI;
		}

		if(FILTRO == LP){
			// Si cambia el encoder de FCS reinicia con otros coeficientes el fitro
			xQueuePeek( cola_fcs, &FCS, (portTickType) 0 );
			if(FCS == FCS_PREV && SET_FILTRO==0) SET_FILTRO = 0;
			else {
				arm_fir_init_f32(&S, NUM_TAPS, (float32_t *) TABLA_FCS[FCS] , &firStateF32[0], blockSize);
				SET_FILTRO=1;
			}
			FCS_PREV = FCS;
		}

		if(FILTRO == BP){

			if (uxQueueMessagesWaiting(cola_fcs)==1)
				xQueuePeek( cola_fcs, &FCS, (portTickType) 0 );
			if (uxQueueMessagesWaiting(cola_fci)==1)
				xQueuePeek( cola_fci, &FCI, (portTickType) 0 );

			if(FCS != FCS_PREV || FCI != FCI_PREV){
				if(FCI==0 && FCS==0)
					arm_fir_init_f32(&S, NUM_TAPS, (float32_t *) TABLA_BP[0] , &firStateF32[0], blockSize);
				if(FCI==0 && FCS==1)
					arm_fir_init_f32(&S, NUM_TAPS, (float32_t *) TABLA_BP[1] , &firStateF32[0], blockSize);
				if(FCI==0 && FCS==2)
					arm_fir_init_f32(&S, NUM_TAPS, (float32_t *) TABLA_BP[2] , &firStateF32[0], blockSize);
				if(FCI==1 && FCS==0)
					arm_fir_init_f32(&S, NUM_TAPS, (float32_t *) TABLA_BP[3] , &firStateF32[0], blockSize);
				if(FCI==1 && FCS==1)
					arm_fir_init_f32(&S, NUM_TAPS, (float32_t *) TABLA_BP[4] , &firStateF32[0], blockSize);
				if(FCI==1 && FCS==2)
					arm_fir_init_f32(&S, NUM_TAPS, (float32_t *) TABLA_BP[5] , &firStateF32[0], blockSize);
				if(FCI==2 && FCS==0)
					arm_fir_init_f32(&S, NUM_TAPS, (float32_t *) TABLA_BP[6] , &firStateF32[0], blockSize);
				if(FCI==2 && FCS==1)
					arm_fir_init_f32(&S, NUM_TAPS, (float32_t *) TABLA_BP[7] , &firStateF32[0], blockSize);
				if(FCI==2 && FCS==2)
					arm_fir_init_f32(&S, NUM_TAPS, (float32_t *) TABLA_BP[8] , &firStateF32[0], blockSize);
				SET_FILTRO = 1;
				FCS_PREV = FCS;
				FCI_PREV = FCI;
			}
		}


		// Carga en el buffer la forma de onda y su amplitud
		if((SET_FORMADEONDA == 1 || SET_VOLUMEN == 1 || SET_FILTRO == 1) && FILTRO == 0){

			switch(FORMADEONDA) {

				case CUADRADA:

					for ( i = 0 ; i < NUMERO_MUESTRAS ; i++ ) {
					tabla_buffer[i]= AMPLITUD * 0.3 *tabla_cuad[i];
					}
				break;

				case SENOIDAL:
					for ( i = 0 ; i < NUMERO_MUESTRAS ; i++ ) {
					tabla_buffer[i]= AMPLITUD * tabla_seno[i];
					}
				break;

				case TRIANGULAR:
					for ( i = 0 ; i < NUMERO_MUESTRAS ; i++ ) {
					tabla_buffer[i]= AMPLITUD * tabla_tria[i];
					}
				break;

				case SIERRA:
					for ( i = 0 ; i < NUMERO_MUESTRAS ; i++ ) {
					tabla_buffer[i]= AMPLITUD * 0.4 *tabla_sier[i];
					}
				break;

				default: FORMADEONDA=CUADRADA; break;
				}
			SET_FORMADEONDA = 0;
			SET_VOLUMEN = 0;
			SET_FILTRO = 0;
			if(OVER != 0) SET_OVER = 1;
			SET_CAMBIO=1;
		}

		if((SET_FORMADEONDA == 1 || SET_VOLUMEN == 1 || SET_FILTRO == 1) && FILTRO != 0){
			for(i=0; i < numBlocks; i++)
			arm_fir_f32(&S, inputF32 + (i * blockSize), outputF32 + (i * blockSize), blockSize);
			for(i=0; i < numBlocks; i++)
			arm_fir_f32(&S, inputF32 + (i * blockSize), outputF32 + (i * blockSize), blockSize);
			for ( i = 0 ; i < NUMERO_MUESTRAS ; i++ ) {
			  tabla_buffer[i]= 512 + 512 *  tabla_buffer_f32[i];
			  tabla_buffer[i]= AMPLITUD * tabla_buffer[i];
			}
			SET_FORMADEONDA = 0;
			SET_VOLUMEN = 0;
			SET_FILTRO = 0;
			if(OVER != 0) SET_OVER = 1;
			SET_CAMBIO=1;
		}
		if(SET_OVER == 1){
			for ( i = 0 ; i < NUMERO_MUESTRAS ; i++ ){
				if(tabla_buffer[i]>valorPICO) valorPICO = tabla_buffer[i];
			}

			for ( i = 0 ; i < NUMERO_MUESTRAS ; i++ ){
				if(tabla_buffer[i] > (valorPICO * (1-overfloat)))
						tabla_buffer[i] =  valorPICO * (1-overfloat);
				tabla_buffer[i] = tabla_buffer[i]/(1-overfloat);
			}
			SET_OVER=0;
			SET_CAMBIO=1;
		}
		if(SET_CAMBIO == 1){
			for ( i = 0 ; i < NUMERO_MUESTRAS ; i++ ) {
			  tabla_salida[i]= tabla_buffer[i];
			  tabla_salida[i] = ( tabla_salida [i] << 6);
			}
			SET_CAMBIO=0;
		}
		vTaskDelay(T_FORMAONDA);
    }
}

static void vSonidoTeclas(void *pvParameters) {

		uint32_t estadoTeclado=0, estadoTeclado_PREV=0, i, j=0, Canal_Libre, timeoutDMA, COLA_TECLAS[cantTECLAS_MAX]={SILENCIO}, CLOCK_DAC_HZ, DMA_SET=0, DELAY_BUF[CANT_DELAY]={SILENCIO},
				ind_DELAY=0, DELAY, SET_DELAY=0, T_DELAY;
		Status estadoDMA;

		for (int a = 0; a < CANT_DELAY; a++){
			DELAY_BUF[a]=SILENCIO;
		}
		for (int b = 0; b < cantTECLAS_MAX; b++){
			COLA_TECLAS[b]=SILENCIO;
		}

	    Canal_Libre = Chip_GPDMA_GetFreeChannel ( LPC_GPDMA , 0 );

	    /* Configuracion del DMA */

	    CLOCK_DAC_HZ = Chip_Clock_GetSystemClockRate();
	    CLOCK_DAC_HZ =  CLOCK_DAC_HZ/4;

	    Chip_DAC_SetDMATimeOut(LPC_DAC, timeoutDMA);

	    Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DBLBUF_ENA | DAC_CNT_ENA | DAC_DMA_ENA);

	    Chip_GPDMA_Init ( LPC_GPDMA );

		while (1) {

			xQueuePeek( cola_estado, &estadoTeclado, (portTickType) 0 );

			xQueuePeek( cola_delay, &DELAY, (portTickType) 0 );
			if(DELAY != 0) {
				SET_DELAY = 1;
				T_DELAY = (DELAY * 100)/ T_TECLAS;
			}
			else SET_DELAY = 0;

			if(ind_DELAY < CANT_DELAY) ind_DELAY++;

			if(SET_DELAY == 0){

				// Guarda las teclas que esten apretadas en un vector
				for(i=0; i<TECLAS ; i++){
					if(estadoTeclado & (1<<i) && j < cantTECLAS_MAX){
						if((COLA_TECLAS[j-1] != i) && (COLA_TECLAS[j]==SILENCIO)){
							COLA_TECLAS[j]=i;
							if(j < cantTECLAS_MAX - 1)j++;
						}
					}
				}

				// Va cambiando la frecuencia según qué tecla está tocada, multiplexa si hay varias
				if(estadoTeclado !=0 && j>=0){
					// Fija la separacion entre muestras.
					timeoutDMA = CLOCK_DAC_HZ / ( FREC_NOTA[COLA_TECLAS[0]] * NUMERO_MUESTRAS );
					Chip_DAC_SetDMATimeOut(LPC_DAC, timeoutDMA);
					if(j > 0) j--;
					for(i=1; i < cantTECLAS_MAX ; i++){
						COLA_TECLAS[i-1] = COLA_TECLAS[i];
					}
					COLA_TECLAS[cantTECLAS_MAX-1]=SILENCIO;
				}
			}
			else {

				if(j > 0) j--;
				// Si llego al tope del bufer retrocede las teclas que se apretaron la última vez
				if(j > CANT_DELAY){
					j=CANT_DELAY;
					for(i=0; i<TECLAS ; i++)
						if(estadoTeclado_PREV & (1<<i))
							j--;
				}

				for(i=1; i < CANT_DELAY ; i++){
					DELAY_BUF[i-1] = DELAY_BUF[i];
				}
				DELAY_BUF[CANT_DELAY-1]=SILENCIO;

				for(i=0; i<TECLAS ; i++){
					if(estadoTeclado & (1<<i)){
						if(DELAY_BUF[j]==SILENCIO)DELAY_BUF[j]=i;
						if(DELAY_BUF[j+T_DELAY]==SILENCIO)DELAY_BUF[j+T_DELAY]=i;
						j++;
					}
				}

				if(estadoTeclado == 0 && DELAY_BUF[0]== SILENCIO){
					DELAY_BUF[j]=SILENCIO;
					j++;
				}
				// Fija la separacion entre muestras.
				timeoutDMA = CLOCK_DAC_HZ / ( FREC_NOTA[DELAY_BUF[0]] * NUMERO_MUESTRAS );
				Chip_DAC_SetDMATimeOut(LPC_DAC, timeoutDMA);

				estadoTeclado_PREV = estadoTeclado;
			}

			// Prende y apaga el transfer
			if((estadoTeclado == 0 && SET_DELAY == 0) || (DELAY_BUF[0]== SILENCIO && SET_DELAY == 1)) {
					Chip_GPDMA_Stop(LPC_GPDMA, Canal_Libre);
					DMA_SET=0;
			}
			else {
				if(DMA_SET == 0){
					estadoDMA = Chip_GPDMA_SGTransfer (LPC_GPDMA , Canal_Libre ,
							&DMA_LLI_buffer , GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
					DMA_SET=1;
				}
			}
			if(estadoDMA == ERROR){
				// Reinicio DMA
				Chip_GPDMA_Init ( LPC_GPDMA );
				estadoDMA = SUCCESS;
			}
			vTaskDelay(T_TECLAS);
		}
}



/*****************************************************************************
 * Main
 ****************************************************************************/

/**
 * @brief	Main
 * @return	Nada, la funcion no deberá salir
 */
int main(void)
{
	prvSetupHardware();

	recurso_estadoteclado = xSemaphoreCreateMutex();
	recurso_volumen = xSemaphoreCreateMutex();
	recurso_formadeonda = xSemaphoreCreateMutex();
	recurso_filtro = xSemaphoreCreateMutex();
	recurso_fci = xSemaphoreCreateMutex();
	recurso_fcs = xSemaphoreCreateMutex();
	recurso_attack = xSemaphoreCreateMutex();
	recurso_delay = xSemaphoreCreateMutex();
	recurso_over = xSemaphoreCreateMutex();


	cola_encoders = xQueueCreate(LARGO_COLA_ENCODERS, sizeof(encoder)); 	//Creamos la cola que contendra el delta del encoder

	cola_estado = xQueueCreate(LARGO_COLA, sizeof(uint32_t)); 	//Creamos la cola que contendra el estado de la matriz del teclado,
																//si apreto la tecla 1 se pone en 1 el bit menos significativo y
																//si apreto la tecla 32 el mas signficativo
	cola_estadoUSB = xQueueCreate(LARGO_COLA, sizeof(uint32_t)); 	//Creamos la cola que contendra el estado de la matriz del teclado,

	cola_lcdCoord = xQueueCreate(LARGO_COLA, sizeof(lcdCoord)); //creamos la cola que contendra la estructura de x,y y pagina del display lcd

	cola_formaDeOnda = xQueueCreate(LARGO_COLA, sizeof(uint32_t));

	cola_volumen = xQueueCreate(LARGO_COLA, sizeof(uint32_t));
	cola_fci = xQueueCreate(LARGO_COLA, sizeof(uint32_t));
	cola_fcs = xQueueCreate(LARGO_COLA, sizeof(uint32_t));
	cola_over = xQueueCreate(LARGO_COLA, sizeof(uint32_t));
	cola_att = xQueueCreate(LARGO_COLA, sizeof(uint32_t));
	cola_delay = xQueueCreate(LARGO_COLA, sizeof(uint32_t));
	cola_filtro = xQueueCreate(LARGO_COLA, sizeof(uint32_t));
	cola_menu_teclado = xQueueCreate(LARGO_COLA, sizeof(uint32_t)); //tendra los valores
																	//0 para teclado general
																	//1 para grabar en i2c

	cola_opcion_elegida = xQueueCreate(LARGO_COLA, sizeof(uint32_t)); //tendra los valores
																	//0 para guarda config
																	//1 para cargar config


	xTaskCreate(vInicializarUSB, (signed char *) "InicializarUSB",
						configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 3UL),
						(xTaskHandle *) NULL);

	xTaskCreate(vInicializarColas, (signed char *) "InicializarColas",
					configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2UL),
					(xTaskHandle *) NULL);

	xTaskCreate(vControlDisplay, (signed char *) "ControlDisplay",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) Display);

	xTaskCreate(vGenFormaOnda, (signed char *) "GenFormaOnda",
			configMINIMAL_STACK_SIZE * 5, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) GenOnda);

	xTaskCreate(vSonidoTeclas, (signed char *) "SonidoTeclas",
				configMINIMAL_STACK_SIZE * 5, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) Teclas);

	xTaskCreate(vLeerBotones, (signed char *) "LeerBotones",
					configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
					(xTaskHandle *) Botones);

	xTaskCreate(vLeerTeclado, (signed char *) "LeerTeclado",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	xTaskCreate(vEncoders, (signed char *) "Encoders",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) Encoders);

	/* Empieza el Scheduler */
	vTaskStartScheduler();

	/* Nunca deberá llegar hasta acá */
	return 1;
}

/**
 * @}
 */
