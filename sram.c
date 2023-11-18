/*
 * eeprom.c
 *
 *  Created on: Sep 15, 2020
 *      Author: Najeeb Uddin
 */

#include "sram.h"

void sram_write_byte(Uint16 address, Uint16 data)
{
    spia_transmit(WRITE);
    spia_transmit(0x00);
    spia_transmit(0x00);
    spia_transmit(0x00);
    spia_transmit(0x02);
}

Uint16 sram_read_byte(Uint16 address)
{
    spia_transmit(READ);
    spia_transmit(0x00);
    spia_transmit(0x00);

    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 0;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 1;

    spia_transmit(0x00);

    while(SpiaRegs.SPIFFRX.bit.RXFFST < 1);

    return SpiaRegs.SPIRXBUF;
}

void sram_write_mode_register(Uint16 config)
{
    spia_transmit(WRITE_MODE_REGISTER);
    spia_transmit(config);
}

Uint16 sram_read_mode_register(void)
{
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 0;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 1;

    spia_transmit(READ_MODE_REGISTER);

    while(SpiaRegs.SPIFFRX.bit.RXFFST < 1);

    return SpiaRegs.SPIRXBUF;
}
