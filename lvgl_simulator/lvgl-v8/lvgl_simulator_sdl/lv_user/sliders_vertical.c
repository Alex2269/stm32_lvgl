#include "lvgl/lvgl.h"
#include "sliders.h"

static lv_obj_t * label1;
static lv_obj_t * label2;
static lv_obj_t * label3;
static lv_obj_t * label4;

static lv_obj_t * slider1;
static lv_obj_t * slider2;
static lv_obj_t * slider3;
static lv_obj_t * slider4;

static void slider_event_cb(lv_event_t * e);

void sliders_vertical(lv_obj_t* parent)
{
  // knob only visual element and does not have touch size
  // create pointers for sliders
  slider1 = lv_slider_create(parent);
  slider2 = lv_slider_create(parent);
  slider3 = lv_slider_create(parent);
  slider4 = lv_slider_create(parent);

  // set style sliders
  static lv_style_t style_sliders;
  lv_style_init(&style_sliders);

  lv_style_set_transform_width(&style_sliders, 4);
  lv_style_set_transform_height(&style_sliders, 4);
  lv_style_set_bg_color(&style_sliders, lv_palette_darken(LV_PALETTE_BLUE,4));
  lv_style_set_bg_opa(&style_sliders, 250);

  lv_obj_add_style(slider1, &style_sliders, 0);
  lv_obj_add_style(slider2, &style_sliders, 0);
  lv_obj_add_style(slider3, &style_sliders, 0);
  lv_obj_add_style(slider4, &style_sliders, 0);

  // knob size
  lv_obj_set_style_pad_all(slider1, 8, LV_PART_KNOB);
  lv_obj_set_style_pad_all(slider2, 8, LV_PART_KNOB);
  lv_obj_set_style_pad_all(slider3, 8, LV_PART_KNOB);
  lv_obj_set_style_pad_all(slider4, 4, LV_PART_KNOB);

  // set slider size and direction
  lv_obj_set_size(slider1, LV_PCT(2), LV_PCT(80));
  lv_obj_set_size(slider2, LV_PCT(2), LV_PCT(80));
  lv_obj_set_size(slider3, LV_PCT(2), LV_PCT(80));
  lv_obj_set_size(slider4, LV_PCT(4), LV_PCT(80));

  // align
  lv_obj_align(slider1, LV_ALIGN_CENTER,  -90, 0);
  lv_obj_align(slider2, LV_ALIGN_CENTER,  -30, 0);
  lv_obj_align(slider3, LV_ALIGN_CENTER,  +30, 0);
  lv_obj_align(slider4, LV_ALIGN_CENTER,  +90, 0);

  // callback functions
  lv_obj_add_event_cb(slider1, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(slider2, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(slider3, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(slider4, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  // mode slider4
  lv_slider_set_mode(slider4, LV_SLIDER_MODE_RANGE);
  lv_slider_set_value(slider4, 70, LV_ANIM_OFF);
  lv_slider_set_left_value(slider4, 20, LV_ANIM_OFF);

  // create a label below the slider
  label1 = lv_label_create(parent); lv_label_set_text(label1, "");
  label2 = lv_label_create(parent); lv_label_set_text(label2, "");
  label3 = lv_label_create(parent); lv_label_set_text(label3, "");
  label4 = lv_label_create(parent); lv_label_set_text(label4, "");
}

static void slider_event_cb(lv_event_t * e)
{
  // static lv_obj_t * label;
  static int value, left_value;
  char buf[16];
  lv_obj_t * slider = lv_event_get_target(e);

  value = lv_slider_get_value(slider);
  left_value = lv_slider_get_left_value(slider);

  if(slider1 == slider)
  {
    lv_obj_set_style_text_font(label1, &arial_20, 0);
    lv_obj_set_style_text_letter_space(label1, 2, 0);
    lv_obj_set_style_text_color(label1, lv_palette_darken(LV_PALETTE_PURPLE,2), 0);

    lv_snprintf(buf, sizeof(buf), "%d%%\n", value);
    printf("slider1 %d%%\n", value);
    lv_label_set_text(label1, buf);
    lv_obj_align_to(label1, slider, LV_ALIGN_CENTER, 0, 255-(value+200));
  }

  if(slider2 == slider)
  {
    lv_obj_set_style_text_font(label2, &arial_20, 0);
    lv_obj_set_style_text_letter_space(label2, 2, 0);
    lv_obj_set_style_text_color(label2, lv_palette_darken(LV_PALETTE_LIME,2), 0);

    lv_snprintf(buf, sizeof(buf), "%d%%\n", value);
    printf("slider2 %d%%\n", value);
    lv_label_set_text(label2, buf);
    lv_obj_align_to(label2, slider, LV_ALIGN_CENTER, 0, 255-(value+200));
  }

  if(slider3 == slider)
  {
    lv_obj_set_style_text_font(label3, &arial_20, 0);
    lv_obj_set_style_text_letter_space(label3, 2, 0);
    lv_obj_set_style_text_color(label3, lv_palette_darken(LV_PALETTE_BROWN,2), 0);

    lv_snprintf(buf, sizeof(buf), "%d%%\n", value);
    printf("slider3 %d%%\n", value);
    lv_label_set_text(label3, buf);
    lv_obj_align_to(label3, slider, LV_ALIGN_CENTER, 0, 255-(value+200));
  }

  if(slider4 == slider)
  {
    lv_obj_set_style_text_font(label4, &arial_20, 0);
    lv_obj_set_style_text_letter_space(label4, 2, 0);
    lv_obj_set_style_text_color(label4, lv_palette_darken(LV_PALETTE_AMBER,2), 0);

    lv_snprintf(buf, sizeof(buf), "%d%%\n\n%d%%", value, left_value);
    printf("%d%%\n%d%%", value, left_value);
    lv_label_set_text(label4, buf);
    lv_obj_align_to(label4, slider, LV_ALIGN_CENTER, 0, 255-((100+value+left_value) / 2 + 150));
  }
}

