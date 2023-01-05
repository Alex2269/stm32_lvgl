#include "main.h"
#include "SSD1963.h"
#include "io_SSD1963.h"
#include "lvgl_init_f4.h"
#include "lv_encoder.h"
#include "lv_conf.h"
#include "lvgl/lvgl.h"
#include <string.h>
#include "stm32f4xx.h"

static void lcd_flush_cb(lv_disp_draw_buf_t * drv, const lv_area_t * area, lv_color_t * color_p);
static lv_disp_drv_t disp_drv;
static volatile uint32_t t_saved = 0;

void monitor_cb(lv_disp_drv_t * d, uint32_t t, uint32_t p)
{
  t_saved = t;
}

void lv_lcd_init()
{
  #define USE_DBL_BUFF 0
  #define BUFF_LINES 2 // 20 for double buffer, 40 for single buffer (to fit to RAM)
  #define LV_HOR_RES          (800)
  #define LV_VER_RES          (480)

  lv_disp_drv_init(&disp_drv); /*Basic driver initialization*/

  disp_drv.hor_res          = LV_HOR_RES;
  disp_drv.ver_res          = LV_VER_RES;
  disp_drv.physical_hor_res = -1;
  disp_drv.physical_ver_res = -1;
  disp_drv.offset_x         = 0;
  disp_drv.offset_y         = 0;
  disp_drv.full_refresh     = 0;
  disp_drv.flush_cb         = lcd_flush_cb; /*Set a flush callback to draw to the display*/
  disp_drv.monitor_cb       = monitor_cb;
  disp_drv.antialiasing     = 1;

  /* define & init buffers */
  static lv_disp_draw_buf_t buf;
  #if USE_DBL_BUFF
    static lv_color_t disp_buf1[LV_HOR_RES * BUFF_LINES];
    static lv_color_t disp_buf2[LV_HOR_RES * BUFF_LINES];
    lv_disp_draw_buf_init(&buf, disp_buf1, disp_buf2, disp_drv.hor_res * BUFF_LINES);
  #else
    static lv_color_t disp_buf1[LV_HOR_RES * BUFF_LINES];
    lv_disp_draw_buf_init(&buf, disp_buf1, NULL, disp_drv.hor_res * BUFF_LINES);
  #endif

  disp_drv.draw_buf         = &buf; /*Set an initialized buffer*/

  lv_disp_t * disp = lv_disp_drv_register(&disp_drv);

  lv_theme_t * th = lv_theme_default_init(disp,
                                          lv_palette_darken(LV_PALETTE_BLUE, 1),
                                          lv_palette_lighten(LV_PALETTE_RED, 1),
                                          LV_THEME_DEFAULT_DARK /*LV_THEME_DEFAULT_GROW*/,
                                          LV_FONT_DEFAULT);
  lv_disp_set_theme(disp, th);

  Display_Init(2); /* Init LCD hardware */
  // lcdSetOrientation(1);
  // lcdSetOrientation(LCD_ORIENTATION_PORTRAIT_MIRROR);
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
  uint16_t x2 = area->x2 > disp_drv.hor_res - 1 ? disp_drv.hor_res - 1 : area->x2;
  uint16_t y2 = area->y2 > disp_drv.ver_res - 1 ? disp_drv.ver_res - 1 : area->y2;

  /*
  DMA_WindowSet(x1,y1,x2,y2)*/
  DMA_WindowSet(x1,x2,y1,y2);

  uint16_t x,y;
  for(x = x1; x <= x2; x++)
  {
    for(y = y1; y <= y2; y++)
    {
      // DMA_Pixel_Set(x, y, color_p->full);
      DMA_WriteData24(color_p->full);
      color_p++;
    }
  }
  lv_disp_flush_ready(&disp_drv);
}
