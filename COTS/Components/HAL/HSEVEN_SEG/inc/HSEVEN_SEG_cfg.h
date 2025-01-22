#ifndef HSEVEN_SEG_CFG_H
#define HSEVEN_SEG_CFG_H

#include "STD_TYPES.h"
#include "HSEVEN_SEG.h"

#define HSEVEN_SEG_NUM_OF_SEVEN_SEG 4

#define HSEVEN_SEG_SEVEN_SEG1   0
#define HSEVEN_SEG_SEVEN_SEG2   1
#define HSEVEN_SEG_SEVEN_SEG3   2
#define HSEVEN_SEG_SEVEN_SEG4   3

#define HSEVEN_SEG_NUM_OF_SEVEN_SEG_PINS    8

#define HSEVEN_SEG_MAX_NUM_TO_DISPLAY   9

typedef enum {
    HSEVEN_SEG_NUM_0 = 0b00111111,
    HSEVEN_SEG_NUM_1 = 0b00000110,
    HSEVEN_SEG_NUM_2 = 0b01011011,
    HSEVEN_SEG_NUM_3 = 0b01001111,
    HSEVEN_SEG_NUM_4 = 0b01100110,
    HSEVEN_SEG_NUM_5 = 0b01101101,
    HSEVEN_SEG_NUM_6 = 0b01111101,
    HSEVEN_SEG_NUM_7 = 0b00000111,
    HSEVEN_SEG_NUM_8 = 0b01111111,
    HSEVEN_SEG_NUM_9 = 0b01101111,

}HSEVEN_SEG_enuSevenSegNums_t;

typedef struct {
    union {
        struct {
            u8 HSEVEN_SEG_PIN_A;
            u8 HSEVEN_SEG_PIN_B;
            u8 HSEVEN_SEG_PIN_C;
            u8 HSEVEN_SEG_PIN_D;
            u8 HSEVEN_SEG_PIN_E;
            u8 HSEVEN_SEG_PIN_F;
            u8 HSEVEN_SEG_PIN_G;
            u8 HSEVEN_SEG_PIN_DP;
        };
        u8 HSEVEN_SEG_PINS[HSEVEN_SEG_NUM_OF_SEVEN_SEG_PINS];
    };
} HSEVEN_SEG_strSevenSegPins_t;


typedef struct {
    HSEVEN_SEG_strSevenSegPins_t HSEVEN_SEG_strSevenSegPins;
    HSEVEN_SEG_enuSevenSegConnection_t HSEVEN_SEG_enuSevenSegConnection;
} HSEVEN_SEG_strSevenSegCfg_t;


#endif // HSEVEN_SEG_CFG_H