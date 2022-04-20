/*
 * API_LCD.c
 *
 *  Created on: Apr 9, 2022
 *      Author: Lucas
 */

#include "API_LCD.h"

static LCDHandle_t deviceLCD;

void LCD_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	deviceLCD.LCDPixelSizeX = LCD_SCREEN_WIDTH;
	deviceLCD.LCDPixelSizeY = LCD_SCREEN_HEIGHT;

    __SPI1_CLK_ENABLE();
    deviceLCD.SPI_Handle.Instance 				= SPI1;
    deviceLCD.SPI_Handle.Init.Mode 				= SPI_MODE_MASTER;
    deviceLCD.SPI_Handle.Init.Direction 		= SPI_DIRECTION_2LINES;
    deviceLCD.SPI_Handle.Init.DataSize 			= SPI_DATASIZE_8BIT;
    deviceLCD.SPI_Handle.Init.CLKPolarity 		= SPI_POLARITY_HIGH;
    deviceLCD.SPI_Handle.Init.CLKPhase 			= SPI_PHASE_2EDGE;
    deviceLCD.SPI_Handle.Init.NSS 				= SPI_NSS_SOFT;
    deviceLCD.SPI_Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    deviceLCD.SPI_Handle.Init.FirstBit 			= SPI_FIRSTBIT_LSB;
    deviceLCD.SPI_Handle.Init.TIMode 			= SPI_TIMODE_DISABLED;
    deviceLCD.SPI_Handle.Init.CRCCalculation 	= SPI_CRCCALCULATION_DISABLED;
    deviceLCD.SPI_Handle.Init.CRCPolynomial 	= 7;

    if (HAL_SPI_Init(&deviceLCD.SPI_Handle) != HAL_OK)
    {
        //asm("bkpt 255");
    }

    /*Configure GPIO pins : PCPin PCPin PCPin */
    GPIO_InitStruct.Pin = LCD_CS_PIN | LCD_DC_PIN | LCD_RST_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOC, LCD_CS_PIN | LCD_DC_PIN | LCD_RST_PIN, GPIO_PIN_RESET);

}

void LCD_Init(void)
{
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);				//Enables LCD
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);				//CS OFF

	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);

	//SOFTWARE RESET
	LCD_Write_Command(0x01);
	HAL_Delay(1000);

	//POWER CONTROL A
	LCD_Write_Command(0xCB);
	LCD_Write_Data(0x39);
	LCD_Write_Data(0x2C);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x34);
	LCD_Write_Data(0x02);

	//POWER CONTROL B
	LCD_Write_Command(0xCF);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0xC1);
	LCD_Write_Data(0x30);

	//DRIVER TIMING CONTROL A
	LCD_Write_Command(0xE8);
	LCD_Write_Data(0x85);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x78);

	//DRIVER TIMING CONTROL B
	LCD_Write_Command(0xEA);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x00);

	//POWER ON SEQUENCE CONTROL
	LCD_Write_Command(0xED);
	LCD_Write_Data(0x64);
	LCD_Write_Data(0x03);
	LCD_Write_Data(0x12);
	LCD_Write_Data(0x81);

	//PUMP RATIO CONTROL
	LCD_Write_Command(0xF7);
	LCD_Write_Data(0x20);

	//POWER CONTROL,VRH[5:0]
	LCD_Write_Command(0xC0);
	LCD_Write_Data(0x23);

	//POWER CONTROL,SAP[2:0];BT[3:0]
	LCD_Write_Command(0xC1);
	LCD_Write_Data(0x10);

	//VCM CONTROL
	LCD_Write_Command(0xC5);
	LCD_Write_Data(0x3E);
	LCD_Write_Data(0x28);

	//VCM CONTROL 2
	LCD_Write_Command(0xC7);
	LCD_Write_Data(0x86);

	//MEMORY ACCESS CONTROL
	LCD_Write_Command(0x36);
	LCD_Write_Data(0x48);

	//PIXEL FORMAT
	LCD_Write_Command(0x3A);
	LCD_Write_Data(0x55);

	//FRAME RATIO CONTROL, STANDARD RGB COLOR
	LCD_Write_Command(0xB1);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x18);

	//DISPLAY FUNCTION CONTROL
	LCD_Write_Command(0xB6);
	LCD_Write_Data(0x08);
	LCD_Write_Data(0x82);
	LCD_Write_Data(0x27);

	//3GAMMA FUNCTION DISABLE
	LCD_Write_Command(0xF2);
	LCD_Write_Data(0x00);

	//GAMMA CURVE SELECTED
	LCD_Write_Command(0x26);
	LCD_Write_Data(0x01);

	//POSITIVE GAMMA CORRECTION
	LCD_Write_Command(0xE0);
	LCD_Write_Data(0x0F);
	LCD_Write_Data(0x31);
	LCD_Write_Data(0x2B);
	LCD_Write_Data(0x0C);
	LCD_Write_Data(0x0E);
	LCD_Write_Data(0x08);
	LCD_Write_Data(0x4E);
	LCD_Write_Data(0xF1);
	LCD_Write_Data(0x37);
	LCD_Write_Data(0x07);
	LCD_Write_Data(0x10);
	LCD_Write_Data(0x03);
	LCD_Write_Data(0x0E);
	LCD_Write_Data(0x09);
	LCD_Write_Data(0x00);

	//NEGATIVE GAMMA CORRECTION
	LCD_Write_Command(0xE1);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x0E);
	LCD_Write_Data(0x14);
	LCD_Write_Data(0x03);
	LCD_Write_Data(0x11);
	LCD_Write_Data(0x07);
	LCD_Write_Data(0x31);
	LCD_Write_Data(0xC1);
	LCD_Write_Data(0x48);
	LCD_Write_Data(0x08);
	LCD_Write_Data(0x0F);
	LCD_Write_Data(0x0C);
	LCD_Write_Data(0x31);
	LCD_Write_Data(0x36);
	LCD_Write_Data(0x0F);

	//EXIT SLEEP
	LCD_Write_Command(0x11);
	HAL_Delay(120);

	//TURN ON DISPLAY
	LCD_Write_Command(0x29);



}

/* Send command (char) to LCD */
void LCD_Write_Command(uint8_t Command)
{
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
	LCD_SPI_Send(Command);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

/* Send Data (char) to LCD */
void LCD_Write_Data(uint8_t Data)
{
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	LCD_SPI_Send(Data);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

/*Send data (char) to LCD*/
void LCD_SPI_Send(unsigned char SPI_Data)
{
	HAL_SPI_Transmit(&(deviceLCD.SPI_Handle), &SPI_Data, 1, 1);
}

/*
void LCD_writeText(const char * str, color, position, size)
{

	if((str != NULL) &&
		(size > 0) &&
		(size <= 10) &&
		(position >= 0) &&
		(position <= deviceLCD.LCDPixelSizeX) &&
		(position >= 0) &&
		(position <= deviceLCD.LCDPixelSizeY) &&
		(color <= 100) &&
		(color >= 0))
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		//HAL_SPI_Transmit(&deviceLCD.SPI_Handle, (uint8_t *)str, , 10);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	}
	else
	{

	}

}

void LCD_setBackgroundColor(color)
{

	//if((color <= ) && (color >= ))
	//{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		//HAL_SPI_Transmit(&deviceLCD.SPI_Handle, (uint8_t *)str, , 10);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

	//}
		else
		{

		}

}

void LCD_refresh(void)
{


}

void LCD_Error_Handler(void)
{

}


*/
