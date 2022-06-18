#include "ILI9341.h"
#include "main.h"
#include "lvgl_init_f103.h"
#include "lv_conf.h"
#include "lvgl/lvgl.h"
#include <string.h>
#include "stm32f1xx.h"


/* ------------------- display --------------- */
static void LCD_Flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_p);
lv_disp_drv_t disp_drv;
static volatile uint32_t t_saved = 0;

#define USE_DBL_BUFF 0
#define BUFF_LINES 5 // 20 for double buffer, 40 for single buffer(to fit to RAM)

/* ------------------- DISPLAY --------------- */
void monitor_cb(lv_disp_drv_t * d, uint32_t t, uint32_t p)
{
  t_saved = t;
}

void lv_lcd_init()
{
  /* define & init buffers */
  static lv_disp_buf_t buf;
  static lv_color_t disp_buf1[LV_HOR_RES_MAX * BUFF_LINES];
  lv_disp_buf_init(&buf, disp_buf1, NULL, LV_HOR_RES_MAX * BUFF_LINES);

  ILI9341_Init(); /* Init LCD hardware */
  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
  lv_disp_drv_init(&disp_drv); /*Basic driver initialization */
  disp_drv.buffer = &buf; /*Set an initialized buffer */
  disp_drv.flush_cb = LCD_Flush; /*Set a flush callback to draw to the display */
  disp_drv.monitor_cb = monitor_cb;
  lv_disp_drv_register(&disp_drv);
}

/**
 * Flush a color buffer
 * @param x1 left coordinate of the rectangle
 * @param x2 right coordinate of the rectangle
 * @param y1 top coordinate of the rectangle
 * @param y2 bottom coordinate of the rectangle
 * @param color_p pointer to an array of colors
**/
static void LCD_Flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_p)
{
  /* Truncate the area to the screen */
  int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
  int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
  int32_t act_x2 = area->x2 > LV_HOR_RES_MAX - 1 ? LV_HOR_RES_MAX - 1 : area->x2;
  int32_t act_y2 = area->y2 > LV_VER_RES_MAX - 1 ? LV_VER_RES_MAX - 1 : area->y2;
  // ILI9341_Set_Address(act_x1,act_y1,act_x2,act_y2);

  // ILI9341_DrawImage(act_x1, act_y1, (act_x2 - act_x1 + 1), (act_y2 - act_y1 + 1), color_p);
  write_pin(LCD_CS_GPIO_Port, LCD_CS_Pin, 0);
  ILI9341_SetAddressWindow(act_x1,act_y1,act_x2,act_y2);
  ILI9341_WriteData((uint8_t*)color_p, sizeof(uint16_t)*((act_x2 - act_x1 + 1) *(act_y2 - act_y1 + 1)));
  write_pin(LCD_CS_GPIO_Port, LCD_CS_Pin, 1);

  /* int32_t x, y;
  for(y = act_y1; y <= act_y2; y++)
  {
    for(x = act_x1; x <= act_x2; x++)
    {
      // ILI9341_Draw_Pixel(x,y, color_p->full);
      ILI9341_Write_Data(color_p->full>>8);
      ILI9341_Write_Data(color_p->full);
      color_p+=1;
    }
  }
 */
  lv_disp_flush_ready(&disp_drv);
}
