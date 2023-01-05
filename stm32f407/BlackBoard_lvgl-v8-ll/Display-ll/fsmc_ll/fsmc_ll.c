#include "fsmc_ll.h"
#include "stm32f4xx_ll_fsmc.h"

SRAM_Handle hsram1;

void MX_FSMC_Init(void)
{
  FSMC_NORSRAM_TimingTypeDef Timing = {0};

  hsram1.Instance = FSMC_NORSRAM_DEVICE;
  hsram1.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  hsram1.Init.NSBank = FSMC_NORSRAM_BANK1;
  hsram1.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram1.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  hsram1.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram1.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram1.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram1.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  hsram1.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram1.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  hsram1.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  hsram1.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  hsram1.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram1.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
  hsram1.Init.PageSize = FSMC_PAGE_SIZE_NONE;
  Timing.AddressSetupTime = 1;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 5;
  Timing.BusTurnAroundDuration = 0;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;

  FSMC_MspInit();

  SRAM_Init(&hsram1, &Timing);
}

static void FSMC_MspInit(void)
{
  RCC->AHB3ENR |= RCC_AHB3ENR_FSMCEN;

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = LL_GPIO_PIN_7|LL_GPIO_PIN_8|LL_GPIO_PIN_9|
                        LL_GPIO_PIN_10|LL_GPIO_PIN_11|LL_GPIO_PIN_12|
                        LL_GPIO_PIN_13|LL_GPIO_PIN_14|LL_GPIO_PIN_15;

  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_12;
  LL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_8|LL_GPIO_PIN_9|LL_GPIO_PIN_10|LL_GPIO_PIN_13|
                        LL_GPIO_PIN_14|LL_GPIO_PIN_15|LL_GPIO_PIN_0|LL_GPIO_PIN_1|
                        LL_GPIO_PIN_4|LL_GPIO_PIN_5|LL_GPIO_PIN_7;

  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_12;
  LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void FSMC_NORSRAM_Set_Timing(FSMC_Bank1_TypeDef *Device, FSMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank)
{
  uint32_t tmpr = 0U;
  tmpr = Device->BTCR[Bank + 1U];
  tmpr &= (uint32_t) ~(FSMC_BTR1_ADDSET | FSMC_BTR1_ADDHLD |
                       FSMC_BTR1_DATAST | FSMC_BTR1_BUSTURN |
                       FSMC_BTR1_CLKDIV | FSMC_BTR1_DATLAT |
                       FSMC_BTR1_ACCMOD);

  tmpr |= (uint32_t) (Timing->AddressSetupTime |
                      Timing->AddressHoldTime << 4U |
                      Timing->DataSetupTime << 8U |
                      Timing->CLKDivision-1U << 20U |
                      Timing->DataLatency-2U << 24U |
                      Timing->AccessMode);

  Device->BTCR[Bank + 1] = tmpr;
}

void SRAM_Init(SRAM_HandleTypeDef *hsram, FSMC_NORSRAM_TimingTypeDef *Timing)
{
  FSMC_NORSRAM_Set_Timing(hsram->Instance, Timing, hsram->Init.NSBank);
}

static void FSMC_MspDeInit(void)
{
  RCC->AHB3ENR &= ~RCC_AHB3ENR_FSMCEN;

  LL_GPIO_DeInit(GPIOE);
  LL_GPIO_DeInit(GPIOE);
  LL_GPIO_DeInit(GPIOE);
  LL_GPIO_DeInit(GPIOE);
  LL_GPIO_DeInit(GPIOE);
  LL_GPIO_DeInit(GPIOE);
  LL_GPIO_DeInit(GPIOE);
  LL_GPIO_DeInit(GPIOE);
  LL_GPIO_DeInit(GPIOE);
  LL_GPIO_DeInit(GPIOD);
  LL_GPIO_DeInit(GPIOD);
  LL_GPIO_DeInit(GPIOD);
  LL_GPIO_DeInit(GPIOD);
  LL_GPIO_DeInit(GPIOD);
  LL_GPIO_DeInit(GPIOD);
  LL_GPIO_DeInit(GPIOD);
  LL_GPIO_DeInit(GPIOD);
  LL_GPIO_DeInit(GPIOD);
  LL_GPIO_DeInit(GPIOD);
  LL_GPIO_DeInit(GPIOD);
}

