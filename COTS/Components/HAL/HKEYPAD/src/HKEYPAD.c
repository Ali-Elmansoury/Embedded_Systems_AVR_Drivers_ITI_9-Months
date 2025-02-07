#include "HKEYPAD.h"
#include "HKEYPAD_cfg.h"
#include "MDIO.h"
#include "MPORT.h"
#include "BIT_MATH.h"

extern HKEYPAD_strKeypadCfg_t HKEYPAD_strKeypadCfg[HKEYPAD_NUM_OF_KEYPADS];

extern char HKEYPAD_arrKeypad1_Mapping[4][4];

HKEYPAD_enuErrorStatus_t HKEYPAD_enuInit(void)
{
    HKEYPAD_enuErrorStatus_t Loc_enuErrorStatus = HKEYPAD_enuErrorStatus_OK;
    for (u8 keyPadItter = 0; keyPadItter < HKEYPAD_NUM_OF_KEYPADS; keyPadItter++)
    {
        if (HKEYPAD_strKeypadCfg[keyPadItter].HKEYPAD_numRows > HKEYPAD_MAX_NUM_OF_ROWS)
        {
            Loc_enuErrorStatus = HKEYPAD_enuErrorStatus_INVALID_ROWS_NO;
        }
        else if (HKEYPAD_strKeypadCfg[keyPadItter].HKEYPAD_numCols > HKEYPAD_MAX_NUM_OF_COLS)
        {
            Loc_enuErrorStatus = HKEYPAD_enuErrorStatus_INVALID_COLS_NO;
        }
        else
        {
            for (u8 row = 0; row < HKEYPAD_strKeypadCfg[keyPadItter].HKEYPAD_numRows; row++)
            {
                MPORT_enuSetPinDirection(HKEYPAD_strKeypadCfg[keyPadItter].HKEYPAD_strKeypadPins.HKEYPAD_rowPins[row], MPORT_PIN_DIRECTION_INPUT);
                MPORT_enuSetPinMode(HKEYPAD_strKeypadCfg[keyPadItter].HKEYPAD_strKeypadPins.HKEYPAD_rowPins[row], MPORT_enuPIN_INTERNAL_PULL_UP);
            }

            for (u8 col = 0; col < HKEYPAD_strKeypadCfg[keyPadItter].HKEYPAD_numCols; col++)
            {
                MPORT_enuSetPinDirection(HKEYPAD_strKeypadCfg[keyPadItter].HKEYPAD_strKeypadPins.HKEYPAD_colPins[col], MPORT_PIN_DIRECTION_OUTPUT);
                u8 Loc_colPortNum = GET_HIGH_NIB(HKEYPAD_strKeypadCfg[keyPadItter].HKEYPAD_strKeypadPins.HKEYPAD_colPins[col]);
                u8 Loc_colPinNum = GET_LOW_NIB(HKEYPAD_strKeypadCfg[keyPadItter].HKEYPAD_strKeypadPins.HKEYPAD_colPins[col]);
                MDIO_enuSetPinValue(Loc_colPortNum, Loc_colPinNum, MDIO_enuPIN_HIGH);
            }
        }
    }
    return Loc_enuErrorStatus;
}

HKEYPAD_enuErrorStatus_t HKEYPAD_enuGetPressedKey(u8 Copy_u8KeypadNum, u8 *Addr_u8Key)
{
    HKEYPAD_enuErrorStatus_t Loc_enuErrorStatus = HKEYPAD_enuErrorStatus_OK;
    u8 Loc_colPortNum = 0;
    u8 Loc_colPinNum = 0;
    u8 Loc_rowPortNum = 0;
    u8 Loc_rowPinNum = 0;
    u8 LocValue = 0;
    u8 flag = 0;
    if (HKEYPAD_strKeypadCfg[Copy_u8KeypadNum].HKEYPAD_numRows > HKEYPAD_MAX_NUM_OF_ROWS)
    {
        Loc_enuErrorStatus = HKEYPAD_enuErrorStatus_INVALID_ROWS_NO;
    }
    else if (HKEYPAD_strKeypadCfg[Copy_u8KeypadNum].HKEYPAD_numCols > HKEYPAD_MAX_NUM_OF_COLS)
    {
        Loc_enuErrorStatus = HKEYPAD_enuErrorStatus_INVALID_COLS_NO;
    }
    else if (Addr_u8Key == NULL)
    {
        Loc_enuErrorStatus = HKEYPAD_enuErrorStatus_NULL_POINTER;
    }
    else
    {
        for (u8 col = 0; col < HKEYPAD_strKeypadCfg[Copy_u8KeypadNum].HKEYPAD_numCols; col++)
        {
            Loc_colPortNum = GET_HIGH_NIB(HKEYPAD_strKeypadCfg[Copy_u8KeypadNum].HKEYPAD_strKeypadPins.HKEYPAD_colPins[col]);
            Loc_colPinNum = GET_LOW_NIB(HKEYPAD_strKeypadCfg[Copy_u8KeypadNum].HKEYPAD_strKeypadPins.HKEYPAD_colPins[col]);
            MDIO_enuSetPinValue(Loc_colPortNum, Loc_colPinNum, MDIO_enuPIN_LOW);
            for (u8 row = 0; row < HKEYPAD_strKeypadCfg[Copy_u8KeypadNum].HKEYPAD_numRows; row++)
            {
                Loc_rowPortNum = GET_HIGH_NIB(HKEYPAD_strKeypadCfg[Copy_u8KeypadNum].HKEYPAD_strKeypadPins.HKEYPAD_rowPins[row]);
                Loc_rowPinNum = GET_LOW_NIB(HKEYPAD_strKeypadCfg[Copy_u8KeypadNum].HKEYPAD_strKeypadPins.HKEYPAD_rowPins[row]);
                Loc_enuErrorStatus = MDIO_enuGetPinValue(Loc_rowPortNum, Loc_rowPinNum, &LocValue);
                if (LocValue == MDIO_enuPIN_LOW)
                {
                    *Addr_u8Key = HKEYPAD_arrKeypad1_Mapping[row][col];
                    while (LocValue == MDIO_enuPIN_LOW)
                    {
                        Loc_enuErrorStatus = MDIO_enuGetPinValue(Loc_rowPortNum, Loc_rowPinNum, &LocValue);
                    }
                    flag = 1;
                    break;
                }
            }
            MDIO_enuSetPinValue(Loc_colPortNum, Loc_colPinNum, MDIO_enuPIN_HIGH);
            if (flag == 1)
            {
                break;
            }
        }
    }
    return Loc_enuErrorStatus;
}