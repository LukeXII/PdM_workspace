/*
 * API_debounce.c
 *
 *  Created on: Mar 27, 2022
 *      Author: Lucas
 */

#include "API_debounce.h"

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING
}debounceState_t;

static delay_t buttonDelay;
static debounceState_t estadoActual;
static bool_t keyPressed;

bool_t readKey()
{
	if(keyPressed)
	{
		keyPressed = false;
		return true;
	}
	else
		return false;
}

// Funcion: inicializa la maquina de estados con el estado inicial y las variables internas al mismo
// Entrada; Ninguna
// Salida: Ninguna
void debounceFSM_init()
{
	estadoActual = BUTTON_UP;							// Asigna el estado inicial
	delayInit(&buttonDelay, DEBOUNCE_DELAY);			// Inicializacion del delay
	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);			// Inicializa el boton
}

// Funcion: actualiza la maquina de estados evaluando si sucedio alguno de los eventos que la hacen conmutar
// Entrada; Ninguna
// Salida: Ninguna
void debounceFSM_update()
{

	switch (estadoActual)
	{
		case BUTTON_UP:

			if(BSP_PB_GetState(BUTTON_USER))			// Si se detecta un flanco ascendente, inicializa el timer y avanza al siguiente estado
			{
				delayRead(&buttonDelay);
				estadoActual = BUTTON_FALLING;
			}

		break;

		case BUTTON_FALLING:

			if(delayRead(&buttonDelay))					// Una vez transcurrido el tiempo de debounce, pregunta si el boton sigue apretado
			{
				if(BSP_PB_GetState(BUTTON_USER))
				{
					estadoActual = BUTTON_DOWN;			// Si sigue apretado, avanza al siguiente estado y llama a la funcion de boton presionado
					buttonPressed();
				}
				else
					estadoActual = BUTTON_UP;			// Si no sigue apretado, vuelve al estado anterior
			}

		break;

		case BUTTON_DOWN:

			if(!BSP_PB_GetState(BUTTON_USER))			// Si se detecta un flanco descendente, inicializa el timer y avanza al siguiente estado
			{
				delayRead(&buttonDelay);
				estadoActual = BUTTON_RISING;
			}

		break;

		case BUTTON_RISING:

			if(delayRead(&buttonDelay))					// Una vez transcurrido el tiempo de debounce, pregunta si el boton no esta apretado
			{
				if(!BSP_PB_GetState(BUTTON_USER))
				{
					estadoActual = BUTTON_UP;			// Si no esta apretado, avanza al siguiente estado y llama a la funcion de boton liberado
					buttonReleased();
				}
				else
					estadoActual = BUTTON_DOWN;			// Si sigue apretado, vuelve al estado anterior
			}


		break;

		default:
			//Si algo modificó la variable estadoActual a un estado no válido llevo la MEF a un lugar seguro, por ejemplo, la reinicio:
			//controlDeErrores();
			debounceFSM_init();

		break;
	}

}

// Funcion: instrucciones a ejecutar cuando se detecta que se presiono el boton
// Entrada: Ninguna
// Salida: Ninguna
void buttonPressed()
{

}

// Funcion: instrucciones a ejecutar cuando se detecta que se libero el boton
// Entrada: Ninguna
// Salida: Ninguna
void buttonReleased()
{
	keyPressed = true;
}
