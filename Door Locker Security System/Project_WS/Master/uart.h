/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/* Enumeration for the number of data bits in UART frame */
typedef enum
{
	UART_5_BIT_DATA,
	UART_6_BIT_DATA,
	UART_7_BIT_DATA,
	UART_8_BIT_DATA,
	UART_RESERVED_BIT_DATA,
	UART_RES_BIT_DATA,
	UART_R_BIT_DATA,
	UART_9_BIT_DATA
}UART_BitData;

/* Enumeration for UART parity configuration */
typedef enum
{
	DISABLED,
	RESERVED,
	ENABLED_EVEN_PARITY,
	ENABLED_ODD_PARITY
}UART_Parity;

/* Enumeration for number of stop bits in UART frame */
typedef enum
{
	UART_STOP_1_BIT,
	UART_STOP_2_BIT
}UART_StopBit;

/* Enumeration for UART baud rate options */
typedef enum
{
	UART_BAUDRATE_2400=416,
	UART_BAUDRATE_4800=207,
	UART_BAUDRATE_9600=103,
	UART_BAUDRATE_14400=68,
	UART_BAUDRATE_19200=51,
	UART_BAUDRATE_28800=34,
	UART_BAUDRATE_38400=25,
	UART_BAUDRATE_57600=16,
	UART_BAUDRATE_76800=12,
	UART_BAUDRATE_115200=8,
	UART_BAUDRATE_230400=3,
	UART_BAUDRATE_250000=3,
	UART_BAUDRATE_500000=1
}UART_BaudRate;

/* UART configuration structure */
typedef struct{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Initializes the UART device by setting up the frame format, enabling the UART,
 * and setting the baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description:
 * Sends a single byte to another UART device.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description:
 * Sends a single byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description:
 * Receives a byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description:
 * Sends the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description:
 * Receives a string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); /* Receive until # */

#endif /* UART_H_ */
