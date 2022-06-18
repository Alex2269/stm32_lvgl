#include "stm32f4xx_hal.h"

volatile uint32_t uwTick;

uint32_t uwTickPrio = (1UL << __NVIC_PRIO_BITS);
HAL_TickFreqTypeDef uwTickFreq = HAL_TICK_FREQ_DEFAULT;

__weak void HAL_IncTick(void)
{
  uwTick += uwTickFreq;
}

__weak uint32_t HAL_GetTick(void)
{
  return uwTick;
}

uint32_t HAL_GetTickPrio(void)
{
  return uwTickPrio;
}

__weak HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  HAL_SYSTICK_Config(SystemCoreClock / (1000U / uwTickFreq));
  return HAL_OK;
}

