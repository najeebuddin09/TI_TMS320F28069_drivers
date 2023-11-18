/*
 * ds18b20_through_extender.h
 *
 *  Created on: Sep 4, 2020
 *      Author: Najeeb Uddin
 */

#ifndef DS18B20_THROUGH_EXTENDER_H_
#define DS18B20_THROUGH_EXTENDER_H_

#include "extender.h"
#define xdc__strict
#include <ti/sysbios/knl/Task.h>

Uint16 read_temperature(float * temperature_buffer, Uint16 ext_channel);

#endif /* DS18B20_THROUGH_EXTENDER_H_ */
