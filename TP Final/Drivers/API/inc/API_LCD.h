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
#include "stm32f4xx_nucleo_144.h"

#define LCD_SCREEN_HEIGHT 	240
#define LCD_SCREEN_WIDTH 	320

#define BLACK       		0x0000
#define NAVY        		0x000F
#define DARKGREEN   		0x03E0
#define DARKCYAN    		0x03EF
#define MAROON      		0x7800
#define PURPLE      		0x780F
#define OLIVE       		0x7BE0
#define LIGHTGREY   		0xC618
#define DARKGREY    		0x7BEF
#define BLUE        		0x001F
#define GREEN       		0x07E0
#define CYAN        		0x07FF
#define RED         		0xF800
#define MAGENTA     		0xF81F
#define YELLOW     			0xFFE0
#define WHITE       		0xFFFF
#define ORANGE      		0xFD20
#define GREENYELLOW 		0xAFE5
#define PINK        		0xF81F

#define SCREEN_VERTICAL_1	0
#define SCREEN_HORIZONTAL_1	1
#define SCREEN_VERTICAL_2	2
#define SCREEN_HORIZONTAL_2	3

//RESET PIN AND PORT, STANDARD GPIO
#define	LCD_PORT_RST		GPIOC
#define	LCD_PIN_RST			GPIO_PIN_9

//CS PIN AND PORT, STANDARD GPIO
#define	LCD_PORT_DC			GPIOC
#define	LCD_PIN_DC			GPIO_PIN_8

//DC PIN AND PORT, STANDARD GPIO
#define	LCD_PORT_CS			GPIOC
#define	LCD_PIN_CS			GPIO_PIN_10

#define	LCD_PORT_LED		GPIOC
#define	LCD_PIN_LED			GPIO_PIN_11

#define BURST_MAX_SIZE 		500

typedef struct
{
	SPI_HandleTypeDef SPI_Handle;
	uint16_t LCDSizeX;
	uint16_t LCDSizeY;
}LCDHandle_t;

// Configura los pines del LCD
void LCD_Config(void);

// Inicializa el LCD
void LCD_Init(void);

void LCD_Write_Command(uint8_t Command);

void LCD_Write_Data(uint8_t Data);

void LCD_SPI_Send(unsigned char SPI_Data);

void LCD_Set_Rotation(uint8_t Rotation);

void LCD_Draw_Colour_Burst(uint16_t Colour, uint32_t Size);

void LCD_Fill_Screen(uint16_t Colour);

void LCD_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);

void LCD_Draw_Pixel(uint16_t X, uint16_t Y, uint16_t Colour);
//
void LCD_refresh(void);

//void LCD_Error_Handler(void);

#endif /* API_INC_API_LCD_H_ */
