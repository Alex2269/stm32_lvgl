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

void draw_rect_for_sliders(lv_obj_t* parent)
{
  /* simple rect line */
  static lv_style_t style1;
  static lv_style_t style2;

  lv_style_init(&style1);
  lv_style_init(&style2);

  lv_style_set_line_color(&style1, lv_palette_main(LV_PALETTE_CYAN));
  lv_style_set_line_color(&style2, lv_palette_darken(LV_PALETTE_LIME,2));
  lv_style_set_line_rounded(&style1, true);
  lv_style_set_line_rounded(&style2, true);

  /*Create an object with the new style*/
  lv_obj_t * obj1 = lv_line_create(parent);
  lv_obj_t * obj2 = lv_line_create(parent);

  lv_style_set_line_width(&style1, 2);
  lv_style_set_line_width(&style2, 1);
  lv_obj_add_style(obj1, &style1, 0);
  lv_obj_add_style(obj2, &style2, 0);

  static lv_point_t p[] = {{30, 80}, {260, 80}, {260, 340}, {30, 340}, {30, 80}};
  static lv_point_t p2[] = {{430, 80}, {660, 80}, {660, 340}, {430, 340}, {430, 80}};

  lv_line_set_points(obj1, p, 5);
  lv_line_set_points(obj2, p2, 5);

  // lv_obj_center(obj);
}

void sliders_horisontal(lv_obj_t* parent)
{
  // knob only visual element and does not have touch size
  // create pointers for sliders
  slider1 = lv_slider_create(parent);
  slider2 = lv_slider_create(parent);
  slider3 = lv_slider_create(parent);
  slider4 = lv_slider_create(parent);

  draw_rect_for_sliders(parent);

  lv_slider_set_range(slider1, 1, 20);
  lv_slider_set_range(slider2, 1, 20);
  lv_slider_set_range(slider3, 0, 12);

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
  lv_obj_set_style_pad_all(slider4, 6, LV_PART_KNOB);

  // set slider size and direction
  lv_obj_set_size(slider1, LV_PCT(26), LV_PCT(1));
  lv_obj_set_size(slider2, LV_PCT(26), LV_PCT(1));
  lv_obj_set_size(slider3, LV_PCT(26), LV_PCT(1));
  lv_obj_set_size(slider4, LV_PCT(26), LV_PCT(1));

  // align
  lv_obj_align(slider1, LV_ALIGN_LEFT_MID, 45, -90);
  lv_obj_align(slider2, LV_ALIGN_LEFT_MID, 45, -30);
  lv_obj_align(slider3, LV_ALIGN_LEFT_MID, 45, +30);
  lv_obj_align(slider4, LV_ALIGN_LEFT_MID, 45, +90);

  // callback functions
  lv_obj_add_event_cb(slider1, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(slider2, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(slider3, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(slider4, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  // mode slider4
  lv_slider_set_range(slider4, 65, 85);
  lv_slider_set_mode(slider4, LV_SLIDER_MODE_RANGE);
  lv_slider_set_value(slider4, 80, LV_ANIM_OFF);
  lv_slider_set_left_value(slider4, 70, LV_ANIM_OFF);

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
  char buf[60];
  lv_obj_t * slider = lv_event_get_target(e);

  value = lv_slider_get_value(slider);
  left_value = lv_slider_get_left_value(slider);

  if(slider1 == slider)
  {
    lv_obj_set_style_text_font(label1, &arial_14, 0);
    lv_obj_set_style_text_letter_space(label1, 2, 0);
    lv_obj_set_style_text_color(label1, lv_palette_lighten(LV_PALETTE_CYAN,2), 0);

    lv_snprintf(buf, sizeof(buf), "\xEF\x80\x93 ACTIVE %dms", value);
    printf("slider_h_1 %d ms\n", value);
    lv_label_set_text(label1, buf);
    lv_obj_align_to(label1, slider, LV_ALIGN_LEFT_MID, 220, 0);
  }

  if(slider2 == slider)
  {
    lv_obj_set_style_text_font(label2, &arial_14, 0);
    lv_obj_set_style_text_letter_space(label2, 2, 0);
    lv_obj_set_style_text_color(label2, lv_palette_lighten(LV_PALETTE_LIME,2), 0);

    lv_snprintf(buf, sizeof(buf), "\xEF\x80\x93 PASSIVE %dms", value);
    printf("slider_h_2 %d ms\n", value);
    lv_label_set_text(label2, buf);
    lv_obj_align_to(label2, slider, LV_ALIGN_LEFT_MID, 220, 0);
  }

  if(slider3 == slider)
  {
    lv_obj_set_style_text_font(label3, &arial_14, 0);
    lv_obj_set_style_text_letter_space(label3, 2, 0);
    lv_obj_set_style_text_color(label3, lv_palette_darken(LV_PALETTE_ORANGE,2), 0);

    lv_snprintf(buf, sizeof(buf), "\xEF\x80\x93 WORK %dsec", value * 5);
    printf("slider_h_3 %d sec\n", value * 5);
    lv_label_set_text(label3, buf);
    lv_obj_align_to(label3, slider, LV_ALIGN_LEFT_MID, 220, 0);
  }

  if(slider4 == slider)
  {
    lv_obj_set_style_text_font(label4, &arial_14, 0);
    lv_obj_set_style_text_letter_space(label4, 2, 0);
    lv_obj_set_style_text_color(label4, lv_palette_lighten(LV_PALETTE_AMBER,2), 0);

    lv_snprintf(buf, sizeof(buf), "\xEF\x80\x93 min%d max%d", left_value, value);
    printf("%d%%\n%d%%", value, left_value);
    lv_label_set_text(label4, buf);
    lv_obj_align_to(label4, slider, LV_ALIGN_LEFT_MID, 220, 0);
  }
}

