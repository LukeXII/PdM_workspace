/*
 * API_FSM.c
 *
 *  Created on: Apr 10, 2022
 *      Author: Lucas
 */

#include "API_FSM.h"

static FSMState_t currentState;
static FSMEvent_t newEvent;

void FSM_Init()
{
	currentState = STATE_A;
	newEvent = NO_EVENT;
}

void FSM_Update()
{

}
