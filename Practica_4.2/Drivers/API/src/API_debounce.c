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

void debounceFSM_init()
{
	estadoActual = BUTTON_UP;
	delayInit(&buttonDelay, DEBOUNCE_DELAY);			// Inicializacion del delay
	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
}

void debounceFSM_update()
{

	switch (estadoActual)
	{
		case BUTTON_UP:

			if(BSP_PB_GetState(BUTTON_USER))
			{
				delayRead(&buttonDelay);
				estadoActual = BUTTON_FALLING;
			}

		break;

		case BUTTON_FALLING:

			if(delayRead(&buttonDelay))
			{
				if(BSP_PB_GetState(BUTTON_USER))
					estadoActual = BUTTON_DOWN;
				else
					estadoActual = BUTTON_UP;
			}

		break;

		case BUTTON_DOWN:

			if(!BSP_PB_GetState(BUTTON_USER))
			{
				delayRead(&buttonDelay);
				estadoActual = BUTTON_RISING;
			}

		break;

		case BUTTON_RISING:

			if(delayRead(&buttonDelay))
			{
				if(!BSP_PB_GetState(BUTTON_USER))
				{
					estadoActual = BUTTON_UP;
					keyPressed = true;
				}
				else
					estadoActual = BUTTON_DOWN;
			}


		break;

		default:
			//Si algo modificó la variable estadoActual a un estado no válido llevo la MEF a un lugar seguro, por ejemplo, la reinicio:
			//controlDeErrores();
			debounceFSM_init();

		break;
	}

}
