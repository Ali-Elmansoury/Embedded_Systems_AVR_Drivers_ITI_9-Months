#ifndef LED_CFG_H
#define LED_CFG_H

#include "STD_TYPES.h"
#include "HLED.h"

#define HLED_NUM_OF_LEDS 3

#define HLED_LED_START 0
#define HLED_LED_STOP 1
#define HLED_LED_ALERT 2

typedef struct {
    u8 HLED_u8LedPort;
    u8 HLED_u8LedPin;
    HLED_enuLedConnection_t HLED_enuLedConnection;
}HLED_strLedCfg_t;

#endif // LED_CFG_H