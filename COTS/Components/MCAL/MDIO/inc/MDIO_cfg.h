/*#ifndef MDIO_CFG_H
#define MDIO_CFG_H

#include "STD_TYPES.h"
#include "MDIO.h"

#define MDIO_NUM_OF_PORTS 4
#define MDIO_NUM_OF_PINS 8

#define MDIO_PINA0 0x00
#define MDIO_PINA1 0x01
#define MDIO_PINA2 0x02
#define MDIO_PINA3 0x03
#define MDIO_PINA4 0x04
#define MDIO_PINA5 0x05
#define MDIO_PINA6 0x06
#define MDIO_PINA7 0x07

#define MDIO_PINB0 0x10
#define MDIO_PINB1 0x11
#define MDIO_PINB2 0x12
#define MDIO_PINB3 0x13
#define MDIO_PINB4 0x14
#define MDIO_PINB5 0x15
#define MDIO_PINB6 0x16
#define MDIO_PINB7 0x17

#define MDIO_PINC0 0x20
#define MDIO_PINC1 0x21
#define MDIO_PINC2 0x22
#define MDIO_PINC3 0x23
#define MDIO_PINC4 0x24
#define MDIO_PINC5 0x25
#define MDIO_PINC6 0x26
#define MDIO_PINC7 0x27

#define MDIO_PIND0 0x30
#define MDIO_PIND1 0x31
#define MDIO_PIND2 0x32
#define MDIO_PIND3 0x33
#define MDIO_PIND4 0x34
#define MDIO_PIND5 0x35
#define MDIO_PIND6 0x36
#define MDIO_PIND7 0x37

typedef enum{
    MDIO_enuPinDir_UNASSIGNED,
    MDIO_enuPinDir_OUTPUT,
    MDIO_enuPinDir_INPUT
}MDIO_enuPinDir_t; 

typedef struct{
    u8 pin;
    MDIO_enuPinDir_t dir;
    MDIO_enuPinCfg_t cfg;
}MDIO_strPinCfg_t;

#endif // MDIO_CFG_H*/