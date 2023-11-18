/*
 * spi.h
 *
 *  Created on: Sep 8, 2020
 *      Author: Najeeb Uddin
 */

#ifndef CUTOM_LIBS_SPI_H_
#define CUTOM_LIBS_SPI_H_

#include "DSP28x_Project.h"

#include <stdint.h>

void spib_gpio_init(void);
void spib_fifo_init(void);
Uint16 spib_transmit(Uint16);
Uint8 spib_receive(void);
void spib_init(void);
void spib_buffer_reset(void);

void spia_gpio_init(void);
void spia_fifo_init(void);
Uint16 spia_transmit(Uint16);
void spia_init(void);

#endif /* CUTOM_LIBS_SPI_H_ */
