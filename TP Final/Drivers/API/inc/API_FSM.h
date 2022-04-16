/*
 * API_FSM.h
 *
 *  Created on: Apr 10, 2022
 *      Author: Lucas
 */

#ifndef API_INC_API_FSM_H_
#define API_INC_API_FSM_H_

/*typedef enum {
	state_A,
	state_B,
	state_C
}FSMState_t;
*/
typedef enum {
	UART_NEXT,
	UART_PREV,
	NO_EVENT
}FSMEvent_t;

typedef struct{
	FSMTableCell_t * nextState;
	FSMEvent_t event;
	void (*action)(void);
}FSMTableCell_t;

void FSM_Init();
void FSM_Update(FSMEvent_t event);

void no_Action(void);


#endif /* API_INC_API_FSM_H_ */
