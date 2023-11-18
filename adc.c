/*
 * adc.c
 *
 *  Created on: Nov 18, 2020
 *      Author: Najeeb Uddin
 */

#include "adc.h"

void adc_init_pins(void)
{
    //GpioCtrlRegs.AIOMUX1.bit.AIO2 = 2;
}

void adc_init_mux_pins(void)
{
    EALLOW;
    GpioCtrlRegs.AIOMUX1.bit.AIO10 = 0;  //configure for io operation
    GpioCtrlRegs.AIOMUX1.bit.AIO12 = 0;  //configure for io operation
    GpioCtrlRegs.AIOMUX1.bit.AIO14 = 0;  //configure for io operation

    GpioCtrlRegs.AIODIR.bit.AIO10 = 1;   //configure for output
    GpioCtrlRegs.AIODIR.bit.AIO12 = 1;   //configure for output
    GpioCtrlRegs.AIODIR.bit.AIO14 = 1;   //configure for output
    EDIS;
}

void adc_init_gain_pins(void)
{
    EALLOW;
    GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;

    GpioCtrlRegs.GPBDIR.bit.GPIO52 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO53 = 1;
    EDIS;
}

void adc_init_bias_pin(void)
{
    EALLOW;
    GpioCtrlRegs.AIOMUX1.bit.AIO4 = 0;  //configure for io operation

    GpioCtrlRegs.AIODIR.bit.AIO4 = 1;   //configure for output
    EDIS;
}

void adc_init(void)
{
    //adc_init_pins();
    adc_init_mux_pins();
    adc_init_gain_pins();
    adc_init_bias_pin();

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
    (*Device_cal)();
    EDIS;

    EALLOW;
    AdcRegs.ADCCTL1.bit.ADCBGPWD  = 1;      // Power ADC BG
    AdcRegs.ADCCTL1.bit.ADCREFPWD = 1;      // Power reference
    AdcRegs.ADCCTL1.bit.ADCPWDN   = 1;      // Power ADC
    AdcRegs.ADCCTL1.bit.ADCENABLE = 1;      // Enable ADC
    AdcRegs.ADCCTL1.bit.ADCREFSEL = 0;      // Select interal BG
    EDIS;

    //DELAY_US(1000);
    delay(1000);

    EALLOW;
    AdcRegs.ADCCTL2.bit.CLKDIV2EN = 1;
    EDIS;

    //DELAY_US(1000);
    delay(1000);

    EALLOW;
    AdcRegs.ADCCTL1.bit.VREFLOCONV = 0;
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1;
    AdcRegs.ADCSOC1CTL.bit.CHSEL= 0x1;
    AdcRegs.ADCSOC1CTL.bit.ACQPS  = 6;
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 0;
    EDIS;

    //DELAY_US(1000);
    delay(1000);

}

void adc_trigger(void)
{
    AdcRegs.ADCSOCFRC1.bit.SOC1 = 1;
}

Uint16 adc_read_result(void)
{
    return AdcResult.ADCRESULT1;
}

void adc_mux_select(Uint8 s)
{
    if (s & 1){
        GpioDataRegs.AIOSET.bit.AIO10 = 1;
    } else {
        GpioDataRegs.AIOCLEAR.bit.AIO10 = 1;
    }
    if (s & 2){
        GpioDataRegs.AIOSET.bit.AIO12 = 1;
    } else {
        GpioDataRegs.AIOCLEAR.bit.AIO12 = 1;
    }
    if (s & 4){
        GpioDataRegs.AIOSET.bit.AIO14 = 1;
    } else {
        GpioDataRegs.AIOCLEAR.bit.AIO14 = 1;
    }
    //GpioDataRegs.AIODAT.bit.AIO10 = s & 1;  //configure for io operatio
    //GpioDataRegs.AIODAT.bit.AIO12 = (s & 2)>>1;  //configure for io operation
    //GpioDataRegs.AIODAT.bit.AIO14 = (s & 4)>>2;  //configure for io operation
}

void adc_gain_select(Uint8 s)
{
    if (s & 1){
        GpioDataRegs.GPBSET.bit.GPIO52 = 1;
    } else {
        GpioDataRegs.GPBCLEAR.bit.GPIO52 = 1;
    }
    if (s & 2){
        GpioDataRegs.GPBSET.bit.GPIO53 = 1;
    } else {
        GpioDataRegs.GPBCLEAR.bit.GPIO52 = 1;
    }
}

void adc_bias_select(Uint8 s)
{
    if (s & 1){
        GpioDataRegs.AIOSET.bit.AIO4 = 1;  //configure for io operation
    } else {
        GpioDataRegs.AIOCLEAR.bit.AIO4 = 1;  //configure for io operation
    }
}
