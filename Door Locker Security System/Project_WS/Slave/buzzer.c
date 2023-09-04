/*
 ============================================================================
 File: buzzer.c
 Description: Implementation of the Buzzer control functions.
 Author: Basel Dawoud
 ============================================================================
 */

#include "bzzer.h"
#include "gpio.h"
#include "std_types.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * Initializes the Buzzer by configuring the GPIO pin as an output and turning off the buzzer.
 */
void Buzzer_init() {
	/* Set the direction of the buzzer pin as an output through the GPIO driver */
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);

    /* Turn off the buzzer through the GPIO */
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}

/*
 * Description:
 * Turns on the buzzer by setting the corresponding GPIO pin to a high logic level.
 */
void Buzzer_on() {
	/* Enable the buzzer through the GPIO */
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);
}

/*
 * Description:
 * Turns off the buzzer by setting the corresponding GPIO pin to a low logic level.
 */
void Buzzer_off() {
    /* Disable the buzzer through the GPIO */
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}
