/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega32 ADC driver
 *
 * Author: Basel Dawoud
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023 /* Maximum digital value of ADC conversion */
#define ADC_REF_VOLT_VALUE   2.56 /* Reference voltage for ADC in volts */

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	AREF, /* Internal Vref turned off */
	AVCC, /* External Vref connected to AVCC */
	Reserved, /* Reserved option */
	Internal_2_56v /* Internal 2.56V Voltage Reference with external capacitor at AREF pin */
} ADC_ReferenceVolatge;

typedef enum
{
	DF_2 , DF_2_, DF_8, DF_16, DF_32, DF_64, DF_128
}ADC_Prescaler;

typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Function to initialize the ADC driver by configuring the reference voltage and prescaler.
 * Takes a pointer to the ADC configuration structure as input.
 * No return value.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description:
 * Function to read analog data from a specified ADC channel,
 * convert it to digital using the ADC driver, and return the digital value.
 * Takes the channel number as input.
 * Returns the digital value read from the ADC.
 */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
