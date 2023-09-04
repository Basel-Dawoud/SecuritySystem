/*
 * timer1.h
 * Header file for Timer1 driver
 * Created on: 02/07/2023
 * Author: Basel Dawoud
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TIMER1_u8_PRESCALLER	TIMER1_u8_DIV_BY_1
#define TIMER1_u8_INPUT_CAPTURE	TIMER1_u8_FALLING_INPUT_CAPTURE
#define TIMER1_CHANNEL_A_ENABLE		3
#define TIMER1_CHANNEL_B_ENABLE		4

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	Timer_Normal_Mode,
	Timer_CTC_Mode = 4
} Timer1_Mode;

typedef enum
{
	NO_CLK_SRC,
	NO_PRESCALAR,
	PRESCALAR_CLK8,
	PRESCALAR_CLK64,
	PRESCALAR_CLK256,
	PRESCALAR_CLK1024,
	EXT_CLK_FALLING,
	EXT_CLK_RISING
}Timer1_Prescaler;

typedef struct {
	uint16 initial_value;
	uint16 compare_value; /* Used in compare mode only. */
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description:
 * Initializes the Timer1 driver with the provided configuration.
 * Inputs: Pointer to the configuration structure of type Timer1_ConfigType.
 * Return: None
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description:
 * Disables Timer1.
 * Inputs: None
 * Return: None
 */
void Timer1_deInit(void);

/*
 * Description:
 * Sets the Call Back function address.
 * Inputs: Pointer to the Call Back function.
 * Return: None
 */
void Timer1_setCallBack(void(*a_ptr)(void));

/*
 * Description:
 * Delays for a specified number of seconds.
 * Inputs: Number of seconds to delay.
 * Return: None
 */
void delay_sec(uint8 sec);

/*
 * Description:
 * Calculates and prints the current time.
 * Inputs: None
 * Return: None
 */
void timeCalc(void);


#endif /* TIMER1_H_ */
