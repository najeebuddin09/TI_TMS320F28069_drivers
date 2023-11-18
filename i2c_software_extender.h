/*
 * i2c_software_extender.h
 *
 *  Created on: Dec 1, 2020
 *      Author: Najeeb Uddin
 */

#ifndef CUSTOM_LIBS_I2C_SOFTWARE_EXTENDER_H_
#define CUSTOM_LIBS_I2C_SOFTWARE_EXTENDER_H_


#include "DSP28x_Project.h"

#define SCL_SET_EXT GpioDataRegs.GPBSET.bit.GPIO33=1
#define SCL_CLEAR_EXT GpioDataRegs.GPBCLEAR.bit.GPIO33=1
#define SDA_SET_EXT GpioDataRegs.GPBSET.bit.GPIO32=1
#define SDA_CLEAR_EXT GpioDataRegs.GPBCLEAR.bit.GPIO32=1
#define SDA_EXT GpioDataRegs.GPBDAT.bit.GPIO32
#define SDA_DIR_EXT GpioCtrlRegs.GPBDIR.bit.GPIO32
#define IN_MODE_EXT 0
#define OUT_MODE_EXT 1

void i2c_software_gpio_init_ext(void);
void i2c_software_start_condition_ext(void);
void i2c_software_stop_condition_ext(void);
void i2c_software_write_byte_ext(Uint16);
Uint16 i2c_software_read_byte_ext(Uint16);
void delay_ext(Uint16);
void i2c_software_send_packet_ext(Uint8 address, Uint8 data[], Uint8 bytes);
Uint8 i2c_software_read_packet_ext(Uint8 address);
void i2c_software_send_byte_ext(Uint8 address, Uint8 data);


#endif /* CUSTOM_LIBS_I2C_SOFTWARE_EXTENDER_H_ */
