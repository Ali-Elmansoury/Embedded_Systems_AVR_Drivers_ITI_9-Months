#ifndef SWITCH_H
#define SWITCH_H

#include "STD_TYPES.h"

typedef enum {
  HSWITCH_enuSwitch_NOT_PRESSED,
  HSWITCH_enuSwitch_PRESSED
}HSWITCH_enuSwitchState_t;

typedef enum {
  HSWITCH_enuError_OK,
  HSWITCH_enuError_NOK,
  HSWITCH_enuError_INVALID_NUM_OF_SWITCHS,
  HSWITCH_enuError_INVALID_SWITCH_CONNECTION
}HSWITCH_enuErrorStatus_t;

typedef enum {
    HSWITCH_enuSwitch_EXTERNAL_PULL_DOWN,
    HSWITCH_enuSwitch_EXTERNAL_PULL_UP,
    HSWITCH_enuSwitch_INTERNAL_PULL_UP,
}HSWITCH_enuSwitchConnection_t;

typedef enum {
    HSWITCH_enuSwitchDebounce_OFF,
    HSWITCH_enuSwitchDebounce_ON
}HSWITCH_enuSwitchDebounce_t;

void HSWITCH_vInit(void);
HSWITCH_enuErrorStatus_t HSWITCH_enuGetSwitchState(u8 Copy_u8SwitchName, u8 *Add_u8State);

#endif // SWITCH_H