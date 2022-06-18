#ifndef __FSMC_H
#define __FSMC_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

typedef struct
{
  FSMC_Bank1_TypeDef *Instance;
  FSMC_Bank1E_TypeDef *Extended;
  FSMC_NORSRAM_InitTypeDef Init;
  DMA_HandleTypeDef *hdma;
} SRAM_Handle;

void MX_FSMC_Init(void);
static void FSMC_MspInit(void);
void FSMC_NORSRAM_Set_Timing(FSMC_Bank1_TypeDef *Device, FSMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank);
void SRAM_Init(SRAM_HandleTypeDef *hsram, FSMC_NORSRAM_TimingTypeDef *Timing);
static void FSMC_MspDeInit(void);

#ifdef __cplusplus
}
#endif
#endif /*__FSMC_H */

