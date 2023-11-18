/*
 * eeprom.c
 *
 *  Created on: Sep 17, 2020
 *      Author: Najeeb Uddin
 */

#include "eeprom.h"

void eeprom_write_byte(Uint16 byte, Uint16 address)
{
    i2c_software_start_condition();
    i2c_software_write_byte(EEPROM_ADDRESS); //addressing slave, rw = 0
    i2c_software_write_byte(address>>8 & 0xff); // sending high byte of data address
    i2c_software_write_byte(address & 0xff); // sending low byte of data adddress
    i2c_software_write_byte(byte & 0xff); // sending low byte of data adddress
    i2c_software_stop_condition();
}

Uint16 eeprom_read_byte_random(Uint16 address)
{
    Uint16 byte = 0;
    i2c_software_start_condition();
    i2c_software_write_byte(EEPROM_ADDRESS); //addressing slave
    i2c_software_write_byte(address>>8); // sending high byte of data address
    i2c_software_write_byte(address & 0xff); // sending low byte of data adddress
    i2c_software_stop_condition();
    i2c_software_start_condition();
    i2c_software_write_byte(EEPROM_ADDRESS | 1); //addressing slave, rw = 1
    byte = i2c_software_read_byte(0); // reading data
    i2c_software_stop_condition();
    return byte & 0xff;
}

Uint16 eeprom_read_byte_current(void)
{
    Uint16 byte = 0;
    i2c_software_start_condition();
    i2c_software_write_byte(EEPROM_ADDRESS | 1); //addressing slave, rw = 1
    byte = i2c_software_read_byte(0); // reading data
    i2c_software_stop_condition();
    return byte;
}

void eeprom_store_two_bytes(Uint16 word, Uint16 address)
{
    address *= 2;
    Task_disable();
    eeprom_write_byte((word >> 8) & 0xff, address);
    Task_enable();
    Task_sleep(5);
    Task_disable();
    eeprom_write_byte(word & 0xff, address+1);
    Task_enable();
}

Uint16 eeprom_read_two_bytes(Uint16 address)
{
    Uint16 data = 0;
    address *= 2;
    Task_disable();
    data = eeprom_read_byte_random(address);
    data = (data & 0xff) << 8;
    data |= (eeprom_read_byte_random(address+1) & 0xff);
    Task_enable();
    return data;
}

