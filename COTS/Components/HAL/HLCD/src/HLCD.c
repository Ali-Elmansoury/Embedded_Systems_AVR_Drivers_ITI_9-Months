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

void HLCD_vInit(void)
{
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
            // Step 1: Send 0x3 three times with delays to wake up the LCD
            HLCD_enuWriteCommand(lcdIterator, 0x03); // Send 0x30 (only upper nibble is used)
            _delay_ms(5);                            // Wait for 4.1ms

            HLCD_enuWriteCommand(lcdIterator, 0x03); // Send 0x30 again
            _delay_us(150);                          // Wait for 100us

            HLCD_enuWriteCommand(lcdIterator, 0x03); // Send 0x30 again
            _delay_us(150);                          // Wait for 100us

            // Step 2: Set 4-bit mode by sending 0x2
            HLCD_enuWriteCommand(lcdIterator, 0x02); // Send 0x20 (only upper nibble is used)
            _delay_us(150);                          // Wait for 100us
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
}

HLCD_enuErrorStatus_t HLCD_enuWriteData(u8 Copy_u8LCDNum, u8 Copy_u8Data)
{
    HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_enuErrorStatus_OK;
    if (Copy_u8LCDNum > HLCD_NUM_OF_LCDs)
    {
        Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_LCD_NUM;
    }
    else
    {
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

            for (u8 i = 0; i < HLCD_NUM_OF_DATA_BITS / 2; i++)
            {
                u8 Loc_bitState = (dataHighNib & (1 << i)) ? MDIO_enuPIN_HIGH : MDIO_enuPIN_LOW;
                MDIO_enuSetPinValue(GET_HIGH_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[i + 4]), GET_LOW_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[i + 4]), Loc_bitState);
            }
            enablePulse(Copy_u8LCDNum);

            for (u8 j = 0; j < HLCD_NUM_OF_DATA_BITS / 2; j++)
            {
                u8 Loc_bitState = (dataLowNib & (1 << j)) ? MDIO_enuPIN_HIGH : MDIO_enuPIN_LOW;
                MDIO_enuSetPinValue(GET_HIGH_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[j + 4]), GET_LOW_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[j + 4]), Loc_bitState);
            }
            enablePulse(Copy_u8LCDNum);
        }
    }
    return Loc_enuErrorStatus;
}

HLCD_enuErrorStatus_t HLCD_enuWriteCommand(u8 Copy_u8LCDNum, u8 Copy_u8Command)
{
    HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_enuErrorStatus_OK;
    if (Copy_u8LCDNum > HLCD_NUM_OF_LCDs)
    {
        Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_LCD_NUM;
    }
    else
    {
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

            for (u8 i = 0; i < HLCD_NUM_OF_DATA_BITS / 2; i++)
            {
                u8 Loc_bitState = (cmdHighNib & (1 << i)) ? MDIO_enuPIN_HIGH : MDIO_enuPIN_LOW;
                MDIO_enuSetPinValue(GET_HIGH_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[i + 4]), GET_LOW_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[i + 4]), Loc_bitState);
            }
            enablePulse(Copy_u8LCDNum);

            for (u8 j = 0; j < HLCD_NUM_OF_DATA_BITS / 2; j++)
            {
                u8 Loc_bitState = (cmdLowNib & (1 << j)) ? MDIO_enuPIN_HIGH : MDIO_enuPIN_LOW;
                MDIO_enuSetPinValue(GET_HIGH_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[j + 4]), GET_LOW_NIB(HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strLCDPins.HLCD_arrDataPins[j + 4]), Loc_bitState);
            }
            enablePulse(Copy_u8LCDNum);
        }
    }
    return Loc_enuErrorStatus;
}

HLCD_enuErrorStatus_t HLCD_enuGotoXY(u8 Copy_u8LCDNum, u8 Copy_u8X, u8 Copy_u8Y)
{
    HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_enuErrorStatus_OK;
    u8 Loc_u8Location = 0;
    if (Copy_u8LCDNum > HLCD_NUM_OF_LCDs)
    {
        Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_LCD_NUM;
    }
    else if (Copy_u8Y > HLCD_MAX_Y_INDEX)
    {
        Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_Y;
    }
    else
    {
        if (HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strFunctionSet.HLCD_enuDisplayLineNumber == HLCD_enuOneDisplayLine)
        {
            if (Copy_u8X > 1)
            {
                Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_X_ONE_LINE_CONFIG;
            }
            else
            {
                Loc_u8Location = Copy_u8Y;
            }
        }
        else
        {
            if (Copy_u8X == 0)
            {
                Loc_u8Location = Copy_u8Y;
            }
            else if (Copy_u8X == 1)
            {
                Loc_u8Location = 0x40 + Copy_u8Y;
            }
            else
            {
                Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_X;
            }
        }
    }
    HLCD_enuWriteCommand(Copy_u8LCDNum, (HLCD_DDRAM_ADDRESS_MASK | Loc_u8Location));
    return Loc_enuErrorStatus;
}

static HLCD_enuErrorStatus_t HLCD_enuGotoCGRAM(u8 Copy_u8LCDNum, u8 Copy_u8BlockNumber)
{
    HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_enuErrorStatus_OK;
    if (Copy_u8LCDNum > HLCD_NUM_OF_LCDs)
    {
        Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_LCD_NUM;
    }
    else if (Copy_u8BlockNumber > HLCD_MAX_BLOCK_NUMBER)
    {
        Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_BLOCK_NUM;
    }
    else
    {
        u8 Loc_address = ((HLCD_CGRAM_ADDRESS_MASK)*Copy_u8BlockNumber);

        // Send the CGRAM address command
        Loc_enuErrorStatus = HLCD_enuWriteCommand(Copy_u8LCDNum, (HLCD_CGRAM_ADDRESS_MASK | Loc_address));
    }
    return Loc_enuErrorStatus;
}

static HLCD_enuErrorStatus_t HLCD_enuStoreSpecialChar(u8 Copy_u8LCDNum, u8 *Addr_pattern, u8 Copy_u8BlockNumber)
{
    HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_enuErrorStatus_OK;
    if (Copy_u8LCDNum > HLCD_NUM_OF_LCDs)
    {
        Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_LCD_NUM;
    }
    else if (Copy_u8BlockNumber > HLCD_MAX_BLOCK_NUMBER)
    {
        Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_BLOCK_NUM;
    }
    else
    {
        HLCD_enuGotoCGRAM(Copy_u8LCDNum, Copy_u8BlockNumber);
        for (u8 i = 0; i < HLCD_MAX_BLOCK_NUMBER; i++)
        {
            HLCD_enuWriteData(Copy_u8LCDNum, Addr_pattern[i]);
        }
    }
    return Loc_enuErrorStatus;
}

HLCD_enuErrorStatus_t HLCD_enuWriteSpecialChar(u8 Copy_u8LCDNum, u8 *Addr_pattern, u8 Copy_u8BlockNumber, u8 Copy_u8X, u8 Copy_u8Y)
{
    HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_enuErrorStatus_OK;
    if (Copy_u8LCDNum > HLCD_NUM_OF_LCDs)
    {
        Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_LCD_NUM;
    }
    else if (Copy_u8BlockNumber > HLCD_MAX_BLOCK_NUMBER)
    {
        Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_BLOCK_NUM;
    }
    else
    {
        // Store the custom character in CGRAM
        Loc_enuErrorStatus = HLCD_enuStoreSpecialChar(Copy_u8LCDNum, Addr_pattern, Copy_u8BlockNumber);
        HLCD_enuGotoXY(Copy_u8LCDNum, Copy_u8X, Copy_u8Y);
        // Write the custom character to the current DDRAM position
        Loc_enuErrorStatus = HLCD_enuWriteData(Copy_u8LCDNum, Copy_u8BlockNumber);
    }
    return Loc_enuErrorStatus;
}

static u16 stringLen(const char data[])
{
    unsigned long count = 0;
    while (*data != '\0')
    {
        data++;
        count++;
    }
    return count;
}

HLCD_enuErrorStatus_t HLCD_enuWriteString(u8 Copy_u8LCDNum, const char *Addr_str)
{
    HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_enuErrorStatus_OK;

    // Get the number of lines configured for the LCD
    u8 Loc_numLines = HLCD_strLCDCfg[Copy_u8LCDNum].HLCD_strFunctionSet.HLCD_enuDisplayLineNumber == HLCD_enuTwoDisplayLines ? 2 : 1;

    // Calculate the maximum allowed characters based on the number of lines
    u8 Loc_maxChars = Loc_numLines == 1 ? HLCD_MAX_Y_INDEX : HLCD_MAX_LCD_INDEX;

    // Calculate the string length
    u16 Loc_strLength = stringLen(Addr_str);

    if (Copy_u8LCDNum > HLCD_NUM_OF_LCDs)
    {
        Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_LCD_NUM;
    }

    // Check if the string exceeds the maximum allowed length
    else if (Loc_strLength > Loc_maxChars)
    {
        Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_STRING_LEN; // Error: String too long
    }
    else
    {
        // Write the string character by character
        for (u16 i = 0; i < Loc_strLength; i++)
        {
            // Check if we need to move to the second line (for 2-line displays)
            if (Loc_numLines == 2 && i == HLCD_MAX_Y_INDEX)
            {
                // Move cursor to the second line
                Loc_enuErrorStatus = HLCD_enuGotoXY(Copy_u8LCDNum, 1, 0); // X=1, Y=0
            }

            // Write the current character to the LCD
            Loc_enuErrorStatus = HLCD_enuWriteData(Copy_u8LCDNum, Addr_str[i]);
        }
    }
    return Loc_enuErrorStatus;
}

HLCD_enuErrorStatus_t HLCD_enuWriteNumber(u8 Copy_u8LCDNum, u64 Copy_u64Number)
{
    HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_enuErrorStatus_OK;
    if (Copy_u8LCDNum > HLCD_NUM_OF_LCDs)
    {
        Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_LCD_NUM;
    }
    else
    {
        if (Copy_u64Number == 0)
        {
            Loc_enuErrorStatus = HLCD_enuWriteData(Copy_u8LCDNum, '0'); // Handle zero case
            return Loc_enuErrorStatus; // Return immediately after writing zero
        }

        char buffer[21]; // Maximum digits for u64 + null terminator: 20 digits + 1
        u8 index = 0;

        // Extract digits and store them in reverse order
        while (Copy_u64Number > 0)
        {
            buffer[index++] = (Copy_u64Number % 10) + '0'; // Convert digit to ASCII
            Copy_u64Number /= 10;                          // Remove the last digit
        }

        // Write characters to the LCD in the correct order
        for (u8 i = index - 1; i >= 0; i--)
        {
            if (i > HLCD_MAX_Y_INDEX)
            {
                Loc_enuErrorStatus = HLCD_enuErrorStatus_INVALID_Y;
                break; // Stop writing if invalid Y index is encountered
            }
            else
            {
                Loc_enuErrorStatus = HLCD_enuWriteData(Copy_u8LCDNum, buffer[i]);
                if (Loc_enuErrorStatus != HLCD_enuErrorStatus_OK)
                {
                    break; // Stop writing if an error occurs
                }
            }
        }
    }
    return Loc_enuErrorStatus;
}