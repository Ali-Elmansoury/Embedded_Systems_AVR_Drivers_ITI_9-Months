#include "HLCD.h"
#include "HLCD_cfg.h"

int main(void)
{
    HLCD_enuInit();
    HLCD_enuWriteCommand(HLCD_LCD1, HLCD_CMD_CLEAR_DISPLAY); // Clear display
    HLCD_enuWriteCommand(HLCD_LCD1, HLCD_CMD_RETURN_HOME);   // Return home
    HLCD_enuWriteData(HLCD_LCD1, 'A');                       // Write 'A'
    return 0;
}