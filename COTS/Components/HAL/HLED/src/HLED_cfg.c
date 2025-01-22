#include "HLED_cfg.h"
#include "HLED.h"
#include "MPORT.h"

HLED_strLedCfg_t HLED_strLedCfg[HLED_NUM_OF_LEDS] = {
    [HLED_LED_START] = {
        .HLED_u8LedPort = MPORT_enuPORTB,
        .HLED_u8LedPin = MPORT_enuPIN0,
        .HLED_enuLedConnection = HLED_enuLED_SOURCE
    },
    [HLED_LED_STOP] = {
        .HLED_u8LedPort = MPORT_enuPORTB,
        .HLED_u8LedPin = MPORT_enuPIN1,
        .HLED_enuLedConnection = HLED_enuLED_SOURCE
    },
    [HLED_LED_ALERT] = {
        .HLED_u8LedPort = MPORT_enuPORTB,
        .HLED_u8LedPin = MPORT_enuPIN2,
        .HLED_enuLedConnection = HLED_enuLED_SOURCE
    }
};