#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/iom32.h>
#include "MDIO.h"

MDIO_enuErrorStatus_t MDIO_enuGetButtonValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, u8* Add_u8PinValue) {
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

void main(void) {
    /*MDIO_enuSetPinConfigration(MDIO_enuPORTA, MDIO_enuPIN0, MDIO_enuPIN_INTERNAL_PULL_UP);
    MDIO_enuSetPinConfigration(MDIO_enuPORTA, MDIO_enuPIN1, MDIO_enuPIN_INTERNAL_PULL_UP);
    MDIO_enuSetPinConfigration(MDIO_enuPORTA, MDIO_enuPIN2, MDIO_enuPIN_INTERNAL_PULL_UP);

    MDIO_enuSetPinConfigration(MDIO_enuPORTB, MDIO_enuPIN0, MDIO_enuPIN_OUTPUT);
    MDIO_enuSetPinConfigration(MDIO_enuPORTB, MDIO_enuPIN1, MDIO_enuPIN_OUTPUT);
    MDIO_enuSetPinConfigration(MDIO_enuPORTB, MDIO_enuPIN2, MDIO_enuPIN_OUTPUT);

    u8 Button0Value;
    u8 Button1Value;
    u8 Button2Value;*/

    MDIO_enuSetPinConfigration(MDIO_enuPORTA, MDIO_enuPIN0, MDIO_enuPIN_INTERNAL_PULL_UP);
    MDIO_enuSetPortConfigration(MDIO_enuPORTB, MDIO_enuPORT_OUTPUT);
    u8* Button1Value = 0;
    u8 counter = 0;

    while (1)
    {
        
        /*MDIO_enuGetButtonValue(MDIO_enuPORTA, MDIO_enuPIN0, &Button0Value);
        MDIO_enuGetButtonValue(MDIO_enuPORTA, MDIO_enuPIN1, &Button1Value);
        MDIO_enuGetButtonValue(MDIO_enuPORTA, MDIO_enuPIN2, &Button2Value);

        if (Button0Value == MDIO_enuPIN_LOW)
        {
            MDIO_enuSetPinValue(MDIO_enuPORTB, MDIO_enuPIN0, MDIO_enuPIN_HIGH);
        } else {
            MDIO_enuSetPinValue(MDIO_enuPORTB, MDIO_enuPIN0, MDIO_enuPIN_LOW);
        }

        if (Button1Value == MDIO_enuPIN_LOW)
        {
            MDIO_enuSetPinValue(MDIO_enuPORTB, MDIO_enuPIN1, MDIO_enuPIN_HIGH);
        } else {
            MDIO_enuSetPinValue(MDIO_enuPORTB, MDIO_enuPIN1, MDIO_enuPIN_LOW);
        }

        if (Button2Value == MDIO_enuPIN_LOW)
        {
            MDIO_enuSetPinValue(MDIO_enuPORTB, MDIO_enuPIN2, MDIO_enuPIN_HIGH);
        } else {
            MDIO_enuSetPinValue(MDIO_enuPORTB, MDIO_enuPIN2, MDIO_enuPIN_LOW);
        }*/

        MDIO_enuGetPinValue(MDIO_enuPORTA, MDIO_enuPIN0, Button1Value);
        if (Button1Value == MDIO_enuPIN_LOW)
        {
            counter++;
            if (counter > 255)
            {
                counter = 0;
            }
        }
        MDIO_enuSetPortCustomValue(MDIO_enuPORTB, counter);
        _delay_ms(100); 
    }
    
}


/*Applications

1) LED Control System

Purpose: Create a system where multiple LEDs are controlled via push buttons.

Functionality: Use the APIs to configure multiple pins for buttons and LEDs. When a button is pressed, its corresponding LED turns on.

2)Binary Counter with LEDs using a switch to start 

Purpose: Implement a binary counter displayed using 8 LEDs After pressing the button to start this counter.

Functionality: Increment a binary counter value and display it on 8 LEDs connected to a single port.*/