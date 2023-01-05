#ifndef __STM32F4xx_HAL_CONF_H
#define __STM32F4xx_HAL_CONF_H

#ifdef __cplusplus
extern "C"
{
  #endif

  #define NVIC_PRIORITYGROUP_4 0x00000003U

  #define HAL_MODULE_ENABLED
  #define HAL_SRAM_MODULE_ENABLED
  #define HAL_DMA_MODULE_ENABLED

  #define VDD_VALUE 3300U
  #define TICK_INT_PRIORITY 0U

  #ifdef HAL_DMA_MODULE_ENABLED
  #include "stm32f4xx_hal_dma.h"
  #endif

  #ifdef HAL_SRAM_MODULE_ENABLED
  #include "stm32f4xx_hal_sram.h"
  #endif

  #ifdef USE_FULL_ASSERT

  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
  void assert_failed(uint8_t* file, uint32_t line);
  #else
  #define assert_param(expr) ((void)0U)
  #endif

  #ifdef __cplusplus
}

#endif
#endif
