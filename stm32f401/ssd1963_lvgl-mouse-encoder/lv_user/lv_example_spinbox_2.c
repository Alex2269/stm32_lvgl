#include "../../lv_examples.h"

static lv_obj_t * spinbox;
static lv_obj_t * spinbox2;

static void lv_spinbox_increment_event_cb(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT)
  {
    lv_spinbox_increment(spinbox);
  }
}

static void lv_spinbox_decrement_event_cb(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT)
  {
    lv_spinbox_decrement(spinbox);
  }
}

static void lv_spinbox3_increment_event_cb(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT)
  {
    lv_spinbox_increment(spinbox2);
  }
}

static void lv_spinbox3_decrement_event_cb(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT)
  {
    lv_spinbox_decrement(spinbox2);
  }
}

void lv_example_spinbox_2(lv_obj_t* parent, int16_t pos_x, int16_t pos_y)
{
  static lv_style_t style_sp_box;
  static lv_style_t style_btn;
  // --
  lv_style_init(&style_sp_box);
  lv_style_set_text_font(&style_sp_box, &arial_20);
  lv_style_set_text_letter_space(&style_sp_box, -2);
  lv_style_set_text_line_space(&style_sp_box, 20);
  lv_style_set_border_width(&style_sp_box, 4); // 8
  // lv_style_set_pad_all(&style_sp_box, 8);
  lv_style_set_pad_hor(&style_sp_box, 12);
  lv_style_set_pad_ver(&style_sp_box, 4);
  lv_style_set_radius(&style_sp_box, 28);
  // --
  spinbox = lv_spinbox_create(parent);
  lv_obj_add_style(spinbox, &style_sp_box, 0);
  lv_spinbox_set_range(spinbox, 0, 9999);
  lv_spinbox_set_digit_format(spinbox, 4, 0);
  lv_spinbox_set_pos(spinbox, 1);
  lv_spinbox_step_prev(spinbox);
  // lv_obj_set_height(spinbox, 76);
  lv_obj_set_width(spinbox, 160);
  // lv_obj_center(spinbox);
  // lv_obj_align(spinbox, LV_ALIGN_CENTER, -80, 80); // force: 100
  lv_obj_align_to(spinbox, parent, LV_ALIGN_CENTER, pos_x, pos_y);
  // --
  lv_style_init(&style_btn);
  lv_style_set_border_width(&style_btn, 4);
  lv_style_set_border_color(&style_btn, lv_palette_main(LV_PALETTE_ORANGE));
  lv_style_set_text_font(&style_btn, &arial_20);
  // --
  lv_coord_t h = lv_obj_get_height(spinbox) - 12;
  lv_style_set_radius(&style_btn, h/4);
  // --
  lv_obj_t * btn = lv_btn_create(parent);
  lv_obj_set_size(btn, h, h+14);
  lv_obj_align_to(btn, spinbox, LV_ALIGN_OUT_RIGHT_MID, 4, 0);
  lv_obj_set_style_bg_img_src(btn, LV_SYMBOL_PLUS, 0);
  lv_obj_add_style(btn, &style_btn, 0);
  lv_obj_add_event_cb(btn, lv_spinbox_increment_event_cb, LV_EVENT_ALL, NULL);
  // --
  btn = lv_btn_create(parent);
  lv_obj_set_size(btn, h, h+14);
  lv_obj_align_to(btn, spinbox, LV_ALIGN_OUT_LEFT_MID, -4, 0);
  lv_obj_set_style_bg_img_src(btn, LV_SYMBOL_MINUS, 0);
  lv_obj_add_style(btn, &style_btn, 0);
  lv_obj_add_event_cb(btn, lv_spinbox_decrement_event_cb, LV_EVENT_ALL, NULL);
}

void lv_example_spinbox_3(lv_obj_t* parent, int16_t pos_x, int16_t pos_y)
{
  static lv_style_t style_sp_box;
  static lv_style_t style_btn;
  // --
  lv_style_init(&style_sp_box);
  lv_style_set_text_font(&style_sp_box, &arial_20);
  lv_style_set_text_letter_space(&style_sp_box, -2);
  lv_style_set_text_line_space(&style_sp_box, 20);
  lv_style_set_border_width(&style_sp_box, 4); // 8
  // lv_style_set_pad_all(&style_sp_box, 8);
  lv_style_set_pad_hor(&style_sp_box, 12);
  lv_style_set_pad_ver(&style_sp_box, 4);
  lv_style_set_radius(&style_sp_box, 28);
  // --
  spinbox2 = lv_spinbox_create(parent);
  lv_obj_add_style(spinbox2, &style_sp_box, 0);
  lv_spinbox_set_range(spinbox2, 0, 9999);
  lv_spinbox_set_digit_format(spinbox2, 4, 0);
  lv_spinbox_set_pos(spinbox2, 1);
  lv_spinbox_step_prev(spinbox2);
  // lv_obj_set_height(spinbox2, 76);
  lv_obj_set_width(spinbox2, 160);
  // lv_obj_center(spinbox2);
  // lv_obj_align(spinbox2, LV_ALIGN_CENTER, -80, 80); // force: 100
  lv_obj_align_to(spinbox2, parent, LV_ALIGN_CENTER, pos_x, pos_y);
  // --
  lv_style_init(&style_btn);
  lv_style_set_border_width(&style_btn, 4);
  lv_style_set_border_color(&style_btn, lv_palette_main(LV_PALETTE_ORANGE));
  lv_style_set_text_font(&style_btn, &arial_20);
  // --
  lv_coord_t h = lv_obj_get_height(spinbox2) - 12;
  lv_style_set_radius(&style_btn, h/4);
  // --
  lv_obj_t * btn3 = lv_btn_create(parent);
  lv_obj_set_size(btn3, h, h+14);
  lv_obj_align_to(btn3, spinbox2, LV_ALIGN_OUT_RIGHT_MID, 4, 0);
  lv_obj_set_style_bg_img_src(btn3, LV_SYMBOL_PLUS, 0);
  lv_obj_add_style(btn3, &style_btn, 0);
  lv_obj_add_event_cb(btn3, lv_spinbox3_increment_event_cb, LV_EVENT_ALL, NULL);
  // --
  btn3 = lv_btn_create(parent);
  lv_obj_set_size(btn3, h, h+14);
  lv_obj_align_to(btn3, spinbox2, LV_ALIGN_OUT_LEFT_MID, -4, 0);
  lv_obj_set_style_bg_img_src(btn3, LV_SYMBOL_MINUS, 0);
  lv_obj_add_style(btn3, &style_btn, 0);
  lv_obj_add_event_cb(btn3, lv_spinbox3_decrement_event_cb, LV_EVENT_ALL, NULL);
}

