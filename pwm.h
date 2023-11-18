/*
 * pwm.h
 *
 *  Created on: Sep 14, 2020
 *      Author: Najeeb Uddin
 */

#ifndef CUSTOM_LIBS_PWM_H_
#define CUSTOM_LIBS_PWM_H_

#include "DSP28x_Project.h"
#include <math.h>
#include "modbus.h"

extern Uint16 modbus_holding_registers[NUMBER_OF_HOLDING_REGISTERS];

void pwm2a_gpio_init(void);
void pwm2b_gpio_init(void);
void pwm2ab_init(void);
void pwm2ab_start(void);
void pwm2ab_stop(void);
void pwm2a_start(void);
void pwm2a_stop(void);
void pwm2b_start(void);
void pwm2b_stop(void);
void pwm2a_set_duty(Uint16);
void pwm2a_set_duty_direct(Uint16);
void pwm2b_set_duty(Uint16);
void pwm2b_set_duty_direct(Uint16);
Uint16 pwm2a_read_duty(void);
Uint16 pwm2b_read_duty(void);
Uint16 pwm2_read_period(void);


#endif /* CUSTOM_LIBS_PWM_H_ */
