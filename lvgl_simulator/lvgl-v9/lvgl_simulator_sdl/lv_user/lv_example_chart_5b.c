#include "../../lv_examples.h"

#if LV_USE_CHART && LV_USE_SLIDER && LV_BUILD_EXAMPLES

#define sinus_points 1023 // 127, 255, 511, etc.
#define sinus_value 128 // value: 8, 16, 32 etc.

float PI = 3.14159;

int16_t sinus_table_a[sinus_points];
int16_t sinus_table_b[sinus_points];
int16_t sinus_table_c[sinus_points];

void sinus_init(uint16_t i)
{
  sinus_table_c[(i+(sinus_points/3*1)) & (sinus_points)]=
  sinus_table_b[(i+(sinus_points/3*2)) & (sinus_points)]=
  sinus_table_a[(i+(sinus_points/3*3)) & (sinus_points)]=
  ((sin((float) i*(2*PI/sinus_value)))*(sinus_value/2));
}

static lv_obj_t *label1, *label2, *label3, *label4, *label5, *label6, *label7;
static lv_obj_t *chart;
static lv_chart_series_t *series_1, *series_2, *series_3;
static lv_chart_cursor_t *cursor1, *cursor2, *cursor3;
static lv_obj_t *slider_multiplier_x, *slider_scrolling_x;
static lv_obj_t *slider_shift_data_x;

static lv_obj_t *slider_double;
static int16_t shift_data_x;
static int16_t scroll_x;
static int16_t multi_x;

static void sliders_cb(lv_event_t * e)
{
  lv_obj_t * obj = lv_event_get_target(e);
  int32_t v = lv_slider_get_value(obj);
  shift_data_x = v-256;
  scroll_x = v-256;
  multi_x = v-256;

  if(obj == slider_multiplier_x)
  {
    lv_chart_set_zoom_x(chart, v);
    lv_slider_set_value(slider_scrolling_x, v, 0);
    lv_obj_scroll_to_x(chart, scroll_x, 0);
  }

  if(obj == slider_scrolling_x)
  {
    lv_obj_scroll_to_x(chart, scroll_x, 0);
  }

  if(obj == slider_shift_data_x)
  {
    lv_chart_set_x_start_point(chart, series_1, shift_data_x);
    lv_chart_set_x_start_point(chart, series_2, shift_data_x);
    lv_chart_set_x_start_point(chart, series_3, shift_data_x);
    // lv_chart_set_cursor_point(chart, cursor3, series_3, shift_data_x*4);
  }

  lv_chart_refresh(chart);
}

static void sliders_cursors_user_cb(lv_event_t * e)
{
  lv_obj_t * obj = lv_event_get_target(e);

  int32_t value_r = lv_slider_get_value(obj);
  int32_t value_l = lv_slider_get_left_value(obj);
  lv_chart_set_cursor_point(chart, cursor1, series_1, value_l);
  lv_chart_set_cursor_point(chart, cursor2, series_2, value_r);
  // lv_chart_set_cursor_point(chart, cursor3, series_3, shift_data_x*4);

  char buf[16];

  if(slider_double == obj)
  {
    lv_obj_set_style_text_font(label1, &arial_14, 0);
    lv_obj_set_style_text_font(label2, &arial_14, 0);
    lv_obj_set_style_text_font(label3, &arial_14, 0);
    lv_obj_set_style_text_font(label4, &arial_14, 0);
    lv_obj_set_style_text_font(label5, &arial_14, 0);
    lv_obj_set_style_text_font(label6, &arial_14, 0);
    lv_obj_set_style_text_font(label7, &arial_14, 0);

    // lv_obj_set_style_text_letter_space(label4, 2, 0);
    lv_obj_set_style_text_color(label1, lv_palette_lighten(LV_PALETTE_LIME,2), 0);
    lv_obj_set_style_text_color(label2, lv_palette_lighten(LV_PALETTE_LIME,2), 0);
    lv_obj_set_style_text_color(label3, lv_palette_lighten(LV_PALETTE_PINK,2), 0);
    lv_obj_set_style_text_color(label4, lv_palette_darken(LV_PALETTE_AMBER,2), 0);
    lv_obj_set_style_text_color(label5, lv_palette_lighten(LV_PALETTE_RED,2), 0);
    lv_obj_set_style_text_color(label6, lv_palette_lighten(LV_PALETTE_RED,2), 0);
    lv_obj_set_style_text_color(label7, lv_palette_lighten(LV_PALETTE_GREEN,2), 0);

    lv_obj_align_to(label1, obj, LV_ALIGN_CENTER, -40, 2);
    lv_obj_align_to(label2, obj, LV_ALIGN_CENTER, -40, 25);
    lv_obj_align_to(label5, obj, LV_ALIGN_CENTER, +40, 2);
    lv_obj_align_to(label6, obj, LV_ALIGN_CENTER, +40, 25);
    lv_obj_align_to(label7, obj, LV_ALIGN_TOP_LEFT, (value_r+value_l)/2*0.6, 55);

    /* draw labels for cursors */
    lv_snprintf(buf, sizeof(buf), "%d", sinus_table_a[value_l]);
    lv_label_set_text(label1, buf);
    lv_snprintf(buf, sizeof(buf), "%d", value_l*100/256);
    lv_label_set_text(label2, buf);

    lv_snprintf(buf, sizeof(buf), "%d", sinus_table_b[value_r]);
    lv_label_set_text(label5, buf);
    lv_snprintf(buf, sizeof(buf), "%d", value_r*100/256);
    lv_label_set_text(label6, buf);

    // lv_obj_align_to(label4, obj, LV_ALIGN_CENTER, ((value_r+value_l) - 1024/* 64 wide text */), sinus_table_a[value_l]+160);

    lv_snprintf(buf, sizeof(buf), "%d", value_r-value_l);
    lv_label_set_text(label7, buf);
  }

  lv_chart_refresh(chart);
}

void lv_example_chart_5b(void)
{
  for (uint32_t i=0; i<sinus_points; i++)
  {
    sinus_init(i);
  }

  /* Create a chart */
  chart = lv_chart_create(lv_scr_act());
  cursor1 = lv_chart_add_cursor(chart, lv_palette_lighten(LV_PALETTE_YELLOW,1), LV_DIR_TOP | LV_DIR_BOTTOM);
  cursor2 = lv_chart_add_cursor(chart, lv_palette_darken(LV_PALETTE_RED,1), LV_DIR_TOP | LV_DIR_BOTTOM);
  cursor3 = lv_chart_add_cursor(chart, lv_palette_main(LV_PALETTE_ORANGE), LV_DIR_TOP | LV_DIR_BOTTOM);

  lv_obj_set_size(chart, LV_PCT(100)-20, LV_PCT(100)-20);
  lv_obj_align(chart, LV_ALIGN_CENTER, 10, -20);
  lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, -250, 250);
  lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_X, 8, 4, 11, 2, true, 10);
  lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y, 8, 4, 10, 2, true, 60);

  series_1 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_LIME), LV_CHART_AXIS_PRIMARY_Y);
  series_2 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
  series_3 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);

  /* Do not display points on the data */
  lv_obj_set_style_size(chart, 0, 0, LV_PART_INDICATOR);
  lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_SHIFT /* LV_CHART_UPDATE_MODE_CIRCULAR */);
  // lv_obj_add_event_cb(chart, draw_grid_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
  // lv_obj_add_event_cb(chart, draw_back_color_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
  // lv_obj_add_event_cb(chart, show_cursor_pionts_cb, LV_EVENT_ALL, NULL);
  lv_chart_set_div_line_count(chart, 7, 11);
  lv_chart_set_zoom_x(chart,256*1);

  uint32_t pcnt = sizeof(sinus_table_a) / sizeof(sinus_table_a[0]);
  lv_chart_set_point_count(chart, pcnt);
  lv_chart_set_ext_y_array(chart, series_1, (lv_coord_t *)sinus_table_a);
  lv_chart_set_ext_y_array(chart, series_2, (lv_coord_t *)sinus_table_b);
  lv_chart_set_ext_y_array(chart, series_3, (lv_coord_t *)sinus_table_c);

  slider_multiplier_x = lv_slider_create(lv_scr_act()); // slider multiplicative x
  lv_slider_set_range(slider_multiplier_x, 256, 256 * 2);
  lv_obj_add_event_cb(slider_multiplier_x, sliders_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_set_size(slider_multiplier_x, 640, 4);
  lv_obj_align_to(slider_multiplier_x, chart, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);

  slider_scrolling_x = lv_slider_create(lv_scr_act()); // scrolling x
  lv_slider_set_range(slider_scrolling_x, 256, 256 * 2);
  lv_obj_add_event_cb(slider_scrolling_x, sliders_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_set_size(slider_scrolling_x, 300, 2);
  lv_obj_align_to(slider_scrolling_x, chart, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

  slider_shift_data_x = lv_slider_create(lv_scr_act()); // shift x
  lv_slider_set_range(slider_shift_data_x, 256, 256 * 2);
  lv_obj_add_event_cb(slider_shift_data_x, sliders_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_set_size(slider_shift_data_x, 300, 2);
  lv_obj_align_to(slider_shift_data_x, chart, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, 10);

  label1 = lv_label_create(chart); lv_label_set_text(label1, "");
  label2 = lv_label_create(chart); lv_label_set_text(label2, "");
  label3 = lv_label_create(chart); lv_label_set_text(label3, "");
  label4 = lv_label_create(chart); lv_label_set_text(label4, "");
  label5 = lv_label_create(chart); lv_label_set_text(label5, "");
  label6 = lv_label_create(chart); lv_label_set_text(label6, "");
  label7 = lv_label_create(chart); lv_label_set_text(label7, "");

  slider_double = lv_slider_create(lv_scr_act()); // cur_one x
  lv_slider_set_range(slider_double, 0, 256 * 4);
  lv_obj_set_style_pad_all(slider_double, 4, LV_PART_KNOB);
  lv_obj_add_event_cb(slider_double, sliders_cursors_user_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_set_size(slider_double, 614, 1);
  // lv_obj_align(slider_double, LV_ALIGN_OUT_TOP_LEFT, 12, -4);
  lv_obj_align_to(slider_double, chart, LV_ALIGN_OUT_TOP_LEFT, 12, 10);

  lv_slider_set_mode(slider_double, LV_SLIDER_MODE_RANGE);
  lv_slider_set_value(slider_double, 256*4, LV_ANIM_OFF);
  lv_slider_set_left_value(slider_double, 0, LV_ANIM_OFF);
}

#endif

