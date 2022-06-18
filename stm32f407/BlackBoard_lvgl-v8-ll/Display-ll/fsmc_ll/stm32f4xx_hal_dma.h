#ifndef __STM32F4xx_HAL_DMA_H
#define __STM32F4xx_HAL_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal_def.h"

typedef struct
{
  uint32_t Channel;
  uint32_t Direction;
  uint32_t PeriphInc;
  uint32_t MemInc;
  uint32_t PeriphDataAlignment;
  uint32_t MemDataAlignment;
  uint32_t Mode;
  uint32_t Priority;
  uint32_t FIFOMode;
  uint32_t FIFOThreshold;
  uint32_t MemBurst;
  uint32_t PeriphBurst;
} DMA_InitTypeDef;

typedef enum
{
  HAL_DMA_STATE_RESET = 0x00U,
  HAL_DMA_STATE_READY = 0x01U,
  HAL_DMA_STATE_BUSY = 0x02U,
  HAL_DMA_STATE_TIMEOUT = 0x03U,
  HAL_DMA_STATE_ERROR = 0x04U,
  HAL_DMA_STATE_ABORT = 0x05U,
} HAL_DMA_StateTypeDef;

// typedef enum
// {
//   HAL_DMA_FULL_TRANSFER = 0x00U,
//   HAL_DMA_HALF_TRANSFER = 0x01U
// } HAL_DMA_LevelCompleteTypeDef;

// typedef enum
// {
//   HAL_DMA_XFER_CPLT_CB_ID = 0x00U,
//   HAL_DMA_XFER_HALFCPLT_CB_ID = 0x01U,
//   HAL_DMA_XFER_M1CPLT_CB_ID = 0x02U,
//   HAL_DMA_XFER_M1HALFCPLT_CB_ID = 0x03U,
//   HAL_DMA_XFER_ERROR_CB_ID = 0x04U,
//   HAL_DMA_XFER_ABORT_CB_ID = 0x05U,
//   HAL_DMA_XFER_ALL_CB_ID = 0x06U
// } HAL_DMA_CallbackIDTypeDef;

typedef struct __DMA_HandleTypeDef
{
  DMA_Stream_TypeDef *Instance;
  DMA_InitTypeDef Init;
  HAL_LockTypeDef Lock;
  volatile HAL_DMA_StateTypeDef State;
  void *Parent;
  void (* XferCpltCallback)( struct __DMA_HandleTypeDef * hdma);
  void (* XferHalfCpltCallback)( struct __DMA_HandleTypeDef * hdma);
  void (* XferM1CpltCallback)( struct __DMA_HandleTypeDef * hdma);
  void (* XferM1HalfCpltCallback)( struct __DMA_HandleTypeDef * hdma);
  void (* XferErrorCallback)( struct __DMA_HandleTypeDef * hdma);
  void (* XferAbortCallback)( struct __DMA_HandleTypeDef * hdma);
  volatile uint32_t ErrorCode;
  uint32_t StreamBaseAddress;
  uint32_t StreamIndex;
} DMA_HandleTypeDef;

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_DMA_H */

