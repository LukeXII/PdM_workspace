/*
 * API_FSM.c
 *
 *  Created on: Apr 10, 2022
 *      Author: Lucas
 */

#include "API_FSM.h"

static FSMTableCell_t * currentState;

static FSMTableCell_t state_A[], state_B[], state_C[];

static FSMTableCell_t state_A[] = {{state_B, UART_NEXT, no_Action}, {state_A, NO_EVENT, no_Action}};
static FSMTableCell_t state_B[] = {{state_B, NO_EVENT, no_Action}};
static FSMTableCell_t state_C[] = {{state_C, NO_EVENT, no_Action}};

void FSM_Init()
{
	currentState = state_A;
}

void FSM_Update(FSMEvent_t newEvent)
{
    uint8_t i;

    for(i = 0;(currentState[i].event != newEvent)&&(currentState[i].event != NO_EVENT);i++)
        ;
    currentState[i].action();
    currentState = currentState[i].nextState;
}

void no_Action(void)
{

}
