/*
 * extender.h
 *
 *  Extender API Prototypes
 */

#ifndef EXTENDER_H_
#define EXTENDER_H_

#define xdc__strict
#include <ti/sysbios/knl/Task.h>
#include "i2c_software_extender.h"

//Extender Cmds
#define EXT_RESET 0xf0
#define EXT_SET_POINTER 0xe1
#define EXT_STATUS_REGISTER_CODE 0xf0
#define EXT_READ_DATA_REGISTER 0xe1
#define EXT_CHANNEL_SELECT_REGISTER 0xd2
#define EXT_CONFIGURATION_REGISTER 0xc3
#define EXT_ONE_WIRE_RESET 0xb4
#define EXT_WRITE_CONFIGURATION_REGISTER 0xd2
#define EXT_ONE_WIRE_READ_BYTE 0x96
#define EXT_ONE_WIRE_WRITE_BYTE 0xa5
#define EXT_CHANNEL_SELECT 0xc3

//One wire commands
#define SKIP_ROM 0xcc
#define CONVERT_T 0x44
#define READ_SCRATCHPAD 0xbe

Uint16 ext_one_wire_reset(void);
Uint16 ext_set_pointer(Uint16);
Uint16 ext_reset(void);
Uint16 ext_write_config(Uint16);
Uint16 ext_one_wire_write_byte(Uint16);
Uint16 ext_channel_select(Uint16);
void ext_send(Uint8);
Uint8 ext_receive(void);

#endif /* EXTENDER_H_ */
