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
static bool mouse_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

void encoder_init(void)
{
  EXTI_GPIO_Init();

  static lv_indev_drv_t indev_drv; /*Descriptor of an input device driver*/
  lv_indev_drv_init(&indev_drv); /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;

  /*This function will be called periodically (by the library) to get the mouse position and state*/
  indev_drv.read_cb = mouse_read;

  lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv);
  /*Set a cursor for the mouse*/
  LV_IMG_DECLARE(mouse_arrows); /*Declare the image file.*/
  cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
  lv_img_set_src(cursor_obj, &mouse_arrows); /*Set the image source*/
  // lv_obj_align(cursor_obj, LV_ALIGN_CENTER, 44, 0);
  // lv_img_set_pivot(cursor_obj, 10, 10); /* Rotate around the top left corner */
  lv_img_set_antialias(cursor_obj,  true);
  // lv_img_set_angle(cursor_obj, -900);
  lv_obj_set_style_img_recolor_opa(cursor_obj, 32, 0);
  // lv_obj_set_style_img_recolor(cursor_obj, lv_palette_darken(LV_PALETTE_GREY,2), 0);
  // lv_img_set_zoom(cursor_obj, 1.0);
  lv_indev_set_cursor(mouse_indev, cursor_obj); /*Connect the image  object to the driver*/
}

/* Will be called by the library to read the encoder */
bool mouse_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
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

  #define LV_HOR_RES          (800)
  #define LV_VER_RES          (480)
  if(data->point.x < 0) data->point.x = 0; // horisontal limit
  if(data->point.y < 0) data->point.y = 0; // vertical   limit
  if(data->point.x > LV_HOR_RES-10) data->point.x = LV_HOR_RES-10;
  if(data->point.y > LV_VER_RES-10) data->point.y = LV_VER_RES-10;

  if(ButtonCount == 0) {
    // lv_obj_set_style_img_recolor_opa(cursor_obj, 32, 0);
    // lv_obj_set_style_img_recolor(cursor_obj, lv_palette_darken(LV_PALETTE_GREY,2), 0);
    lv_img_set_angle(cursor_obj, +1800);
    lv_img_set_pivot(cursor_obj, 15, 4); // horisontal mouse pointer
    data->point.x += encoderStep;
  }
  if(ButtonCount == 1) {
    // lv_obj_set_style_img_recolor_opa(cursor_obj, 32, 0);
    // lv_obj_set_style_img_recolor(cursor_obj, lv_palette_lighten(LV_PALETTE_GREY,3), 0);
    lv_img_set_angle(cursor_obj, +900);
    lv_img_set_pivot(cursor_obj, 5, 5); // vertical mouse pointer
    data->point.y += encoderStep;
  }
  if(ButtonCount  > 1) ButtonCount = 0;

  // data->enc_diff = encoderStep;
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
    encoderStep = +20;
  }

  if(encoderCnt < previousEncoderCnt)
  {
    encoderStep = -20;
  }

  previousEncoderCnt = encoderCnt;
}

