/*
 * sci.h
 *
 *  Created on: Sep 10, 2020
 *      Author: Najeeb Uddin
 */

#ifndef CUSTOM_LIBS_SCI_H_
#define CUSTOM_LIBS_SCI_H_

#include "DSP28x_Project.h"
#include "eeprom.h"

#define CHAR 0
#define NUMBER 2

void scia_gpio_init(void);
void scia_init(void);
Uint16 scia_transmit_string(const char *);
Uint16 scia_transmit_byte(Uint16, Uint16);
void scia_fifo_init(void);
void reverse(char* , int ); 
int intToStr(int x, char str[], int d);
void ftoa(float , char* , int ); 

#endif /* CUSTOM_LIBS_SCI_H_ */
