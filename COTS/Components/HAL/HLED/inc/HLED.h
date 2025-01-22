#ifndef LED_H
#define LED_H

#include "STD_TYPES.h"

typedef enum {
  HLED_enuLED_OFF,
  HLED_enuLED_ON
}HLED_enuLedState_t;

typedef enum {
  HLED_enuError_OK,
  HLED_enuError_NOK,
  HLED_enuError_INVALID_NUM_OF_LEDS,
  HLED_enuError_INVALID_LED_STATE,
  HLED_enuError_INVALID_LED_CONNECTION
}HLED_enuErrorStatus_t;

typedef enum {
    HLED_enuLED_SOURCE,
    HLED_enuLED_SINK
}HLED_enuLedConnection_t;

void HLED_vInit(void);
HLED_enuErrorStatus_t HLED_enuSetLedState(u8 Copy_u8LedName, u8 Copy_u8State);


#endif // LED_H