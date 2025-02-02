#include "HLCD_cfg.h"
#include "MPORT.h"

HLCD_strLCDCfg_t HLCD_strLCDCfg[HLCD_NUM_OF_LCDs] = {
    [HLCD_LCD1] = {
        .HLCD_strLCDPins = {
            .HLCD_PIN_D0 = HLCD_PINA0,
            .HLCD_PIN_D1 = HLCD_PINA1,
            .HLCD_PIN_D2 = HLCD_PINA2,
            .HLCD_PIN_D3 = HLCD_PINA3,
            .HLCD_PIN_D4 = HLCD_PINA4,
            .HLCD_PIN_D5 = HLCD_PINA5,
            .HLCD_PIN_D6 = HLCD_PINA6,
            .HLCD_PIN_D7 = HLCD_PINA7,
            .HLCD_PIN_RS = HLCD_PINB0,
            .HLCD_PIN_RW = HLCD_PINB1,
            .HLCD_PIN_E = HLCD_PINB2
        },
        .HLCD_strFunctionSet = {
            .HLCD_enuCharacterFont = HLCD_enuCharacterFont_5x7,
            .HLCD_enuCursorBlinkOnOff = HLCD_enuCursorBlinkOn,
            .HLCD_enuCursorOnOff = HLCD_enuCursor_On,
            .HLCD_enuDataLengthControlBits = HLCD_enuDataLengthControlBits_8Bit,
            .HLCD_enuDisplayLineNumber = HLCD_enuTwoDisplayLines,
            .HLCD_enuDisplayOnOff = HLCD_enuDisplay_On
        },
        .HLCD_strEntryMode = {
            .HLCD_enuCursorDirection = HLCD_enuCursorDirection_Increment,
            .HLCD_enuDisplayShift = HLCD_enuDisplayShift_NoShift
        },
        .HLCD_enuClearInstructions = HLCD_enuClearInstruction_ClearDisplay
    },

    [HLCD_LCD2] = {
    .HLCD_strLCDPins = {
        .HLCD_PIN_D0 = 0,  // Data pin D0 connected to Port C, Pin 0
        .HLCD_PIN_D1 = 0,  // Data pin D1 connected to Port C, Pin 1
        .HLCD_PIN_D2 = 0,  // Data pin D2 connected to Port C, Pin 2
        .HLCD_PIN_D3 = 0,  // Data pin D3 connected to Port C, Pin 3
        .HLCD_PIN_D4 = HLCD_PINC0,  // Data pin D4 connected to Port C, Pin 4
        .HLCD_PIN_D5 = HLCD_PINC1,  // Data pin D5 connected to Port C, Pin 5
        .HLCD_PIN_D6 = HLCD_PINC2,  // Data pin D6 connected to Port C, Pin 6
        .HLCD_PIN_D7 = HLCD_PINC3,  // Data pin D7 connected to Port C, Pin 7
        .HLCD_PIN_RS = HLCD_PIND0,  // RS pin connected to Port D, Pin 0
        .HLCD_PIN_RW = HLCD_PIND1,  // RW pin connected to Port D, Pin 1
        .HLCD_PIN_E  = HLCD_PIND2   // Enable pin connected to Port D, Pin 2
    },
    .HLCD_strFunctionSet = {
        .HLCD_enuCharacterFont = HLCD_enuCharacterFont_5x10,  // 5x10 font
        .HLCD_enuCursorBlinkOnOff = HLCD_enuCursorBlinkOff,             // Cursor blink OFF
        .HLCD_enuCursorOnOff = HLCD_enuCursor_On,                        // Cursor ON
        .HLCD_enuDataLengthControlBits = HLCD_enuDataLengthControlBits_4Bit,  // 4-bit mode
        .HLCD_enuDisplayLineNumber = HLCD_enuOneDisplayLine,    // 1-line display
        .HLCD_enuDisplayOnOff = HLCD_enuDisplay_On                              // Display ON
    },
    .HLCD_strEntryMode = {
        .HLCD_enuCursorDirection = HLCD_enuCursorDirection_Increment,  // Cursor increments
        .HLCD_enuDisplayShift = HLCD_enuDisplayShift_NoShift        // No display shift
    },
    .HLCD_enuClearInstructions = HLCD_enuClearInstruction_ClearDisplay  // Clear display on init
}
};

