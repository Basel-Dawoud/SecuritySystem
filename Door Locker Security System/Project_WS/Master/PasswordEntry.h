/*
 * PasswordEntry.h
 * Header file for password entry and communication functions.
 *  Created on: ١١‏/٠٧‏/٢٠٢٣
 *      Author: Basel Dawoud
 */

#ifndef APP_H_
#define APP_H_

#include "std_types.h"

/* Functions Declarations */

/*
 * Description:
 * Function to clear the LCD and prompt the user to enter a password.
 * No inputs.
 * No return value.
 */
void Start(void);

/*
 * Description:
 * Function to send a password to another microcontroller through UART.
 * Takes a pointer to the password array as input.
 * No return value.
 */
void sendPassword(uint8 *password);

/*
 * Description:
 * Function to collect a password from the user through the keypad.
 * Takes a pointer to the password array as input.
 * No return value.
 */
void collectPassword(uint8 *password);

#endif /* PASSWORDENTRY_H_ */
