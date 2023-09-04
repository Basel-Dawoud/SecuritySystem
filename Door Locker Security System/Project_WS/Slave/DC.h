/*
 ******************************************************************************
 * Module: DC Motor
 *
 * File Name: DC.h
 *
 * Description: Header file for the DC motor driver.
 *
 * Author: Basel Dawoud
 *
 ******************************************************************************
 */

#ifndef DC_H_
#define DC_H_

#include "std_types.h"
#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define IN1_PORT_ID PORTB_ID
#define IN1_PIN_ID  PIN0_ID
#define IN2_PORT_ID PORTB_ID
#define IN2_PIN_ID  PIN1_ID
#define EN1_PORT_ID PORTB_ID
#define EN1_PIN_ID  PIN3_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	CW,  A_CW, STOP
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description:
 * Function to initialize the DC motor driver.
 * The function is responsible for setting up the direction for the two
 * motor pins through the GPIO driver.
 * It also stops the DC motor at the beginning through the GPIO driver.
 *
 * Inputs: None
 * Return: None
 */
void DcMotor_Init(void);

/*
 * Description:
 * Function to rotate the DC Motor CW, A-CW, or stop the motor based on the state input value.
 * It sends the required duty cycle to the PWM driver based on the required speed value.
 *
 * Inputs:
 * - state: Desired motor state (CW, A-CW, or STOP)
 * - speed: Motor rotation speed represented by a duty cycle
 *
 * Return: None
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* DC_H_ */
