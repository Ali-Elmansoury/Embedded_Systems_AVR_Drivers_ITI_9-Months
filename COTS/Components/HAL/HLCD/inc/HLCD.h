#ifndef HLCD_H
#define HLCD_H

#include "STD_TYPES.h"

#define HLCD_PINA0 0x00
#define HLCD_PINA1 0x01
#define HLCD_PINA2 0x02
#define HLCD_PINA3 0x03
#define HLCD_PINA4 0x04
#define HLCD_PINA5 0x05
#define HLCD_PINA6 0x06
#define HLCD_PINA7 0x07

#define HLCD_PINB0 0x10
#define HLCD_PINB1 0x11
#define HLCD_PINB2 0x12
#define HLCD_PINB3 0x13
#define HLCD_PINB4 0x14
#define HLCD_PINB5 0x15
#define HLCD_PINB6 0x16
#define HLCD_PINB7 0x17

#define HLCD_PINC0 0x20
#define HLCD_PINC1 0x21
#define HLCD_PINC2 0x22
#define HLCD_PINC3 0x23
#define HLCD_PINC4 0x24
#define HLCD_PINC5 0x25
#define HLCD_PINC6 0x26
#define HLCD_PINC7 0x27

#define HLCD_PIND0 0x30
#define HLCD_PIND1 0x31
#define HLCD_PIND2 0x32
#define HLCD_PIND3 0x33
#define HLCD_PIND4 0x34
#define HLCD_PIND5 0x35
#define HLCD_PIND6 0x36
#define HLCD_PIND7 0x37

typedef enum {
    HLCD_enuErrorStatus_NOK,
    HLCD_enuErrorStatus_OK
}HLCD_enuErrorStatus_t;

typedef enum {
    HLCD_enuDataLengthControlBits_4Bit,
    HLCD_enuDataLengthControlBits_8Bit
}HLCD_enuDataLengthControlBits_t;

typedef enum {
    HLCD_enuOneDisplayLine,
    HLCD_enuTwoDisplayLines
}HLCD_enuDisplayLineNumber_t;

typedef enum {
    HLCD_enuCharacterFont_5x7,
    HLCD_enuCharacterFont_5x10
}HLCD_enuCharacterFont_t;

typedef enum {
    HLCD_enuDisplay_On,
    HLCD_enuDisplay_Off
}HLCD_enuDisplayOnOff_t;

typedef enum {
    HLCD_enuCursor_On,
    HLCD_enuCursor_Off
}HLCD_enuCursorOnOff_t;

typedef enum {
    HLCD_enuCursorBlinkOn,
    HLCD_enuCursorBlinkOff
}HLCD_enuCursorBlinkOnOff_t;

typedef enum {
    HLCD_enuClearInstruction_ClearDisplay,
    HLCD_enuClearInstruction_ReturnHome,
}HLCD_enuClearInstructions_t;

typedef enum {
    HLCD_enuCursorDirection_Increment,
    HLCD_enuCursorDirection_Decrement
}HLCD_enuCursorDirection_t;

typedef enum {
    HLCD_enuDisplayShift_NoShift,
    HLCD_enuDisplayShift_Shifts
}HLCD_enuDisplayShift_t;

HLCD_enuErrorStatus_t HLCD_enuInit(void);
HLCD_enuErrorStatus_t HLCD_enuWriteData(u8 Copy_u8LCDNum, u8 Copy_u8Data);
HLCD_enuErrorStatus_t HLCD_enuWriteCommand(u8 Copy_u8LCDNum, u8 Copy_u8Command);
HLCD_enuErrorStatus_t HLCD_enuGotoXY(u8 Copy_u8LCDNum, u8 Copy_u8X, u8 Copy_u8Y);
HLCD_enuErrorStatus_t HLCD_enuWriteSpecialChar(u8 Copy_u8LCDNum, u8* Addr_pattern, u8 Copy_u8BlockNumber);
HLCD_enuErrorStatus_t HLCD_enuWriteString(u8 Copy_u8LCDNum, u16* Addr_str);
HLCD_enuErrorStatus_t HLCD_enuWriteNumber(u8 Copy_u8LCDNum, u16 Copy_u16Number);

#endif //HLCD_H