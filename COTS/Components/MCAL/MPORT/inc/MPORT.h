#ifndef MPORT_H
#define MPORT_H

#include "STD_TYPES.h"

#define MPORT_PIN_DIRECTION_INPUT 0
#define MPORT_PIN_DIRECTION_OUTPUT 1

typedef enum {
  MPORT_enuPORTA,
  MPORT_enuPORTB,
  MPORT_enuPORTC,
  MPORT_enuPORTD
}MPORT_enuPortNum_t;

typedef enum {
  MPORT_enuPIN0,
  MPORT_enuPIN1,
  MPORT_enuPIN2,
  MPORT_enuPIN3,
  MPORT_enuPIN4,
  MPORT_enuPIN5,
  MPORT_enuPIN6,
  MPORT_enuPIN7
}MPORT_enuPinNum_t;

typedef enum {
  MPORT_enuPIN_INTERNAL_PULL_UP,
  MPORT_enuPIN_INTERNAL_PULL_DOWN
}MPORT_enuPinMode_t;

typedef enum {
  MPORT_enuError_OK,
  MPORT_enuError_NOK,
  MPORT_enuError_INVALID_PIN_CFG,
  MPORT_enuError_INVALID_PIN_NUM,
  MPORT_enuError_INVALID_PORT_NUM
}MPORT_enuErrorStatus_t;

void MPORT_vInit(void);
MPORT_enuErrorStatus_t MPORT_enuSetPinDirection(u8 Copy_enuPinNum, u8 Copy_enuPinDirection);
MPORT_enuErrorStatus_t MPORT_enuSetPinMode(u8 Copy_enuPinNum, MPORT_enuPinMode_t Copy_enuPinMode);

#endif // MPORT_H