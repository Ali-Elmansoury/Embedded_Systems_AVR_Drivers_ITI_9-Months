#define F_CPU 8000000UL
#include "HLCD.h"
#include "HLCD_cfg.h"
#include "HKEYPAD.h"
#include "HKEYPAD_cfg.h"
#include <util/delay.h>

int main(void)
{
    // Initialize keypad and LCD
    HKEYPAD_enuInit();
    HLCD_vInit();
    u8 key = 20; // Variable to store the detected key
    u8 currentXpos = 0;
    u8 currentYpos = 0;
    HLCD_enuWriteString(HLCD_LCD1, "LCD_KPD_Task");

    while (1)
    {
        HKEYPAD_enuGetPressedKey(HKEYPAD_1, &key);
        if (key == 0)
        {
            HLCD_enuWriteCommand(HLCD_LCD1, HLCD_CMD_CLEAR_DISPLAY);
            _delay_ms(500);
            key = 20;
        }
        else if (key == 1) // Move down (increase row)
        {
            currentXpos++;
            if (currentXpos >= HLCD_MAX_X_INDEX) // Ensure we don't exceed the last row
            {
                currentXpos = HLCD_MAX_X_INDEX - 1; // Wrap around or stay at the last row
            }
            HLCD_enuGotoXY(HLCD_LCD1, currentXpos, currentYpos);
            key = 20;
        }
        else if (key == 2) // Move up (decrease row)
        {
            currentXpos--;
            if (currentXpos < 0) // Ensure we don't go below the first row
            {
                currentXpos = 0; // Stay at the first row
            }
            HLCD_enuGotoXY(HLCD_LCD1, currentXpos, currentYpos);
            key = 20;
        }
        else if (key == 3) // Move right (increase column)
        {
            currentYpos++;
            if (currentYpos >= HLCD_MAX_Y_INDEX) // Ensure we don't exceed the last column
            {
                currentYpos = HLCD_MAX_Y_INDEX - 1; // Wrap around or stay at the last column
            }
            HLCD_enuGotoXY(HLCD_LCD1, currentXpos, currentYpos);
            key = 20;
        }
        else if (key == 4) // Move left (decrease column)
        {
            currentYpos--;
            if (currentYpos < 0) // Ensure we don't go below the first column
            {
                currentYpos = 0; // Stay at the first column
            }
            HLCD_enuGotoXY(HLCD_LCD1, currentXpos, currentYpos);
            key = 20;
        }
        else if (key == 5) // Write predefined string
        {
            HLCD_enuWriteString(HLCD_LCD1, "Ali Elmansoury, ES Intake 45");
            key = 20;
        }
    }

    return 0;
}