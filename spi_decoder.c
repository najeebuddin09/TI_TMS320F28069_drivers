/*
 * spi_decoder.c
 *
 *  Created on: Sep 8, 2020
 *      Author: Najeeb Uddin
 */

#include "spi_decoder.h"

void spi_decoder_init(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;

    GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;

    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
    //GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;

    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;
    //GpioCtrlRegs.GPADIR.bit.GPIO19 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;
    EDIS;
}

void spi_decoder_select(Uint16 s)
{
    //GpioDataRegs.GPADAT.bit.GPIO15 = s & 0x0001;
    //GpioDataRegs.GPBDAT.bit.GPIO34 = (s & 0x0002) >> 1;
    //GpioDataRegs.GPADAT.bit.GPIO9 = (s & 0x0004) >> 2;

    if (s & 1){
        GpioDataRegs.GPASET.bit.GPIO15 = 1;
    } else {
        GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;
    }
    if (s & 2){
        GpioDataRegs.GPBSET.bit.GPIO34 = 1;
    } else {
        GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
    }
    if (s & 4){
        GpioDataRegs.GPASET.bit.GPIO9 = 1;
    } else {
        GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;
    }

    /*
    if (s == 1){
        SpibRegs.SPICCR.all =0x0087;   // Relinquish SPI from Reset, 8-bit word
    } else if (s == 2) {
        SpibRegs.SPICCR.all =0x0088;   // Relinquish SPI from Reset, 8-bit word
    }
    */
   /*
    GpioDataRegs.GPADAT.bit.GPIO15 = 0;
    GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
    GpioDataRegs.GPADAT.bit.GPIO9 = 0;

    GpioDataRegs.GPADAT.bit.GPIO15 = 1;
    GpioDataRegs.GPBDAT.bit.GPIO34 = 0;
    GpioDataRegs.GPADAT.bit.GPIO9 = 0;
   */

    //GpioDataRegs.GPADAT.bit.GPIO11 = 0;
    //GpioDataRegs.GPADAT.bit.GPIO19 = 0;
    //GpioDataRegs.GPADAT.bit.GPIO12 = 0;
}
