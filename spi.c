/*
 * spi.c
 *
 *  SPI API
 */

#include "spi.h"

void spib_gpio_init(void)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;   // Enable pull-up on GPIO13 (SPISOMIB)
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;   // Enable pull-up on GPIO14 (SPICLKB)
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;   // Enable pull-up on GPIO24 (SPISIMOB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;   // Enable pull-up on GPIO15 (SPISTEB)

    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3; // Asynch input GPIO13 (SPISOMIB)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3; // Asynch input GPIO14 (SPICLKB)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 3; // Asynch input GPIO24 (SPISIMOB)
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;   // Asynch input GPIO15 (SPISTEB)

    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 3; // Configure GPIO13 as SPISOMIB
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 3; // Configure GPIO14 as SPICLKB
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3; // Configure GPIO24 as SPISIMOB
    //GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 3;  // Configure GPIO15 as SPISTEB
    EDIS;
}

void spib_init(void)
{
    spib_gpio_init();
    spib_fifo_init();

    SpibRegs.SPICCR.all =0x0000;  // Reset on

    SpibRegs.SPICTL.all =0x0006;

    /*
        LSPCLK = 22.5 MHz
        22.5 / (99+1) = 225 khz
        0x56 = 400 khz
        0x1c = 800 khz
    */
    SpibRegs.SPIBRR =56;
    SpibRegs.SPICCR.all =0x00c7;   // Relinquish SPI from Reset, 8-bit word
    SpibRegs.SPIPRI.bit.FREE = 1;  // Set so breakpoints don't disturb xmission
}

Uint16 spib_transmit(Uint16 a)
{
    Uint16 timeout = 1000;

    SpibRegs.SPITXBUF = (a << 8);

    while(!(SpibRegs.SPIFFTX.bit.TXFFST < 4) && timeout > 0){
        timeout--;
    }

    if (timeout <= 0){
        /* reset SPI */
        SpibRegs.SPIFFTX.bit.TXFIFO = 0;
        SpibRegs.SPIFFTX.bit.TXFIFO = 1;
        return 0;
    } else {
        return 1;
    }
}

Uint8 spib_receive(void)
{
    Uint16 timeout = 1000;
    while (SpibRegs.SPIFFRX.bit.RXFFST < 1 && timeout > 0)
    {
        timeout--;
    }
    
    if (timeout <= 0){
        return 0xaa;
    } else {
        return SpibRegs.SPIRXBUF; 
    }
}

void spib_fifo_init(void)
{
    //
    // Initialize SPI FIFO registers
    //
    SpibRegs.SPIFFTX.all=0xE040;
    SpibRegs.SPIFFRX.all=0x2040;
    SpibRegs.SPIFFCT.all=0x0;
}

void spib_buffer_reset(void)
{
    SpibRegs.SPIFFRX.bit.RXFIFORESET = 0;
    SpibRegs.SPIFFRX.bit.RXFIFORESET = 1;
}

/* spia */
void spia_gpio_init(void)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;  // Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;  // Enable pull-up on GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;  // Enable pull-up on GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;  // Enable pull-up on GPIO19 (SPISTEA)

    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA
    EDIS;
}

void spia_init(void)
{
    spia_gpio_init();
    spia_fifo_init();

    SpiaRegs.SPICCR.all =0x0000;  // Reset on

    SpiaRegs.SPICTL.all =0x0006;

    SpiaRegs.SPIBRR =0x008;
    SpiaRegs.SPICCR.all =0x0087;   // Relinquish SPI from Reset, 8-bit word
    SpiaRegs.SPIPRI.bit.FREE = 1;  // Set so breakpoints don't disturb xmission
}

Uint16 spia_transmit(Uint16 a)
{
    Uint16 timeout = 1000;

    SpiaRegs.SPITXBUF = a << 8;

    while(!(SpiaRegs.SPIFFTX.bit.TXFFST < 4) && timeout > 0){
        timeout--;
    }

    if (timeout <= 0){
        /* reset SPI */
        SpiaRegs.SPIFFTX.bit.TXFIFO = 0;
        SpiaRegs.SPIFFTX.bit.TXFIFO = 1;
        return 0;
    } else {
        return 1;
    }
}

void spia_fifo_init(void)
{
    //
    // Initialize SPI FIFO registers
    //
    SpiaRegs.SPIFFTX.all=0xE040;
    SpiaRegs.SPIFFRX.all=0x2044;
    SpiaRegs.SPIFFCT.all=0x0;
}
