#ifndef SWITCH_CFG_H
#define SWITCH_CFG_H

#include "STD_TYPES.h"
#include "HSWITCH.h"

#define HSWITCH_NUM_OF_SWITCHS 3

#define HSWITCH_SWITCH_START 0
#define HSWITCH_SWITCH_STOP 1
#define HSWITCH_SWITCH_ALERT 2

typedef struct {
    u8 HSWITCH_u8SwitchPort;
    u8 HSWITCH_u8SwitchPin;
    HSWITCH_enuSwitchConnection_t HSWITCH_enuSwitchConnection;
    HSWITCH_enuSwitchDebounce_t HSWITCH_enuSwitchDebounce;
}HSWITCH_strSwitchCfg_t;

#endif // SWITCH_CFG_H