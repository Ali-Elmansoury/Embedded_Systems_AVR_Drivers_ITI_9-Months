#include "HLCD.h"
#include "HLCD_cfg.h"

int main(void)
{

    const u8 CustomCharPattern[] = {
        0b00000, // Row 1
        0b01010, // Row 2
        0b11111, // Row 3
        0b01110, // Row 4
        0b00100, // Row 5
        0b00000, // Row 6
        0b00000, // Row 7
        0b00000  // Row 8
    };

    HLCD_vInit();
    HLCD_enuWriteString(HLCD_LCD1, "Hello, ITI Intake 45, I'm Ali");
    // HLCD_enuGotoXY(HLCD_LCD1, 1, 0);
    // HLCD_enuWriteData(HLCD_LCD2, 'A');
    // HLCD_enuGotoXY(HLCD_LCD2, 0, 15);
    // HLCD_enuWriteData(HLCD_LCD2, 'A');
    HLCD_enuWriteNumber(HLCD_LCD2, 201112001158);
    HLCD_enuWriteSpecialChar(HLCD_LCD2, CustomCharPattern, 0, 0, 13);
    return 0;
}