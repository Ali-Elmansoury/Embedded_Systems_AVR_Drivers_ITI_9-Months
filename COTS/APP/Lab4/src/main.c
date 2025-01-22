#define F_CPU 8000000UL
#include "MPORT.h"
#include "MDIO.h"
#include <util/delay.h>

MDIO_enuErrorStatus_t MDIO_enuGetButtonValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, u8* Add_u8PinValue) {
    MDIO_enuErrorStatus_t Ret_enuErrorStatus = MDIO_enuGetPinValue(Copy_enuPortNum, Copy_enuPinNum, Add_u8PinValue);
    if (Ret_enuErrorStatus == MDIO_enuError_NOK) {
        if (*Add_u8PinValue != MDIO_enuError_NULL_POINTER)
        {
            _delay_ms(20);
            Ret_enuErrorStatus = MDIO_enuGetPinValue(Copy_enuPortNum, Copy_enuPinNum, Add_u8PinValue);
        } else {
            Ret_enuErrorStatus = MDIO_enuError_NULL_POINTER;
        }
    }
    return Ret_enuErrorStatus;
}

void main (void)
{
    MPORT_vInit();
    u8 Button1Value = 0;
    u8 Button2Value = 0;
    u8 Button3Value = 0;
    while (1)
    {
        MDIO_enuGetButtonValue(MDIO_enuPORTA, MDIO_enuPIN0, &Button1Value);
        MDIO_enuGetButtonValue(MDIO_enuPORTA, MDIO_enuPIN1, &Button2Value);
        MDIO_enuGetButtonValue(MDIO_enuPORTA, MDIO_enuPIN2, &Button3Value);
        if (Button1Value == MDIO_enuPIN_LOW)
        {
            MDIO_enuSetPinValue(MDIO_enuPORTB, MDIO_enuPIN0, MDIO_enuPIN_HIGH);
        }
        else
        {
            MDIO_enuSetPinValue(MDIO_enuPORTB, MDIO_enuPIN0, MDIO_enuPIN_LOW);
        } 
        if (Button2Value == MDIO_enuPIN_LOW)
        {
            MDIO_enuSetPinValue(MDIO_enuPORTB, MDIO_enuPIN1, MDIO_enuPIN_HIGH);
        } 
        else
        {
            MDIO_enuSetPinValue(MDIO_enuPORTB, MDIO_enuPIN1, MDIO_enuPIN_LOW);
        }
        if (Button3Value == MDIO_enuPIN_LOW)
        {
            MDIO_enuSetPinValue(MDIO_enuPORTB, MDIO_enuPIN2, MDIO_enuPIN_HIGH);
        }
        else
        {
            MDIO_enuSetPinValue(MDIO_enuPORTB, MDIO_enuPIN2, MDIO_enuPIN_LOW);
        }
    }
}

/*Application: Controlling 3 LEDs with 3 Buttons

This application simulates a simple digital control system where three push-buttons are used to control the state of three LEDs independently. 
Each button corresponds to a specific LED, allowing users to turn the LED on or off by pressing the associated button.*/