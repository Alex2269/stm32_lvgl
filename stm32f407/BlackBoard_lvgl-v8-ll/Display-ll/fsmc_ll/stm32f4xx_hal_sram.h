#ifndef __STM32F4xx_HAL_SRAM_H
#define __STM32F4xx_HAL_SRAM_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_ll_fsmc.h"

typedef enum
{
  HAL_SRAM_STATE_RESET = 0x00U,
  HAL_SRAM_STATE_READY = 0x01U,
  HAL_SRAM_STATE_BUSY = 0x02U,
  HAL_SRAM_STATE_ERROR = 0x03U,
  HAL_SRAM_STATE_PROTECTED = 0x04U
} HAL_SRAM_StateTypeDef;

typedef struct
{
  FMC_NORSRAM_TypeDef *Instance;
  FMC_NORSRAM_EXTENDED_TypeDef *Extended;
  FMC_NORSRAM_InitTypeDef Init;
  HAL_LockTypeDef Lock;
  volatile HAL_SRAM_StateTypeDef State;
  DMA_HandleTypeDef *hdma;
} SRAM_HandleTypeDef;

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_SRAM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
