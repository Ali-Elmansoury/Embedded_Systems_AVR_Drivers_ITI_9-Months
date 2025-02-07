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
    HLCD_enuWriteString(HLCD_LCD1, "Ali Elmansoury");
    u8 key = 20; // Variable to store the detected key

    while (1)
    {
        HKEYPAD_enuGetPressedKey(HKEYPAD_1, &key);
        if (key == 0)
        {
            HLCD_enuWriteCommand(HLCD_LCD1, HLCD_CMD_CLEAR_DISPLAY);
            HLCD_enuWriteString(HLCD_LCD1, "Hello, ES Inatke 45");
            key = 20;
        }
        else if (key != 20)
        {
            HLCD_enuWriteCommand(HLCD_LCD1, HLCD_CMD_CLEAR_DISPLAY);
            HLCD_enuWriteNumber(HLCD_LCD1, key);
            key = 20;
        }
    }

    // HLCD_enuWriteNumber(HLCD_LCD1, key);

    return 0;
}