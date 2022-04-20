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

#define LCD_SCREEN_HEIGHT 	240
#define LCD_SCREEN_WIDTH 	320

//RESET PIN AND PORT, STANDARD GPIO
#define	LCD_RST_PORT		GPIOC
#define	LCD_RST_PIN			GPIO_PIN_10

//CS PIN AND PORT, STANDARD GPIO
#define	LCD_DC_PORT			GPIOC
#define	LCD_DC_PIN			GPIO_PIN_12

//DC PIN AND PORT, STANDARD GPIO
#define	LCD_CS_PORT			GPIOC
#define	LCD_CS_PIN			GPIO_PIN_14

typedef struct
{
	SPI_HandleTypeDef SPI_Handle;
	uint16_t LCDPixelSizeX;
	uint16_t LCDPixelSizeY;
}LCDHandle_t;

// Configura los pines del LCD
void LCD_Config(void);

// Inicializa el LCD
void LCD_Init(void);

void LCD_Write_Command(uint8_t Command);

void LCD_Write_Data(uint8_t Data);

void LCD_SPI_Send(unsigned char SPI_Data);

// Escribe un texto sobre la pantalla en la posición indicada
//void LCD_writeText(const char * str, color, position, size);

// Setea el color de fondo de la pantalla
//void LCD_setBackgroundColor(const LCDHandle_t  * LCD, color);

//
void LCD_refresh(void);

//void LCD_Error_Handler(void);

#endif /* API_INC_API_LCD_H_ */
