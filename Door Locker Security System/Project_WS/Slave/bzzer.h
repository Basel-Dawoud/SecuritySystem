/*
 ******************************************************************************
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the Buzzer driver.
 *
 * Author: Basel Dawoud
 *
 *******************************************************************************/

#ifndef BZZER_H_
#define BZZER_H_

#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT PORTC_ID   /* Define the port number for the buzzer */
#define BUZZER_PIN PIN7_ID     /* Define the pin number for the buzzer */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description
 * Setup the direction for the buzzer pin as output pin through the GPIO driver.
 * Turn off the buzzer through the GPIO.
 * Inputs: None
 * Return: None
 */
void Buzzer_init();


/*
 * Description
 * Function to enable the Buzzer through the GPIO.
 * Inputs: None
 * Return: None
 */
void Buzzer_on(void);


/*
 * Description
 *  Function to disable the Buzzer through the GPIO.
 * Inputs: None
 * Return: None
 */
void Buzzer_off(void);

#endif /* BZZER_H_ */
