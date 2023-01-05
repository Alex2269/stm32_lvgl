#include "lv_examples.h"
#include "lv_example_meter_5.h"

static lv_obj_t * meter1;
static lv_obj_t * meter2;

static void cb_meter_a(void * indic, int32_t v)
{
    lv_meter_set_indicator_value(meter1, indic, v);
}

static void cb_meter_b(void * indic, int32_t v)
{
    lv_meter_set_indicator_value(meter2, indic, v);
}

/**
 * A simple meter
 */
void lv_example_meter_5a(lv_obj_t* parent, int16_t pos_x, int16_t pos_y)
{
    lv_obj_t * p_meter;
    meter1 = p_meter = lv_meter_create(parent);

    lv_obj_center(p_meter);
    lv_obj_set_size(p_meter, 340, 340);
    lv_obj_align_to(p_meter, parent, LV_ALIGN_CENTER, pos_x, pos_y);

    /*Add a scale first*/
    lv_meter_set_scale_ticks(p_meter, 41, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(p_meter, 8, 4, 15, lv_color_black(), 10);

    lv_meter_indicator_t * indic_1;
    lv_meter_indicator_t * indic_2;
    lv_meter_indicator_t * indic_3;

    //-------
    /*Add a blue arc to the start*/
    indic_1 = lv_meter_add_arc(p_meter,  2, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_meter_set_indicator_start_value(p_meter, indic_1, 0);
    lv_meter_set_indicator_end_value(p_meter, indic_1, 20);

    /*Make the tick lines blue at the start of the scale*/
    indic_1 = lv_meter_add_scale_lines(p_meter,  lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE), false, 0);
    lv_meter_set_indicator_start_value(p_meter, indic_1, 0);
    lv_meter_set_indicator_end_value(p_meter, indic_1, 20);

    /*Add a red arc to the end*/
    indic_1 = lv_meter_add_arc(p_meter,  2, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(p_meter, indic_1, 80);
    lv_meter_set_indicator_end_value(p_meter, indic_1, 100);

    /*Make the tick lines red at the end of the scale*/
    indic_1 = lv_meter_add_scale_lines(p_meter,  lv_palette_main(LV_PALETTE_GREY), lv_palette_main(LV_PALETTE_YELLOW), false, 0);
    lv_meter_set_indicator_start_value(p_meter, indic_1, 20);
    lv_meter_set_indicator_end_value(p_meter, indic_1, 80);

    /*Make the tick lines red at the end of the scale*/
    indic_1 = lv_meter_add_scale_lines(p_meter,  lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 0);
    lv_meter_set_indicator_start_value(p_meter, indic_1, 80);
    lv_meter_set_indicator_end_value(p_meter, indic_1, 100);
    //-------

    /*Add a needle line indicator*/
    indic_1 = lv_meter_add_needle_line(p_meter,  2, lv_palette_darken(LV_PALETTE_CYAN,3), -12);
    indic_2 = lv_meter_add_needle_line(p_meter,  2, lv_palette_lighten(LV_PALETTE_LIME,3), -12);
    indic_3 = lv_meter_add_needle_line(p_meter,  2, lv_palette_lighten(LV_PALETTE_PINK,3), -12);

    /*Create an animation to set the value*/
    lv_anim_t a_1;
    lv_anim_init(&a_1);
    lv_anim_set_exec_cb(&a_1, cb_meter_a);
    lv_anim_set_var(&a_1, indic_1);
    lv_anim_set_values(&a_1, 12, 16);
    lv_anim_set_time(&a_1, 4000);
    lv_anim_set_repeat_delay(&a_1, 100);
    lv_anim_set_playback_time(&a_1, 500);
    lv_anim_set_playback_delay(&a_1, 100);
    lv_anim_set_repeat_count(&a_1, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a_1);

    lv_anim_t a_2;
    lv_anim_init(&a_2);
    lv_anim_set_exec_cb(&a_2, cb_meter_a);
    lv_anim_set_var(&a_2, indic_2);
    lv_anim_set_values(&a_2, 46, 54);
    lv_anim_set_time(&a_2, 3500);
    lv_anim_set_repeat_delay(&a_2, 100);
    lv_anim_set_playback_time(&a_2, 1500);
    lv_anim_set_playback_delay(&a_2, 100);
    lv_anim_set_repeat_count(&a_2, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a_2);

    lv_anim_t a_3;
    lv_anim_init(&a_3);
    lv_anim_set_exec_cb(&a_3, cb_meter_a);
    lv_anim_set_var(&a_3, indic_3);
    lv_anim_set_values(&a_3, 86, 94);
    lv_anim_set_time(&a_3, 6600);
    lv_anim_set_repeat_delay(&a_3, 100);
    lv_anim_set_playback_time(&a_3, 3300);
    lv_anim_set_playback_delay(&a_3, 100);
    lv_anim_set_repeat_count(&a_3, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a_3);
}

void lv_example_meter_5b(lv_obj_t* parent, int16_t pos_x, int16_t pos_y)
{
    lv_obj_t * p_meter;
    meter2 = p_meter = lv_meter_create(parent);

    lv_obj_center(p_meter);
    lv_obj_set_size(p_meter, 340, 340);
    lv_obj_align_to(p_meter, parent, LV_ALIGN_CENTER, pos_x, pos_y);

    /*Add a scale first*/
    lv_meter_set_scale_ticks(p_meter,  41, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(p_meter,  8, 4, 15, lv_color_black(), 10);

    lv_meter_indicator_t * indic_1;
    lv_meter_indicator_t * indic_2;
    lv_meter_indicator_t * indic_3;

    //-------
    /*Add a blue arc to the start*/
    indic_1 = lv_meter_add_arc(p_meter,  2, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_meter_set_indicator_start_value(p_meter, indic_1, 0);
    lv_meter_set_indicator_end_value(p_meter, indic_1, 20);

    /*Make the tick lines blue at the start of the scale*/
    indic_1 = lv_meter_add_scale_lines(p_meter,  lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE), false, 0);
    lv_meter_set_indicator_start_value(p_meter, indic_1, 0);
    lv_meter_set_indicator_end_value(p_meter, indic_1, 20);

    /*Add a red arc to the end*/
    indic_1 = lv_meter_add_arc(p_meter,  2, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(p_meter, indic_1, 80);
    lv_meter_set_indicator_end_value(p_meter, indic_1, 100);

    /*Make the tick lines red at the end of the scale*/
    indic_1 = lv_meter_add_scale_lines(p_meter,  lv_palette_main(LV_PALETTE_GREY), lv_palette_main(LV_PALETTE_YELLOW), false, 0);
    lv_meter_set_indicator_start_value(p_meter, indic_1, 20);
    lv_meter_set_indicator_end_value(p_meter, indic_1, 80);

    /*Make the tick lines red at the end of the scale*/
    indic_1 = lv_meter_add_scale_lines(p_meter,  lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 0);
    lv_meter_set_indicator_start_value(p_meter, indic_1, 80);
    lv_meter_set_indicator_end_value(p_meter, indic_1, 100);
    //-------

    /*Add a needle line indicator*/
    indic_1 = lv_meter_add_needle_line(p_meter,  2, lv_palette_main(LV_PALETTE_BLUE), -12);
    indic_2 = lv_meter_add_needle_line(p_meter,  2, lv_palette_main(LV_PALETTE_YELLOW), -12);
    indic_3 = lv_meter_add_needle_line(p_meter,  2, lv_palette_main(LV_PALETTE_RED), -12);

    /*Create an animation to set the value*/
    lv_anim_t a_1;
    lv_anim_init(&a_1);
    lv_anim_set_exec_cb(&a_1, cb_meter_b);
    lv_anim_set_var(&a_1, indic_1);
    lv_anim_set_values(&a_1, 0, 20);
    lv_anim_set_time(&a_1, 4000+1000);
    lv_anim_set_repeat_delay(&a_1, 100);
    lv_anim_set_playback_time(&a_1, 500);
    lv_anim_set_playback_delay(&a_1, 100);
    lv_anim_set_repeat_count(&a_1, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a_1);

    lv_anim_t a_2;
    lv_anim_init(&a_2);
    lv_anim_set_exec_cb(&a_2, cb_meter_b);
    lv_anim_set_var(&a_2, indic_2);
    lv_anim_set_values(&a_2, 46, 54);
    lv_anim_set_time(&a_2, 3500+1000);
    lv_anim_set_repeat_delay(&a_2, 100);
    lv_anim_set_playback_time(&a_2, 1500);
    lv_anim_set_playback_delay(&a_2, 100);
    lv_anim_set_repeat_count(&a_2, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a_2);

    lv_anim_t a_3;
    lv_anim_init(&a_3);
    lv_anim_set_exec_cb(&a_3, cb_meter_b);
    lv_anim_set_var(&a_3, indic_3);
    lv_anim_set_values(&a_3, 82, 98);
    lv_anim_set_time(&a_3, 6600+1000);
    lv_anim_set_repeat_delay(&a_3, 100);
    lv_anim_set_playback_time(&a_3, 3300);
    lv_anim_set_playback_delay(&a_3, 100);
    lv_anim_set_repeat_count(&a_3, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a_3);
}

