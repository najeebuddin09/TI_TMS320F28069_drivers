/*
 *  I2C API
 */

#include <custom_libs/i2c.h>

void Init_GPIO_I2C(void)
{
    EALLOW;
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pull-up for GPIO32 (SDAA)
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pull-up for GPIO33 (SCLA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;  // Asynch input GPIO32 (SDAA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;  // Asynch input GPIO33 (SCLA)
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;
    EDIS;
}


void I2CA_Init(void)
{
    Init_GPIO_I2C();

    //
    // Initialize I2C
    //
    I2caRegs.I2CSAR = I2C_SLAVE_ADDR;       // Slave address - EEPROM control code

    I2caRegs.I2CPSC.all = 19;       // Prescaler - need 7-12 Mhz on module clk
    I2caRegs.I2CCLKL = 45;          // NOTE: must be non zero
    I2caRegs.I2CCLKH = 45;          // NOTE: must be non zero
    I2caRegs.I2CIER.all = 0x00;       // Enable SCD & ARDY interrupts
    //I2caRegs.I2CIER.bit.SCD = 1;
    //I2caRegs.I2CIER.bit.ARDY = 1;
    //I2caRegs.I2CIER.bit.RRDY = 1;
    //I2caRegs.I2CIER.bit.XRDY = 1;
    //I2caRegs.I2CIER.bit.NACK = 1;

    //
    // I2C module reset
    //
    I2caRegs.I2CMDR.all = 0x0020;

    I2caRegs.I2CFFTX.all = 0x6000;  // Enable FIFO mode and TXFIFO
    I2caRegs.I2CFFRX.all = 0x2040;  // Enable RXFIFO, clear RXFFINT,

    return;
}

Uint16 i2c_send(Uint16 cmd){
    int16 timeout = 1000;

    I2caRegs.I2CMDR.all = 0x2E20;    //START condition, STOP condition, Master, Transmitter, I2C enabled
    I2caRegs.I2CCNT = 0x01;          // bytes to send - 2 here
    I2caRegs.I2CDXR = cmd;

    while (I2caRegs.I2CMDR.bit.STP == 1 && timeout > 0) {
        timeout--;
    }

    if (timeout > 0){
      return 1;
    }else{
      return 0;
    }

}

Uint16 i2c_receive(){
    int16 timeout = 1000;

    I2caRegs.I2CMDR.all = 0x2C20;   // Start condition, Stop condition, Master, I2C enabled
    I2caRegs.I2CCNT = 0x01;         // bytes to receive - always 1

    while (I2caRegs.I2CMDR.bit.STP == 1 && timeout > 0) {
        timeout--;
    }

    /*
     * You can poll the below bits to see if data is received
     */

    //while (I2caRegs.I2CSTR.bit.BB == 1);
    //while(I2caRegs.I2CISRC.all != I2C_RX_ISRC);

    if (timeout > 0){
      return I2caRegs.I2CDRR;
    }else{
      return 0;
    }
}

