/*
 * API_FSM.h
 *
 *  Created on: Apr 10, 2022
 *      Author: Lucas
 */

#ifndef API_INC_API_FSM_H_
#define API_INC_API_FSM_H_

typedef enum {
	STATE_A,
	STATE_B,
	STATE_C
}FSMState_t;

typedef enum {
	UART_NEXT,
	UART_PREV,
	NO_EVENT
}FSMEvent_t;

void FSM_Init();
void FSM_Update();

#endif /* API_INC_API_FSM_H_ */
