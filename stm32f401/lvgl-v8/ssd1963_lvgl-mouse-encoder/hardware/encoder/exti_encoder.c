#include "exti_encoder.h"

void EXTI_GPIO_Init(void)
{
  // LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA); // f1
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA); // f4

  // LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTB, LL_GPIO_AF_EXTI_LINE6); // for f1
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE4); // for f4
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE5); // for f4

  /* button encoder */
  LL_EXTI_DisableEvent_0_31(LL_EXTI_LINE_4);
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_4);
  LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_4);
  LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_4);

  /* wheel encoder */
  LL_EXTI_DisableEvent_0_31(LL_EXTI_LINE_5);
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_5);
  LL_EXTI_DisableFallingTrig_0_31(LL_EXTI_LINE_5);
  LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_5);

  /* button */
  LL_GPIO_SetPinPull(ENC_SW_GPIO_Port, ENC_SW_Pin, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinMode(ENC_SW_GPIO_Port, ENC_SW_Pin, LL_GPIO_MODE_INPUT);

  LL_GPIO_SetPinPull(ENC_DT_GPIO_Port, ENC_DT_Pin, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinMode(ENC_DT_GPIO_Port, ENC_DT_Pin, LL_GPIO_MODE_INPUT);

  /* EXTI interrupt init for button LL_EXTI_LINE_4 */
  NVIC_SetPriority(EXTI4_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(EXTI4_IRQn);

  NVIC_SetPriority(EXTI9_5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void GPIO_Input(void)
{
  LL_APB2_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA); // f4
  // LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB); // f1

  LL_GPIO_SetPinMode(ENC_SW_GPIO_Port, ENC_SW_Pin, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(ENC_DT_GPIO_Port, ENC_DT_Pin, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(ENC_CLK_GPIO_Port, ENC_CLK_Pin, LL_GPIO_MODE_INPUT);

  LL_GPIO_SetPinPull(ENC_SW_GPIO_Port, ENC_SW_Pin, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinPull(ENC_DT_GPIO_Port, ENC_DT_Pin, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinPull(ENC_CLK_GPIO_Port, ENC_CLK_Pin, LL_GPIO_PULL_UP);
}

/**
 * @brief encoder
 * @param None
 * @retval None
 */
void EXTI_Callbac_Encoder(void)
{
  delay_us(1); // anti-tinkling
  LL_EXTI_DeInit();
  GPIO_Input();

  static int32_t count = 0;
  if(LL_GPIO_IsInputPinSet(ENC_CLK_GPIO_Port, ENC_CLK_Pin)) count++;
  else count--;

  encoder_data = count;

  LL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  printf("encoder: %d\r\n", count);
  EXTI_GPIO_Init();

  Interrupt_EncoderChange();
}

void EXTI_Callbac_Button(void)
{
  delay_us(1); // anti-tinkling
  LL_EXTI_DeInit();
  GPIO_Input();
  if(LL_GPIO_IsInputPinSet(ENC_SW_GPIO_Port, ENC_SW_Pin) == 0)
  {
    encBtnFlag = 1;
    ButtonCount++;
  }

  if(LL_GPIO_IsInputPinSet(ENC_SW_GPIO_Port, ENC_SW_Pin) == 1)
  {
    encBtnFlag = 0;
  }

  LL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  printf("button: %d\r\n", encBtnFlag);
  EXTI_GPIO_Init();
}
