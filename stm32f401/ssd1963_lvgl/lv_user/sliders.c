#include "lvgl/lvgl.h"
#include "sliders.h"

static lv_obj_t * slider1_label;
static lv_obj_t * slider2_label;
static lv_obj_t * slider3_label;
static lv_obj_t * slider4_label;

static void slider1_event_cb(lv_event_t * e);
static void slider2_event_cb(lv_event_t * e);
static void slider3_event_cb(lv_event_t * e);
static void slider4_event_cb(lv_event_t * e);

void sliders(lv_obj_t* parent)
{
  // knob only visual element and does not have touch size
  // create pointers for sliders
  lv_obj_t * slider1 = lv_slider_create(parent);
  lv_obj_t * slider2 = lv_slider_create(parent);
  lv_obj_t * slider3 = lv_slider_create(parent);
  lv_obj_t * slider4 = lv_slider_create(parent);

  // set style sliders
  static lv_style_t style_sliders;
  lv_style_init(&style_sliders);

  lv_style_set_transform_width(&style_sliders, -4);
  lv_style_set_transform_height(&style_sliders, 0);
  lv_style_set_bg_color(&style_sliders, lv_palette_lighten(LV_PALETTE_LIME,4));

  lv_obj_add_style(slider1, &style_sliders, 0);
  lv_obj_add_style(slider2, &style_sliders, 0);
  lv_obj_add_style(slider3, &style_sliders, 0);
  lv_obj_add_style(slider4, &style_sliders, 0);

  // knob size
  lv_obj_set_style_pad_all(slider1, 1, LV_PART_KNOB);
  lv_obj_set_style_pad_all(slider2, 1, LV_PART_KNOB);
  lv_obj_set_style_pad_all(slider3, 1, LV_PART_KNOB);
  lv_obj_set_style_pad_all(slider4, 1, LV_PART_KNOB);

  // set slider size and direction
  lv_obj_set_size(slider1, LV_PCT(6), LV_PCT(80));
  lv_obj_set_size(slider2, LV_PCT(6), LV_PCT(80));
  lv_obj_set_size(slider3, LV_PCT(6), LV_PCT(80));
  lv_obj_set_size(slider4, LV_PCT(6), LV_PCT(80));

  // align
  lv_obj_align(slider1, LV_ALIGN_CENTER,  -90, 0);
  lv_obj_align(slider2, LV_ALIGN_CENTER,  -30, 0);
  lv_obj_align(slider3, LV_ALIGN_CENTER,  +30, 0);
  lv_obj_align(slider4, LV_ALIGN_CENTER,  +90, 0);

  // callback functions
  lv_obj_add_event_cb(slider1, slider1_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(slider2, slider2_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(slider3, slider3_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(slider4, slider4_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  // mode slider4
  lv_slider_set_mode(slider4, LV_SLIDER_MODE_RANGE);
  lv_slider_set_value(slider4, 70, LV_ANIM_OFF);
  lv_slider_set_left_value(slider4, 20, LV_ANIM_OFF);

  // create a label below the slider
  slider1_label = lv_label_create(parent);
  slider2_label = lv_label_create(parent);
  slider3_label = lv_label_create(parent);
  slider4_label = lv_label_create(parent);

  // set style labels
  static lv_style_t style_labels;
  lv_style_init(&style_labels);
  lv_style_set_text_color(&style_labels, lv_palette_main(LV_PALETTE_YELLOW));
  lv_style_set_text_font(&style_labels, &lv_font_montserrat_24);
  lv_style_set_text_letter_space( &style_labels, +2);
  lv_obj_add_style(slider1_label, &style_labels,  0);
  lv_obj_add_style(slider2_label, &style_labels,  0);
  lv_obj_add_style(slider3_label, &style_labels,  0);
  lv_obj_set_style_text_font(slider4_label, &lv_font_montserrat_22, 0);
  lv_obj_add_style(slider4_label, &style_labels,  0);

  // set text labels
  lv_label_set_text(slider1_label, "0%");
  lv_label_set_text(slider2_label, "0%");
  lv_label_set_text(slider3_label, "0%");
  lv_label_set_text(slider4_label, "70%\n\n20%");

  // align label to slider
  // lv_obj_align_to(slider1_label, slider1, LV_ALIGN_CENTER,  0, 0);
  // lv_obj_align_to(slider2_label, slider2, LV_ALIGN_CENTER,  0, 0);
  // lv_obj_align_to(slider3_label, slider3, LV_ALIGN_CENTER,  0, 0);
  // lv_obj_align_to(slider4_label, slider4, LV_ALIGN_TOP_MID, 0, 0);

  // lv_obj_align(slider1, LV_ALIGN_LEFT_MID, LV_HOR_RES / 2, 0);

  lv_obj_align_to(slider1_label, slider1, LV_ALIGN_CENTER, 0, 55);
  lv_obj_align_to(slider2_label, slider2, LV_ALIGN_CENTER, 0, 55);
  lv_obj_align_to(slider3_label, slider3, LV_ALIGN_CENTER, 0, 55);
  lv_obj_align_to(slider4_label, slider4, LV_ALIGN_CENTER, 0, 10);
}

static void slider1_event_cb(lv_event_t * e)
{
  char buf[8];
  static int value;
  lv_obj_t * slider = lv_event_get_target(e);
  value = lv_slider_get_value(slider);

  lv_snprintf(buf, sizeof(buf), "%d%%", value);
  LV_LOG_USER("s3: %d", value);
  lv_label_set_text(slider1_label, buf);
  lv_obj_align_to(slider1_label, slider, LV_ALIGN_CENTER, 0, 255-(value+200));
}

static void slider2_event_cb(lv_event_t * e)
{
  char buf[8];
  static int value;
  lv_obj_t * slider = lv_event_get_target(e);
  value = lv_slider_get_value(slider);

  lv_snprintf(buf, sizeof(buf), "%d%%", value);
  LV_LOG_USER("s3: %d", value);
  lv_label_set_text(slider2_label, buf);
  lv_obj_align_to(slider2_label, slider, LV_ALIGN_CENTER, 0, 255-(value+200));
}

static void slider3_event_cb(lv_event_t * e)
{
  char buf[8];
  static int value;
  lv_obj_t * slider = lv_event_get_target(e);
  value = lv_slider_get_value(slider);

  lv_snprintf(buf, sizeof(buf), "%d%%", value);
  LV_LOG_USER("s3: %d", value);
  lv_label_set_text(slider3_label, buf);
  lv_obj_align_to(slider3_label, slider, LV_ALIGN_CENTER, 0, 255-(value+200));
}

static void slider4_event_cb(lv_event_t * e)
{
  static int value, left_value;
  char buf[16];
  lv_obj_t * slider = lv_event_get_target(e);

  if(value != lv_slider_get_value(slider))
  {
    LV_LOG_USER("s4 r_value: %d", value);
  }

  if(left_value != lv_slider_get_left_value(slider))
  {
    LV_LOG_USER("s4 l_value: %d", left_value);
  }

  value = lv_slider_get_value(slider);
  left_value = lv_slider_get_left_value(slider);
  lv_snprintf(buf, sizeof(buf), "%d%%\n\n%d%%", value, left_value);
  lv_label_set_text(slider4_label, buf);
  lv_obj_align_to(slider4_label, slider, LV_ALIGN_CENTER, 0, 255-((left_value+value) / 2 + 200));
}

