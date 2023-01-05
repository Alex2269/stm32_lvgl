#ifndef __STM32F4xx_HAL_DEF
#define __STM32F4xx_HAL_DEF

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx.h"

#include <stddef.h>

typedef enum
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

typedef enum
{
  HAL_UNLOCKED = 0x00U,
  HAL_LOCKED   = 0x01U
} HAL_LockTypeDef;

#define HAL_MAX_DELAY      0xFFFFFFFFU

#define __packed  __attribute__((packed))
#define __weak   __attribute__((weak))
#define __packed __attribute__((__packed__))
#define __ALIGN_END __attribute__ ((aligned (4)))
#define __RAM_FUNC __attribute__((section(".RamFunc")))
#define __NOINLINE __attribute__ ( (noinline) )

#ifdef __cplusplus
}
#endif

#endif /* ___STM32F4xx_HAL_DEF */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
