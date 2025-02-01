#define F_CPU 8000000UL
#include "HLCD.h"
#include "HLCD_cfg.h"
#include "MPORT.h"
#include "MDIO.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

extern HLCD_strLCDCfg_t HLCD_strLCDCfg[HLCD_NUM_OF_LCDs];

static void enablePulse(u8 Copy_u8LCDNum)
{
    u8 Loc_currentCtrlPortPin = HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_PIN_E;
    u8 Loc_currentCtrlPortNum = GET_HIGH_NIB(Loc_currentCtrlPortPin);
    u8 Loc_currentCtrlPinNum = GET_LOW_NIB(Loc_currentCtrlPortPin);

    /* Enable pulse */
    MDIO_enuSetPinValue(Loc_currentCtrlPortNum, Loc_currentCtrlPinNum, MDIO_enuPIN_HIGH);
    _delay_us(1);
    MDIO_enuSetPinValue(Loc_currentCtrlPortNum, Loc_currentCtrlPinNum, MDIO_enuPIN_LOW);
    _delay_ms(2);
}

HLCD_enuErrorStatus_t HLCD_enuInit(void)
{
    HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_enuErrorStatus_OK;
    for (u8 lcdIterator = 0; lcdIterator < HLCD_NUM_OF_LCDs; lcdIterator++)
    {
        for (u8 dataIterator = 0; dataIterator < HLCD_NUM_OF_DATA_BITS; dataIterator++)
        {
            MPORT_enuSetPinDirection(HLCD_strLCDCfg[lcdIterator].HLCD_strLCDPins.HLCD_arrDataPins[dataIterator], MDIO_enuPIN_OUTPUT);
        }
        for (u8 ctrlIterator = 0; ctrlIterator < HLCD_NUM_OF_CTRL_BITS; ctrlIterator++)
        {
            MPORT_enuSetPinDirection(HLCD_strLCDCfg[lcdIterator].HLCD_strLCDPins.HLCD_arrControlPins[ctrlIterator], MDIO_enuPIN_OUTPUT);
        }

        // Wait for the LCD to power up
        _delay_ms(30);

        // Step 0: Special handling for 4-bit mode
        if (HLCD_strLCDCfg[lcdIterator].HLCD_strFunctionSet.HLCD_enuDataLengthControlBits == HLCD_enuDataLengthControlBits_4Bit)
        {
            // Send Function Set command in 8-bit mode to initialize 4-bit mode
            HLCD_enuWriteCommand(lcdIterator, 0x30); // 8-bit mode, 1-line, 5x7 font
            _delay_us(40);

            // Send Function Set command again to switch to 4-bit mode
            HLCD_enuWriteCommand(lcdIterator, 0x20); // 4-bit mode, 1-line, 5x7 font
            _delay_us(40);
        }

        // Step 1: Generate Function Set Command
        uint8_t functionSetCommand = HLCD_CMD_FUNCTION_SET_CMD_BASE;

        // Check Data Length (DL)
        if (HLCD_strLCDCfg[lcdIterator].HLCD_strFunctionSet.HLCD_enuDataLengthControlBits == HLCD_enuDataLengthControlBits_8Bit)
        {
            functionSetCommand |= HLCD_CMD_FUNCTION_SET_DATALENGTH_8BIT;
        }
        else
        {
            functionSetCommand |= HLCD_CMD_FUNCTION_SET_DATALENGTH_4BIT;
        }

        // Check Display Lines (N)
        if (HLCD_strLCDCfg[lcdIterator].HLCD_strFunctionSet.HLCD_enuDisplayLineNumber == HLCD_enuTwoDisplayLines)
        {
            functionSetCommand |= HLCD_CMD_FUNCTION_SET_DISPLAYLINE_2LINE;
        }
        else
        {
            functionSetCommand |= HLCD_CMD_FUNCTION_SET_DISPLAYLINE_1LINE;
        }

        // Check Character Font (F)
        if (HLCD_strLCDCfg[lcdIterator].HLCD_strFunctionSet.HLCD_enuCharacterFont == HLCD_enuCharacterFont_5x10)
        {
            functionSetCommand |= HLCD_CMD_FUNCTION_SET_CHARACTERFONT_5X10;
        }
        else
        {
            functionSetCommand |= HLCD_CMD_FUNCTION_SET_CHARACTERFONT_5X7;
        }

        // Send Function Set Command
        HLCD_enuWriteCommand(lcdIterator, functionSetCommand);
        _delay_us(40);

        // Step 2: Generate Display ON/OFF Command
        uint8_t displayOnOffCommand = HLCD_CMD_DISPLAY_ONOFF_CMD_BASE;

        // Check Display ON/OFF (D)
        if (HLCD_strLCDCfg[lcdIterator].HLCD_strFunctionSet.HLCD_enuDisplayOnOff == HLCD_enuDisplay_On)
        {
            displayOnOffCommand |= HLCD_CMD_DISPLAY_ON;
        }
        else
        {
            displayOnOffCommand |= HLCD_CMD_DISPLAY_OFF;
        }

        // Check Cursor ON/OFF (C)
        if (HLCD_strLCDCfg[lcdIterator].HLCD_strFunctionSet.HLCD_enuCursorOnOff == HLCD_enuCursor_On)
        {
            displayOnOffCommand |= HLCD_CMD_CURSOR_ON;
        }
        else
        {
            displayOnOffCommand |= HLCD_CMD_CURSOR_OFF;
        }

        // Check Cursor Blink ON/OFF (B)
        if (HLCD_strLCDCfg[lcdIterator].HLCD_strFunctionSet.HLCD_enuCursorBlinkOnOff == HLCD_enuCursorBlinkOn)
        {
            displayOnOffCommand |= HLCD_CMD_CURSOR_BLINK_ON;
        }
        else
        {
            displayOnOffCommand |= HLCD_CMD_CURSOR_BLINK_OFF;
        }

        // Send Display ON/OFF Command
        HLCD_enuWriteCommand(lcdIterator, displayOnOffCommand);
        _delay_us(40);

        // Step 3: Clear Display
        HLCD_enuWriteCommand(lcdIterator, HLCD_CMD_CLEAR_DISPLAY);
        _delay_ms(2);

        // Step 4: Generate Entry Mode Command
        uint8_t entryModeCommand = HLCD_CMD_ENTRY_MODE_CMD_BASE;

        // Check Cursor Direction (I/D)
        if (HLCD_strLCDCfg[lcdIterator].HLCD_strEntryMode.HLCD_enuCursorDirection == HLCD_enuCursorDirection_Increment)
        {
            entryModeCommand |= HLCD_CMD_ENTRY_MODE_INCREMENT;
        }
        else
        {
            entryModeCommand |= HLCD_CMD_ENTRY_MODE_DECREMENT;
        }

        // Check Display Shift (S)
        if (HLCD_strLCDCfg[lcdIterator].HLCD_strEntryMode.HLCD_enuDisplayShift == HLCD_enuDisplayShift_Shifts)
        {
            entryModeCommand |= HLCD_CMD_ENTRY_MODE_SHIFT;
        }
        else
        {
            entryModeCommand |= HLCD_CMD_ENTRY_MODE_NOSHIFT;
        }

        // Send Entry Mode Command
        HLCD_enuWriteCommand(lcdIterator, entryModeCommand);
        _delay_us(40);
    }
    return Loc_enuErrorStatus;
}

HLCD_enuErrorStatus_t HLCD_enuWriteData(u8 Copy_u8LCDNum, u8 Copy_u8Data)
{
    HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_enuErrorStatus_OK;
    MDIO_enuSetPinValue(GET_HIGH_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_PIN_RW), GET_LOW_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_PIN_RW), MDIO_enuPIN_LOW);
    MDIO_enuSetPinValue(GET_HIGH_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_PIN_RS), GET_LOW_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_PIN_RS), MDIO_enuPIN_HIGH);

    if (HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strFunctionSet.HLCD_enuDataLengthControlBits == HLCD_enuDataLengthControlBits_8Bit)
    {
        for (u8 i = 0; i < HLCD_NUM_OF_DATA_BITS; i++)
        {
            u8 Loc_bitState = (Copy_u8Data & (1 << i)) ? MDIO_enuPIN_HIGH : MDIO_enuPIN_LOW;
            MDIO_enuSetPinValue(GET_HIGH_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[i]), GET_LOW_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[i]), Loc_bitState);
        }
        enablePulse(Copy_u8LCDNum);
    }
    else
    {
        u8 dataHighNib = GET_HIGH_NIB(Copy_u8Data);
        u8 dataLowNib = GET_LOW_NIB(Copy_u8Data);

        for (u8 i = 0; i < HLCD_NUM_OF_DATA_BITS/2; i++)
        {
            u8 Loc_bitState = (dataHighNib & (1 << i)) ? MDIO_enuPIN_HIGH : MDIO_enuPIN_LOW;
            MDIO_enuSetPinValue(GET_HIGH_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[i+4]), GET_LOW_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[i+4]), Loc_bitState);
        }
        enablePulse(Copy_u8LCDNum);

        for (u8 j = 0; j < HLCD_NUM_OF_DATA_BITS/2; j++)
        {
            u8 Loc_bitState = (dataLowNib & (1 << j)) ? MDIO_enuPIN_HIGH : MDIO_enuPIN_LOW;
            MDIO_enuSetPinValue(GET_HIGH_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[j+4]), GET_LOW_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[j+4]), Loc_bitState);
        }
        enablePulse(Copy_u8LCDNum);
    }
    return Loc_enuErrorStatus;
}

HLCD_enuErrorStatus_t HLCD_enuWriteCommand(u8 Copy_u8LCDNum, u8 Copy_u8Command)
{
    HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_enuErrorStatus_OK;
    MDIO_enuSetPinValue(GET_HIGH_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_PIN_RW), GET_LOW_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_PIN_RW), MDIO_enuPIN_LOW);
    MDIO_enuSetPinValue(GET_HIGH_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_PIN_RS), GET_LOW_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_PIN_RS), MDIO_enuPIN_LOW);

    if (HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strFunctionSet.HLCD_enuDataLengthControlBits == HLCD_enuDataLengthControlBits_8Bit)
    {
        for (u8 i = 0; i < HLCD_NUM_OF_DATA_BITS; i++)
        {
            u8 Loc_bitState = (Copy_u8Command & (1 << i)) ? MDIO_enuPIN_HIGH : MDIO_enuPIN_LOW;
            MDIO_enuSetPinValue(GET_HIGH_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[i]), GET_LOW_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[i]), Loc_bitState);
        }
        enablePulse(Copy_u8LCDNum);
    }
    else
    {
        u8 cmdHighNib = GET_HIGH_NIB(Copy_u8Command);
        u8 cmdLowNib = GET_LOW_NIB(Copy_u8Command);

        for (u8 i = 0; i < HLCD_NUM_OF_DATA_BITS/2; i++)
        {
            u8 Loc_bitState = (cmdHighNib & (1 << i)) ? MDIO_enuPIN_HIGH : MDIO_enuPIN_LOW;
            MDIO_enuSetPinValue(GET_HIGH_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[i+4]), GET_LOW_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[i+4]), Loc_bitState);
        }
        enablePulse(Copy_u8LCDNum);

        for (u8 j = 0; j < HLCD_NUM_OF_DATA_BITS/2; j++)
        {
            u8 Loc_bitState = (cmdLowNib & (1 << j)) ? MDIO_enuPIN_HIGH : MDIO_enuPIN_LOW;
            MDIO_enuSetPinValue(GET_HIGH_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[j+4]), GET_LOW_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[j+4]), Loc_bitState);
        }
        enablePulse(Copy_u8LCDNum);
    }
    return Loc_enuErrorStatus;
}

HLCD_enuErrorStatus_t HLCD_enuGotoXY(u8 Copy_u8LCDNum, u8 Copy_u8X, u8 Copy_u8Y)
{
}

HLCD_enuErrorStatus_t HLCD_enuWriteSpecialChar(u8 Copy_u8LCDNum, u8 *Addr_pattern, u8 Copy_u8BlockNumber)
{
}

HLCD_enuErrorStatus_t HLCD_enuWriteString(u8 Copy_u8LCDNum, u16 *Addr_str)
{
}

HLCD_enuErrorStatus_t HLCD_enuWriteNumber(u8 Copy_u8LCDNum, u16 Copy_u16Number)
{
}

static HLCD_enuErrorStatus_t HLCD_enuGotoXY_DDRAM(u8 Copy_u8LCDNum, u8 Copy_u8X, u8 Copy_u8Y)
{
}

static HLCD_enuErrorStatus_t HLCD_enuGotoCGRAM(u8 Copy_u8LCDNum, u8 Copy_u8BlockNumber)
{
}

static HLCD_enuErrorStatus_t HLCD_enuStoreSpecialChar(u8 Copy_u8LCDNum, u8 *Addr_pattern, u8 Copy_u8BlockNumber)
{
}