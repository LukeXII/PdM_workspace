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

	deviceLCD.LCDSizeX = LCD_SCREEN_WIDTH;
	deviceLCD.LCDSizeY = LCD_SCREEN_HEIGHT;

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

    if (HAL_SPI_Init(&deviceLCD.SPI_Handle) != HAL_OK)
    {
    	BSP_LED_On(LED2);
    }

/*
    GPIO_InitStruct.Pin = 12;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
*/

}

void LCD_Init(void)
{
	LCD_Config();

	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);				//Enables LCD

	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_RESET);			//CS OFF

	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);

	//SOFTWARE RESET
	LCD_Write_Command(0x01);
	HAL_Delay(5);

/*
	LCD_Write_Command(0xEF);
	LCD_Write_Data(0x03);
	LCD_Write_Data(0x80);
	LCD_Write_Data(0x02);
*/
	LCD_Write_Command(0xCA);
	LCD_Write_Data(0xC3);
	LCD_Write_Data(0x08);
	LCD_Write_Data(0x50);

	//POWER CONTROL B
	LCD_Write_Command(0xCF);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0xC1);
	LCD_Write_Data(0x30);

	//POWER ON SEQUENCE CONTROL
	LCD_Write_Command(0xED);
	LCD_Write_Data(0x64);
	LCD_Write_Data(0x03);
	LCD_Write_Data(0x12);
	LCD_Write_Data(0x81);

	//DRIVER TIMING CONTROL A
	LCD_Write_Command(0xE8);
	LCD_Write_Data(0x85);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x78);

	//POWER CONTROL A
	LCD_Write_Command(0xCB);
	LCD_Write_Data(0x39);
	LCD_Write_Data(0x2C);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x34);
	LCD_Write_Data(0x02);

	//PUMP RATIO CONTROL
	LCD_Write_Command(0xF7);
	LCD_Write_Data(0x20);

	//DRIVER TIMING CONTROL B
	LCD_Write_Command(0xEA);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x00);

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
	LCD_Write_Command(0x0B);
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

	//STARTING ROTATION
	LCD_Set_Rotation(SCREEN_VERTICAL_1);

	LCD_Fill_Screen(WHITE);

	LCD_Draw_Pixel(150, 150, BLACK);
	LCD_Draw_Pixel(100, 100, BLACK);
	LCD_Draw_Pixel(200, 200, BLACK);
	LCD_Draw_Pixel(50, 50, BLACK);

}

//FILL THE ENTIRE SCREEN WITH SELECTED COLOUR (either #define-d ones or custom 16bit)
/*Sets address (entire screen) and Sends Height*Width amount of colour information to LCD*/
void LCD_Fill_Screen(uint16_t Colour)
{
	LCD_Set_Address(0, 0, deviceLCD.LCDSizeX, deviceLCD.LCDSizeY);
	LCD_Draw_Colour_Burst(Colour, (deviceLCD.LCDSizeX)*(deviceLCD.LCDSizeY));
}

/* Set Address - Location block - to draw into */
void LCD_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
	LCD_Write_Command(0x2A);
	LCD_Write_Data(X1>>8);
	LCD_Write_Data(X1);
	LCD_Write_Data(X2>>8);
	LCD_Write_Data(X2);

	LCD_Write_Command(0x2B);
	LCD_Write_Data(Y1>>8);
	LCD_Write_Data(Y1);
	LCD_Write_Data(Y2>>8);
	LCD_Write_Data(Y2);

	LCD_Write_Command(0x2C);
}

//INTERNAL FUNCTION OF LIBRARY
/*Sends block colour information to LCD*/
void LCD_Draw_Colour_Burst(uint16_t Colour, uint32_t Size)
{
	//SENDS COLOUR
	uint32_t Buffer_Size = 0;
	if((Size*2) < BURST_MAX_SIZE)
	{
		Buffer_Size = Size;
	}
	else
	{
		Buffer_Size = BURST_MAX_SIZE;
	}

	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN_R, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_RESET);

	unsigned char chifted = 	Colour>>8;;
	unsigned char burst_buffer[Buffer_Size];
	for(uint32_t j = 0; j < Buffer_Size; j+=2)
		{
			burst_buffer[j] = 	chifted;
			burst_buffer[j+1] = Colour;
		}

	uint32_t Sending_Size = Size*2;
	uint32_t Sending_in_Block = Sending_Size/Buffer_Size;
	uint32_t Remainder_from_block = Sending_Size%Buffer_Size;

	if(Sending_in_Block != 0)
	{
		for(uint32_t j = 0; j < (Sending_in_Block); j++)
			{
			HAL_SPI_Transmit(&(deviceLCD.SPI_Handle), (unsigned char *)burst_buffer, Buffer_Size, 10);
			}
	}

	//REMAINDER!
	HAL_SPI_Transmit(&(deviceLCD.SPI_Handle), (unsigned char *)burst_buffer, Remainder_from_block, 10);

	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_SET);
}

/*Set rotation of the screen - changes x0 and y0*/
void LCD_Set_Rotation(uint8_t Rotation)
{

	uint8_t screen_rotation = Rotation;

	LCD_Write_Command(0x36);
	HAL_Delay(1);

	switch(screen_rotation)
	{
		case SCREEN_VERTICAL_1:
			LCD_Write_Data(0x40|0x08);
			deviceLCD.LCDSizeX = 240;
			deviceLCD.LCDSizeY = 320;
			break;
		case SCREEN_HORIZONTAL_1:
			LCD_Write_Data(0x20|0x08);
			deviceLCD.LCDSizeX  = 320;
			deviceLCD.LCDSizeY = 240;
			break;
		case SCREEN_VERTICAL_2:
			LCD_Write_Data(0x80|0x08);
			deviceLCD.LCDSizeX  = 240;
			deviceLCD.LCDSizeY = 320;
			break;
		case SCREEN_HORIZONTAL_2:
			LCD_Write_Data(0x40|0x80|0x20|0x08);
			deviceLCD.LCDSizeX  = 320;
			deviceLCD.LCDSizeY = 240;
			break;
		default:
			//EXIT IF SCREEN ROTATION NOT VALID!
			break;
	}
}

//DRAW PIXEL AT XY POSITION WITH SELECTED COLOUR
//
//Location is dependant on screen orientation. x0 and y0 locations change with orientations.
//Using pixels to draw big simple structures is not recommended as it is really slow
//Try using either rectangles or lines if possible
//
void LCD_Draw_Pixel(uint16_t X, uint16_t Y, uint16_t Colour)
{
	if((X < deviceLCD.LCDSizeX) && (Y < deviceLCD.LCDSizeY))			//Verifica que la posicion este dentro de los limites de la pantalla
	{
		unsigned char tempBuffer[4];
		//ADDRESS
		HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN_R, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_RESET);
		LCD_SPI_Send(0x2A);
		HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN_R, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_SET);

		//XDATA
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_RESET);
		tempBuffer[0] = X>>8;
		tempBuffer[1] = X;
		tempBuffer[2] = (X+1)>>8;
		tempBuffer[3] = X+1;
		HAL_SPI_Transmit(&(deviceLCD.SPI_Handle), tempBuffer, 4, 1);
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_SET);

		//ADDRESS
		HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN_R, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_RESET);
		LCD_SPI_Send(0x2B);
		HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN_R, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_SET);

		//YDATA
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_RESET);
		tempBuffer[0] = Y>>8;
		tempBuffer[1] = Y;
		tempBuffer[2] = (Y+1)>>8;
		tempBuffer[3] = Y+1;
		HAL_SPI_Transmit(&(deviceLCD.SPI_Handle), tempBuffer, 4, 1);
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_SET);

		//ADDRESS
		HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN_R, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_RESET);
		LCD_SPI_Send(0x2C);
		HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN_R, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_SET);

		//COLOUR
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_RESET);
		tempBuffer[0] = Colour>>8;
		tempBuffer[1] = Colour;
		HAL_SPI_Transmit(&(deviceLCD.SPI_Handle), tempBuffer, 2, 1);
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_SET);
	}

}

/* Send command (char) to LCD */
void LCD_Write_Command(uint8_t Command)
{
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN_R, GPIO_PIN_RESET);
	LCD_SPI_Send(Command);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_SET);
}

/* Send Data (char) to LCD */
void LCD_Write_Data(uint8_t Data)
{
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN_R, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_RESET);
	LCD_SPI_Send(Data);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN_R, GPIO_PIN_SET);
}

/*Send data (char) to LCD*/
void LCD_SPI_Send(unsigned char SPI_Data)
{
	HAL_SPI_Transmit(&(deviceLCD.SPI_Handle), &SPI_Data, 1, 1);
}

/*


void LCD_Error_Handler(void)
{

}


*/
