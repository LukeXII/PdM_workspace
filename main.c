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

/** @addtogroup STM32F4xx_HAL_Examples
 * @{
 */

/** @addtogroup UART_Printf
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

// Duracion de cada delay
#define DEBOUNCE_DELAY	40

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING
}debounceState_t;

/* Private functions ---------------------------------------------------------*/

// Variables globales
debounceState_t estadoActual;
delay_t buttonDelay;

const char * RISING_EDGE  = "FLANCO ASCENDENTE\r\n";
const char * FALLING_EDGE = "FLANCO DESCENDENTE\r\n";

// Prototipos de funciones
void inicializarMEF(void);
void actualizarMEF(void);

void debounceFSM_init();       	// debe cargar el estado inicial
void debounceFSM_update();    	// debe leer las entradas, resolver la lógica de
                    			// transición de estados y actualizar las salidas
void buttonPressed();			// debe togglear el LED1
void buttonReleased();        	// debe togglear el LED3

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

	BSP_LED_Init(LED1);						// Inicializacion de todos los LED
	BSP_LED_Init(LED3);

	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	void debounceFSM_init();
	uartinit();

	/* Infinite loop */
	while (1)
	{

		debounceFSM_update();

	}
}

// Funcion: inicializa la maquina de estados con el estado inicial y las variables internas al mismo
// Entrada; Ninguna
// Salida: Ninguna
void debounceFSM_init()
{
	estadoActual = BUTTON_UP;							// Asigna el estado inicial
	delayInit(&buttonDelay, DEBOUNCE_DELAY);			// Inicializa el delay del debouncer

}

// Funcion: actualiza la maquina de estados evaluando si sucedio alguno de los eventos que la hacen conmutar
// Entrada; Ninguna
// Salida: Ninguna
void debounceFSM_update()
{

	switch (estadoActual)
	{
		case BUTTON_UP:

			if(BSP_PB_GetState(BUTTON_USER))		// Si se detecta un flanco ascendente, inicializa el timer y avanza al siguiente estado
			{
				delayRead(&buttonDelay);
				estadoActual = BUTTON_FALLING;
			}

		break;

		case BUTTON_FALLING:

			if(delayRead(&buttonDelay))				// Una vez transcurrido el tiempo de debounce, pregunta si el boton sigue apretado
			{
				if(BSP_PB_GetState(BUTTON_USER))
				{
					estadoActual = BUTTON_DOWN;		// Si sigue apretado, avanza al siguiente estado y llama a la funcion que togglea el LED1
					buttonPressed();
				}
				else
					estadoActual = BUTTON_UP;		// Si no sigue apretado, vuelve al estado anterior
			}

		break;

		case BUTTON_DOWN:

			if(!BSP_PB_GetState(BUTTON_USER))		// Si se detecta un flanco descendente, inicializa el timer y avanza al siguiente estado
			{
				delayRead(&buttonDelay);
				estadoActual = BUTTON_RISING;
			}

		break;

		case BUTTON_RISING:

			if(delayRead(&buttonDelay))				// Una vez transcurrido el tiempo de debounce, pregunta si el boton no esta apretado
			{
				if(!BSP_PB_GetState(BUTTON_USER))
				{
					estadoActual = BUTTON_UP;		// Si no esta apretado, avanza al siguiente estado y llama a la funcion que togglea el LED1
					buttonReleased();
				}
				else
					estadoActual = BUTTON_DOWN;		// Si sigue apretado, vuelve al estado anterior
			}


		break;

		default:
			//Si algo modificó la variable estadoActual a un estado no válido llevo la MEF a un lugar seguro, por ejemplo, la reinicio
			debounceFSM_init();

		break;
	}

}

// Funcion: togglear el LED3
// Entrada: Ninguna
// Salida: Ninguna
void buttonPressed()
{
	BSP_LED_Toggle(LED3);
	uartSendStringSize((uint8_t *)FALLING_EDGE, 20);
}

// Funcion: togglear el LED1
// Entrada: Ninguna
// Salida: Ninguna
void buttonReleased()
{
	BSP_LED_Toggle(LED1);
	uartSendStringSize((uint8_t *)RISING_EDGE, 20);
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
