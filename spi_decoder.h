/*
 * spi_decoder.h
 *
 *  to enable spi connected device, you to select that device
 *  through a decoder using these functions
 */

#ifndef CUTOM_LIBS_SPI_DECODER_H_
#define CUTOM_LIBS_SPI_DECODER_H_

#include "DSP28x_Project.h"

#include <stdint.h>

void spi_decoder_select(Uint16);
void spi_decoder_init(void);

#endif /* CUTOM_LIBS_SPI_DECODER_H_ */
