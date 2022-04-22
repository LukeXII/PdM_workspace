/*
 * API_GPIO.c
 *
 *  Created on: Apr 21, 2022
 *      Author: Lucas
 */

#include "API_GPIO.h"

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

    /*Configure GPIO pins */
    GPIO_InitStruct.Pin = LCD_PIN_RST | LCD_PIN_DC | LCD_PIN_CS | LCD_PIN_LED;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOC, LCD_PIN_LED, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_RST | LCD_PIN_DC | LCD_PIN_CS, GPIO_PIN_RESET);

}
