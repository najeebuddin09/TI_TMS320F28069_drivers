/*
 * pwm.c
 *
 *  Created on: Sep 14, 2020
 *      Author: Najeeb Uddin
 */

#include "pwm.h"

void pwm2a_gpio_init(void)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;    // Disable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;    // Configure GPIO2 for output
    EDIS;
}

void pwm2b_gpio_init(void)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;    // Disable pull-up on GPIO3 (EPWM2B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;    // Configure GPIO3 for output
    EDIS;
}

void pwm2ab_init(void)
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;
    InitEPwm();                             // [F2806x_EPwm.c]
    EPwm2Regs.TBCTL.bit.CTRMODE = 3;        // freeze TB counter
    EPwm2Regs.TBCTL.bit.PRDLD = 1;          // immediate load
    EPwm2Regs.TBCTL.bit.PHSEN = 0;          // disable phase loading
    EPwm2Regs.TBCTL.bit.SYNCOSEL = 3;       // disable SYNCOUT signal
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;      // TBCLK = SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = 7;         // clock divider = /1
    //EPwm2Regs.TBCTL.bit.CLKDIV = 0;         // clock divider = /1
    //EPwm2Regs.TBCTL.bit.FREE_SOFT = 2;      // free run on emulation suspend
    EPwm2Regs.TBPRD = 0x3704;                // set period for ePWM1 (0x3704 = 50Hz)
    //EPwm2Regs.TBPRD = 0xa000;                // set period for ePWM1 (0x3704 = 50Hz)
    //EPwm2Regs.TBPRD = 0x2328;                // set period for ePWM1 (0x2328 = 10kHz)
    EPwm2Regs.TBPHS.all = 0;                // time-base Phase Register
    EPwm2Regs.TBCTR = 0;                    // time-base Counter Register
    //EPwm1Regs.ETSEL.bit.SOCAEN = 1;         // enable SOC on A group
    //EPwm1Regs.ETSEL.bit.SOCASEL = 1;        // select SOC from zero match
    //EPwm1Regs.ETPS.bit.SOCAPRD = 1;         // generate pulse on 1st event
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = 0;     // enable shadow mode
    EPwm2Regs.CMPCTL.bit.LOADAMODE = 2;     // reload on CTR=zero
    EPwm2Regs.CMPA.half.CMPA = 0x0080;      // set compare A value
    EPwm2Regs.CMPB = 0x0080;      // set compare A value
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;      // HIGH on CMPA up match
    EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;      // HIGH on CMPA up match
    EPwm2Regs.AQCTLB.bit.ZRO = AQ_SET;      // HIGH on CMPA up match
    EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;    // LOW on zero match
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

void pwm2ab_start(void)
{
    EPwm2Regs.TBCTL.bit.CTRMODE = 0;        // start counter

}

void pwm2ab_stop(void)
{
    EPwm2Regs.TBCTL.bit.CTRMODE = 3;        // freeze TB counter

    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;   // Configure GPIO2 as EPWM2A
    EDIS;
    GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;      // clear gpio pin
    GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;      // clear gpio pin
}

void pwm2a_start(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    EDIS;
}

void pwm2a_stop(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;   // Configure GPIO2 as EPWM2A
    EDIS;
    if (modbus_holding_registers[125] & 1){
        GpioDataRegs.GPADAT.bit.GPIO2 = 1;      // clear gpio pin
    } else {
        GpioDataRegs.GPADAT.bit.GPIO2 = 0;      // clear gpio pin
    }
}

void pwm2b_start(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO2 as EPWM2A
    EDIS;
}

void pwm2b_stop(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;   // Configure GPIO2 as EPWM2A
    EDIS;
    if (modbus_holding_registers[125] & 2){
        GpioDataRegs.GPADAT.bit.GPIO3 = 1;      // clear gpio pin
    } else {
        GpioDataRegs.GPADAT.bit.GPIO3 = 0;      // clear gpio pin
    }
}

void pwm2a_set_duty(Uint16 percentage)
{
    if (modbus_holding_registers[125] & 1){
        percentage = 100 - percentage;
    }
    if (percentage >= 100){
        EALLOW;
        GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;   // Configure GPIO2 as EPWM2A
        EDIS;
        GpioDataRegs.GPADAT.bit.GPIO2 = 1;      // clear gpio pin
    } else if ((modbus_holding_registers[125] & 1) && percentage == 0) {
        EALLOW;
        GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;   // Configure GPIO2 as EPWM2A
        EDIS;
        GpioDataRegs.GPADAT.bit.GPIO2 = 0;      // clear gpio pin
    } else {
        if (modbus_holding_registers[125] & 1) {
            GpioDataRegs.GPADAT.bit.GPIO2 = 1;      // clear gpio pin
        } else {
            GpioDataRegs.GPADAT.bit.GPIO2 = 0;      // clear gpio pin
        }
        EPwm2Regs.CMPA.half.CMPA = EPwm2Regs.TBPRD * ((float)percentage/100.0);
    }
}

void pwm2a_set_duty_direct(Uint16 duty)
{
    EPwm2Regs.CMPA.half.CMPA = duty;
}

void pwm2b_set_duty(Uint16 percentage)
{
    if (modbus_holding_registers[125] & 2){
        percentage = 100 - percentage;
    }
    if (percentage >= 100){
        EALLOW;
        GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;   // Configure GPIO2 as EPWM2A
        EDIS;
        GpioDataRegs.GPADAT.bit.GPIO3 = 1;      // clear gpio pin
    } else if ((modbus_holding_registers[125] & 2) && percentage == 0) {
        EALLOW;
        GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;   // Configure GPIO2 as EPWM2A
        EDIS;
        GpioDataRegs.GPADAT.bit.GPIO3 = 0;      // clear gpio pin
    } else {
        if (modbus_holding_registers[125] & 2){
            GpioDataRegs.GPADAT.bit.GPIO3 = 1;      // clear gpio pin
        } else {
            GpioDataRegs.GPADAT.bit.GPIO3 = 0;      // clear gpio pin
        }
        EPwm2Regs.CMPB = EPwm2Regs.TBPRD * ((float)percentage/100.0);
    }
}

void pwm2b_set_duty_direct(Uint16 duty)
{
    EPwm2Regs.CMPB = duty;
}

Uint16 pwm2a_read_duty(void)
{
    if (!GpioCtrlRegs.GPAMUX1.bit.GPIO2){
        if(GpioDataRegs.GPADAT.bit.GPIO2){
            if (modbus_holding_registers[125] & 1){
                return 0;
            } else {
                return 100;
            }
            //return 100;
        } else {
            if (modbus_holding_registers[125] & 1){
                return 100;
            } else {
                return 0;
            }
            //return 0;
        }
    } else {
        if (modbus_holding_registers[125] & 1){
            return 100 - ceil(((float)EPwm2Regs.CMPA.half.CMPA/(float)EPwm2Regs.TBPRD)*100.0);
        } else {
            return ceil(((float)EPwm2Regs.CMPA.half.CMPA/(float)EPwm2Regs.TBPRD)*100.0);
        }
    }
}

Uint16 pwm2b_read_duty(void)
{
    if (!GpioCtrlRegs.GPAMUX1.bit.GPIO3){
        if(GpioDataRegs.GPADAT.bit.GPIO3){
            if (modbus_holding_registers[125] & 2){
                return 0;
            } else {
                return 100;
            }
        } else {
            if (modbus_holding_registers[125] & 2){
                return 100;
            } else {
                return 0;
            }

            //return 0;
        }
    } else {
        if (modbus_holding_registers[125] & 2){
            return 100 - ceil(((float)EPwm2Regs.CMPB/(float)EPwm2Regs.TBPRD)*100.0);
        } else {
            return ceil(((float)EPwm2Regs.CMPB/(float)EPwm2Regs.TBPRD)*100.0);
        }
    }
}

Uint16 pwm2_read_period(void)
{
    return EPwm2Regs.TBPRD;
}
