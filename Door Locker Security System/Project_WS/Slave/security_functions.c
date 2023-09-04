/*
 * security_functions.c
 * Contains functions related to security operations
 * Created on: 2/7/2023
 * Author: Basel Dawoud
 */

#include "security_functions.h"
#include <util/delay.h>
#include "uart.h"
#include "std_types.h"
#define PASSWORD_LENGTH 5

/* Functions Definitions */

void receivePassword(uint8 *password){
	/* Receive the password from the master */
	for (uint8 i = 0; i < PASSWORD_LENGTH; i++) {
		password[i] = UART_recieveByte();
		_delay_ms(10); /* Delay after receiving each byte */
	}
}

uint8 comparePasswords(uint8 *password,uint8 *secpassword){
	/* Compare the passwords */
	for (uint8 i = 0; i < PASSWORD_LENGTH; i++) {
		if (password[i] != secpassword[i]) {
			return 0;
		}
	}
	return 1;
}
