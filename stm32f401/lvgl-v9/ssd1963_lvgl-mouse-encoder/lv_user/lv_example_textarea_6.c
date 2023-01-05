#include "../../lv_examples.h"

static lv_obj_t *ta1, *ta2; // = lv_textarea_create(parent);
static lv_obj_t * btnm; // = lv_btnmatrix_create(lv_scr_act());

static void textarea_event_handler1(lv_event_t * e)
{
  lv_obj_t * ta = lv_event_get_target(e);
  LV_LOG_USER("Enter was pressed. The current text is: %s", lv_textarea_get_text(ta));
}

static void textarea_event_handler2(lv_event_t * e)
{
  lv_obj_t * ta = lv_event_get_target(e);
  LV_LOG_USER("Enter was pressed. The current text is: %s", lv_textarea_get_text(ta));
}

static void btnm_event_handler(lv_event_t * e)
{
  lv_obj_t * obj = lv_event_get_target(e);
  lv_obj_t * ta = lv_event_get_user_data(e);
  const char * txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));

  if(strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) lv_textarea_del_char(ta);
  else if(strcmp(txt, LV_SYMBOL_NEW_LINE) == 0) lv_event_send(ta, LV_EVENT_READY, NULL);
  else lv_textarea_add_text(ta, txt);
}

void lv_example_textarea_6(lv_obj_t* parent)
{
  textarea_6(parent);
  btnmatrix6(parent);
}

void textarea_6(lv_obj_t* parent)
{
  /*set style*/
  static lv_style_t style_ta;
  lv_style_init(&style_ta);

  lv_style_set_transform_width(&style_ta, -2);
  lv_style_set_transform_height(&style_ta, -10);
  lv_style_set_radius(&style_ta, 8);

  lv_style_set_bg_opa(&style_ta, 64); /*opacity 50% = 128*/
  lv_style_set_bg_color(&style_ta, lv_palette_darken(LV_PALETTE_YELLOW, 4));
  lv_style_set_border_width(&style_ta, 2);
  lv_style_set_border_color(&style_ta, lv_palette_main(LV_PALETTE_BLUE));
  lv_style_set_pad_all(&style_ta, 8); /*To make the indicator smaller*/

  lv_style_set_text_font(&style_ta, &arial_14);
  lv_style_set_text_color(&style_ta, lv_palette_lighten(LV_PALETTE_PINK,4));
  lv_style_set_text_letter_space(&style_ta, 8);
  lv_style_set_text_line_space(&style_ta, 2);
  /*lv_style_set_text_decor(&style_ta, LV_TEXT_DECOR_UNDERLINE);*/

  // lv_obj_t * ta1; // = lv_textarea_create(parent);
  if(parent) ta1 = lv_textarea_create(parent);
  else ta1 = lv_textarea_create(lv_scr_act());
  lv_obj_add_style(ta1, &style_ta, 0);
  lv_obj_set_style_text_font(ta1, &arial_14, 0);
  lv_obj_align(ta1, LV_ALIGN_TOP_MID, +70, -16);
  lv_obj_set_size(ta1, 140, 56);
  lv_obj_add_event_cb(ta1, textarea_event_handler1, LV_EVENT_READY, ta1);


  if(parent) ta2 = lv_textarea_create(parent);
  else ta2 = lv_textarea_create(lv_scr_act());
  lv_obj_add_style(ta2, &style_ta, 0);
  lv_obj_set_style_text_font(ta2, &arial_14, 0);
  lv_obj_align(ta2, LV_ALIGN_TOP_MID, -70, -16);
  lv_obj_set_size(ta2, 140, 56);
  lv_obj_add_event_cb(ta2, textarea_event_handler2, LV_EVENT_READY, ta2);
}

void btnmatrix6(lv_obj_t* parent)
{
  static lv_style_t style_btns;
  lv_style_init(&style_btns);

  lv_style_set_transform_width(&style_btns, -2);
  lv_style_set_transform_height(&style_btns, -2);
  lv_style_set_radius(&style_btns, 8);

  lv_style_set_bg_opa(&style_btns, 128); /*opacity 50% = 128*/
  lv_style_set_bg_color(&style_btns, lv_palette_darken(LV_PALETTE_YELLOW, 4));
  lv_style_set_border_width(&style_btns, 4);
  lv_style_set_border_color(&style_btns, lv_palette_darken(LV_PALETTE_GREEN, 2));

  lv_style_set_text_font(&style_btns, &arial_14);
  lv_style_set_text_color(&style_btns, lv_palette_lighten(LV_PALETTE_PINK,4));
  lv_style_set_text_letter_space(&style_btns, 8);
  lv_style_set_text_line_space(&style_btns, 2);
  /*lv_style_set_text_decor(&style_btns, LV_TEXT_DECOR_UNDERLINE);*/

  /*create space betwen objects*/
  /**
  lv_style_set_pad_left(&style_btns, 16);
  lv_style_set_pad_right(&style_btns, 8);
  lv_style_set_pad_top(&style_btns, 16);
  lv_style_set_pad_bottom(&style_btns, 8);
  lv_style_set_pad_all(&style_btns, 8); **/

  static const char * btnm_map[] =
  {
    "1", "2", "3", "4", "5", "\n",
    "6", "7", "8", "9", "0", "\n",
    LV_SYMBOL_BACKSPACE, LV_SYMBOL_NEW_LINE, ""
  };

  // lv_obj_t * btnm; // = lv_btnmatrix_create(lv_scr_act());
  if(parent) btnm = lv_keyboard_create(parent);
  else btnm = lv_keyboard_create(lv_scr_act());
  // if(parent) btnm = lv_btnmatrix_create(parent);
  // else btnm = lv_btnmatrix_create(lv_scr_act());
  // lv_obj_set_style_text_font(btnm, &arial_14, 0);
  lv_obj_set_size(btnm, 280, 140);

  /*To make spacess betwen buttons*/
  lv_obj_set_style_pad_top(btnm, 16, 0);
  lv_obj_set_style_pad_bottom(btnm, 8, 0);
  lv_obj_set_style_pad_left(btnm, 16, 0);
  lv_obj_set_style_pad_right(btnm, 8, 0);
  // lv_obj_set_style_pad_row(btnm, 12, 0);
  // lv_obj_set_style_pad_column(btnm, 12, 0);

  lv_obj_align(btnm, LV_ALIGN_BOTTOM_MID, 0, 0);

  lv_obj_add_event_cb(btnm, btnm_event_handler, LV_EVENT_VALUE_CHANGED, ta1);
  lv_obj_add_event_cb(btnm, btnm_event_handler, LV_EVENT_VALUE_CHANGED, ta2);
  lv_obj_clear_flag(btnm, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
  lv_btnmatrix_set_map(btnm, btnm_map);

  lv_obj_add_style(btnm, &style_btns, 0);
}

