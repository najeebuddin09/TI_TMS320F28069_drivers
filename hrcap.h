/*
 * hrcap.h
 *
 *  Created on: Sep 18, 2020
 *      Author: Najeeb Uddin
 */

#ifndef CUSTOM_LIBS_HRCAP_H_
#define CUSTOM_LIBS_HRCAP_H_

#include "DSP28x_Project.h"

void hrcap_1_init(void);
void hrcap_1_gpio_init(void);
void hrcap_2_init(void);
void hrcap_2_gpio_init(void);
void hrcap_1_disable(void);
void hrcap_1_enable(void);
void hrcap_2_disable(void);
void hrcap_2_enable(void);

#endif /* CUSTOM_LIBS_HRCAP_H_ */
