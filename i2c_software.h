/*
 * i2c_software.h
 *
 *  Created on: Sep 16, 2020
 *      Author: Najeeb Uddin
 */

#ifndef CUSTOM_LIBS_I2C_SOFTWARE_H_
#define CUSTOM_LIBS_I2C_SOFTWARE_H_

#define xdc__strict
#include "DSP28x_Project.h"
#include <ti/sysbios/knl/Task.h>

#define SCL_SET GpioDataRegs.GPASET.all|=0x40000000
#define SCL_CLEAR GpioDataRegs.GPACLEAR.all|=0x40000000
#define SDA_SET GpioDataRegs.GPASET.all|=0x80000000
#define SDA_CLEAR GpioDataRegs.GPACLEAR.all|=0x80000000
#define SDA GpioDataRegs.GPADAT.bit.GPIO31
#define SDA_DIR GpioCtrlRegs.GPADIR.bit.GPIO31
#define IN_MODE 0
#define OUT_MODE 1

void i2c_software_gpio_init(void);
void i2c_software_start_condition(void);
void i2c_software_stop_condition(void);
void i2c_software_write_byte(Uint16);
Uint16 i2c_software_read_byte(Uint16);
void delay(Uint16);



#endif /* CUSTOM_LIBS_I2C_SOFTWARE_H_ */
