#ifndef HKEYPAD_CFG_H
#define HKEYPAD_CFG_H

#include "HKEYPAD.h"
#include "STD_TYPES.h"

#define HKEYPAD_NUM_OF_KEYPADS (1)
#define HKEYPAD_MAX_NUM_OF_ROWS (8)
#define HKEYPAD_MAX_NUM_OF_COLS (8)

#define HKEYPAD_1 (0)
#define HKEYPAD_2 (1)
#define HKEYPAD_3 (2)

typedef struct
{
    union
    {
        struct
        {
            /*You can add more based on your config*/
            u8 HKEYPAD_PIN_ROW0;
            u8 HKEYPAD_PIN_ROW1;
            u8 HKEYPAD_PIN_ROW2;
            u8 HKEYPAD_PIN_ROW3;
            u8 HKEYPAD_PIN_ROW4;
            u8 HKEYPAD_PIN_ROW5;
            u8 HKEYPAD_PIN_ROW6;
            u8 HKEYPAD_PIN_ROW7;
        };
        u8 HKEYPAD_rowPins[HKEYPAD_MAX_NUM_OF_ROWS];
    };
    union
    {
        struct
        {
            /*You can add more based on your config*/
            u8 HKEYPAD_PIN_COL0;
            u8 HKEYPAD_PIN_COL1;
            u8 HKEYPAD_PIN_COL2;
            u8 HKEYPAD_PIN_COL3;
            u8 HKEYPAD_PIN_COL4;
            u8 HKEYPAD_PIN_COL5;
            u8 HKEYPAD_PIN_COL6;
            u8 HKEYPAD_PIN_COL7;
        };
        u8 HKEYPAD_colPins[HKEYPAD_MAX_NUM_OF_COLS];
    };
} HKEYPAD_strKeypadPins_t;

typedef struct
{
    u8 HKEYPAD_numRows;
    u8 HKEYPAD_numCols;
    HKEYPAD_strKeypadPins_t HKEYPAD_strKeypadPins;
    u8 HKEYPAD_debounceTime; // Debounce delay in milliseconds
} HKEYPAD_strKeypadCfg_t;

#endif // HKEYPAD_CFG_H