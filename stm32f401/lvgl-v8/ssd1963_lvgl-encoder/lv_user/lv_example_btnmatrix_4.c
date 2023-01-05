#include "../../lv_examples.h"

void lv_example_label_for_bm(lv_obj_t* parent);

lv_obj_t * ltr_label;
lv_obj_t * cz_label;
char buf[8];


static void event_handler(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED)
  {
    uint32_t id = lv_btnmatrix_get_selected_btn(obj);
    const char * txt = lv_btnmatrix_get_btn_text(obj, id);
    LV_LOG_USER("%s was pressed\n", txt);

    // lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
    // printf("%d%%\n", (int)lv_slider_get_value(slider));

    lv_label_set_text(ltr_label, txt);
    lv_label_set_text(cz_label, txt);
  }
}

static const char * btnm_map[] =
{
  "1", "2", "3", "4", "5", "\n", "6", "7", "8", "9", "0", "\n", "Act1", "Act2", ""
};

void lv_example_btnmatrix_4(lv_obj_t* parent)
{
  /*Initialize the styles*/
  static lv_style_t style_btn;
  lv_style_init(&style_btn);
  lv_style_set_bg_color(&style_btn, lv_palette_main(LV_PALETTE_YELLOW));
  lv_style_set_border_color(&style_btn, lv_palette_darken(LV_PALETTE_GREEN, 2));
  lv_style_set_bg_opa(&style_btn, 255);
  lv_style_set_border_width(&style_btn, 4);
  lv_style_set_text_font(&style_btn, &arial_20);
  // --
  lv_obj_t * btnm1;
  if(parent)
    btnm1 = lv_btnmatrix_create(parent);
  else
    btnm1 = lv_btnmatrix_create(lv_scr_act());

  lv_obj_add_style(btnm1, &style_btn, 0);
  lv_obj_set_style_radius(btnm1, 24, 0);
  lv_btnmatrix_set_map(btnm1, btnm_map);
  // --
  lv_btnmatrix_set_btn_ctrl(btnm1, 10, LV_BTNMATRIX_CTRL_CHECKABLE);
  lv_btnmatrix_set_btn_ctrl(btnm1, 11, LV_BTNMATRIX_CTRL_CHECKED);
  // --
  lv_obj_set_style_pad_row(btnm1, 8, LV_PART_MAIN);
  lv_obj_set_style_pad_column(btnm1, 8, LV_PART_MAIN);
  // --
  lv_obj_set_width(btnm1, 280);
  lv_obj_set_height(btnm1, 110);
  // --
  lv_btnmatrix_set_btn_width(btnm1, 10, 2);
  lv_btnmatrix_set_btn_width(btnm1, 11, 3);
  // --
  lv_obj_align(btnm1, LV_ALIGN_CENTER, 0, 30);
  lv_obj_add_event_cb(btnm1, event_handler, LV_EVENT_ALL, NULL);
  lv_example_label_for_bm(parent);
}

void lv_example_label_for_bm(lv_obj_t* parent)
{
  ltr_label = lv_label_create(parent);
  lv_label_set_text(ltr_label, "mode1");
  lv_obj_set_style_text_font(ltr_label, &arial_20, 0);
  lv_obj_set_width(ltr_label, 80);
  lv_obj_align(ltr_label, LV_ALIGN_CENTER, -60, -60);

  cz_label = lv_label_create(parent);
  lv_label_set_text(cz_label, "mode2");
  lv_obj_set_style_text_font(cz_label, &arial_20, 0);
  lv_obj_set_width(cz_label, 80);
  lv_obj_align(cz_label, LV_ALIGN_CENTER, +60, -60);
}
