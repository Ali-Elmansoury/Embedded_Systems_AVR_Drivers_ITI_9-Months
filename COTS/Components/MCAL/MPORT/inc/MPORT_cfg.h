#ifndef MPORT_CFG_H
#define MPORT_CFG_H

#include "STD_TYPES.h"
#include "MPORT.h"

#define MPORT_NUM_OF_PORTS 4
#define MPORT_NUM_OF_PINS 8

#define MPORT_PINA0 0x00
#define MPORT_PINA1 0x01
#define MPORT_PINA2 0x02
#define MPORT_PINA3 0x03
#define MPORT_PINA4 0x04
#define MPORT_PINA5 0x05
#define MPORT_PINA6 0x06
#define MPORT_PINA7 0x07

#define MPORT_PINB0 0x10
#define MPORT_PINB1 0x11
#define MPORT_PINB2 0x12
#define MPORT_PINB3 0x13
#define MPORT_PINB4 0x14
#define MPORT_PINB5 0x15
#define MPORT_PINB6 0x16
#define MPORT_PINB7 0x17

#define MPORT_PINC0 0x20
#define MPORT_PINC1 0x21
#define MPORT_PINC2 0x22
#define MPORT_PINC3 0x23
#define MPORT_PINC4 0x24
#define MPORT_PINC5 0x25
#define MPORT_PINC6 0x26
#define MPORT_PINC7 0x27

#define MPORT_PIND0 0x30
#define MPORT_PIND1 0x31
#define MPORT_PIND2 0x32
#define MPORT_PIND3 0x33
#define MPORT_PIND4 0x34
#define MPORT_PIND5 0x35
#define MPORT_PIND6 0x36
#define MPORT_PIND7 0x37

typedef struct{
    u8 pin;
    u8 dir;
    MPORT_enuPinMode_t cfg;
}MPORT_strPinCfg_t;


#endif // MPORT_CFG_H