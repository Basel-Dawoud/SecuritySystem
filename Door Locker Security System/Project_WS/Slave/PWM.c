/*
 * Created: 1/22/2014 6:15:47 PM
 *  Author: Mohamed Tarek
 */

#include <avr/io.h>
#include <util/delay.h>
#include "PWM.h"

/*
 * Description:
 * Generate a PWM signal with frequency 500Hz
 * Timer0 will be used with pre-scaler F_CPU/8
 * F_PWM=(F_CPU)/(256*N) = (10^6)/(256*8) = 500Hz
 * Duty Cycle can be changed by updating the value
 * in The Compare Register
 */
void Timer0_PWM_Init(uint8 set_duty_cycle)
{

	OCR0= (uint8)(((uint16)(set_duty_cycle*255))/(100));  /* Set Compare Value */

	DDRB  = DDRB | (1<<PB3); // Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC

	/* to make PWM mode and non-inverting mode
		 *  and prescalar of 8 */

	TCCR0=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS01);
	TCNT0=0; // Set Timer Initial Value to 0
}
