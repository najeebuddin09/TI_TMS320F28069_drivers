/*
 * i2c_software_extender.c
 *
 *  Created on: Dec 1, 2020
 *      Author: Najeeb Uddin
 */
#include "i2c_software_extender.h"

void i2c_software_gpio_init_ext(void)
{
    EALLOW;
    // disable internal pullup because these pins are already pulled up in the
    // schematic
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 1;
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 1;

    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;

    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;
    EDIS;
}


void i2c_software_start_condition_ext(void)
{
    SDA_SET_EXT;
    SCL_SET_EXT;
    delay_ext(40);
    SDA_CLEAR_EXT;
    delay_ext(40);
    SCL_CLEAR_EXT;
    delay_ext(40);
}


void i2c_software_stop_condition_ext(void)
{
    SDA_CLEAR_EXT;
    SCL_SET_EXT;
    delay_ext(40);
    SDA_SET_EXT;
    delay_ext(40);
}

void i2c_software_write_byte_ext(Uint16 byte)
{
    Uint16 i;
    for (i=0; i<8; i++){
        if (byte & 0x80) SDA_SET_EXT;
        else SDA_CLEAR_EXT;
        SCL_SET_EXT;
        delay_ext(20);
        SCL_CLEAR_EXT;
        delay_ext(20);
        byte <<= 1;
    }
    SDA_CLEAR_EXT;
    SCL_SET_EXT;
    delay_ext(20);
    SCL_CLEAR_EXT;
    delay_ext(20);

    return;
}

Uint16 i2c_software_read_byte_ext(Uint16 ACK_BIT)
{
    Uint16 i, byte = 0;
    SDA_SET_EXT;
    EALLOW;
    SDA_DIR_EXT = IN_MODE_EXT;
    EDIS;
    for (i=0; i<8; i++){
        SCL_SET_EXT;
        byte <<= 1;
        delay_ext(10);
        byte = (byte | SDA_EXT);
        delay_ext(10);
        SCL_CLEAR_EXT;
        delay_ext(20);
    }

    EALLOW;
    SDA_DIR_EXT = OUT_MODE_EXT;
    EDIS;

    if (ACK_BIT == 1)
        SDA_CLEAR_EXT;
    else
        SDA_SET_EXT;

    delay_ext(12);
    SCL_SET_EXT;
    delay_ext(20);
    SCL_CLEAR_EXT;
    delay_ext(20);

    return byte;
}

//  nops = 1 ~ 2.5 us delay
void delay_ext(Uint16 nops)
{
    Uint16 i = 0;

    for (i=0; i<nops; i++){
        __asm("          NOP");
    }
}

void i2c_software_send_packet_ext(Uint8 address, Uint8 data[], Uint8 bytes)
{
    Uint8 i = 0;
    i2c_software_start_condition_ext();
    i2c_software_write_byte_ext(address << 1); //addressing slave, rw = 0
    for (i=0; i<bytes; i++){
        i2c_software_write_byte_ext(data[i]); // sending low byte of data adddress
    }
    i2c_software_stop_condition_ext();
}

Uint8 i2c_software_read_packet_ext(Uint8 address)
{
    Uint8 data = 0;
    i2c_software_start_condition_ext();
    i2c_software_write_byte_ext((address << 1) | 1); //addressing slave, rw = 0
    data = i2c_software_read_byte_ext(0); //addressing slave, rw = 0
    i2c_software_stop_condition_ext();

    return data;
}

void i2c_software_send_byte_ext(Uint8 address, Uint8 data)
{
    i2c_software_start_condition_ext();
    i2c_software_write_byte_ext(address << 1);
    i2c_software_write_byte_ext(data);
    i2c_software_stop_condition_ext();

    return;
}
