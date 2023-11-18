/*
 * sci.c
 *
 *  Created on: Sep 10, 2020
 *      Author: Najeeb Uddin
 */

#include "sci.h"

void scia_gpio_init(void)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;

    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;

    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;
    EDIS;
}

void scia_init(void)
{
    Uint8 mode = 0;
    scia_gpio_init();
    scia_fifo_init();

    SciaRegs.SCICCR.all =0x0007;
    SciaRegs.SCICTL1.all =0x0043;
    SciaRegs.SCICTL2.all =0x0000;
    SciaRegs.SCICTL2.bit.TXINTENA = 0;
    //SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
    // Baud rate 14400 for scilbaud = 0x00C2 and scihbaud = 0x0000
    /* LOSPCP = 0x0002
     *  Sysclk/4 = 22.5Mhz
     *  Baud rate = 19200
     *  (22500000/(19200*8))-1 = 145.48 ~= 146 = 0x92
     */
    mode = eeprom_read_byte_random(265);
    switch (mode)
    {
    case 0: // 9600 baud rate
        SciaRegs.SCIHBAUD    =0x0001;
        SciaRegs.SCILBAUD    =0x0024;
        break;
    case 1: // 14400 baud rate
        SciaRegs.SCIHBAUD    =0x0000;
        SciaRegs.SCILBAUD    =0x00c3;
        break;
    case 2: // 19200 baud rate
        SciaRegs.SCIHBAUD    =0x0000;
        SciaRegs.SCILBAUD    =0x0092;
        break;
    case 3: // 28800 baud rate
        SciaRegs.SCIHBAUD    =0x0000;
        SciaRegs.SCILBAUD    =0x0061;
        break;
    case 4: // 38400 baud rate
        SciaRegs.SCIHBAUD    =0x0000;
        SciaRegs.SCILBAUD    =0x0049;
        break;
    
    default:
        SciaRegs.SCIHBAUD    =0x0000;
        SciaRegs.SCILBAUD    =0x0049;
        break;
    }
    //SciaRegs.SCIHBAUD    =0x0001;
    //SciaRegs.SCILBAUD    =0x0024;
    SciaRegs.SCICCR.bit.LOOPBKENA = 0; // Enable loop back
    SciaRegs.SCICTL1.all = 0x0023;     // Relinquish SCI from Reset
    SciaRegs.SCIPRI.bit.SOFT = 1;
    SciaRegs.SCIPRI.bit.FREE = 1;
}

void scia_fifo_init(void)
{
    SciaRegs.SCIFFTX.all=0xE040;
    SciaRegs.SCIFFRX.all=0x2044;
    SciaRegs.SCIFFRX.bit.RXFFIENA=1; //enable interrupt for data reception
    SciaRegs.SCIFFRX.bit.RXFFIL=1;
    SciaRegs.SCIFFCT.all=0x0;
}

Uint16 scia_transmit_string(const char * string)
{
    Uint16 k = 0, CHAR_FAIL_FLAG = 0;
    while(string[k] != '\0'){
        if (!scia_transmit_byte((Uint16)string[k++],CHAR)){
            CHAR_FAIL_FLAG = 1;
        }
    }

    if (CHAR_FAIL_FLAG){
        return 0;
    } else {
        return 1;
    }
}

Uint16 scia_transmit_byte(Uint16 a, Uint16 BYTE_TYPE)
{
    int16 timeout = 1000;

    if (BYTE_TYPE == CHAR){
        SciaRegs.SCITXBUF = (char)a;
    } else if (BYTE_TYPE == NUMBER){
        SciaRegs.SCITXBUF = (char)(a | 0x30);
    } else {
        /* invalid type */
        return 0;
    }

    /* wait until there is space in buffer */
    while(!(SciaRegs.SCIFFTX.bit.TXFFST < 4) && timeout > 0){
        timeout--;
    }

    if (timeout <= 0){
        /* reset SCI */
        SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 0;
        SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 1;
        return 0;
    } else {
        return 1;
    }
}

int pow(int base, int exponent)
{
    int result=1;
    for (; exponent>0; exponent--)
    {
        result = result * base;
    }
    return result;
}

// Reverses a string 'str' of length 'len' 
void reverse(char* str, int len) 
{ 
    int i = 0, j = len - 1, temp; 
    while (i < j) { 
        temp = str[i]; 
        str[i] = str[j]; 
        str[j] = temp; 
        i++; 
        j--; 
    } 
} 

// Converts a given integer x to string str[].  
// d is the number of digits required in the output.  
// If d is more than the number of digits in x,  
// then 0s are added at the beginning. 
int intToStr(int x, char str[], int d) 
{ 
    int i = 0; 
    while (x) { 
        str[i++] = (x % 10) + '0'; 
        x = x / 10; 
    } 
  
    // If number of digits required is more, then 
    // add 0s at the beginning 
    while (i < d) 
        str[i++] = '0'; 
  
    reverse(str, i); 
    str[i] = '\0'; 
    return i; 
} 
  
// Converts a floating-point/double number to a string. 
void ftoa(float n, char* res, int afterpoint) 
{ 
    // Extract integer part 
    int ipart = (int)n; 
  
    // Extract floating part 
    float fpart = n - (float)ipart; 
  
    // convert integer part to string 
    int i = intToStr(ipart, res, 0); 
  
    // check for display option after point 
    if (afterpoint != 0) { 
        res[i] = '.'; // add dot 
  
        // Get the value of fraction part upto given no. 
        // of points after dot. The third parameter  
        // is needed to handle cases like 233.007 
        fpart = fpart * pow(10, afterpoint); 
  
        intToStr((int)fpart, res + i + 1, afterpoint); 
    } 
}
