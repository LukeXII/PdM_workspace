/*
 * API_FSM.c
 *
 *  Created on: Apr 10, 2022
 *      Author: Lucas
 */

#include "API_FSM.h"

static FSMTableCell_t * currentState;

static FSMTableCell_t state_A[], state_B[], state_C[];

static FSMTableCell_t state_A[] = {{state_C, UART_PREV, actionC}, {state_B, UART_NEXT, actionB}, {state_A, NO_EVENT, no_Action}};
static FSMTableCell_t state_B[] = {{state_A, UART_PREV, actionA}, {state_C, UART_NEXT, actionC}, {state_B, NO_EVENT, no_Action}};
static FSMTableCell_t state_C[] = {{state_B, UART_PREV, actionB}, {state_A, UART_NEXT, actionA}, {state_C, NO_EVENT, no_Action}};

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

void actionA(void)
{
	LCD_Fill_Screen(RED);
	LCD_Draw_Text("CESE 2022 =D", 15, 60, BLUE, 4, WHITE);
	LCD_Draw_Text("FIUBA", 80, 120, BLACK, 5, RED);

	uartSendString((uint8_t *)"ESTADO A\r\n");
}

void actionB(void)
{
	LCD_Fill_Screen(GREEN);
	LCD_Draw_Filled_Circle(70, 100, 25, YELLOW);
	LCD_Draw_Filled_Circle(170, 60, 45, BLACK);
	LCD_Draw_Filled_Circle(220, 170, 35, ORANGE);
	LCD_Draw_Filled_Rectangle_Coord(60, 150, 100, 200, BLUE);

	uartSendString((uint8_t *)"ESTADO B\r\n");
}

void actionC(void)
{
	LCD_Fill_Screen(WHITE);
	LCD_Draw_Horizontal_Line(10, 50, 200, RED);
	LCD_Draw_Horizontal_Line(40, 120, 100, GREEN);
	LCD_Draw_Vertical_Line(180, 20, 200, YELLOW);
	LCD_Draw_Vertical_Line(60, 100, 100, BLACK);

	uartSendString((uint8_t *)"ESTADO C\r\n");

}
