/*
 * sram.h
 *
 *  Created on: Sep 15, 2020
 *      Author: Najeeb Uddin
 */

#ifndef CUSTOM_LIBS_SRAM_H_
#define CUSTOM_LIBS_SRAM_H_


#include "DSP28x_Project.h"
#include "spi.h"

#define READ 0x03
#define WRITE 0x02
#define READ_MODE_REGISTER 0x05
#define WRITE_MODE_REGISTER 0x01

Uint16 sram_read_byte(Uint16);
void sram_write_byte(Uint16,Uint16);
void sram_write_mode_register(Uint16);
Uint16 sram_read_mode_register(void);


#endif /* CUSTOM_LIBS_SRAM_H_ */
