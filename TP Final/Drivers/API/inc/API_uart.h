/*
 * API_uart.h
 *
 *  Created on: Apr 4, 2022
 *      Author: Lucas
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <string.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "API_delay.h"

/* API Functions */

bool_t uartinit(void);
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

#endif /* API_INC_API_UART_H_ */
