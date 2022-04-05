/*
 * API_delay.c
 *
 *  Created on: Mar 19, 2022
 *      Author: lucas
 */

#include "API_delay.h"

// Entrada: Puntero al delay y su duracion delay en ms
// Salida: Ninguna
// Funcion: Inicializa los parametros internos del delay
void delayInit( delay_t * delay, tick_t duration )
{
	if((delay != NULL) && (duration > 0))			// Verifica que el puntero sea valido y que la duracion sea un valor positivo y mayor a cero
	{
		delay->duration = duration;
		delay->running = false;						// Inicializa el delay detenido
	}
}

// Entrada: Puntero al delay
// Salida: Bool que indica si ya transcurrio el tiempo del delay o no. True en el primer caso, false en el segundo
// Funcion: Comprueba si ya transcurrio el tiempo del delay
bool_t delayRead( delay_t * delay )
{
	bool timeReached = false;

	if(delay != NULL)
	{
		if(delay->running)							// Si el delay esta corriendo, calcula si ya paso el tiempo
		{
			if((HAL_GetTick() - delay->startTime) >= delay->duration)		// Si ya paso el tiempo, guarda el timestamp actual
			{
				timeReached = true;
				delay->startTime = HAL_GetTick();
			}
		}
		else										// Si el delay esta detenido, lo reanuda y guarda el timestamp actual
		{
			delay->startTime = HAL_GetTick();
			delay->running = true;
		}
	}

	return timeReached;
}

// Entrada: Puntero al delay y su duracion delay en ms
// Salida: Ninguna
// Funcion: Cambia la duracion del delay, sin importar si esta corriendo o no
void delayWrite( delay_t * delay, tick_t duration )
{
	if((delay != NULL) && (duration > 0))			// Verifica que el puntero sea valido y que la duracion sea un valor positivo y mayor a cero
		delay->duration = duration;

}

