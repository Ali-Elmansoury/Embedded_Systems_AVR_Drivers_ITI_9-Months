#include "MPORT.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "MPORT_cfg.h"

typedef struct
{
    u8 PIN;
    u8 DDR;
    u8 PORT;
} MPORT_strPortReg_t;

#define MPORT_PORT_REG_BASE_ADDRESS ((volatile MPORT_strPortReg_t *)0x39)

#define MPORT_GET_PORT_REG_ADDRESS(PORT_NUM) (MPORT_strPortReg_t *)(MPORT_PORT_REG_BASE_ADDRESS) - (PORT_NUM)

extern MPORT_strPinCfg_t MPORT_PinCfg[MPORT_NUM_OF_PORTS * MPORT_NUM_OF_PINS];

void MPORT_vInit(void)
{
    MPORT_enuPortNum_t Loc_enuCurrnetPortNum = MPORT_enuPORTA;
    MPORT_enuPinNum_t Loc_enuCurrentPinNum = MPORT_enuPIN0;
    for (u8 iterator = 0; iterator < MPORT_NUM_OF_PORTS * MPORT_NUM_OF_PINS; iterator++)
    {
        Loc_enuCurrnetPortNum = iterator / MPORT_NUM_OF_PINS;
        Loc_enuCurrentPinNum = iterator % MPORT_NUM_OF_PINS;
        if (MPORT_PinCfg[iterator].dir == MPORT_PIN_DIRECTION_INPUT)
        {
            MPORT_enuSetPinDirection(Loc_enuCurrnetPortNum * 0x10 + Loc_enuCurrentPinNum, MPORT_PIN_DIRECTION_INPUT);
            MPORT_enuSetPinMode(Loc_enuCurrnetPortNum * 0x10 + Loc_enuCurrentPinNum, MPORT_PinCfg[iterator].cfg);
        }
        else if (MPORT_PinCfg[iterator].dir == MPORT_PIN_DIRECTION_OUTPUT)
        {
            MPORT_enuSetPinDirection(Loc_enuCurrnetPortNum * 0x10 + Loc_enuCurrentPinNum, MPORT_PIN_DIRECTION_OUTPUT);
        }
        else
        {
            /* Do Nothing */
        }
    }
    
}

MPORT_enuErrorStatus_t MPORT_enuSetPinDirection(u8 Copy_enuPinNum, u8 Copy_enuPinDirection)
{
    MPORT_enuErrorStatus_t Ret_enuErrorStatus = MPORT_enuError_NOK;
    MPORT_enuPortNum_t Loc_enuPortNum = GET_HIGH_NIB(Copy_enuPinNum);
    MPORT_enuPinNum_t Loc_enuPinNum = GET_LOW_NIB(Copy_enuPinNum);
    if (Loc_enuPortNum > MPORT_enuPORTD)
    {
        Ret_enuErrorStatus = MPORT_enuError_INVALID_PORT_NUM;
    }
    else if (Loc_enuPinNum > MPORT_enuPIN7)
    {
        Ret_enuErrorStatus = MPORT_enuError_INVALID_PIN_NUM;
    }
    else
    {
        Ret_enuErrorStatus = MPORT_enuError_OK;
        MPORT_strPortReg_t *Loc_strPortReg = MPORT_GET_PORT_REG_ADDRESS(Loc_enuPortNum);
        if (Copy_enuPinDirection == MPORT_PIN_DIRECTION_INPUT)
        {
            CLEAR_BIT(Loc_strPortReg->DDR, Loc_enuPinNum);
        }
        else if (Copy_enuPinDirection == MPORT_PIN_DIRECTION_OUTPUT)
        {
            SET_BIT(Loc_strPortReg->DDR, Loc_enuPinNum);
        }
        else
        {
            Ret_enuErrorStatus = MPORT_enuError_INVALID_PIN_CFG;
        }
    }
    return Ret_enuErrorStatus;
}

MPORT_enuErrorStatus_t MPORT_enuSetPinMode(u8 Copy_enuPinNum, MPORT_enuPinMode_t Copy_enuPinMode)
{
    MPORT_enuErrorStatus_t Ret_enuErrorStatus = MPORT_enuError_OK;
    MPORT_enuPortNum_t Loc_enuPortNum = GET_HIGH_NIB(Copy_enuPinNum);
    MPORT_enuPinNum_t Loc_enuPinNum = GET_LOW_NIB(Copy_enuPinNum);
    if (Loc_enuPortNum > MPORT_enuPORTD)
    {
        Ret_enuErrorStatus = MPORT_enuError_INVALID_PORT_NUM;
    }
    else if (Loc_enuPinNum > MPORT_enuPIN7)
    {
        Ret_enuErrorStatus = MPORT_enuError_INVALID_PIN_NUM;
    }
    else
    {
        MPORT_strPortReg_t *Loc_strPortReg = MPORT_GET_PORT_REG_ADDRESS(Loc_enuPortNum);
        if (Copy_enuPinMode == MPORT_enuPIN_INTERNAL_PULL_UP)
        {
            SET_BIT(Loc_strPortReg->PORT, Loc_enuPinNum);
        }
        else if (Copy_enuPinMode == MPORT_enuPIN_INTERNAL_PULL_DOWN)
        {
            CLEAR_BIT(Loc_strPortReg->PORT, Loc_enuPinNum);
        }
        else
        {
            Ret_enuErrorStatus = MPORT_enuError_INVALID_PIN_CFG;
        }
    }
    return Ret_enuErrorStatus;
}