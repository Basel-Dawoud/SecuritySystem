/*
 * CONTROL_ECU_AppFile.c
 * Main file for the Control Electronic Control Unit application.
 * Created on: 2/7/2023
 * Author: Basel Dawoud
 */

#include <avr/io.h>             /* AVR IO library to use i-bit */
#include <util/delay.h> 	    /* Delay library */
#include "uart.h"               /* UART communication with the master */
#include "twi.h"                /* TWI/I2C communication */
#include "external_eeprom.h"    /* External EEPROM Memory */
#include "DC.h"                 /* DC Motor driver */
#include "adc.h"                /* ADC driver */
#include "bzzer.h"              /* Buzzer driver */
#include "security_functions.h" /* Slave application definitions */
/* #include "lcd.h"  Enable it if needed */


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

int main() {
	uint8 password[PASSWORD_LENGTH],secPass[PASSWORD_LENGTH]; /* arrays carries the passwords sent by the master */
	uint8 passwordsMatch; /* carries the passwords comparison result */
	uint8 step=1,counter=0,choice=0; /* variable controls the steps of the program */
	uint16 address = 0x0311; /* EEPROM address to store the password */

	/* ADC Configuration */
	ADC_ConfigType ADC_ConfigType = {Internal_2_56v, DF_8};

	/* ADC driver Initialization */
	ADC_init(&ADC_ConfigType);

	/* DC Motor driver Initialization */
	DcMotor_Init();

	/* Buzzer driver Initialization */
	Buzzer_init();

	/* LCD_init();  Enable it if needed */

	/* UART Configuration */
	UART_ConfigType UART_Config_Ptr = { UART_8_BIT_DATA, DISABLED, UART_STOP_1_BIT, UART_BAUDRATE_9600 };

	/* UART driver Initialization */
	UART_init(&UART_Config_Ptr);

	/* TWI/I2C Configuration */
	TWI_ConfigType TWI_Config_Ptr = {0x04, TWI_BAUDRATE_400K };

	/* TWI/I2C driver Initialization */
	TWI_init(&TWI_Config_Ptr);

	SREG|=(1<<7);	/*  Enable global interrupts */

	for (;;){
		/* Check if the current step satisfies the condition for the buzzer */
		if (step<3){
			/* Wait until the master is ready to send the password */
			while(UART_recieveByte() != MASTER_READY){}

			/* Receiving the password from the master */
			receivePassword(password);

			if (1==step){
				/* Step 1 - Create a System Password */

				/* Wait until the master is ready to send the confirmation password */
				while(UART_recieveByte() != MASTER_READY){}

				/* Receive the confirmation password from the master. */
				receivePassword(secPass);

				/* compare the two passwords */
				passwordsMatch= comparePasswords(password,secPass);

				UART_sendByte(PASS_CHECKED);   /* Send password verification status. */
				UART_sendByte(passwordsMatch); /* Send passwords comparison result. */

				if (passwordsMatch) {
					/* passwords match, save the password in EEPROM */
					for (uint8 i = 0; i < PASSWORD_LENGTH; i++) {
						EEPROM_writeByte(address++, password[i]);
					}
				}
				else {
					step=0;
					/* Reset the step to repeat step 1. */
				}
			}
		}

		else{
			/* Wait for the Buzzer time */
			while(UART_recieveByte() != BUZZER){}
			/* Activate Buzzer for 3-seconds. */
			Buzzer_on(); /* Activate Buzzer. */
			delay_sec(3); /* Buzzer active for 3 seconds. */
			Buzzer_off();  /* Deactivate Buzzer. */
			UART_sendByte(AFTERBUZZER); /* Send action after Buzzer activation. */
			step=1;	/* return to repeat step2 again */
			passwordsMatch=1; /* Reset passwords match indicator. */
			counter=0; /* Reset trials counter. */
		}

		if (1==step || 2==step){
			switch (step){
			case 1:
				step=1; /* Proceed to step 2. */
				break;
			case 2:
				/* Retrieve the saved password. */
				for (uint8 i = 0; i < PASSWORD_LENGTH; i++) {
					EEPROM_readByte(address++,&secPass[i]);
					_delay_us(10); /* Delay after reading each byte */
				}

				/* Compare the two passwords */
				passwordsMatch= comparePasswords(password,secPass);
				UART_sendByte(PASS_CHECKED); /* Send password verification status. */
				UART_sendByte(passwordsMatch); /* Send passwords comparison result. */

				if(passwordsMatch){

					counter=0;	/* Clear the counter of the incorrect pass */

					/* Wait until the master is ready to send the choice variable. */
					while(UART_recieveByte() != CHOICE){}

					/* Receive the user choice from the master. */
					choice=UART_recieveByte();

					switch(choice){
					case PLUS:
						/* Passwords match,
						 * Rotate motor for 2 seconds CW.
						 */
						DcMotor_Rotate(CW,100);
						delay_sec(2);
						UART_sendByte(NEXT);

						/* Hold the motor for 1 second. */
						DcMotor_Rotate(STOP,0);
						delay_sec(1);
						UART_sendByte(NEXT);

						/* Rotate motor for 2 seconds A-CW. */
						DcMotor_Rotate(A_CW,100);
						delay_sec(2);
						UART_sendByte(NEXT);

						DcMotor_Rotate(STOP,0); /* Stop the motor. */
						step=1; /* Return to step 2. */
						break;

					case MINUS:
						step=0; /* Reset the step to repeat step 1. */
						break;
					}
					break;
				}

				else{
					/* count for 3 trials */
					counter++; /* Increment trials counter. */
					step=1; /* Return to step 1. */
					if (3==counter){
						/* Activate Buzzer after 3 trials. */
						step=2; /* Go to step 3 */
					}
				}
			}
		}
		step++; /* Move to the next step. */
	}
	return 0;
}
