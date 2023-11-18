/*
 * dio.c
 *
 *  Created on: Nov 25, 2020
 *      Author: Najeeb Uddin
 */

#include "dio.h"

//  nops = 1 ~ 2.5 us delay
void delay2(Uint16 nops)
{
    //UInt task_restore_key = Task_disable();

    Uint16 i = 0;

    for (i=0; i<nops; i++){
        __asm("          NOP");
    }

    //Task_restore(task_restore_key);
}

void dio_send_packet(Uint8 device_address, Uint8 address, Uint8 data)
{
    spi_decoder_select(0);
    spi_decoder_select(1);
    spib_transmit(device_address);
    //delay2(10);
    spib_transmit(address);
    //delay2(10);
    spib_transmit(data);
    //delay2(10);
    //spi_decoder_select(0);
}



void dio_init(void)
{
    /*
    dio_send_packet(CONTROL_BYTE, 0x0a,0x3c);
    dio_send_packet(CONTROL_BYTE, 0x0b,0x3c);
    dio_send_packet(CONTROL_BYTE, 0x0,0xff);
    dio_send_packet(CONTROL_BYTE, 0x01,0xff);
    dio_send_packet(CONTROL_BYTE, 0x0c,0xff);
    dio_send_packet(CONTROL_BYTE, 0x0d,0xff);
    dio_send_packet(CONTROL_BYTE, 0x02,0xff);
    dio_send_packet(CONTROL_BYTE, 0x03,0xff);
    */
    Uint8 i = 0;
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE, 0x0a,0x3c);
        Task_sleep(100);
    }
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE, 0x0b,0x3c);
        Task_sleep(100);
    }
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE, 0x0,0xff);
        Task_sleep(100);
    }
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE, 0x01,0xff);
        Task_sleep(100);
    }
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE, 0x0c,0xff);
        Task_sleep(100);
    }
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE, 0x0d,0xff);
        Task_sleep(100);
    }
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE, 0x02,0xff);
        Task_sleep(100);
    }
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE, 0x03,0xff);
        Task_sleep(100);
    }
    /*
    //delay2(1000);
    Task_sleep(100);
    dio_send_packet(0x0b,0x3c);
    //delay2(1000);
    Task_sleep(1);
    for (i=0; i<4; i++){
        dio_send_packet(i,0xff);
    }
    dio_send_packet(0x00,0xff);
    //delay2(1000);
    Task_sleep(1);
    dio_send_packet(0x01,0xff);
    //delay2(1000);
    Task_sleep(1);
    dio_send_packet(0x0c,0x77);
    //delay2(1000);
    Task_sleep(1);
    dio_send_packet(0x0d,0x77);
    //delay2(1000);
    Task_sleep(1);
    */
}

void dio2_init(void)
{
    Uint8 i = 0;
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE2, 0x0a,0x3c);
        Task_sleep(100);
    }
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE2, 0x0b,0x3c);
        Task_sleep(100);
    }
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE2, 0x0,0xff);
        Task_sleep(100);
    }
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE2, 0x01,0xff);
        Task_sleep(100);
    }
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE2, 0x0c,0xff);
        Task_sleep(100);
    }
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE2, 0x0d,0xff);
        Task_sleep(100);
    }
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE2, 0x02,0xff);
        Task_sleep(100);
    }
    for (i=0; i<5; i++){
        dio_send_packet(CONTROL_BYTE2, 0x03,0xff);
        Task_sleep(100);
    }
}

Uint8 dio_receive_packet(Uint8 device_address, Uint8 address)
{
    Uint8 data = 0;
    //spi_decoder_select(2);
    spi_decoder_select(0);
    spi_decoder_select(1);
    spib_buffer_reset();
    spib_transmit(device_address | 1);
    data = spib_receive();
    //delay2(5);
    spib_transmit(address);
    //delay2(5);
    data = spib_receive();
    //SpibRegs.SPIFFRX.bit.RXFFST = 0;
    spib_transmit(0x00);
    data = spib_receive();
    //delay2(5);
    //data = spib_receive();
    //data = spib_receive();
    //data = spib_receive();
    //spi_decoder_select(0);
    return data;
}

Uint16 dio_read(void)
{
    Uint16 data = 0;

    data = dio_receive_packet(CONTROL_BYTE, 0x12);
    delay2(1000);
    data |= (dio_receive_packet(CONTROL_BYTE, 0x13) << 8);

    return data;
}

Uint16 dio2_read(void)
{
    Uint16 data = 0;

    data = dio_receive_packet(CONTROL_BYTE2, 0x12);
    delay2(1000);
    data |= (dio_receive_packet(CONTROL_BYTE2, 0x13) << 8);

    return data;
}
