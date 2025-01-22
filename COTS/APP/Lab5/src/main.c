#include "HSWITCH.h"
#include "HSWITCH_cfg.h"
#include "HLED.h"
#include "HLED_cfg.h"

void main (void)
{
    HSWITCH_vInit();
    HLED_vInit();
    u8 Switch1Value = 0;
    u8 Switch2Value = 0;
    u8 Switch3Value = 0;
    while (1)
    {
        HSWITCH_enuGetSwitchState(HSWITCH_SWITCH_START, &Switch1Value);
        HSWITCH_enuGetSwitchState(HSWITCH_SWITCH_STOP, &Switch2Value);
        HSWITCH_enuGetSwitchState(HSWITCH_SWITCH_ALERT, &Switch3Value);
        if (Switch1Value == HSWITCH_enuSwitch_NOT_PRESSED)
        {
            HLED_enuSetLedState(HLED_LED_START, HLED_enuLED_ON);
        }
        else
        {
            HLED_enuSetLedState(HLED_LED_START, HLED_enuLED_OFF);
        } 
        if (Switch2Value == HSWITCH_enuSwitch_NOT_PRESSED)
        {
            HLED_enuSetLedState(HLED_LED_STOP, HLED_enuLED_ON);
        } 
        else
        {
            HLED_enuSetLedState(HLED_LED_STOP, HLED_enuLED_OFF);
        }
        if (Switch3Value == HSWITCH_enuSwitch_NOT_PRESSED)
        {
            HLED_enuSetLedState(HLED_LED_ALERT, HLED_enuLED_ON);
        }
        else
        {
            HLED_enuSetLedState(HLED_LED_ALERT, HLED_enuLED_OFF);
        }
    }
}