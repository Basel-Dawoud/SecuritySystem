/*
 * security_functions.h
 * Header file for security-related functions
 * Created on: 2/07/2023
 * Author: Basel Dawoud
 */

#ifndef SECURITY_FUNCTIONS_H_
#define SECURITY_FUNCTIONS_H_

#include "std_types.h"

/* Functions Declaration */
void receivePassword(uint8 *password);
uint8 comparePasswords(uint8 *password,uint8 *secpassword);

#endif /* SECURITY_FUNCTIONS_H_ */
