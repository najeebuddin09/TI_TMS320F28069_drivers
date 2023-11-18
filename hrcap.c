/*
 * hrcap.c
 *
 *  Created on: Sep 18, 2020
 *      Author: Najeeb Uddin
 */

#include "hrcap.h"

void hrcap_1_gpio_init(void)
{
    EALLOW;
    GpioCtrlRegs.GPBPUD.bit.GPIO54 = 0;	    // Enable pull-up on GPIO54 (HRCAP1)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 3;   // Asynch to SYSCLKOUT GPIO54 (HRCAP1)
    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 3;	// configure gpio54 as hrcap1
    //GpioCtrlRegs.GPBDIR.bit.GPIO54 = 0;
    EDIS;
}

void hrcap_1_init(void)
{
    hrcap_1_gpio_init();
    EALLOW;
    HRCap1Regs.HCCTL.bit.SOFTRESET = 1;
    HRCap1Regs.HCCTL.bit.HCCAPCLKSEL = 0;  // HCCAPCLK = SYSCLK
    
    //
    // Enable Rising Edge Capture Event Interrupt
    //
    HRCap1Regs.HCCTL.bit.RISEINTE = 1;
    
    //
    // Disable Falling Edge Capture Event Interrupt
    //
    HRCap1Regs.HCCTL.bit.FALLINTE = 0;
    
    //
    // Disable Interrupt on 16-bit Counter Overflow Event
    //
    HRCap1Regs.HCCTL.bit.OVFINTE = 1;
    EDIS;
}

void hrcap_1_disable(void)
{
    EALLOW;
    HRCap1Regs.HCCTL.bit.RISEINTE = 0;
    
    //
    // Disable Falling Edge Capture Event Interrupt
    //
    HRCap1Regs.HCCTL.bit.FALLINTE = 0;
    
    //
    // Disable Interrupt on 16-bit Counter Overflow Event
    //
    HRCap1Regs.HCCTL.bit.OVFINTE = 0;
    EDIS;
}

void hrcap_1_enable(void)
{
    EALLOW;
    HRCap1Regs.HCCTL.bit.RISEINTE = 1;
    
    //
    // Disable Falling Edge Capture Event Interrupt
    //
    HRCap1Regs.HCCTL.bit.FALLINTE = 0;
    
    //
    // Disable Interrupt on 16-bit Counter Overflow Event
    //
    HRCap1Regs.HCCTL.bit.OVFINTE = 1;
    EDIS;
}

void hrcap_2_gpio_init(void)
{
    EALLOW;
    GpioCtrlRegs.GPBPUD.bit.GPIO55 = 0;	    // Enable pull-up on GPIO54 (HRCAP1)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = 3;   // Asynch to SYSCLKOUT GPIO54 (HRCAP1)
    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 3;	// configure gpio54 as hrcap1
    EDIS;
}

void hrcap_2_init(void)
{
    hrcap_2_gpio_init();
    EALLOW;
    HRCap2Regs.HCCTL.bit.SOFTRESET = 1;
    HRCap2Regs.HCCTL.bit.HCCAPCLKSEL = 0;  // HCCAPCLK = SYSCLK
    
    //
    // Enable Rising Edge Capture Event Interrupt
    //
    HRCap2Regs.HCCTL.bit.RISEINTE = 1;
    
    //
    // Disable Falling Edge Capture Event Interrupt
    //
    HRCap2Regs.HCCTL.bit.FALLINTE = 0;
    
    //
    // Disable Interrupt on 16-bit Counter Overflow Event
    //
    HRCap2Regs.HCCTL.bit.OVFINTE = 1;
    EDIS;
}

void hrcap_2_disable(void)
{
    EALLOW;
    HRCap2Regs.HCCTL.bit.RISEINTE = 0;
    
    //
    // Disable Falling Edge Capture Event Interrupt
    //
    HRCap2Regs.HCCTL.bit.FALLINTE = 0;
    
    //
    // Disable Interrupt on 16-bit Counter Overflow Event
    //
    HRCap2Regs.HCCTL.bit.OVFINTE = 0;
    EDIS;
}

void hrcap_2_enable(void)
{
    EALLOW;
    HRCap2Regs.HCCTL.bit.RISEINTE = 1;
    
    //
    // Disable Falling Edge Capture Event Interrupt
    //
    HRCap2Regs.HCCTL.bit.FALLINTE = 0;
    
    //
    // Disable Interrupt on 16-bit Counter Overflow Event
    //
    HRCap2Regs.HCCTL.bit.OVFINTE = 1;
    EDIS;
}
