/*
 * i2c.h
 *
 *  I2C Prototypes
 */

#ifndef I2C_H_
#define I2C_H_

#include "DSP28x_Project.h"

#define I2C_SLAVE_ADDR 0x18

void   Init_GPIO_I2C(void);
void   I2CA_Init(void);
Uint16 i2c_send(Uint16);
Uint16 i2c_receive();

#endif /* I2C_H_ */
