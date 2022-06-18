#ifndef __STM32F4xx_HAL_H
#define __STM32F4xx_HAL_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal_conf.h"

typedef enum
{
  HAL_TICK_FREQ_10HZ = 100U,
  HAL_TICK_FREQ_100HZ = 10U,
  HAL_TICK_FREQ_1KHZ = 1U,
  HAL_TICK_FREQ_DEFAULT = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;

#define __HAL_SYSCFG_REMAPMEMORY_FLASH() (SYSCFG->MEMRMP &= ~(SYSCFG_MEMRMP_MEM_MODE))

HAL_StatusTypeDef HAL_InitTick (uint32_t TickPriority);
void HAL_IncTick(void);

#ifdef __cplusplus
}
#endif

#endif
