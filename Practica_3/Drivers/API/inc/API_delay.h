/*
 * API_delay.h
 *
 *  Created on: Mar 19, 2022
 *      Author: lucas
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */

// Delay API types

typedef uint32_t tick_t; 	//
typedef bool bool_t;      	// Incluida stdbool.h
typedef struct
{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

// Delay API functions

void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );

#endif /* API_INC_API_DELAY_H_ */
