#include "main.h"
#include "SSD1963.h"
#include "io_SSD1963.h"
#include "lvgl_init_f4.h"
#include "lv_conf.h"
#include "lvgl/lvgl.h"
#include <string.h>
#include "stm32f4xx.h"

static void lcd_flush_cb(lv_disp_draw_buf_t * drv, const lv_area_t * area, lv_color_t * color_p);
static lv_disp_drv_t disp_drv;
static volatile uint32_t t_saved = 0;

#define USE_DBL_BUFF 0
#define BUFF_LINES 2 // 20 for double buffer, 40 for single buffer (to fit to RAM)

void monitor_cb(lv_disp_drv_t * d, uint32_t t, uint32_t p)
{
  t_saved = t;
}

void lv_lcd_init()
{
  /* define & init buffers */
  static lv_disp_draw_buf_t buf;
  #if USE_DBL_BUFF
    static lv_color_t disp_buf1[LV_HOR_RES_MAX * BUFF_LINES];
    static lv_color_t disp_buf2[LV_HOR_RES_MAX * BUFF_LINES];
    lv_disp_draw_buf_init(&buf, disp_buf1, disp_buf2, LV_HOR_RES_MAX * BUFF_LINES);
  #else
    static lv_color_t disp_buf1[LV_HOR_RES_MAX * BUFF_LINES];
    lv_disp_draw_buf_init(&buf, disp_buf1, NULL, LV_HOR_RES_MAX * BUFF_LINES);
  #endif
  Display_Init(1); /* Init LCD hardware */
  // lcdSetOrientation(1);
  // lcdSetOrientation(LCD_ORIENTATION_PORTRAIT_MIRROR);
  lv_disp_drv_init(&disp_drv); /*Basic driver initialization*/
  disp_drv.draw_buf = &buf; /*Set an initialized buffer*/
  disp_drv.flush_cb = lcd_flush_cb; /*Set a flush callback to draw to the display*/
  disp_drv.monitor_cb = monitor_cb;
  disp_drv.full_refresh = 0;
  lv_disp_drv_register(&disp_drv);
}

/**
 * Flush a color buffer
 * @param x1 left coordinate of the rectangle
 * @param x2 right coordinate of the rectangle
 * @param y1 top coordinate of the rectangle
 * @param y2 bottom coordinate of the rectangle
 * @param color_p pointer to an array of colors
 */
static void lcd_flush_cb(lv_disp_draw_buf_t * drv, const lv_area_t * area, lv_color_t * color_p)
{
  /*Truncate the area to the screen*/
  uint16_t x1 = area->x1 < 0 ? 0 : area->x1;
  uint16_t y1 = area->y1 < 0 ? 0 : area->y1;
  uint16_t x2 = area->x2 > LV_HOR_RES_MAX - 1 ? LV_HOR_RES_MAX - 1 : area->x2;
  uint16_t y2 = area->y2 > LV_VER_RES_MAX - 1 ? LV_VER_RES_MAX - 1 : area->y2;

  /*
  Display_WindowSet(x1,y1,x2,y2)*/
  Display_WindowSet(x1,x2,y1,y2);

  uint16_t x,y;
  for(y = y1; y <= y2; y++)
  {
    for(x = x1; x <= x2; x++)
    {
      // Display_PSet(x, y, color_p->full);
      Display_WriteData24(color_p->full);
      color_p++;
    }
  }
  lv_disp_flush_ready(&disp_drv);
}
