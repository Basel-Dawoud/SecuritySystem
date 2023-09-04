/*
 ******************************************************************************
 * Module: DC Motor
 *
 * File Name: DC.c
 *
 * Description: Source file for the DC motor driver.
 *
 * Author: Basel Dawoud
 *
 ******************************************************************************
 */

#include "DC.h"
#include "std_types.h"
#include "gpio.h"
#include "PWM.h"

/*
 * Description:
 * Function to initialize the DC motor driver.
 * The function is responsible for setting up the direction for the two
 * motor pins through the GPIO driver.
 * It also stops the DC motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void)
{
	/* Set up the two pins of the motor as output pins */
	GPIO_setupPinDirection(IN1_PORT_ID, IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(IN2_PORT_ID, IN2_PIN_ID, PIN_OUTPUT);

	/* Stop the motor in the beginning */
	GPIO_writePin(IN1_PORT_ID, IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(IN2_PORT_ID, IN2_PIN_ID, LOGIC_LOW);
}

/*
 * Description:
 * Function to rotate the DC Motor CW, A-CW, or stop the motor based on the state input value.
 * It sends the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{
	Timer0_PWM_Init(speed);

	switch (state)
	{
	case CW:
		GPIO_writePin(IN1_PORT_ID, IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(IN2_PORT_ID, IN2_PIN_ID, LOGIC_LOW);
		break;

	case A_CW:
		GPIO_writePin(IN1_PORT_ID, IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(IN2_PORT_ID, IN2_PIN_ID, LOGIC_HIGH);
		break;

	case STOP:
		GPIO_writePin(IN1_PORT_ID, IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(IN2_PORT_ID, IN2_PIN_ID, LOGIC_LOW);
		break;
	}
}
