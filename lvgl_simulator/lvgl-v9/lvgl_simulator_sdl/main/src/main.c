
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <unistd.h>
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
#include <SDL2/SDL.h>
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"

#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/mouse.h"
#include "lv_drivers/indev/keyboard.h"
#include "lv_drivers/indev/mousewheel.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);
static int tick_thread(void *data);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

int main(int argc, char **argv)
{
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/

  /*Initialize LVGL*/
  lv_init();

  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  hal_init();

  // ---------------------

  // lv_example_arc_1();
  // lv_example_arc_2();

  // lv_example_animimg_1();

  // lv_example_bar_1();
  // lv_example_bar_2();
  // lv_example_bar_3();
  // lv_example_bar_4();
  // lv_example_bar_5();
  // lv_example_bar_6();

  // lv_example_btn_1();
  // lv_example_btn_2();
  // lv_example_btn_3();

  // lv_example_btnmatrix_1();
  // lv_example_btnmatrix_2();
  // lv_example_btnmatrix_3();

  // lv_example_calendar_1();

  // lv_example_canvas_1();
  // lv_example_canvas_2();

  // lv_example_chart_1();
  // lv_example_chart_2();
  // lv_example_chart_3();
  // lv_example_chart_4();
  // lv_example_chart_5();
  // lv_example_chart_6();
  // lv_example_chart_7();
  // lv_example_chart_8();
  // lv_example_chart_9();

  // lv_example_checkbox_1();
  // lv_example_checkbox_2();

  // lv_example_colorwheel_1();

  // lv_example_dropdown_1();
  // lv_example_dropdown_2();
  // lv_example_dropdown_3();

  // lv_example_img_1();
  // lv_example_img_2();
  // lv_example_img_3();
  // lv_example_img_4();

  // lv_example_imgbtn_1();

  // lv_example_keyboard_1();
  // lv_example_keyboard_2();
  // lv_keyboard_create(lv_scr_act());

  // lv_example_label_1();
  // lv_example_label_2();
  // lv_example_label_3();
  // lv_example_label_4();

  // lv_example_led_1();

  // lv_example_line_1();

  // lv_example_list_1();
  // lv_example_list_2();

  // lv_example_menu_1();
  // lv_example_menu_2();
  // lv_example_menu_3();
  // lv_example_menu_4();
  // lv_example_menu_5();

  // lv_example_meter_1();
  // lv_example_meter_2();
  // lv_example_meter_3(); // clock with dial
  // lv_example_meter_4();

  // lv_example_msgbox_1();

  // lv_example_obj_1();
  // lv_example_obj_2();

  // lv_example_roller_1();
  // lv_example_roller_2();
  // lv_example_roller_3();

  // lv_example_slider_1();
  // lv_example_slider_2();
  // lv_example_slider_3();

  // lv_example_spinbox_1();

  // lv_example_spinner_1();

  // lv_example_switch_1();

  // lv_example_table_1();
  // lv_example_table_2();

  // lv_example_tabview_1();
  // lv_example_tabview_2();

  // lv_example_textarea_1();
  // lv_example_textarea_2();
  // lv_example_textarea_3();

  // lv_example_tileview_1();

  // lv_example_win_1();

  // lv_example_span_1();

  // ---------------------

  // ---------------------

  // lv_demo_widgets();
  // lv_demo_stress();
  // lv_demo_benchmark();
  // lv_demo_music();

  // ---------------------

  // ---------------------
  // lv_example_scroll_1();
  // lv_example_flex_1();
  // lv_example_flex_6();
  // lv_example_event_1();
  // ---------------------
  user_tabview_6();
  // ---------------------
  // lv_example_clock_1(lv_scr_act());
  // lv_example_compas_0(lv_scr_act());

  // lv_example_style_1();
  // lv_example_style_2();
  // lv_example_style_3();
  // lv_example_style_4();
  // lv_example_style_5();
  // lv_example_style_6();
  // lv_example_style_7();
  // lv_example_style_8();
  // lv_example_style_9();
  // lv_example_style_10();
  // lv_example_style_11();

  // lv_user_keypad_encoder();
  // lv_user_keypad_encoder2();
  // lv_example_menu_5b();
  // lv_example_menu_6b();
  // lv_example_chart_6();
  // lv_example_chart_5b();
  // lv_example_keyboard_3();
  // lv_example_msg_3b();


  while(1) {
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    lv_timer_handler();
    usleep(5 * 1000);
  }

  return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static void hal_init(void)
{
  /* Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
  monitor_init();
  /* Tick init.
   * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL about
   * how much time were elapsed Create an SDL thread to do this*/
  SDL_CreateThread(tick_thread, "tick", NULL);

  /*Create a display buffer*/
  static lv_disp_draw_buf_t disp_buf1;
  static lv_color_t buf1_1[MONITOR_HOR_RES * 100];
  static lv_color_t buf1_2[MONITOR_HOR_RES * 100];
  lv_disp_draw_buf_init(&disp_buf1, buf1_1, buf1_2, MONITOR_HOR_RES * 100);

  /*Create a display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/
  disp_drv.draw_buf = &disp_buf1;
  disp_drv.flush_cb = monitor_flush;
  disp_drv.hor_res = MONITOR_HOR_RES;
  disp_drv.ver_res = MONITOR_VER_RES;
  disp_drv.antialiasing = 1;

  lv_disp_t * disp = lv_disp_drv_register(&disp_drv);

  lv_theme_t * th = lv_theme_default_init(disp,
                                          lv_palette_darken(LV_PALETTE_BLUE, 1),
                                          lv_palette_lighten(LV_PALETTE_RED, 1),
                                          LV_THEME_DEFAULT_DARK/*LV_THEME_DEFAULT_GROW*/,
                                          LV_FONT_DEFAULT);
  lv_disp_set_theme(disp, th);

  lv_group_t * g = lv_group_create();
  lv_group_set_default(g);

  /* Add the mouse as input device
   * Use the 'mouse' driver which reads the PC's mouse*/
  mouse_init();
  static lv_indev_drv_t indev_drv_1;
  lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
  indev_drv_1.type = LV_INDEV_TYPE_POINTER;

  /*This function will be called periodically (by the library) to get the mouse position and state*/
  indev_drv_1.read_cb = mouse_read;
  lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);

  keyboard_init();
  static lv_indev_drv_t indev_drv_2;
  lv_indev_drv_init(&indev_drv_2); /*Basic initialization*/
  indev_drv_2.type = LV_INDEV_TYPE_KEYPAD;
  indev_drv_2.read_cb = keyboard_read;
  lv_indev_t *kb_indev = lv_indev_drv_register(&indev_drv_2);
  lv_indev_set_group(kb_indev, g);
  mousewheel_init();
  static lv_indev_drv_t indev_drv_3;
  lv_indev_drv_init(&indev_drv_3); /*Basic initialization*/
  indev_drv_3.type = LV_INDEV_TYPE_ENCODER;
  indev_drv_3.read_cb = mousewheel_read;

  lv_indev_t * enc_indev = lv_indev_drv_register(&indev_drv_3);
  lv_indev_set_group(enc_indev, g);

  /*Set a cursor for the mouse*/
  LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  lv_obj_t * cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
  lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
  lv_indev_set_cursor(mouse_indev, cursor_obj);             /*Connect the image  object to the driver*/
}

/**
 * A task to measure the elapsed time for LVGL
 * @param data unused
 * @return never return
 */
static int tick_thread(void *data) {
  (void)data;

  while(1) {
    SDL_Delay(5);
    lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
  }

  return 0;
}