#define F_CPU 8000000UL
#include "HSWITCH.h"
#include "HSWITCH_cfg.h"
#include "MPORT.h"
#include "MDIO.h"
#include "STD_TYPES.h"
#include <util/delay.h>

extern HSWITCH_strSwitchCfg_t HSWITCH_strSwitchCfg[HSWITCH_NUM_OF_SWITCHS];

void HSWITCH_vInit(void)
{
    u8 Loc_currentPortPin = 0;
    u8 Loc_currentPort = 0;
    u8 Loc_currentPin = 0;
    u8 Loc_switchConnection = 0;
    for (u8 iterator = 0; iterator < HSWITCH_NUM_OF_SWITCHS; iterator++) 
    {
        Loc_currentPort = HSWITCH_strSwitchCfg[iterator].HSWITCH_u8SwitchPort; 
        Loc_currentPin = HSWITCH_strSwitchCfg[iterator].HSWITCH_u8SwitchPin;   
        Loc_currentPortPin = (Loc_currentPort << 4) | Loc_currentPin;
        Loc_switchConnection = HSWITCH_strSwitchCfg[iterator].HSWITCH_enuSwitchConnection;
        MPORT_enuSetPinDirection(Loc_currentPortPin, MPORT_PIN_DIRECTION_INPUT);
        if (Loc_switchConnection == HSWITCH_enuSwitch_EXTERNAL_PULL_DOWN)
        {
            MPORT_enuSetPinMode(Loc_currentPortPin, MPORT_enuPIN_INTERNAL_PULL_DOWN);
        }
        else if (Loc_switchConnection == HSWITCH_enuSwitch_EXTERNAL_PULL_UP)
        {
            MPORT_enuSetPinMode(Loc_currentPortPin, MPORT_enuPIN_INTERNAL_PULL_DOWN);
        }
        else if (Loc_switchConnection == HSWITCH_enuSwitch_INTERNAL_PULL_UP)
        {
            MPORT_enuSetPinMode(Loc_currentPortPin, MPORT_enuPIN_INTERNAL_PULL_UP);
        }
        else
        {
            /* Do nothing */
        }
    }
}

MDIO_enuErrorStatus_t static MDIO_enuGetSwitchStateWithDebounce(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, u8* Add_u8PinValue) {
    MDIO_enuErrorStatus_t Ret_enuErrorStatus = MDIO_enuGetPinValue(Copy_enuPortNum, Copy_enuPinNum, Add_u8PinValue);
    if (Ret_enuErrorStatus == MDIO_enuError_NOK) {
        if (Add_u8PinValue != NULL)
        {
            _delay_ms(20);
            Ret_enuErrorStatus = MDIO_enuGetPinValue(Copy_enuPortNum, Copy_enuPinNum, Add_u8PinValue);
        } else {
            Ret_enuErrorStatus = MDIO_enuError_NULL_POINTER;
        }
    }
    return Ret_enuErrorStatus;
}

HSWITCH_enuErrorStatus_t HSWITCH_enuGetSwitchState(u8 Copy_u8SwitchName, u8 *Add_u8State)
{
    HSWITCH_enuErrorStatus_t Ret_enuErrorStatus = HSWITCH_enuError_NOK;
    u8 Loc_portNum = HSWITCH_strSwitchCfg[Copy_u8SwitchName].HSWITCH_u8SwitchPort;
    u8 Loc_pinNum = HSWITCH_strSwitchCfg[Copy_u8SwitchName].HSWITCH_u8SwitchPin;
    u8 Loc_switchDebounce = HSWITCH_strSwitchCfg[Copy_u8SwitchName].HSWITCH_enuSwitchDebounce;
    if (Copy_u8SwitchName > HSWITCH_NUM_OF_SWITCHS)
    {
        Ret_enuErrorStatus = HSWITCH_enuError_INVALID_NUM_OF_SWITCHS;
    }
    else if (Add_u8State == NULL)
    {
        Ret_enuErrorStatus = MDIO_enuError_NULL_POINTER;
    }
    else
    {
        Ret_enuErrorStatus = HSWITCH_enuError_OK;
        if (Loc_switchDebounce == HSWITCH_enuSwitchDebounce_ON)
        {
            Ret_enuErrorStatus = MDIO_enuGetSwitchStateWithDebounce(Loc_portNum, Loc_pinNum, Add_u8State);
        }
        else
        {
            Ret_enuErrorStatus = MDIO_enuGetPinValue(Loc_portNum, Loc_pinNum, Add_u8State);
        }
    }
    return Ret_enuErrorStatus;
}