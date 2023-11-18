/*
 * eeprom.h
 *
 *  Created on: Sep 17, 2020
 *      Author: Najeeb Uddin
 */

#ifndef CUSTOM_LIBS_EEPROM_H_
#define CUSTOM_LIBS_EEPROM_H_

#include "DSP28x_Project.h"
#include "i2c_software.h"

#define EEPROM_ADDRESS 0xA0
#define EEPROM_MAGIC_NUMBER 0xAAAA
#define EEPROM_MAGIC_NUMBER_LOCATION 0xffff

void eeprom_write_byte(Uint16, Uint16);
Uint16 eeprom_read_byte_random(Uint16);
Uint16 eeprom_read_byte_current(void);
void eeprom_store_two_bytes(Uint16, Uint16);
Uint16 eeprom_read_two_bytes(Uint16);

#endif /* CUSTOM_LIBS_EEPROM_H_ */
