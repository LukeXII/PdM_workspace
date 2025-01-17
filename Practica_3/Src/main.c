/**
 ******************************************************************************
 * @file    UART/UART_Printf/Src/main.c
 * @author  MCD Application Team
 * @brief   This example shows how to retarget the C library printf function
 *          to the UART.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_delay.h"

/** @addtogroup STM32F4xx_HAL_Examples
 * @{
 */

/** @addtogroup UART_Printf
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
typedef enum my_LEDs{LED_1, LED_2, LED_3} myLEDs;		// Enumeracion de los LEDs
enum secuencias{SEC_1, SEC_2};							// Enumeracion de las secuencias de prendido

/* Private define ------------------------------------------------------------*/

// Duracion de cada delay
#define COUNT_DELAY 	200
#define DEBOUNCE_DELAY	20

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const myLEDs secuencia1[] = {LED_1, LED_2, LED_3};		// Secuencias de encendido de LEDs
const myLEDs secuencia2[] = {LED_1, LED_3, LED_2};

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

void turnOnLED(myLEDs activeLED);

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
	/* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
	 */
	HAL_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	BSP_LED_Init(LED1);							// Inicializa todos los LED
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	delay_t myDelay, buttonDelay;

	delayInit(&myDelay, COUNT_DELAY);			// Inicializa el delay del LED
	delayInit(&buttonDelay, DEBOUNCE_DELAY);	// Inicializa el delay del antirrebote

	enum secuencias secuenciaActiva = SEC_1;	// Inicializa en secuencia 1

	uint8_t index = 0;
	bool_t edgeDetected = false;				// Variable que indica si se detecto un flanco ascendente
	bool_t latched = false;						// Variable que indica si se esta manteniendo apretado el boton

	/* Infinite loop */
	while (1)
	{

		if(delayRead(&myDelay))						// Si transcurrieron los 200 ms se debe prender otro LED
		{
			index = (index == 2) ? 0 : index + 1;	// Avanza el contador de la secuencia de encendido. Si llego al final, vuelve a 0

			if(secuenciaActiva == SEC_1)			// Llama a la funcion que prende el LED dependiendo de la secuencia activa
				turnOnLED(secuencia1[index]);
			else
				turnOnLED(secuencia2[index]);

		}


		if(delayRead(&buttonDelay) && edgeDetected && BSP_PB_GetState(BUTTON_USER))			// Si se detecto un flanco, paso el tiempo de antirrebote y el boton sigue apretado, entonces se toma como valido
		{
			if(!latched)																	// Si no esta latcheado el boton, entonces se cambia la secuencia y de ahora en mas se considera al boton latcheado
			{
				secuenciaActiva = (secuenciaActiva == SEC_1) ? SEC_2 : SEC_1;
				latched = true;
			}
		}

		if(BSP_PB_GetState(BUTTON_USER))
		{
			if(!edgeDetected)																// Si se detecta el primer flanco, se dispara el delay antirrebote
			{
				edgeDetected = true;
				delayRead(&buttonDelay);
			}
		}
		else																				// Si no esta presionado, se elimina el latch y la deteccion de flanco
		{
			edgeDetected = false;
			latched = false;
		}

	}
}
// Entradas: LED que debe prenderse
// Salidas: Ninguna
// Funcion: Prende el LED correspondiente y apaga los demas
void turnOnLED(myLEDs activeLED)
{
	switch(activeLED)
	{
		case LED_1:					// Prende el LED 1 y apaga el 2 y el 3
				BSP_LED_On(LED1);
				BSP_LED_Off(LED3);
				BSP_LED_Off(LED2);
		break;

		case LED_2:					// Prende el LED 2 y apaga el 1 y el 3
				BSP_LED_On(LED2);
				BSP_LED_Off(LED1);
				BSP_LED_Off(LED3);
		break;

		case LED_3:					// Prende el LED 3 y apaga el 1 y el 2
				BSP_LED_On(LED3);
				BSP_LED_Off(LED2);
				BSP_LED_Off(LED1);
		break;
	}
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 180000000
 *            HCLK(Hz)                       = 180000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 8000000
 *            PLL_M                          = 8
 *            PLL_N                          = 360
 *            PLL_P                          = 2
 *            PLL_Q                          = 7
 *            PLL_R                          = 2
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 5
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 360;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	if(HAL_PWREx_EnableOverDrive() != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}
}
/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void)
{
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1)
	{
	}
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
