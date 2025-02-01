#ifndef HLCD_CFG_H
#define HLCD_CFG_H

#include "HLCD.h"

#define HLCD_NUM_OF_DATA_BITS   8
#define HLCD_NUM_OF_CTRL_BITS  3

#define HLCD_NUM_OF_LCDs        1
#define HLCD_LCD1               0
#define HLCD_LCD2               1

/* Function Set Command Bits */
#define HLCD_CMD_FUNCTION_SET_CMD_BASE              (0b00100000)  // Base command for Function Set
#define HLCD_CMD_FUNCTION_SET_DATALENGTH_8BIT       (0b00010000)  // DL=1 (8-bit mode)
#define HLCD_CMD_FUNCTION_SET_DATALENGTH_4BIT       (0b00000000)  // DL=0 (4-bit mode)
#define HLCD_CMD_FUNCTION_SET_DISPLAYLINE_2LINE     (0b00001000)  // N=1 (2-line display)
#define HLCD_CMD_FUNCTION_SET_DISPLAYLINE_1LINE     (0b00000000)  // N=0 (1-line display)
#define HLCD_CMD_FUNCTION_SET_CHARACTERFONT_5X10    (0b00000100)  // F=1 (5x10 font)
#define HLCD_CMD_FUNCTION_SET_CHARACTERFONT_5X7     (0b00000000)  // F=0 (5x7 font)

/* Display ON/OFF Control Bits */
#define HLCD_CMD_DISPLAY_ONOFF_CMD_BASE             (0b00001000)  // Base command for Display ON/OFF
#define HLCD_CMD_DISPLAY_ON                         (0b00000100)  // D=1 (Display ON)
#define HLCD_CMD_DISPLAY_OFF                        (0b00000000)  // D=0 (Display OFF)
#define HLCD_CMD_CURSOR_ON                          (0b00000010)  // C=1 (Cursor ON)
#define HLCD_CMD_CURSOR_OFF                         (0b00000000)  // C=0 (Cursor OFF)
#define HLCD_CMD_CURSOR_BLINK_ON                    (0b00000001)  // B=1 (Blink ON)
#define HLCD_CMD_CURSOR_BLINK_OFF                   (0b00000000)  // B=0 (Blink OFF)

/* Entry Mode Set Bits */
#define HLCD_CMD_ENTRY_MODE_CMD_BASE                (0b00000100)  // Base command for Entry Mode
#define HLCD_CMD_ENTRY_MODE_INCREMENT               (0b00000010)  // I/D=1 (Increment)
#define HLCD_CMD_ENTRY_MODE_DECREMENT               (0b00000000)  // I/D=0 (Decrement)
#define HLCD_CMD_ENTRY_MODE_SHIFT                   (0b00000001)  // S=1 (Shift)
#define HLCD_CMD_ENTRY_MODE_NOSHIFT                 (0b00000000)  // S=0 (No Shift)

/* Clear Instructions */
#define HLCD_CMD_CLEAR_DISPLAY                      (0b00000001)  // Clear Display
#define HLCD_CMD_RETURN_HOME                        (0b00000010)  // Return Home

typedef struct
{
    union {
        struct {
            u8 HLCD_PIN_D0;
            u8 HLCD_PIN_D1;
            u8 HLCD_PIN_D2;
            u8 HLCD_PIN_D3;
            u8 HLCD_PIN_D4;
            u8 HLCD_PIN_D5;
            u8 HLCD_PIN_D6;
            u8 HLCD_PIN_D7;
        };
        u8 HLCD_arrDataPins[HLCD_NUM_OF_DATA_BITS];

        struct {
            u8 HLCD_PIN_RS;
            u8 HLCD_PIN_RW;
            u8 HLCD_PIN_E;
        };
        u8 HLCD_arrControlPins[HLCD_NUM_OF_CTRL_BITS];        
    };
}HLCD_strLCDPins_t;

typedef struct
{
    HLCD_enuDataLengthControlBits_t HLCD_enuDataLengthControlBits;
    HLCD_enuDisplayLineNumber_t HLCD_enuDisplayLineNumber;
    HLCD_enuDisplayOnOff_t HLCD_enuDisplayOnOff;
    HLCD_enuCursorOnOff_t HLCD_enuCursorOnOff;
    HLCD_enuCursorBlinkOnOff_t HLCD_enuCursorBlinkOnOff;
    HLCD_enuCharacterFont_t HLCD_enuCharacterFont;
}HLCD_strFunctionSet_t;

typedef struct
{
    HLCD_enuCursorDirection_t HLCD_enuCursorDirection;
    HLCD_enuDisplayShift_t HLCD_enuDisplayShift;
}HLCD_strEntryMode_t;

typedef struct
{
    HLCD_strLCDPins_t HLCD_strLCDPins;
    HLCD_strFunctionSet_t HLCD_strFunctionSet;
    HLCD_enuClearInstructions_t HLCD_enuClearInstructions;
    HLCD_strEntryMode_t HLCD_strEntryMode;
}HLCD_strLCDCfg_t;

#endif //HLCD_CFG_H