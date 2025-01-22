#include "HLED.h"
#include "HLED_cfg.h"
#include "MPORT.h"
#include "MDIO.h"
#include "STD_TYPES.h"

extern HLED_strLedCfg_t HLED_strLedCfg[HLED_NUM_OF_LEDS];

void HLED_vInit(void)
{
    u8 Loc_currentPortPin = 0;
    u8 Loc_currentPort = 0;
    u8 Loc_currentPin = 0;
    for (u8 iterator = 0; iterator < HLED_NUM_OF_LEDS; iterator++) 
    {
        Loc_currentPort = HLED_strLedCfg[iterator].HLED_u8LedPort; 
        Loc_currentPin = HLED_strLedCfg[iterator].HLED_u8LedPin;   
        Loc_currentPortPin = (Loc_currentPort << 4) | Loc_currentPin;
        MPORT_enuSetPinDirection(Loc_currentPortPin, MPORT_PIN_DIRECTION_OUTPUT);
    }
}

HLED_enuErrorStatus_t HLED_enuSetLedState(u8 Copy_u8LedName, u8 Copy_u8State)
{
    HLED_enuErrorStatus_t Ret_enuErrorStatus = HLED_enuError_NOK;
    u8 Loc_portNum = HLED_strLedCfg[Copy_u8LedName].HLED_u8LedPort;
    u8 Loc_pinNum = HLED_strLedCfg[Copy_u8LedName].HLED_u8LedPin;
    u8 Loc_ledConnection = HLED_strLedCfg[Copy_u8LedName].HLED_enuLedConnection;
    if (Copy_u8LedName > HLED_NUM_OF_LEDS)
    {
        Ret_enuErrorStatus = HLED_enuError_INVALID_NUM_OF_LEDS;
    }
    else if (Copy_u8State != HLED_enuLED_ON && Copy_u8State != HLED_enuLED_OFF)
    {
        Ret_enuErrorStatus = HLED_enuError_INVALID_LED_STATE;
    }
    else
    {
        Ret_enuErrorStatus = HLED_enuError_OK;
        if (Loc_ledConnection == HLED_enuLED_SOURCE && Copy_u8State == HLED_enuLED_ON)
        {
            Ret_enuErrorStatus = MDIO_enuSetPinValue(Loc_portNum, Loc_pinNum, MDIO_enuPIN_HIGH);
        }
        else if (Loc_ledConnection == HLED_enuLED_SOURCE && Copy_u8State == HLED_enuLED_OFF)
        {
            Ret_enuErrorStatus = MDIO_enuSetPinValue(Loc_portNum, Loc_pinNum, MDIO_enuPIN_LOW);
        }
        else if (Loc_ledConnection == HLED_enuLED_SINK && Copy_u8State == HLED_enuLED_ON)
        {
            Ret_enuErrorStatus = MDIO_enuSetPinValue(Loc_portNum, Loc_pinNum, MDIO_enuPIN_LOW);
        }
        else if (Loc_ledConnection == HLED_enuLED_SINK && Copy_u8State == HLED_enuLED_OFF)
        {
            Ret_enuErrorStatus = MDIO_enuSetPinValue(Loc_portNum, Loc_pinNum, MDIO_enuPIN_HIGH);
        }
        else
        {
            Ret_enuErrorStatus = HLED_enuError_INVALID_LED_CONNECTION;
        }
    }
    return Ret_enuErrorStatus;
}