//
// Created by ali on 12/17/24.
//

#include <stddef.h>
#include "MDIO.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "MDIO_cfg.h"

typedef struct
{
    u8 PIN;
    u8 DDR;
    u8 PORT;
} MDIO_strPortReg_t;

#define MDIO_PORT_REG_BASE_ADDRESS ((volatile MDIO_strPortReg_t *)0x39)

#define MDIO_GET_PORT_REG_ADDRESS(PORT_NUM) (MDIO_strPortReg_t *)(MDIO_PORT_REG_BASE_ADDRESS) - (PORT_NUM)

/*extern MDIO_strPinCfg_t MDIO_PinCfg[MDIO_NUM_OF_PORTS * MDIO_NUM_OF_PINS];

void MDIO_vInit(void)
{
    MDIO_enuPortNum_t Loc_enuCurrnetPortNum = MDIO_enuPORTA;
    MDIO_enuPinNum_t Loc_enuCurrentPinNum = MDIO_enuPIN0;
    for (u8 iterator = 0; iterator < MDIO_NUM_OF_PORTS * MDIO_NUM_OF_PINS; iterator++)
    {
        Loc_enuCurrnetPortNum = iterator / MDIO_NUM_OF_PINS;
        Loc_enuCurrentPinNum = iterator % MDIO_NUM_OF_PINS;
        MDIO_enuSetPinConfigration(Loc_enuCurrnetPortNum, Loc_enuCurrentPinNum, MDIO_PinCfg[iterator].cfg);
    }
    
}

MDIO_enuErrorStatus_t MDIO_enuSetPinConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinCfg_t Copy_enuConfigration)
{
    MDIO_strPortReg_t *Loc_strPortReg = MDIO_GET_PORT_REG_ADDRESS(Copy_enuPortNum);
    MDIO_enuErrorStatus_t Ret_enuErrorStatus = MDIO_enuError_NOK;
    if (Copy_enuPortNum > MDIO_enuPORTD)
    {
        Ret_enuErrorStatus = MDIO_enuError_INVALID_PORT_NUM;
    }
    else if (Copy_enuPinNum > MDIO_enuPIN7)
    {
        Ret_enuErrorStatus = MDIO_enuError_INVALID_PIN_NUM;
    }
    else
    {
        Ret_enuErrorStatus = MDIO_enuError_OK;
        if (Copy_enuConfigration == MDIO_enuPIN_INPUT)
        {
            CLEAR_BIT(Loc_strPortReg->DDR, Copy_enuPinNum);
            CLEAR_BIT(Loc_strPortReg->PORT, Copy_enuPinNum);
        }
        else if (Copy_enuConfigration == MDIO_enuPIN_OUTPUT)
        {
            SET_BIT(Loc_strPortReg->DDR, Copy_enuPinNum);
        }
        else if (Copy_enuConfigration == MDIO_enuPIN_INTERNAL_PULL_UP)
        {
            CLEAR_BIT(Loc_strPortReg->DDR, Copy_enuPinNum);
            SET_BIT(Loc_strPortReg->PORT, Copy_enuPinNum);
        }
        else
        {
            Ret_enuErrorStatus = MDIO_enuError_INVALID_PIN_CFG;
        }
    }
    return Ret_enuErrorStatus;
}

MDIO_enuErrorStatus_t MDIO_enuSetPortConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortCfg_t Copy_enuConfigration)
{
    MDIO_strPortReg_t *Loc_strPortReg = MDIO_GET_PORT_REG_ADDRESS(Copy_enuPortNum);
    MDIO_enuErrorStatus_t Ret_enuErrorStatus = MDIO_enuError_NOK;
    if (Copy_enuPortNum > MDIO_enuPORTD)
    {
        Ret_enuErrorStatus = MDIO_enuError_INVALID_PORT_NUM;
    }
    else
    {
        Ret_enuErrorStatus = MDIO_enuError_OK;
        if (Copy_enuConfigration == MDIO_enuPORT_INPUT)
        {
            Loc_strPortReg->DDR = 0x00;
            Loc_strPortReg->PORT = 0x00;
        }
        else if (Copy_enuConfigration == MDIO_enuPORT_OUTPUT)
        {
            Loc_strPortReg->DDR = 0xFF;
        }
        else if (Copy_enuConfigration == MDIO_enuPORT_INTERNAL_PULL_UP)
        {
            Loc_strPortReg->DDR = 0x00;
            Loc_strPortReg->PORT = 0xFF;
        }
        else
        {
            Ret_enuErrorStatus = MDIO_enuError_INVALID_PORT_CFG;
        }
    }
    return Ret_enuErrorStatus;
}*/

MDIO_enuErrorStatus_t MDIO_enuSetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinState_t Copy_enuState)
{
    MDIO_strPortReg_t *Loc_strPortReg = MDIO_GET_PORT_REG_ADDRESS(Copy_enuPortNum);
    MDIO_enuErrorStatus_t Ret_enuErrorStatus = MDIO_enuError_NOK;
    if (Copy_enuPortNum > MDIO_enuPORTD)
    {
        Ret_enuErrorStatus = MDIO_enuError_INVALID_PORT_NUM;
    }
    else if (Copy_enuPinNum > MDIO_enuPIN7)
    {
        Ret_enuErrorStatus = MDIO_enuError_INVALID_PIN_NUM;
    }
    else
    {
        Ret_enuErrorStatus = MDIO_enuError_OK;
        if (Copy_enuState == MDIO_enuPIN_LOW)
        {
            CLEAR_BIT(Loc_strPortReg->PORT, Copy_enuPinNum);
        }
        else if (Copy_enuState == MDIO_enuPIN_HIGH)
        {
            SET_BIT(Loc_strPortReg->PORT, Copy_enuPinNum);
        }
        else
        {
            Ret_enuErrorStatus = MDIO_enuError_INVALID_PIN_CFG;
        }
    }
    return Ret_enuErrorStatus;
}

MDIO_enuErrorStatus_t MDIO_enuSetPortValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortState_t Copy_enuPortState)
{
    MDIO_strPortReg_t *Loc_strPortReg = MDIO_GET_PORT_REG_ADDRESS(Copy_enuPortNum);
    MDIO_enuErrorStatus_t Ret_enuErrorStatus = MDIO_enuError_NOK;
    if (Copy_enuPortNum > MDIO_enuPORTD)
    {
        Ret_enuErrorStatus = MDIO_enuError_INVALID_PORT_NUM;
    }
    else
    {
        Ret_enuErrorStatus = MDIO_enuError_OK;
        if (Copy_enuPortState == MDIO_enuPORT_LOW)
        {
            Loc_strPortReg->PORT = 0x00;
        }
        else if (Copy_enuPortState == MDIO_enuPORT_HIGH)
        {
            Loc_strPortReg->PORT = 0xFF;
        }
        else
        {
            Ret_enuErrorStatus = MDIO_enuError_INVALID_PORT_CFG;
        }
    }
    return Ret_enuErrorStatus;
}

MDIO_enuErrorStatus_t MDIO_enuSetPortCustomValue(MDIO_enuPortNum_t Copy_enuPortNum, u8 Copy_u8PortValue)
{
    MDIO_strPortReg_t *Loc_strPortReg = MDIO_GET_PORT_REG_ADDRESS(Copy_enuPortNum);
    MDIO_enuErrorStatus_t Ret_enuErrorStatus = MDIO_enuError_NOK;
    if (Copy_enuPortNum > MDIO_enuPORTD)
    {
        Ret_enuErrorStatus = MDIO_enuError_INVALID_PORT_NUM;
    }
    else
    {
        Ret_enuErrorStatus = MDIO_enuError_OK;
        Loc_strPortReg->PORT = Copy_u8PortValue;
    }
    return Ret_enuErrorStatus;
}

MDIO_enuErrorStatus_t MDIO_enuGetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, u8 *Add_u8PinValue)
{
    MDIO_strPortReg_t *Loc_strPortReg = MDIO_GET_PORT_REG_ADDRESS(Copy_enuPortNum);
    MDIO_enuErrorStatus_t Ret_enuErrorStatus = MDIO_enuError_NOK;
    if (Copy_enuPortNum > MDIO_enuPORTD)
    {
        Ret_enuErrorStatus = MDIO_enuError_INVALID_PORT_NUM;
    }
    else if (Copy_enuPinNum > MDIO_enuPIN7)
    {
        Ret_enuErrorStatus = MDIO_enuError_INVALID_PIN_NUM;
    }
    else if (Add_u8PinValue == NULL)
    {
        Ret_enuErrorStatus = MDIO_enuError_NULL_POINTER;
    }
    else
    {
        Ret_enuErrorStatus = MDIO_enuError_OK;
        *Add_u8PinValue = GET_BIT(Loc_strPortReg->PIN, Copy_enuPinNum);
    }
    return Ret_enuErrorStatus;
}