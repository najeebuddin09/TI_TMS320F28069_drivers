/*
 * i2c_software.c
 *
 *  Created on: Sep 16, 2020
 *      Author: Najeeb Uddin
 */

#include "i2c_software.h"

void i2c_software_gpio_init(void)
{
    EALLOW;
    // disable internal pullup because these pins are already pulled up in the
    // schematic
    GpioCtrlRegs.GPAPUD.bit.GPIO30 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 1;

    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;

    GpioCtrlRegs.GPADIR.bit.GPIO30 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
    //GpioDataRegs.GPASET.all = 0x80000000;
    EDIS;
}


void i2c_software_start_condition(void)
{
    SDA_SET;
    SCL_SET;
    delay(40);
    SDA_CLEAR;
    delay(40);
    SCL_CLEAR;
    delay(40);
}


void i2c_software_stop_condition(void)
{
    SDA_CLEAR;
    SCL_SET;
    delay(40);
    SDA_SET;
    delay(40);
}

//Uint8 i2c_software_write_byte(Uint16 byte)
void i2c_software_write_byte(Uint16 byte)
{
    Uint16 i;
    //Uint8 ACK = 0;
    for (i=0; i<8; i++){
        if (byte & 0x80) SDA_SET;
        else SDA_CLEAR;
        SCL_SET;
        delay(20);
        SCL_CLEAR;
        delay(20);
        byte <<= 1;
    }
    SDA_CLEAR;
    SCL_SET;
    //SDA_DIR = IN_MODE;
    //ACK = SDA;
    delay(20);
    SCL_CLEAR;
    //SDA_DIR = OUT_MODE;
    //SDA_CLEAR;
    delay(20);
    //return !ACK;
    return;
}

Uint16 i2c_software_read_byte(Uint16 ACK_BIT)
{
    Uint16 i, byte = 0;
    SDA_SET;
    EALLOW;
    SDA_DIR = IN_MODE;
    EDIS;
    for (i=0; i<8; i++){
        SCL_SET;
        byte <<= 1;
        delay(10);
        byte = (byte | SDA);
        delay(10);
        SCL_CLEAR;
        delay(20);
    }

    EALLOW;
    SDA_DIR = OUT_MODE;
    EDIS;

    if (ACK_BIT == 1)
        SDA_CLEAR;
    else
        SDA_SET;

    delay(12);
    SCL_SET;
    delay(20);
    SCL_CLEAR;
    delay(20);

    return byte;
}

/////////////////////////////////
/*
void i2c_software_start_condition(void)
{
    SDA_SET;
    SCL_SET;
    delay(40);
    SDA_CLEAR;
    delay(40);
    SCL_CLEAR;
}


void i2c_software_stop_condition(void)
{
    SDA_CLEAR;
    SCL_SET;
    delay(40);
    SDA_SET;
    delay(40);
    SCL_CLEAR;
}

void i2c_software_write_byte(Uint16 byte)
{
    Uint16 i;
    for (i=0; i<8; i++){
         if (byte & 0x80) SDA_SET;
         else SDA_CLEAR;
        SCL_SET;
        delay(20);
        SCL_CLEAR;
        byte <<= 1;
    }

    SCL_SET;
    delay(20);
    SCL_CLEAR;
}

Uint16 i2c_software_read_byte(Uint16 ACK_BIT)
{
    Uint16 i, byte = 0;
    SDA_DIR = IN_MODE;
    for (i=0; i<8; i++){
        SCL_SET;
        byte <<= 1;
        delay(20);
        byte = (byte | SDA);
        SCL_CLEAR;
    }

    SDA_DIR = OUT_MODE;

    if (ACK_BIT == 1)
        SDA_CLEAR;
    else
        SDA_SET;

    delay(20);
    SCL_SET;
    delay(20);
    SCL_CLEAR;

    return byte;
}
*/
///////////////////////////////////////////

/*
void i2c_software_send_frame(Uint16 address, Uint16 byte)
{
    i2c_software_start_condition();
    i2c_software_write_byte(address);
    i2c_software_stop_condition();
    Task_sleep(5);
    i2c_software_start_condition();
    i2c_software_write_byte(byte);
    i2c_software_stop_condition();
}

Uint16 i2c_software_receive_frame(Uint16 address, Uint16 ACK_BIT)
{
    Uint16 rdata = 0;
    i2c_software_start_condition();
    i2c_software_write_byte( (address<<1) | 0x01);
    rdata = i2c_software_read_byte(ACK_BIT);
    i2c_software_stop_condition();
    return rdata;
}
*/
//  nops = 1 ~ 2.5 us delay
void delay(Uint16 nops)
{
    //UInt task_restore_key = Task_disable();

    Uint16 i = 0;

    for (i=0; i<nops; i++){
        __asm("          NOP");
    }

    //Task_restore(task_restore_key);
}
