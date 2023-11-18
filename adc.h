/*
 * adc.h
 *
 *  Created on: Nov 18, 2020
 *      Author: Najeeb Uddin
 */

#ifndef CUSTOM_LIBS_ADC_H_
#define CUSTOM_LIBS_ADC_H_


#include "DSP28x_Project.h"
#include "i2c_software.h"

void adc_init_pins(void);
void adc_init(void);
void adc_trigger(void);
Uint16 adc_read_result(void);
void adc_mux_select(Uint8);
void adc_gain_select(Uint8);
void adc_init_bias_pin(void);
void adc_bias_select(Uint8 s);


#endif /* CUSTOM_LIBS_ADC_H_ */
