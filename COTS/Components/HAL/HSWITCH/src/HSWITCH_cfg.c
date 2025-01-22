#include "HSWITCH_cfg.h"
#include "HSWITCH.h"
#include "MPORT.h"

HSWITCH_strSwitchCfg_t HSWITCH_strSwitchCfg[HSWITCH_NUM_OF_SWITCHS] = {
    [HSWITCH_SWITCH_START] = {
        .HSWITCH_u8SwitchPort = MPORT_enuPORTA,
        .HSWITCH_u8SwitchPin = MPORT_enuPIN0,
        .HSWITCH_enuSwitchConnection = HSWITCH_enuSwitch_INTERNAL_PULL_UP,
        .HSWITCH_enuSwitchDebounce = HSWITCH_enuSwitchDebounce_ON
    },
    [HSWITCH_SWITCH_STOP] = {
        .HSWITCH_u8SwitchPort = MPORT_enuPORTA,
        .HSWITCH_u8SwitchPin = MPORT_enuPIN1,
        .HSWITCH_enuSwitchConnection = HSWITCH_enuSwitch_INTERNAL_PULL_UP,
        .HSWITCH_enuSwitchDebounce = HSWITCH_enuSwitchDebounce_ON
    },
    [HSWITCH_SWITCH_ALERT] = {
        .HSWITCH_u8SwitchPort = MPORT_enuPORTA,
        .HSWITCH_u8SwitchPin = MPORT_enuPIN2,
        .HSWITCH_enuSwitchConnection = HSWITCH_enuSwitch_INTERNAL_PULL_UP,
        .HSWITCH_enuSwitchDebounce = HSWITCH_enuSwitchDebounce_ON
    }
};