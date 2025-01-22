#include "HSEVEN_SEG.h"
#include "HSEVEN_SEG_cfg.h"
#include "MPORT.h"
#include "MDIO.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

HSEVEN_SEG_enuSevenSegNums_t HSEVEN_SEG_enuSevenSegNums[10] = {
    HSEVEN_SEG_NUM_0,
    HSEVEN_SEG_NUM_1,
    HSEVEN_SEG_NUM_2,
    HSEVEN_SEG_NUM_3,
    HSEVEN_SEG_NUM_4,
    HSEVEN_SEG_NUM_5,
    HSEVEN_SEG_NUM_6,
    HSEVEN_SEG_NUM_7,
    HSEVEN_SEG_NUM_8,
    HSEVEN_SEG_NUM_9};

extern HSEVEN_SEG_strSevenSegCfg_t HSEVEN_SEG_strSevenSegCfg[HSEVEN_SEG_NUM_OF_SEVEN_SEG];

void HSEVENSEG_vInit(void)
{
    u8 Loc_currentPortPin = 0;
    for (u8 iteratorSevenSeg = 0; iteratorSevenSeg < HSEVEN_SEG_NUM_OF_SEVEN_SEG; iteratorSevenSeg++)
    {
        for (u8 iteratorPins = 0; iteratorPins < HSEVEN_SEG_NUM_OF_SEVEN_SEG_PINS; iteratorPins++)
        {
            Loc_currentPortPin = HSEVEN_SEG_strSevenSegCfg[iteratorSevenSeg].HSEVEN_SEG_strSevenSegPins.HSEVEN_SEG_PINS[iteratorPins];
            MPORT_enuSetPinDirection(Loc_currentPortPin, MPORT_PIN_DIRECTION_OUTPUT);
        }
    }
}

void HSEVENSEG_vSetValue(u8 Copy_enuSevenSegNum, u8 Copy_u8Value)
{
    u8 Loc_currentPortPin = 0;
    u8 Loc_currentPortNum = 0;
    u8 Loc_currentPinNum = 0;
    u8 Loc_currentSevenSegConnection = 0;
    u8 Loc_segPattern = 0;
    if (Copy_enuSevenSegNum >= HSEVEN_SEG_NUM_OF_SEVEN_SEG || Copy_u8Value > HSEVEN_SEG_MAX_NUM_TO_DISPLAY)
    {
        return;
    }
    else
    {
        Loc_currentSevenSegConnection = HSEVEN_SEG_strSevenSegCfg[Copy_enuSevenSegNum].HSEVEN_SEG_enuSevenSegConnection;
        Loc_segPattern = HSEVEN_SEG_enuSevenSegNums[Copy_u8Value];
        for (u8 iteratorSevenSegPin = 0; iteratorSevenSegPin < HSEVEN_SEG_NUM_OF_SEVEN_SEG_PINS; iteratorSevenSegPin++)
        {

            Loc_currentPortPin = HSEVEN_SEG_strSevenSegCfg[Copy_enuSevenSegNum].HSEVEN_SEG_strSevenSegPins.HSEVEN_SEG_PINS[iteratorSevenSegPin];
            Loc_currentPortNum = GET_HIGH_NIB(Loc_currentPortPin);
            Loc_currentPinNum = GET_LOW_NIB(Loc_currentPortPin);
            u8 Loc_pinState = (Loc_segPattern & (1 << iteratorSevenSegPin)) ? MDIO_enuPIN_HIGH : MDIO_enuPIN_LOW;
            if (Loc_currentSevenSegConnection == HSEVEN_SEG_enuCommon_Anode)
            {
                Loc_pinState = (Loc_pinState == MDIO_enuPIN_HIGH) ? MDIO_enuPIN_LOW : MDIO_enuPIN_HIGH;
            }
            MDIO_enuSetPinValue(Loc_currentPortNum, Loc_currentPinNum, Loc_pinState);
        }
    }
}

HSEVENSEG_enuErrorStatus_t HSEVENSEG_enuSetMultiDigitValue(u16 Copy_u16Value)
{
    u8 Loc_currentDigit = 0;
    u8 Loc_numDigits = 0;
    u16 Loc_tempValue = Copy_u16Value;
    HSEVENSEG_enuErrorStatus_t Ret_enuErrorStatus = HSEVEN_SEG_enuError_NOK;

    // Calculate the number of digits in the given number
    do
    {
        Loc_numDigits++;
        Loc_tempValue /= 10;
    } while (Loc_tempValue != 0);

    // Check if the number of digits exceeds the available seven-segment displays
    if (Loc_numDigits > HSEVEN_SEG_NUM_OF_SEVEN_SEG)
    {
        return HSEVEN_SEG_enuError_INVALID_NUM_OF_SEVEN_SEG;
    }
    else
    {
        Ret_enuErrorStatus = HSEVEN_SEG_enuError_OK;

        // Loop through all the displays
        for (u8 Loc_iteratorSevenSeg = 0; Loc_iteratorSevenSeg < HSEVEN_SEG_NUM_OF_SEVEN_SEG; Loc_iteratorSevenSeg++)
        {
            if (Loc_iteratorSevenSeg < Loc_numDigits)
            {
                // Extract the least significant digit
                Loc_currentDigit = Copy_u16Value % 10;

                // Set the value on the corresponding seven-segment display
                HSEVENSEG_vSetValue((Loc_numDigits-Loc_iteratorSevenSeg-1), Loc_currentDigit);

                // Remove the processed digit
                Copy_u16Value /= 10;
            }
            else
            {
                // Clear remaining displays
                HSEVENSEG_vSetValue(Loc_iteratorSevenSeg, 0);
            }
        }
    }

    return Ret_enuErrorStatus;
}
