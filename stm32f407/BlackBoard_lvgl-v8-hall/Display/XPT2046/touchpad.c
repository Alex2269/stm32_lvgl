
#include "lvgl/lvgl.h"
#include "touchpad.h"
#include "xpt2046.h"

// void get_point(TS_Point *p)
extern TS_Point p;

lv_indev_t * indev_touchpad;

bool xpt2046_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static bool read_cb(lv_indev_drv_t * drv, lv_indev_data_t*data);

void lv_touchpad_init(void)
{
  static lv_indev_drv_t indev_drv;        /*Descriptor of an input device driver*/
  lv_indev_drv_init(&indev_drv);          /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER; /*The touchpad is pointer type device*/
  indev_drv.read_cb = xpt2046_read;

  lv_indev_drv_register(&indev_drv);
  indev_touchpad = lv_indev_drv_register(&indev_drv);
}

bool xpt2046_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
  #define press_count 32
  static float x[press_count];
  static float y[press_count];
  static float sumx, sumy;

  for(uint16_t i = 0; i < press_count; i++)
  {
    get_point(&p);
    if(p.z > 980)
    {
      data->state = LV_INDEV_STATE_REL; // EASED;
      return false; /*No buffering now so no more data read*/
    }
    else
    {
      x[i] = p.x;
      y[i] = p.y;
    }

    sumx = sumy = 0;
    for(uint16_t i = 0; i < press_count; i++)
    {
      sumx += x[i];
      sumy += y[i];
    }
    data->point.x = sumx / press_count;
    data->point.y = sumy / press_count;

  }

  static uint8_t count;
  count++;
  if(count > 1)
  {
    count = 0;
    data->state = LV_INDEV_STATE_PR; // ESSED;
  }

  return false;
}

