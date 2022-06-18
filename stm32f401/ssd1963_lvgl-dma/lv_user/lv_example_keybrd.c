#include "../../lv_examples.h"

static void textarea_event_handler(lv_event_t * e)
{
  lv_obj_t * ta = lv_event_get_target(e);
  LV_LOG_USER("Enter was pressed. The current text is: %s", lv_textarea_get_text(ta));
}

static void ta_event_cb(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * ta = lv_event_get_target(e);
  lv_obj_t * keybrd = lv_event_get_user_data(e);

  if(code == LV_EVENT_FOCUSED) {
    lv_keyboard_set_textarea(keybrd, ta);
    lv_obj_clear_flag(keybrd, LV_OBJ_FLAG_HIDDEN);
  }

  if(code == LV_EVENT_DEFOCUSED) {
    lv_keyboard_set_textarea(keybrd, NULL);
    lv_obj_add_flag(keybrd, LV_OBJ_FLAG_HIDDEN);
  }
}

static void lv_keyboard_event_cb(lv_event_t * e)
{
  lv_obj_t * obj = lv_event_get_target(e);
  lv_keyboard_t * keyboard = (lv_keyboard_t *)obj;

  const char * txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));
  if(strcmp(txt, LV_SYMBOL_CLOSE) == 0)
  {
    lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
  }
}

void lv_example_keybrd(lv_obj_t* parent)
{
  static const char * btnm_map[] =
  {
    "1", "2", "3", "4", "5", LV_SYMBOL_BACKSPACE, "\n",
    "6", "7", "8", "9", "0", LV_SYMBOL_CLOSE, ""
  };

  /*Initialize the styles*/
  static lv_style_t style_btns;
  lv_style_init(&style_btns);

  lv_style_set_transform_width(&style_btns, -2);
  lv_style_set_transform_height(&style_btns, -2);
  lv_style_set_radius(&style_btns, 8);

  lv_style_set_bg_opa(&style_btns, 128); /*opacity 50% = 128*/
  lv_style_set_bg_color(&style_btns, lv_palette_darken(LV_PALETTE_YELLOW, 4));
  lv_style_set_border_width(&style_btns, 4);
  lv_style_set_border_color(&style_btns, lv_palette_darken(LV_PALETTE_GREEN, 2));

  lv_style_set_text_font(&style_btns, &lv_font_montserrat_28);
  lv_style_set_text_color(&style_btns, lv_palette_lighten(LV_PALETTE_PINK,4));
  lv_style_set_text_letter_space(&style_btns, 8);
  lv_style_set_text_line_space(&style_btns, 2);
  /*lv_style_set_text_decor(&style_btns, LV_TEXT_DECOR_UNDERLINE);*/

  /*create space betwen objects*/
  lv_style_set_pad_left(&style_btns, 4);
  lv_style_set_pad_right(&style_btns, -4);
  lv_style_set_pad_top(&style_btns, 4);
  lv_style_set_pad_bottom(&style_btns, -4);
  // lv_style_set_pad_all(&style_btns, 8);

  lv_obj_t * button_matrix; // = lv_keyboard_create(lv_scr_act());
  if(parent)
    button_matrix = lv_keyboard_create(parent); // lv_btnmatrix_create(parent);
  else
    button_matrix = lv_keyboard_create(lv_scr_act()); // lv_btnmatrix_create(lv_scr_act());

  // lv_obj_set_style_text_font(button_matrix, &lv_font_montserrat_20, 0);
  lv_style_set_text_font(&style_btns, &lv_font_montserrat_28);
  lv_obj_add_style(button_matrix, &style_btns, 0);

  lv_obj_set_size(button_matrix, 300, 120); // set size

  /*To make spacess betwen buttons*/
  /** lv_obj_set_style_pad_top(button_matrix, 16, 0);
  lv_obj_set_style_pad_bottom(button_matrix, 8, 0);
  lv_obj_set_style_pad_left(button_matrix, 16, 0);
  lv_obj_set_style_pad_right(button_matrix, 8, 0);
  lv_obj_set_style_pad_row(button_matrix, 12, 0);
  lv_obj_set_style_pad_column(button_matrix, 12, 0); **/

  lv_obj_align(button_matrix, LV_ALIGN_BOTTOM_MID, 0, 0);

  lv_obj_clear_flag(button_matrix, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
  lv_btnmatrix_set_map(button_matrix, btnm_map);
  lv_obj_add_event_cb(button_matrix, lv_keyboard_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  // -----style text area--------
  /*set style*/
  static lv_style_t style_ta;
  lv_style_init(&style_ta);

  lv_style_set_transform_width(&style_ta, -2);
  lv_style_set_transform_height(&style_ta, -2);
  lv_style_set_radius(&style_ta, 8);

  lv_style_set_bg_opa(&style_ta, 64); /*opacity 50% = 128*/
  lv_style_set_bg_color(&style_ta, lv_palette_darken(LV_PALETTE_YELLOW, 4));
  lv_style_set_border_width(&style_ta, 2);
  lv_style_set_border_color(&style_ta, lv_palette_main(LV_PALETTE_BLUE));
  lv_style_set_pad_all(&style_ta, 8); /*To make the indicator smaller*/

  lv_style_set_text_font(&style_ta, &lv_font_montserrat_10);
  lv_style_set_text_color(&style_ta, lv_palette_lighten(LV_PALETTE_PINK,4));
  lv_style_set_text_letter_space(&style_ta, 8);
  lv_style_set_text_line_space(&style_ta, 2);
  /*lv_style_set_text_decor(&style_ta, LV_TEXT_DECOR_UNDERLINE);*/
  // ---style text area--end---
  /*Create a text area. The keyboard will write here*/

  lv_obj_t * ta;

  // left top
  ta = lv_textarea_create(parent);
  lv_obj_add_style(ta, &style_ta, 0);
  // lv_style_set_text_font(&style_..., &lv_font_montserrat_28);
  lv_obj_set_style_text_font(ta, &lv_font_montserrat_10, 0);
  lv_obj_align(ta, LV_ALIGN_TOP_LEFT, 10, -8);
  lv_textarea_set_placeholder_text(ta, "FREQ");
  lv_obj_set_size(ta, 130, 34);
  lv_keyboard_set_textarea(button_matrix, ta);
  lv_obj_add_event_cb(ta, textarea_event_handler, LV_EVENT_VALUE_CHANGED, ta);
  lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, button_matrix);

  // left bottom
  ta = lv_textarea_create(parent);
  lv_obj_add_style(ta, &style_ta, 0);
  // lv_style_set_text_font(&style_..., &lv_font_montserrat_28);
  lv_obj_set_style_text_font(ta, &lv_font_montserrat_10, 0);
  lv_obj_align(ta, LV_ALIGN_TOP_LEFT, 10, +20);
  lv_textarea_set_placeholder_text(ta, "PERI");
  lv_obj_set_size(ta, 130, 34);
  lv_keyboard_set_textarea(button_matrix, ta);
  lv_obj_add_event_cb(ta, textarea_event_handler, LV_EVENT_VALUE_CHANGED, ta);
  lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, button_matrix);

  // right top
  ta = lv_textarea_create(parent);
  lv_obj_add_style(ta, &style_ta, 0);
  // lv_style_set_text_font(&style_..., &lv_font_montserrat_28);
  lv_obj_set_style_text_font(ta, &lv_font_montserrat_10, 0);
  lv_obj_align(ta, LV_ALIGN_TOP_RIGHT, -10, -8);
  lv_textarea_set_placeholder_text(ta, "COUNT");
  lv_obj_set_size(ta, 130, 34);
  lv_keyboard_set_textarea(button_matrix, ta);
  lv_obj_add_event_cb(ta, textarea_event_handler, LV_EVENT_VALUE_CHANGED, ta);
  lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, button_matrix);

  // right bottom
  ta = lv_textarea_create(parent);
  lv_obj_add_style(ta, &style_ta, 0);
  // lv_style_set_text_font(&style_..., &lv_font_montserrat_28);
  lv_obj_set_style_text_font(ta, &lv_font_montserrat_10, 0);
  lv_obj_align(ta, LV_ALIGN_TOP_RIGHT, -10, +20);
  lv_textarea_set_placeholder_text(ta, "TIME");
  lv_obj_set_size(ta, 130, 34);
  lv_keyboard_set_textarea(button_matrix, ta);
  lv_obj_add_event_cb(ta, textarea_event_handler, LV_EVENT_VALUE_CHANGED, ta);
  lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, button_matrix);

}
