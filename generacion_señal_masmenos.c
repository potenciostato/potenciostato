#include <stdlib.h>
#include <stdio.h>

#define GAN_AT 165 //100*3300mV/2000 se multiplica por 100 para no utilizar punto flotante
#define CANT_MUESTRAS_MAX 1000
#define CANT_BITS_DAC 10
#define PTO_MEDIO 1000 //mV

/*
	Los parametros de entrada son:
	- Punto inicial [mV]
	- Pico maximo [mV]
	- Punto final [mV]
	- Velocidad [mV/seg]
	
	Los parametros de salida son:
	- vector de CANT_MUESTAS_MAX posiciones con la señal generada
	- timeout (del timer) con el cual se deberá recorrer cada valor para lograr la velocidad elegida
*/
void main(){
	int i, j, aux = 0;
	int cant_valores_dac = 1;

	int pto_inicial = -1000; //mV
	int pto_picomax = 1000; //mV
	int pto_final = -1000; //mV
	int velocidad = 50; //mV
	int vector_valores_subida[CANT_MUESTRAS_MAX] = {0};
	int vector_valores_bajada[CANT_MUESTRAS_MAX] = {0};
	int ms_entrepuntos_subida;
	int ms_entrepuntos_bajada;
	
	velocidad = velocidad * GAN_AT; //50*165 = 8250
	pto_inicial = pto_inicial * GAN_AT; //-1000 * 165 = -165000
	pto_picomax = pto_picomax * GAN_AT; //1000 * 165 = 165000
	pto_final = pto_final * GAN_AT; //-1000 * 165 = -165000
	
	// se calcula la potencia
	for (i = 0; i < CANT_BITS_DAC; i++){
		cant_valores_dac *= 2;
	}
	cant_valores_dac -= 1;

	printf("Cant valores DAC: %d\n",cant_valores_dac);
	
	// se obtiene el vector de valores ya escalado para mV (con la ganancia tenida en cuenta)
	for (i = 0; i < CANT_MUESTRAS_MAX; i++){
		vector_valores_subida[i] = ((pto_picomax-pto_inicial)/(CANT_MUESTRAS_MAX)*i);
	}

	for (i = 0; i < CANT_MUESTRAS_MAX; i++){
		printf("%d, ",vector_valores_subida[i]);
	}
	printf("\n");
	
	// se calculan los milisegundos que deberan trascurrir entre puntos
	ms_entrepuntos_subida = 2000*(pto_picomax-pto_inicial)/(velocidad*CANT_MUESTRAS_MAX);
	printf("Milisegundos entre puntos: %d\n", ms_entrepuntos_subida);

	
	
	
	// se obtiene el vector de valores ya escalado para mV (con la ganancia tenida en cuenta)
	for (i = 0; i < CANT_MUESTRAS_MAX; i++){
		vector_valores_bajada[i] = vector_valores_subida[CANT_MUESTRAS_MAX-1]+
			((pto_final-pto_picomax)/(CANT_MUESTRAS_MAX)*i);
	}

	for (i = 0; i < CANT_MUESTRAS_MAX; i++){
		printf("%d, ",vector_valores_bajada[i]);
	}
	printf("\n");
	
	// se calculan los milisegundos que deberan trascurrir entre puntos
	ms_entrepuntos_bajada = 2000*(pto_picomax-pto_final)/(velocidad*CANT_MUESTRAS_MAX);
	printf("Milisegundos entre puntos: %d\n", ms_entrepuntos_bajada);

}
