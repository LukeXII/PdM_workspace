/*
 * API_LCD.h
 *
 *  Created on: Apr 9, 2022
 *      Author: Lucas
 */

#ifndef API_INC_API_LCD_H_
#define API_INC_API_LCD_H_

#include <stdbool.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */

typedef struct
{
	SPI_HandleTypeDef SPI_Handle;
	uint16_t LCDPixelSizeX;
	uint16_t LCDPixelSizeY;
}LCDHandle_t;

// Inicializa el handle del LCD
void LCD_init (void);

// Escribe un texto sobre la pantalla en la posición indicada
//void LCD_writeText(const char * str, color, position, size);

// Setea el color de fondo de la pantalla
//void LCD_setBackgroundColor(const LCDHandle_t  * LCD, color);

//
void LCD_refresh(void);

#endif /* API_INC_API_LCD_H_ */
