/******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: timer1.c
 *
 * Description: Source file for the TIMER1 AVR driver
 *
 * Author: Basel Dawoud
 *
 *******************************************************************************/

#include "timer1.h"
#include "avr/io.h" /* To use the TIMER1 Registers */
#include <avr/interrupt.h>	/* To use ISRs */
#include "std_types.h"
/* #include "lcd.h"  Enable it if needed */

#define COMPARE_MODE  4
#define OVERFLOW_MODE 0

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variable to hold the address of the callback function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/* global variable contain the ticks count of the timer */
volatile uint32 g_tick = 0;

/* global variable contain the required delay in seconds */
uint32 delaySeconds=0;

/* Timer1 Configuration */
/* Set the compare value for 1 second at 8MHz clock with a 256 prescaler */
Timer1_ConfigType Timer1_Config = {0, 31249, PRESCALAR_CLK256, Timer_CTC_Mode};

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/* Timer1 Compare Match A Interrupt Service Routine */
ISR(TIMER1_COMPA_vect){
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Callback function in the application after the compare match */
		(g_callBackPtr)();
	}
}

/* Timer1 Overflow Interrupt Service Routine */
ISR(TIMER1_OVF_vect){
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Callback function in the application after the overflow */
		(g_callBackPtr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * Initializes Timer1 by configuring the timer mode, setting registers, and enabling interrupts.
 */

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	if (Config_Ptr->mode == OVERFLOW_MODE){
		/* Set the timer mode to normal mode */
		TCCR1A &= ~(0x03);
		/* Enable Timer1 overflow interrupt */
		TIMSK |= (1 << TOIE1);
	}

	else{
		/* Set the timer mode to CTC mode */
		TCCR1B |= (1<<WGM12);
		/* Enable Timer1 compare match interrupt */
		TIMSK |= (1 << OCIE1A);
		/* Set the compare match value */
		OCR1A = Config_Ptr->compare_value;
	}

	/* Set the initial timer value */
	TCNT1 = Config_Ptr->initial_value;
	/* Set the required F_CPU prescaler */
	TCCR1B |= (Config_Ptr->prescaler);
}

/*
 * Description:
 * Stops the Timer1.
 */
void Timer1_deInit(void)
{
	/* Disable Timer1 by clearing the prescaler bits */
	TCCR1B &= ~(0x07);
}

/*
 * Description :
 * Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the callback function in a global variable */
	g_callBackPtr = a_ptr;
}

/*
 * Description:
 * Uses Timer1 to introduce a delay in seconds.
 */
void delay_sec(uint8 sec){
	Timer1_init(&Timer1_Config);

	Timer1_setCallBack(timeCalc);

	delaySeconds = sec;

	while(delaySeconds>0) {
		/* Wait for the delay to complete */
	}
}

/* Callback function to calculate the seconds required */
void timeCalc(void){
	g_tick++;
	if (g_tick == delaySeconds)
	{
		g_tick=0;
		delaySeconds=0;
		Timer1_deInit();
	}
}
