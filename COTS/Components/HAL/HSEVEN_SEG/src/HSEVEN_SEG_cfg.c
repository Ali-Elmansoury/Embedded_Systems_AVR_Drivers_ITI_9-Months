#include "HSEVEN_SEG.h"
#include "HSEVEN_SEG_cfg.h"
#include "MPORT_cfg.h"

HSEVEN_SEG_strSevenSegCfg_t HSEVEN_SEG_strSevenSegCfg[HSEVEN_SEG_NUM_OF_SEVEN_SEG] = {
    [HSEVEN_SEG_SEVEN_SEG1] = {
        .HSEVEN_SEG_strSevenSegPins = {
            .HSEVEN_SEG_PIN_A = MPORT_PINA0,
            .HSEVEN_SEG_PIN_B = MPORT_PINA1,
            .HSEVEN_SEG_PIN_C = MPORT_PINA2,
            .HSEVEN_SEG_PIN_D = MPORT_PINA3,
            .HSEVEN_SEG_PIN_E = MPORT_PINA4,
            .HSEVEN_SEG_PIN_F = MPORT_PINA5,
            .HSEVEN_SEG_PIN_G = MPORT_PINA6,
            .HSEVEN_SEG_PIN_DP = MPORT_PINA7,
        },
        .HSEVEN_SEG_enuSevenSegConnection = HSEVEN_SEG_enuCommon_Cathode
    },
    [HSEVEN_SEG_SEVEN_SEG2] = {
        .HSEVEN_SEG_strSevenSegPins = {
            .HSEVEN_SEG_PIN_A = MPORT_PINB0,
            .HSEVEN_SEG_PIN_B = MPORT_PINB1,
            .HSEVEN_SEG_PIN_C = MPORT_PINB2,
            .HSEVEN_SEG_PIN_D = MPORT_PINB3,
            .HSEVEN_SEG_PIN_E = MPORT_PINB4,
            .HSEVEN_SEG_PIN_F = MPORT_PINB5,
            .HSEVEN_SEG_PIN_G = MPORT_PINB6,
            .HSEVEN_SEG_PIN_DP = MPORT_PINB7,
        },
        .HSEVEN_SEG_enuSevenSegConnection = HSEVEN_SEG_enuCommon_Anode
    },
    [HSEVEN_SEG_SEVEN_SEG3] = {
        .HSEVEN_SEG_strSevenSegPins = {
            .HSEVEN_SEG_PIN_A = MPORT_PINC0,
            .HSEVEN_SEG_PIN_B = MPORT_PINC1,
            .HSEVEN_SEG_PIN_C = MPORT_PINC2,
            .HSEVEN_SEG_PIN_D = MPORT_PINC3,
            .HSEVEN_SEG_PIN_E = MPORT_PINC4,
            .HSEVEN_SEG_PIN_F = MPORT_PINC5,
            .HSEVEN_SEG_PIN_G = MPORT_PINC6,
            .HSEVEN_SEG_PIN_DP = MPORT_PINC7,
        },
        .HSEVEN_SEG_enuSevenSegConnection = HSEVEN_SEG_enuCommon_Cathode
    },
    [HSEVEN_SEG_SEVEN_SEG4] = {
        .HSEVEN_SEG_strSevenSegPins = {
            .HSEVEN_SEG_PIN_A = MPORT_PIND0,
            .HSEVEN_SEG_PIN_B = MPORT_PIND1,
            .HSEVEN_SEG_PIN_C = MPORT_PIND2,
            .HSEVEN_SEG_PIN_D = MPORT_PIND3,
            .HSEVEN_SEG_PIN_E = MPORT_PIND4,
            .HSEVEN_SEG_PIN_F = MPORT_PIND5,
            .HSEVEN_SEG_PIN_G = MPORT_PIND6,
            .HSEVEN_SEG_PIN_DP = MPORT_PIND7,
        },
        .HSEVEN_SEG_enuSevenSegConnection = HSEVEN_SEG_enuCommon_Cathode
    }
};