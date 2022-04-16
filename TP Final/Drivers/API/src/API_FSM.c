/*
 * API_FSM.c
 *
 *  Created on: Apr 10, 2022
 *      Author: Lucas
 */

#include "API_FSM.h"

static FSMState_t currentState;

static FSMTableCell_t state_A[] = {{state_A, NO_EVENT, &no_Action}};
static FSMTableCell_t state_B[] = {{state_B, NO_EVENT, &no_Action}};
static FSMTableCell_t state_C[] = {{state_C, NO_EVENT, &no_Action}};

void FSM_Init()
{
	currentState = state_A;
}

void FSM_Update(FSMEvent_t event)
{
	//for(;;)
		//;
}

void no_Action(void)
{

}
