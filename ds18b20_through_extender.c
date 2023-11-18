/*
 * ds18b20_through_extender.c
 *
 *  API to control DS18B20 through DS2482-800
 */

#include <custom_libs/ds18b20_through_extender.h>

Uint16 read_temperature(float * temperature_buffer, Uint16 ext_channel)
{
    Uint16 raw = 0;
    Task_disable();
        ext_channel_select(ext_channel);
    //Task_sleep(10);
    //DELAY_US(10);
    delay_ext(10);
    if (ext_one_wire_reset()){
            ext_one_wire_write_byte(SKIP_ROM);
        //Task_sleep(2);
        //DELAY_US(1500);
        delay_ext(1500);
            ext_one_wire_write_byte(READ_SCRATCHPAD);
        //Task_sleep(2);
        //DELAY_US(1500);
        delay_ext(1500);
            //i2c_send(EXT_ONE_WIRE_READ_BYTE);
            ext_send(EXT_ONE_WIRE_READ_BYTE);
        //Task_sleep(5);
        //DELAY_US(5000);
        delay_ext(5000);
            ext_set_pointer(EXT_READ_DATA_REGISTER);
        //Task_sleep(1);
        //DELAY_US(10);
        delay_ext(10);
            raw = ext_receive();
        //Task_sleep(1);
        //DELAY_US(10);
        delay_ext(10);
            //i2c_send(EXT_ONE_WIRE_READ_BYTE);
            ext_send(EXT_ONE_WIRE_READ_BYTE);
        //Task_sleep(5);
        //DELAY_US(5000);
        delay_ext(5000);
            ext_set_pointer(EXT_READ_DATA_REGISTER);
        //Task_sleep(1);
        //DELAY_US(10);
        delay_ext(10);
            //raw |= i2c_receive() << 8;
            raw |= ext_receive() << 8;
        //Task_sleep(1);
        //DELAY_US(10);
        delay_ext(10);
            *temperature_buffer = (float)raw / 16.0;
            ext_one_wire_reset();
        //Task_sleep(1);
        //DELAY_US(10);
        delay_ext(10);
            ext_one_wire_write_byte(SKIP_ROM);
        //Task_sleep(2);
        //DELAY_US(1500);
        delay_ext(1500);
            ext_one_wire_write_byte(CONVERT_T);
    }else{
        *temperature_buffer = 0xff;
    }
    Task_enable();
    return 1;
}
