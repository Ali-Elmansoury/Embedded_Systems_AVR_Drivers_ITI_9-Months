//
// Created by ali on 12/17/24.
//

#ifndef MDIO_H
#define MDIO_H

#include "STD_TYPES.h"

typedef enum {
  MDIO_enuPORTA,
  MDIO_enuPORTB,
  MDIO_enuPORTC,
  MDIO_enuPORTD
}MDIO_enuPortNum_t;

typedef enum {
  MDIO_enuPIN0,
  MDIO_enuPIN1,
  MDIO_enuPIN2,
  MDIO_enuPIN3,
  MDIO_enuPIN4,
  MDIO_enuPIN5,
  MDIO_enuPIN6,
  MDIO_enuPIN7
}MDIO_enuPinNum_t;

typedef enum {
  MDIO_enuPIN_INPUT,
  MDIO_enuPIN_OUTPUT,
  MDIO_enuPIN_INTERNAL_PULL_UP,
  MDIO_enuPIN_EXTERNAL_PULL_DOWN
}MDIO_enuPinCfg_t;

typedef enum {
  MDIO_enuPORT_INPUT = 0x00,
  MDIO_enuPORT_OUTPUT = 0xFF,
  MDIO_enuPORT_INTERNAL_PULL_UP,
  MDIO_enuPORT_EXTERNAL_PULL_DOWN
}MDIO_enuPortCfg_t;

typedef enum {
  MDIO_enuPIN_LOW,
  MDIO_enuPIN_HIGH
}MDIO_enuPinState_t;

typedef enum {
  MDIO_enuPORT_LOW,
  MDIO_enuPORT_HIGH
}MDIO_enuPortState_t;

typedef enum {
  MDIO_enuError_OK,
  MDIO_enuError_NOK,
  MDIO_enuError_INVALID_PIN_CFG,
  MDIO_enuError_INVALID_PORT_CFG,
  MDIO_enuError_INVALID_PIN_NUM,
  MDIO_enuError_INVALID_PORT_NUM,
  MDIO_enuError_NULL_POINTER,
  MDIO_enuError_DEBOUNCE_FAIL
}MDIO_enuErrorStatus_t;

/*void MDIO_vInit(void);
MDIO_enuErrorStatus_t MDIO_enuSetPinConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinCfg_t Copy_enuConfigration);
MDIO_enuErrorStatus_t MDIO_enuSetPortConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortCfg_t Copy_enuConfigration);*/
MDIO_enuErrorStatus_t MDIO_enuSetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinState_t Copy_enuState);
MDIO_enuErrorStatus_t MDIO_enuSetPortValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortState_t Copy_enuPortState);
MDIO_enuErrorStatus_t MDIO_enuSetPortCustomValue(MDIO_enuPortNum_t Copy_enuPortNum, u8 Copy_u8PortValue);
MDIO_enuErrorStatus_t MDIO_enuGetPinValue(MDIO_enuPortNum_t Copy_enuPortNum,MDIO_enuPinNum_t Copy_enuPinNum, u8* Add_u8PinValue);

#endif //MDIO_H
