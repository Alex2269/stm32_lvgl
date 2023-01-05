#include "main.h"
#include "lv_encoder.h"
#include "lv_conf.h"
#include "lvgl/lvgl.h"
#include <string.h>
#include "stm32f4xx.h"
#include "exti_encoder.h"

static lv_obj_t * cursor_obj; /*Create an image object for the cursor */
uint8_t encBtnFlag = 0;
static int16_t encoderStep = 0;
int32_t encoder_data;
uint8_t ButtonCount = 0;

static bool read_cb(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static bool encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

void encoder_init(void)
{
  EXTI_GPIO_Init();

  static lv_indev_drv_t indev_drv; /*Descriptor of an input device driver*/
  lv_indev_drv_init(&indev_drv); /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_ENCODER;

  /*This function will be called periodically (by the library) to get the mouse position and state*/
  indev_drv.read_cb = encoder_read;

  /*Register a encoder input device*/
  lv_indev_t * indev_encoder = lv_indev_drv_register(&indev_drv);
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
  static int16_t encoderCnt = 0;

  encoderCnt = encoder_data;

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

