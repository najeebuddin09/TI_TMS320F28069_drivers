/*
 * dio.h
 *
 *  Created on: Nov 25, 2020
 *      Author: Najeeb Uddin
 */

#ifndef CUSTOM_LIBS_DIO_H_
#define CUSTOM_LIBS_DIO_H_


#include "DSP28x_Project.h"
#include "spi.h"
#include "spi_decoder.h"
#define xdc__strict
#include <ti/sysbios/knl/Task.h>

#define CONTROL_BYTE 0x40
#define CONTROL_BYTE2 0x42

void dio_init(void);
Uint16 dio_read(void);
void dio2_init(void);
Uint16 dio2_read(void);
Uint8 dio_receive_packet(Uint8 device_address, Uint8 address);
void dio_send_packet(Uint8 device_address, Uint8 address, Uint8 data);


#endif /* CUSTOM_LIBS_DIO_H_ */
