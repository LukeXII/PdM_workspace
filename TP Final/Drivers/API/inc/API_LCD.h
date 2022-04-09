/*
 * API_LCD.h
 *
 *  Created on: Apr 9, 2022
 *      Author: Lucas
 */

#ifndef API_INC_API_LCD_H_
#define API_INC_API_LCD_H_

#include "stm32f4xx_hal.h"  		/* <- HAL include */

typedef struct
{
	SPI_HandleTypeDef SPI_Handle;

}LCDHandle_t;

// Inicializa el handle del LCD
// bool initLCD(const LCDHandle_t  * LCD, );

// Escribe un texto sobre la pantalla en la posición indicada
// void writeLCD(const LCDHandle_t  * LCD, const char * str, color, position, size)

// Setea el color de fondo de la pantalla
// void setBackgroundColor(const LCDHandle_t  * LCD, color)


#endif /* API_INC_API_LCD_H_ */