#include "exti_encoder.h"

void EXTI_GPIO_Init(void)
{
  // LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA); // f4
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA); // f1
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB); // f1

  // LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE6); // for f4
  LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTB, LL_GPIO_AF_EXTI_LINE6); // for f1

  LL_EXTI_DisableEvent_0_31(LL_EXTI_LINE_6);
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_6);
  LL_EXTI_DisableFallingTrig_0_31(LL_EXTI_LINE_6);
  LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_6);

  LL_GPIO_SetPinPull(ENC_DT_GPIO_Port, ENC_DT_Pin, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinMode(ENC_DT_GPIO_Port, ENC_DT_Pin, LL_GPIO_MODE_INPUT);

  /* button */
  LL_GPIO_SetPinPull(MY_BTN_GPIO_Port, MY_BTN_Pin, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinMode(MY_BTN_GPIO_Port, MY_BTN_Pin, LL_GPIO_MODE_INPUT);

  /* EXTI interrupt init for button */
  NVIC_SetPriority(EXTI1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(EXTI1_IRQn);

  /* EXTI interrupt init for encoder */
  NVIC_SetPriority(EXTI9_5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void GPIO_Input(void)
{
  // LL_APB2_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA); // f4
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB); // f1

  LL_GPIO_SetPinMode(MY_BTN_GPIO_Port, MY_BTN_Pin, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(ENC_DT_GPIO_Port, ENC_DT_Pin, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(ENC_CLK_GPIO_Port, ENC_CLK_Pin, LL_GPIO_MODE_INPUT);

  LL_GPIO_SetPinPull(MY_BTN_GPIO_Port, MY_BTN_Pin, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinPull(ENC_DT_GPIO_Port, ENC_DT_Pin, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinPull(ENC_CLK_GPIO_Port, ENC_CLK_Pin, LL_GPIO_PULL_UP);
}

/**
 * @brief encoder connected to pins: PB6 and PB7, pin PA1 button switch
 * @param None
 * @retval None
 */
void EXTI_Callbac(void)
{
  delay_us(1); // anti-tinkling
  // LL_EXTI_DeInit();
  GPIO_Input();

  static int32_t count = 0;
  if(LL_GPIO_IsInputPinSet(ENC_CLK_GPIO_Port, ENC_CLK_Pin)) count++;
  else count--;
  encoder_data = count;

  LL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  printf("encoder: %d\r\n", count);
  // EXTI_GPIO_Init();

  Interrupt_EncoderChange();
}

