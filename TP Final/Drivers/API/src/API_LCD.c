/*
 * API_LCD.c
 *
 *  Created on: Apr 9, 2022
 *      Author: Lucas
 */

#include "API_LCD.h"

static LCDHandle_t deviceLCD;

bool LCD_init(void)
{

    __SPI1_CLK_ENABLE();
    deviceLCD.SPI_Handle.Instance 				= SPI1;
    deviceLCD.SPI_Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    deviceLCD.SPI_Handle.Init.Direction 		= SPI_DIRECTION_2LINES;
    deviceLCD.SPI_Handle.Init.CLKPhase 			= SPI_PHASE_2EDGE;
    deviceLCD.SPI_Handle.Init.CLKPolarity 		= SPI_POLARITY_HIGH;
    deviceLCD.SPI_Handle.Init.CRCCalculation 	= SPI_CRCCALCULATION_DISABLED;
    deviceLCD.SPI_Handle.Init.DataSize 			= SPI_DATASIZE_8BIT;
    deviceLCD.SPI_Handle.Init.FirstBit 			= SPI_FIRSTBIT_LSB;
    deviceLCD.SPI_Handle.Init.NSS 				= SPI_NSS_SOFT;
    deviceLCD.SPI_Handle.Init.TIMode 			= SPI_TIMODE_DISABLED;
    deviceLCD.SPI_Handle.Init.Mode 				= SPI_MODE_MASTER;

    if (HAL_SPI_Init(&deviceLCD.SPI_Handle) != HAL_OK)
    {
        asm("bkpt 255");
    }


}

void LCD_writeText(const char * str, color, position, size)
{



	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&deviceLCD.SPI_Handle, (uint8_t *)str, , 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

void LCD_setBackgroundColor(color)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	//HAL_SPI_Transmit(&deviceLCD.SPI_Handle, (uint8_t *)str, , 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

}
