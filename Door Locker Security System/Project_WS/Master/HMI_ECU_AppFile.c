/*
 * HMI_ECU_AppFile.c
 * This is the main file for the Human Machine Interface application of the Door Locker Security System.
 * It controls the interaction between the user and the system.
 * Created on: 2/7/2023
 * Author: Basel Dawoud
 */

#include "keypad.h"        /* Include the keypad driver for input */
#include "timer1.h"        /* Include the timer1 driver for timing */
#include "lcd.h"           /* Include the LCD driver for displaying messages */
#include "uart.h"          /* Include the UART driver for communication with the slave */
#include "PasswordEntry.h" /* Include the PasswordEntry file for password handling */
#include <util/delay.h>    /* Include the delay library for adding delays */

/* Constants and command codes used in the application for communication and control purposes. */

/* The length of the password, set to 5 characters. */
#define PASSWORD_LENGTH 5

/* Command code indicating that the Master device is ready to send data. */
#define MASTER_READY 0x10

/* Command code indicating that the Slave device is ready to send data. */
#define SLAVE_READY 0x11

/* Command code indicating that password verification result is being sent. */
#define PASS_CHECKED SLAVE_READY

/* Command code indicating the next step or action. */
#define NEXT SLAVE_READY

/* Command code indicating that the Buzzer should be activated. */
#define BUZZER MASTER_READY

/* Command code indicating an action after the Buzzer has been activated. */
#define AFTERBUZZER SLAVE_READY

/* Command code indicating that a user choice is being sent. */
#define CHOICE MASTER_READY

/* Command code representing the '+' sign */
#define PLUS 16

/* Command code representing the '-' sign */
#define MINUS 12


/* Declaration of global arrays */
uint8 password[PASSWORD_LENGTH],confPass[PASSWORD_LENGTH];

int main(){

	uint8 passwordsMatch=1; /* Variable to track if password comparison is true */
	uint8 step=1; /* Variable to control the program's steps */

	/* Initialize the LCD driver */
	LCD_init();

	/* UART Configuration */
	UART_ConfigType Config_Ptr = {UART_8_BIT_DATA,DISABLED,UART_STOP_1_BIT,UART_BAUDRATE_9600};

	/* Initialize the UART driver */
	UART_init(&Config_Ptr);

	uint8 counter = 0; /* Variable to count invalid password attempts */
	uint8 choice = 0; /* Variable to store user's choice */

	for (;;){
		/* Check if the current step satisfies the condition for the buzzer */
		if (step<3){
			/* Collect and send passwords for verification */
			Start();
			collectPassword(password);

			/* Step 1 - Create a System Password */
			if (1==step){
				/*Prompt user to re-enter password for confirmation */
				LCD_displayStringRowColumn(0,0,"Plz re-enter the");
				LCD_displayStringRowColumn(1,0,"same pass:");
				collectPassword(confPass);
			}
			_delay_ms(10);

			/* Send the password to the slave */
			sendPassword(password);
			_delay_ms(10);

			if (1==step)
			{
				/* Send the confirmation password to the slave */
				sendPassword(confPass);
			}
			/* Wait for verification result */
			while(UART_recieveByte() != PASS_CHECKED){}
			passwordsMatch=UART_recieveByte();
		}

		else{
			passwordsMatch=1;
			step=1; /* go to step1 */
		}

		if (passwordsMatch){

			counter=0;	/* Clear the counter of the incorrect pass */

			if (1 == step){
				choice=0;
				/* Display main system options */
				LCD_displayStringRowColumn(0,0,"+ : Open Door    ");
				LCD_displayStringRowColumn(1,0,"- : Change Pass  ");

				/* Wait for user's choice */
				while(choice!='+' && choice!= '-')
				{
					/* Get the pressed button from keypad */
					choice = KEYPAD_getPressedKey();
				}
				step=1; /* Go to step 2 */
			}

			else /*if (2 == step)*/{

				switch (choice){

				case '+':
					LCD_displayStringRowColumn(0,0,"Correct pass      ");
					/* Send choice to slave and execute actions */
					UART_sendByte(CHOICE);
					UART_sendByte(PLUS);
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Door is          ");
					LCD_displayStringRowColumn(1,0,"Unlocking");
					while(UART_recieveByte() != NEXT){}
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Door is Stable");
					while(UART_recieveByte() != NEXT){}
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Door is Locking");
					while(UART_recieveByte() != NEXT){}

					break;

				case '-':
					LCD_displayStringRowColumn(0,0,"Correct pass      ");
					/* Send choice to slave and repeat step 1 */
					UART_sendByte(CHOICE);
					UART_sendByte(MINUS);
					step=0;
					/* return to repeat step1 again */
					break;
				}
			}
		}

		else{
			switch (step){
			case 1:
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Passwords do not ");
				LCD_displayStringRowColumn(1,0,"match");
				_delay_ms(10);
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Please try again ");
				_delay_ms(100);
				step=0; /* return to repeat step 1 again */
				break;
			case 2:
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Invalid Password ");
				_delay_ms(100);
				/* count 3 trials */
				counter++;
				/* go to step2 */
				step=1;

				if (3==counter){
					/* Activate Buzzer after 3 trials. */
					_delay_ms(10);
					UART_sendByte(BUZZER);
					LCD_displayStringRowColumn(0,0,"Security Alert  ");
					/* Activate Buzzer after 3 trials. */
					while(UART_recieveByte() != AFTERBUZZER){}
					/* Wait until the buzzer time duration elapses */
					step=2; /* return to the main options again */
				}
				break;
			}
		}
		step++; /* Move to the next step. */
	}
	return 0;
}

