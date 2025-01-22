#ifndef HSEVEN_SEG_H
#define HSEVEN_SEG_H

#include "STD_TYPES.h"

typedef enum {
  HSEVEN_SEG_enuError_OK,
  HSEVEN_SEG_enuError_NOK,
  HSEVEN_SEG_enuError_INVALID_NUM_OF_SEVEN_SEG,
  HSEVEN_SEG_enuError_INVALID_SEVEN_SEG_CONNECTION
}HSEVENSEG_enuErrorStatus_t;

typedef enum {
    HSEVEN_SEG_enuCommon_Cathode,
    HSEVEN_SEG_enuCommon_Anode
}HSEVEN_SEG_enuSevenSegConnection_t;

void HSEVENSEG_vInit(void);
void HSEVENSEG_vSetValue(u8 Copy_enuSevenSegNum , u8 Copy_u8Value);
HSEVENSEG_enuErrorStatus_t HSEVENSEG_enuSetMultiDigitValue(u16 Copy_u16Value);

#endif // HSEVEN_SEG_H