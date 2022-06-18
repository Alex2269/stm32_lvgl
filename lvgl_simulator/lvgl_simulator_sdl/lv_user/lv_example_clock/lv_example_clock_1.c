#include "lv_examples.h"
#include "lv_example_clock_1.h"

static void set_angle(void * img, int32_t v)
{
  lv_img_set_angle(img, v);
}

static void set_zoom(void * img, int32_t v)
{
  lv_img_set_zoom(img, v);
}

/* *
 * Show transformations (zoom and rotation) using a pivot point.
 */
void lv_example_clock_1(lv_obj_t* parent)
{
  // lv_obj_remove_style_all(parent);

  /* Initialize the styles */
  static lv_style_t style_bg;
  lv_style_init(&style_bg);
  lv_style_set_border_color(&style_bg, lv_palette_main(LV_PALETTE_RED));
  lv_style_set_border_width(&style_bg, 4);
  lv_style_set_pad_all(&style_bg, 8); /* To make the indicator smaller */
  lv_style_set_radius(&style_bg, 16);
  lv_obj_add_style(parent, &style_bg, 0);

  static lv_style_t style_fg;
  lv_style_init(&style_fg);
  lv_style_set_bg_opa(&style_fg, LV_OPA_COVER);
  lv_style_set_bg_color(&style_fg, lv_palette_darken(LV_PALETTE_CYAN, LV_PCT(4)));
  lv_style_set_radius(&style_fg, 16);
  lv_obj_add_style(parent, &style_fg, 0);

  #define siz_clk 400
  static lv_obj_t * meter;
  meter = lv_meter_create(parent);

  lv_obj_remove_style_all(meter);
  lv_obj_set_size(meter, siz_clk, siz_clk);
  lv_obj_center(meter);

  /* --- */
  /* set style */
  static lv_style_t style;
  lv_style_init(&style);

  lv_style_set_transform_width(&style, 2);
  lv_style_set_transform_height(&style, 2);
  lv_style_set_radius(&style, 90);

  lv_style_set_bg_opa(&style, 64); /* opacity 50% = 128 */
  lv_style_set_bg_color(&style, lv_palette_darken(LV_PALETTE_YELLOW, 4));
  lv_style_set_border_width(&style, 3);
  lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_BLUE));
  lv_style_set_pad_all(&style, 10);

  lv_style_set_text_color(&style, lv_palette_lighten(LV_PALETTE_PINK,4));
  lv_style_set_text_letter_space(&style, 2);
  lv_style_set_text_line_space(&style, 2);
  /* lv_style_set_text_decor(&style, LV_TEXT_DECOR_UNDERLINE); */
  lv_obj_add_style(meter, &style, 0);


  /* --- */
  /* 12 ticks in a 360 degrees range (the last and the first line overlaps) */
  lv_meter_scale_t * hairlines_12 = lv_meter_add_scale(meter);
  hairlines_12->r_mod += -4; /* increasing the radius for drawings hairlines */
  lv_meter_set_scale_ticks(meter, hairlines_12, 13, 6, 14, lv_color_hex(0xffff00));
  lv_meter_set_scale_range(meter, hairlines_12, 0, 12, 360, 270);

  /* 24 ticks in a 360 degrees range (the last and the first line overlaps) */
  // lv_meter_scale_t * hairlines_24 = lv_meter_add_scale(meter);
  // hairlines_24->r_mod += 24; /* increasing the radius for drawings hairlines */
  // lv_meter_set_scale_ticks(meter, hairlines_24, 25, 6, 6, lv_color_hex(0xff00ff));
  // lv_meter_set_scale_range(meter, hairlines_24, 0, 24, 360, 270);

  /* 61 ticks in a 360 degrees range (the last and the first line overlaps) */
  // lv_meter_scale_t * hairlines_60 = lv_meter_add_scale(meter);
  // hairlines_60->r_mod += 32; /* increasing the radius for drawings hairlines */
  // lv_meter_set_scale_ticks(meter, hairlines_60, 61, 4, 4, lv_color_hex(0xffffff));
  // lv_meter_set_scale_range(meter, hairlines_60, 0, 60, 360, 270);


  /* --- */
  // lv_meter_scale_t * scale = lv_meter_add_scale(meter);
  // lv_meter_indicator_t * indicator;

  // /* Add a blue arc to the start */
  // indicator = lv_meter_add_arc(meter, scale, 4, lv_palette_main(LV_PALETTE_BLUE), -4);
  // lv_meter_set_indicator_start_value(meter, indicator, 0);
  // lv_meter_set_indicator_end_value(meter, indicator, 100);

  // /* Add a red arc to the end */
  // indicator = lv_meter_add_arc(meter, scale, 4, lv_palette_main(LV_PALETTE_RED), -1);
  // lv_meter_set_indicator_start_value(meter, indicator, 50);
  // lv_meter_set_indicator_end_value(meter, indicator, 100);


  // /* Make the tick lines blue at the start of the scale */
  // indicator = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE), false, 0);
  // lv_meter_set_indicator_start_value(meter, indicator, 0);
  // lv_meter_set_indicator_end_value(meter, indicator, 20);

  // /* Make the tick lines gradient at the end of the scale */
  // indicator = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_GREY), lv_palette_main(LV_PALETTE_YELLOW), false, 0);
  // lv_meter_set_indicator_start_value(meter, indicator, 20);
  // lv_meter_set_indicator_end_value(meter, indicator, 80);

  // /* Make the tick lines red at the end of the scale */
  // indicator = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 0);
  // lv_meter_set_indicator_start_value(meter, indicator, 80);
  // lv_meter_set_indicator_end_value(meter, indicator, 100);


  /* --- */
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


  static lv_style_t style_n1;
  static lv_style_t style_n2;
  static lv_style_t style_n3;

  lv_style_init(&style_n1);
  lv_style_init(&style_n2);
  lv_style_init(&style_n3);

  lv_style_set_text_font(&style_n1, &arial_20);
  lv_style_set_text_color(&style_n1, lv_palette_lighten(LV_PALETTE_CYAN,4));
  lv_style_set_text_letter_space(&style_n1, 2);
  lv_style_set_text_line_space(&style_n1, 2);
  lv_obj_add_style(meter1, &style_n1, 0);

  lv_style_set_text_font(&style_n2, &arial_20);
  lv_style_set_text_color(&style_n2, lv_palette_lighten(LV_PALETTE_ORANGE,4));
  lv_style_set_text_letter_space(&style_n2, 2);
  lv_style_set_text_line_space(&style_n2, 2);
  lv_obj_add_style(meter2, &style_n2, 0);

  lv_style_set_text_font(&style_n3, &arial_20);
  lv_style_set_text_color(&style_n3, lv_palette_lighten(LV_PALETTE_LIME,4));
  lv_style_set_text_letter_space(&style_n3, 2);
  lv_style_set_text_line_space(&style_n3, 2);
  lv_obj_add_style(meter3, &style_n3, 0);


  /* create labels one */
  /* Create an other scale for the hours. It's only visual and contains only major ticks */
  lv_meter_scale_t * scale_radius_in_1 = lv_meter_add_scale(meter1);
  scale_radius_in_1->r_mod += 24; /* increasing the radius for drawings hairlines */
  lv_meter_set_scale_ticks(meter1, scale_radius_in_1, 60, 0, 0, lv_palette_main(LV_PALETTE_PINK));  // 24 ticks
  lv_meter_set_scale_major_ticks(meter1, scale_radius_in_1, 1, 0,  0, lv_palette_darken(LV_PALETTE_PINK,4), 26); // Every tick is major
  lv_meter_set_scale_range(meter1, scale_radius_in_1, 1, 60, 354, 276);  // [1..24] values in an almost full circle

  /* create labels two */
  /* Create an other scale for the hours. It's only visual and contains only major ticks */
  lv_meter_scale_t * scale_radius_in_2 = lv_meter_add_scale(meter2);
  scale_radius_in_2->r_mod += -12; /* increasing the radius for drawings hairlines */
  lv_meter_set_scale_ticks(meter2, scale_radius_in_2, 6, 0, 0, lv_palette_main(LV_PALETTE_GREY)); /* 6 ticks */
  lv_meter_set_scale_major_ticks(meter2, scale_radius_in_2, 1, 0,  0, lv_palette_darken(LV_PALETTE_YELLOW,4), 26); /* Every tick is major */
  lv_meter_set_scale_range(meter2, scale_radius_in_2, 0, 5, 300, 270); /* [0..5] values in an almost full circle */

  /* create labels tree */
  /* Create an other scale for the hours. It's only visual and contains only major ticks */
  lv_meter_scale_t * scale_radius_in = lv_meter_add_scale(meter3);
  scale_radius_in->r_mod += +16; /* increasing the radius for drawings hairlines */
  lv_meter_set_scale_ticks(meter3, scale_radius_in, 12, 0, 0, lv_palette_main(LV_PALETTE_GREY)); /* 12 ticks */
  lv_meter_set_scale_major_ticks(meter3, scale_radius_in, 1, 0,  0, lv_palette_darken(LV_PALETTE_PINK,4), -6); /* Every tick is major */
  lv_meter_set_scale_range(meter3, scale_radius_in, 1, 12, 330, 300); /* [1..12] values in an almost full circle */


  LV_IMG_DECLARE(arrow_midle);
  LV_IMG_DECLARE(arrow_small);
  LV_IMG_DECLARE(arrow_big);

  /* Now create the actual image */
  lv_obj_t * ihour = lv_img_create(parent);
  lv_obj_t * imin = lv_img_create(parent);
  lv_obj_t * isec = lv_img_create(parent);

  lv_img_set_src(ihour, &arrow_big);
  lv_img_set_src(imin, &arrow_midle);
  lv_img_set_src(isec, &arrow_small);

  // lv_obj_align(ihour, LV_ALIGN_CENTER, -1, -1);
  lv_obj_align(ihour, LV_ALIGN_CENTER, 44, 0);
  lv_obj_align(imin, LV_ALIGN_CENTER, 44, 0);
  lv_obj_align(isec, LV_ALIGN_CENTER, 44, 0);

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
  lv_obj_set_style_img_recolor(ihour, lv_palette_darken(LV_PALETTE_GREY,4), 0);
  /* recolor arrow to blue color */
  lv_obj_set_style_img_recolor_opa(imin, 250, 0);
  lv_obj_set_style_img_recolor(imin, lv_palette_lighten(LV_PALETTE_GREY,4), 0);

  lv_img_set_zoom(isec, siz_clk * 0.8); // стрелы пропорционально индикатору
  lv_img_set_zoom(ihour, siz_clk * 0.8);
  lv_img_set_zoom(imin, siz_clk * 0.8);

  /* --- */
  // animation
  lv_anim_t a_sec;
  lv_anim_init(&a_sec);
  lv_anim_set_var(&a_sec, isec);

  lv_anim_set_exec_cb(&a_sec, set_angle);
  lv_anim_set_values(&a_sec, 0, 3600);
  lv_anim_set_time(&a_sec, 1e5L);
  lv_anim_set_repeat_count(&a_sec, LV_ANIM_REPEAT_INFINITE);
  lv_anim_start(&a_sec);

  lv_anim_t a_hour;
  lv_anim_init(&a_hour);
  lv_anim_set_var(&a_hour, ihour);

  lv_anim_set_exec_cb(&a_hour, set_angle);
  lv_anim_set_values(&a_hour, 0, 3600);
  lv_anim_set_time(&a_hour, 72e6L);
  lv_anim_set_repeat_count(&a_hour, LV_ANIM_REPEAT_INFINITE);
  lv_anim_start(&a_hour);

  lv_anim_t a_min;
  lv_anim_init(&a_min);
  lv_anim_set_var(&a_min, imin);

  lv_anim_set_exec_cb(&a_min, set_angle);
  lv_anim_set_values(&a_min, 0, 3600);
  lv_anim_set_time(&a_min, 6e6L);
  lv_anim_set_repeat_count(&a_min, LV_ANIM_REPEAT_INFINITE);
  lv_anim_start(&a_min);
}
