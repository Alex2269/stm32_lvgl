#include "main.h"
#include "lv_conf.h"
#include "lvgl/lvgl.h"
#include <string.h>
#include "stm32f1xx.h"

#include "lv_encoder.h"
#include "exti_encoder.h"

// #include "lv_drv_conf.h"

/* -------------- encoder def --------------- */
uint8_t encBtnFlag = 0;
volatile int16_t encoderStep = 0;
lv_indev_t * indev_encoder;
// static lv_indev_state_t encoder_state;

extern volatile uint8_t encoderBtnInterruptFlag;
int32_t encoder_data;
static bool read_cb(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static bool encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

/* -------------- encoder rel ------------ */
void lv_encoder_init(void)
{
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_ENCODER;
  indev_drv.read_cb = encoder_read;
  indev_encoder = lv_indev_drv_register(&indev_drv);
  // lv_indev_drv_register(&indev_drv);

  /*
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.read_cb = touchpad_read;
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  lv_indev_drv_register(&indev_drv);
 */
}

/* Will be called by the library to read the encoder */
bool encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
  (void) indev_drv; /* Unused */
  if(encBtnFlag == 1)
  {
    data->state = LV_INDEV_STATE_PR;
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }

  data->enc_diff = encoderStep;
  encoderStep = 0;

  return false;
}

void Interrupt_EncoderChange(void)
{
  static int16_t previousEncoderCnt = 0;
  int16_t encoderCnt = 0;

  encoderCnt = encoder_data; // ((int16_t)__HAL_TIM_GET_COUNTER(&htim4))/2;

  if(encoderCnt > previousEncoderCnt)
  {
    encoderStep = 1;
  }

  if(encoderCnt < previousEncoderCnt)
  {
    encoderStep = -1;
  }

  previousEncoderCnt = encoderCnt;
}

void Interrupt_ButtonPressed(void)
{
  if(LL_GPIO_IsInputPinSet(MY_BTN_GPIO_Port, MY_BTN_Pin) == 0)
  {
    encBtnFlag = 1;
  }

  if(LL_GPIO_IsInputPinSet(MY_BTN_GPIO_Port, MY_BTN_Pin) == 1)
  {
    encBtnFlag = 0;
  }
}

