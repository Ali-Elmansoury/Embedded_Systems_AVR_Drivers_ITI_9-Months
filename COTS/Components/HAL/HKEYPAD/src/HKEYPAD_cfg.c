#include "HKEYPAD.h"
#include "HKEYPAD_cfg.h"

HKEYPAD_strKeypadCfg_t HKEYPAD_strKeypadCfg[HKEYPAD_NUM_OF_KEYPADS] = {
    [HKEYPAD_1] = {
        .HKEYPAD_numRows = 4,
        .HKEYPAD_numCols = 4,
        .HKEYPAD_debounceTime = 20,
        .HKEYPAD_strKeypadPins = {
            .HKEYPAD_PIN_ROW0 = HKEYPAD_PINB3,
            .HKEYPAD_PIN_ROW1 = HKEYPAD_PINB4,
            .HKEYPAD_PIN_ROW2 = HKEYPAD_PINB5,
            .HKEYPAD_PIN_ROW3 = HKEYPAD_PINB6,

            .HKEYPAD_PIN_COL0 = HKEYPAD_PIND3,
            .HKEYPAD_PIN_COL1 = HKEYPAD_PIND4,
            .HKEYPAD_PIN_COL2 = HKEYPAD_PIND5,
            .HKEYPAD_PIN_COL3 = HKEYPAD_PIND6
        }
    }
};

char HKEYPAD_arrKeypad1_Mapping [4][4] = {
    {0,1,2,3},
    {4,5,6,7},
    {8,9,10,11},
    {12,13,14,15}
};