/*
 * extender.c
 *
 *  Extender API Source
 *
 */

#include "extender.h"

Uint16 ext_channel_select(Uint16 channel)
{
  /*
    int16 timeout = 1000;

    I2caRegs.I2CMDR.all = 0x2E20;    //START condition, STOP condition, Master, Transmitter, I2C enabled
    I2caRegs.I2CCNT = 0x02;          // bytes to send - 2 here
    I2caRegs.I2CDXR = EXT_CHANNEL_SELECT;
    I2caRegs.I2CDXR = channel;

    while (I2caRegs.I2CMDR.bit.STP == 1 && timeout > 0) {
        timeout--;
    }

    if (timeout > 0){
      return 1;
    }else{
      return 0;
    }
  */

  Uint8 data[2] = {EXT_CHANNEL_SELECT, channel};
  i2c_software_send_packet_ext(0x18, data, 2);

  return 1;
}

Uint16 ext_reset(void)
{
  /*
    i2c_send(EXT_RESET);
  */
    Uint8 data[1] = {EXT_RESET};
    i2c_software_send_packet_ext(0x18, data,1);

    return 0;
}

Uint16 ext_set_pointer(Uint16 register_pointer_code){
  /*
    int16 timeout = 1000;
    I2caRegs.I2CMDR.all = 0x2E20;    //START condition, STOP condition, Master, Transmitter, I2C enabled
    I2caRegs.I2CCNT = 0x02;          // bytes to send - 2 here
    I2caRegs.I2CDXR = EXT_SET_POINTER;
    I2caRegs.I2CDXR = register_pointer_code;

    while (I2caRegs.I2CMDR.bit.STP == 1 && timeout > 0) {
        timeout--;
    }

    if (timeout > 0){
      return 1;
    }else{
      return 0;
  */
    Uint8 data[2] = {EXT_SET_POINTER, register_pointer_code};
    i2c_software_send_packet_ext(0x18, data, 2);

    return 1;
}

Uint16 ext_write_config(Uint16 config)
{
  /*
    int16 timeout = 1000;

    I2caRegs.I2CMDR.all = 0x2E20;    //START condition, STOP condition, Master, Transmitter, I2C enabled
    I2caRegs.I2CCNT = 0x02;          // bytes to send - 2 here
    I2caRegs.I2CDXR = EXT_WRITE_CONFIGURATION_REGISTER;
    I2caRegs.I2CDXR = config;

    while (I2caRegs.I2CMDR.bit.STP == 1 && timeout > 0) {
        timeout--;
    }

    if (timeout > 0){
      return 1;
    }else{
      return 0;
  */
    Uint8 data[2] = {EXT_WRITE_CONFIGURATION_REGISTER, config};
    i2c_software_send_packet_ext(0x18, data, 2);

    return 1;
}



Uint16 ext_one_wire_reset(void)
{
    /*
    Uint16 presence = 0;
    Uint16 status_reg = 0;

    i2c_send(EXT_ONE_WIRE_RESET);
    //Task_sleep(10);
    //DELAY_US(1000);
    delay(1000);
    ext_set_pointer(EXT_STATUS_REGISTER_CODE);
    status_reg = i2c_receive();

    return presence;
    */
    Uint16 presence = 0;
    Uint16 status_reg = 0;
    
    Uint8 data[1] = {EXT_ONE_WIRE_RESET};
    i2c_software_send_packet_ext(0x18, data, 1);
    delay_ext(1000);
    ext_set_pointer(EXT_STATUS_REGISTER_CODE);
    status_reg = i2c_software_read_packet_ext(0x18);

    presence = (status_reg & 0x02) >> 1;

    return presence;
}

Uint16 ext_one_wire_write_byte(Uint16 byte)
{
  /*
    int16 timeout = 1000;

    I2caRegs.I2CMDR.all = 0x2E20;    //START condition, STOP condition, Master, Transmitter, I2C enabled
    I2caRegs.I2CCNT = 0x02;          // bytes to send - 2 here
    I2caRegs.I2CDXR = EXT_ONE_WIRE_WRITE_BYTE;
    I2caRegs.I2CDXR = byte;

    while (I2caRegs.I2CMDR.bit.STP == 1 && timeout > 0) {
        timeout--;
    }

    if (timeout > 0){
      return 1;
    }else{
     
  */
    Uint8 data[2] = {EXT_ONE_WIRE_WRITE_BYTE, byte};
    i2c_software_send_packet_ext(0x18, data, 2);

    return 1;
}

void ext_send(Uint8 data)
{
  i2c_software_send_byte_ext(0x18,data);

  return;
}

Uint8 ext_receive(void)
{
  return i2c_software_read_packet_ext(0x18);
}
