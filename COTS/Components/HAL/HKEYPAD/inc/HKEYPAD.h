#ifndef HKEYPAD_H
#define HKEYPAD_H

#include "STD_TYPES.h"

#define HKEYPAD_PINA0 0x00
#define HKEYPAD_PINA1 0x01
#define HKEYPAD_PINA2 0x02
#define HKEYPAD_PINA3 0x03
#define HKEYPAD_PINA4 0x04
#define HKEYPAD_PINA5 0x05
#define HKEYPAD_PINA6 0x06
#define HKEYPAD_PINA7 0x07

#define HKEYPAD_PINB0 0x10
#define HKEYPAD_PINB1 0x11
#define HKEYPAD_PINB2 0x12
#define HKEYPAD_PINB3 0x13
#define HKEYPAD_PINB4 0x14
#define HKEYPAD_PINB5 0x15
#define HKEYPAD_PINB6 0x16
#define HKEYPAD_PINB7 0x17

#define HKEYPAD_PINC0 0x20
#define HKEYPAD_PINC1 0x21
#define HKEYPAD_PINC2 0x22
#define HKEYPAD_PINC3 0x23
#define HKEYPAD_PINC4 0x24
#define HKEYPAD_PINC5 0x25
#define HKEYPAD_PINC6 0x26
#define HKEYPAD_PINC7 0x27

#define HKEYPAD_PIND0 0x30
#define HKEYPAD_PIND1 0x31
#define HKEYPAD_PIND2 0x32
#define HKEYPAD_PIND3 0x33
#define HKEYPAD_PIND4 0x34
#define HKEYPAD_PIND5 0x35
#define HKEYPAD_PIND6 0x36
#define HKEYPAD_PIND7 0x37

typedef enum {
    HKEYPAD_enuErrorStatus_NOK,
    HKEYPAD_enuErrorStatus_OK,
    HKEYPAD_enuErrorStatus_NULL_POINTER,
    HKEYPAD_enuErrorStatus_INVALID_ROWS_NO,
    HKEYPAD_enuErrorStatus_INVALID_COLS_NO,
    HKEYPAD_enuErrorStatus_INVALID_KEYPAD_NO
}HKEYPAD_enuErrorStatus_t;

HKEYPAD_enuErrorStatus_t HKEYPAD_enuInit(void);
HKEYPAD_enuErrorStatus_t HKEYPAD_enuGetPressedKey(u8 Copy_u8KeypadNum, u8* Addr_u8Key);

#endif //HKEYPAD_H