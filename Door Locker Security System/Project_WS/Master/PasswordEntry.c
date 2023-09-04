/*
 * PasswordEntry.c
 * handling password entry and communication with the user.
 *
 *  Created on: 2/7/2023
 *      Author: Basel Dawoud
 */

#include "PasswordEntry.h"
#include <util/delay.h>
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "std_types.h"

#define MASTER_READY 0x10
#define PASSWORD_LENGTH 5
#define ENTER 13

uint8 key;

/* Functions Definitions */

void Start(){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0," Plz enter pass ");
	LCD_moveCursor(1,0); /* Move the cursor to the second row */
}

void collectPassword(uint8 *password){
	uint8 i=0;

	while(1){
		/* Get the pressed button from keypad */
		key = KEYPAD_getPressedKey();

		while(i<PASSWORD_LENGTH){
			/* Get the pressed button from keypad */
			key = KEYPAD_getPressedKey();
			if (key || key==0) {
				if (key!=ENTER){
					LCD_displayCharacter('*');
					password[i] = key;
					i++;
					_delay_ms(15);
				}
			}
		}
		if (ENTER==key && PASSWORD_LENGTH==i){
			break;
		}
	}
}

void sendPassword(uint8 *password){
	/* Send MC2_READY byte to Slave to ask it to start receiving the password */
	UART_sendByte(MASTER_READY);

	for (uint8 i=0;i<PASSWORD_LENGTH;i++){
		/* Send the pass to the other micro-controller through the UART */
		UART_sendByte(password[i]);
		_delay_ms(10);
	}
}
