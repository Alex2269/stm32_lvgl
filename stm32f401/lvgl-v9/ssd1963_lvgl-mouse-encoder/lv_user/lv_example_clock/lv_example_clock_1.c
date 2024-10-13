#include "lv_examples.h"
#include "lv_example_clock_1.h"

static lv_obj_t * label1;
static lv_obj_t * label2;
static lv_obj_t * rect_lbl1;

static lv_obj_t * isec;
static lv_obj_t * imin;
static lv_obj_t * ihour;

static void timer_cb(lv_timer_t *timer);
static lv_timer_t* timer_create(uint16_t period);
static timer_repeat_count(lv_timer_t* timer, uint16_t count);
static timer_set_period(lv_timer_t* timer, uint16_t new_period);
static timer_reset_period(lv_timer_t* timer);
static void timer_stop(lv_timer_t* timer);
static void arc_create(lv_obj_t* parent, lv_style_t * style, uint16_t sz, uint16_t width, int16_t start, int16_t end, uint16_t opa, lv_color_t color);
static void update_label(lv_obj_t * lbl, uint16_t value);
static lv_obj_t * rectangle_rounded(lv_obj_t* parent, lv_style_t * style, uint16_t x, uint16_t y, uint16_t w, int16_t h, uint16_t opa, lv_palette_t palette);

static void timer_cb(lv_timer_t *timer)
{
  timer_stop(timer);
  timer_repeat_count(timer, 1);
  timer_reset_period(timer);
  timer_set_period(timer, 1000); // 1000 msec

  static int32_t sec;
  static int32_t min;
  static int32_t hour;

  sec+=60;

  if(sec >3599)  sec=0;
  if(min >3599)  min=0;
  if(hour>3599) hour=0;

  if(!(sec % 360))
  {
    min+=6;
    if(!(min % 18) && !sec)
    {
      hour+=15;
    }
  }

  lv_img_set_angle(isec, sec-900); // (img, v+2700);
  lv_img_set_angle(imin, min-900); // (img, v+2700);
  lv_img_set_angle(ihour, hour-900); // (img, v+2700);
  update_label(label1, sec/60);
  update_label(label2, min/60);
}

static lv_timer_t* timer_create(uint16_t period)
{
  lv_timer_t* timer = lv_timer_create(timer_cb, period, NULL);
  lv_timer_set_repeat_count(timer, -1);
  lv_timer_ready(timer);
  return timer;
}

static timer_repeat_count(lv_timer_t* timer, uint16_t count)
{
  lv_timer_set_repeat_count(timer, count);
  lv_timer_ready(timer);
}

static timer_set_period(lv_timer_t* timer, uint16_t new_period)
{
  lv_timer_reset(timer);
  lv_timer_set_period(timer, new_period);
}

static timer_reset_period(lv_timer_t* timer)
{
  lv_timer_reset(timer);
}

static void timer_stop(lv_timer_t* timer)
{
  lv_timer_set_repeat_count(timer, 0);
}

static void arc_create(lv_obj_t* parent, lv_style_t * style, uint16_t sz, uint16_t width, int16_t start, int16_t end, uint16_t opa, lv_color_t color)
{
  lv_obj_t * obj = lv_arc_create(parent);
  lv_obj_remove_style_all(obj); // the remove knob
  lv_obj_set_size(obj, sz, sz);

  lv_style_init(style);
  lv_style_reset(style);
  lv_style_set_arc_width(style, width);
  lv_style_set_arc_opa(style, opa);
  lv_obj_add_style(obj, style, LV_PART_INDICATOR);

  lv_obj_set_style_arc_color(obj, color, LV_PART_INDICATOR);
  lv_arc_set_start_angle(obj, start);
  lv_arc_set_end_angle(obj, end);
  lv_obj_center(obj);
}

static void update_label(lv_obj_t * lbl, uint16_t value)
{
  lv_obj_set_style_text_font(lbl, &arial_14, 0);
  lv_obj_set_style_text_letter_space(lbl, 2, 0);
  lv_obj_set_style_text_color(lbl, lv_palette_darken(LV_PALETTE_ORANGE,2), 0);

  static char buf[4];
  lv_snprintf(buf, sizeof(buf), "%d", value);
  lv_obj_align_to(lbl, rect_lbl1, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(lbl, buf);
}

static lv_obj_t * rectangle_rounded(lv_obj_t* parent, lv_style_t * style, uint16_t x, uint16_t y, uint16_t w, int16_t h, uint16_t opa, lv_palette_t palette)
{
  /*static*/ lv_obj_t * rect_for_label;
  rect_for_label = lv_obj_create(parent);
  lv_obj_remove_style_all(rect_for_label); // the remove knob

  lv_style_init(style);
  lv_style_reset(style);
  lv_style_set_radius(style, 6);
  lv_style_set_bg_opa(style, opa);
  lv_style_set_border_width(style, 2);
  lv_style_set_border_opa(style, LV_OPA_50);
  lv_obj_add_style(rect_for_label, style, 0);

  lv_obj_set_style_bg_color(rect_for_label, lv_palette_lighten(palette, 1), 0);
  lv_obj_set_style_border_color(rect_for_label, lv_palette_lighten(palette, 1), 0);
  lv_obj_set_style_shadow_color(rect_for_label, lv_palette_lighten(palette, 1), 0);
  lv_obj_set_size(rect_for_label, w, h);
  // lv_obj_set_width(rect_for_label, w);
  // lv_obj_set_height(rect_for_label, h);
  lv_obj_set_pos(rect_for_label, x, y); // x y position
  // lv_obj_center(rect_for_label);

  return lv_label_create(rect_for_label);
}

/* *
 * Show transformations (zoom and rotation) using a pivot point.
 */
void lv_example_clock_1(lv_obj_t* parent)
{
  #define siz_clk 400

  /* meters */
  static lv_obj_t * meter1;
  static lv_obj_t * meter2;
  static lv_obj_t * meter3;

  meter1 = lv_meter_create(parent);
  meter2 = lv_meter_create(parent);
  meter3 = lv_meter_create(parent);

  lv_obj_remove_style_all(meter1);
  lv_obj_remove_style_all(meter2);
  lv_obj_remove_style_all(meter3);

  lv_obj_set_size(meter1, siz_clk, siz_clk);
  lv_obj_set_size(meter2, siz_clk, siz_clk);
  lv_obj_set_size(meter3, siz_clk, siz_clk);

  lv_obj_center(meter1);
  lv_obj_center(meter2);
  lv_obj_center(meter3);

  //--draw arcs beg--
  static lv_obj_t * arc_obj;
  arc_obj = lv_obj_create(meter1);
  lv_obj_remove_style_all(arc_obj);
  lv_obj_align(arc_obj, LV_ALIGN_CENTER, 0, 0);
  lv_obj_center(arc_obj);

  static lv_style_t style_arc1;
  static lv_style_t style_arc2;
  static lv_style_t style_arc3;
  static lv_style_t style_arc4;
  static lv_style_t style_arc5;
  static lv_style_t style_arc6;
  static lv_style_t style_arc7;

  arc_create(meter1, &style_arc1, 330, 60,   0,360, LV_OPA_20, lv_color_change_lightness(lv_palette_main(LV_PALETTE_ORANGE),96));
  arc_create(meter1, &style_arc2, 342,  4,   0,360, LV_OPA_80, lv_palette_main(LV_PALETTE_YELLOW));
  arc_create(meter1, &style_arc3, 350,  4,   0,360, LV_OPA_80, lv_palette_main(LV_PALETTE_LIME));
  arc_create(meter1, &style_arc4, 400, 28,   0, 90, LV_OPA_20, lv_palette_darken(LV_PALETTE_ORANGE,1));
  arc_create(meter1, &style_arc5, 400, 28,  90,180, LV_OPA_40, lv_palette_darken(LV_PALETTE_RED,1));
  arc_create(meter1, &style_arc6, 400, 28, 180,270, LV_OPA_60, lv_palette_darken(LV_PALETTE_GREEN,2));
  arc_create(meter1, &style_arc7, 400, 28, 270,360, LV_OPA_40, lv_palette_lighten(LV_PALETTE_BLUE,1));
  //--draw arcs end--

  //--draw rects--
  static lv_style_t style_round;
  label1 = rectangle_rounded(meter1, &style_round, 105, siz_clk/2-16, 64, 32, LV_OPA_30, LV_PALETTE_BLUE);
  label2 = rectangle_rounded(meter1, &style_round, 230, siz_clk/2-16, 64, 32, LV_OPA_30, LV_PALETTE_GREEN);
  //--draw rects end--

  lv_obj_set_style_text_color(meter1, lv_palette_darken(LV_PALETTE_CYAN,1), LV_PART_MAIN);
  lv_obj_set_style_text_color(meter2, lv_palette_lighten(LV_PALETTE_YELLOW,1), LV_PART_MAIN);
  lv_obj_set_style_text_color(meter3, lv_palette_lighten(LV_PALETTE_LIME,4), LV_PART_MAIN);

  lv_obj_set_style_text_font(meter1, &arial_14, LV_PART_MAIN);
  lv_obj_set_style_text_font(meter2, &arial_14, LV_PART_MAIN);
  lv_obj_set_style_text_font(meter3, &arial_14, LV_PART_MAIN);

  lv_obj_set_style_text_letter_space(meter1, 2, LV_PART_MAIN);
  lv_obj_set_style_text_letter_space(meter2, 2, LV_PART_MAIN);
  lv_obj_set_style_text_letter_space(meter3, 2, LV_PART_MAIN);

  lv_obj_set_style_text_line_space(meter1, 2, LV_PART_MAIN);
  lv_obj_set_style_text_line_space(meter2, 2, LV_PART_MAIN);
  lv_obj_set_style_text_line_space(meter3, 2, LV_PART_MAIN);

  /* --- */
  /*Create a scale for the minutes*/
  /*61 ticks in a 360 degrees range (the last and the first line overlaps)*/
  lv_meter_set_scale_ticks(meter1, 60, 2, 8, lv_palette_main(LV_PALETTE_ORANGE));  // 24 ticks
  lv_meter_set_scale_major_ticks(meter1, 5, 4, 8, lv_palette_lighten(LV_PALETTE_YELLOW,2), +8);
  lv_meter_set_scale_range(meter1, 0, 59, 354, 270);  // [1..60] values in an almost full circle

  lv_meter_set_scale_ticks(meter2, 12, 0, 0, lv_palette_main(LV_PALETTE_ORANGE)); /* 12 ticks */
  lv_meter_set_scale_major_ticks(meter2, 1, 0,  0, lv_palette_darken(LV_PALETTE_YELLOW,4), 48);
  lv_meter_set_scale_range(meter2, 12, 23, 330, 270);

  lv_meter_set_scale_ticks(meter3, 12, 0, 0, lv_palette_main(LV_PALETTE_ORANGE)); /* 12 ticks */
  lv_meter_set_scale_major_ticks(meter3, 1, 0,  0, lv_palette_darken(LV_PALETTE_YELLOW,4), 80);
  lv_meter_set_scale_range(meter3, 0, 11, 330, 270); /* [1..12] values in an almost full circle */

  LV_IMG_DECLARE(arrow_midle);
  LV_IMG_DECLARE(arrow_small);
  LV_IMG_DECLARE(arrow_big);

  /* Now create the actual image */
  ihour = lv_img_create(parent);
  imin = lv_img_create(parent);
  isec = lv_img_create(parent);

  lv_img_set_src(ihour, &arrow_big);
  lv_img_set_src(imin, &arrow_midle);
  lv_img_set_src(isec, &arrow_small);

  // lv_obj_align(ihour, LV_ALIGN_CENTER, -1, -1);
  lv_obj_align(ihour, LV_ALIGN_CENTER, 40, 0);
  lv_obj_align(imin, LV_ALIGN_CENTER, 40, 0);
  lv_obj_align(isec, LV_ALIGN_CENTER, 40, 0);

  /*
   * By default, the pivot point of the rotation
   * is the center of the image.
   * It can be changed with
   * lv_img_set_pivot(img, pivot_x, pivot_y). 0;0 is the top left corner. */
  lv_img_set_pivot(isec, 60, 9); /* Rotate around the top left corner */
  lv_img_set_pivot(ihour, 60, 9); /* Rotate around the top left corner */
  lv_img_set_pivot(imin, 60, 9); /* Rotate around the top left corner */
  // lv_img_set_antialias (ihour,  true);
  // lv_img_set_antialias (imin,  true);

  /* recolor arrow to green color */
  lv_obj_set_style_img_recolor_opa(isec, 250, 0);
  lv_obj_set_style_img_recolor(isec, lv_palette_lighten(LV_PALETTE_PINK,4), 0);
  /* recolor arrow to red color */
  lv_obj_set_style_img_recolor_opa(ihour, 250, 0);
  lv_obj_set_style_img_recolor(ihour, lv_palette_darken(LV_PALETTE_ORANGE,2), 0);
  /* recolor arrow to blue color */
  lv_obj_set_style_img_recolor_opa(imin, 250, 0);
  lv_obj_set_style_img_recolor(imin, lv_palette_lighten(LV_PALETTE_LIME,3), 0);

  lv_img_set_zoom(isec, siz_clk * 0.8); // стрелы пропорционально индикатору
  lv_img_set_zoom(ihour, siz_clk * 0.8);
  lv_img_set_zoom(imin, siz_clk * 0.8);

  /* --- */
  // animation
  // lv_timer_t* timer = timer_create(1000);
  lv_timer_t* timer =  lv_timer_create_basic();
  lv_timer_set_cb(timer, timer_cb);
  timer_stop(timer);
  timer_repeat_count(timer, 1);
  timer_reset_period(timer);
  timer_set_period(timer, 1);
}

