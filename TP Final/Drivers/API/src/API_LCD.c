/*
 * API_LCD.c
 *
 *  Created on: Apr 9, 2022
 *      Author: Lucas
 */

#include "API_LCD.h"

bool initLCD(const LCDHandle_t  * LCD, )
{
	HAL_SPI_Init(LCD.SPI_Handle);


}