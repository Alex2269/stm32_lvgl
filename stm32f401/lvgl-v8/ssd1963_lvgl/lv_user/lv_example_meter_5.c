#include "lv_examples.h"
#include "lv_example_meter_5.h"

static lv_obj_t * meter;

static void set_value_1(void * indic, int32_t v)
{
    lv_meter_set_indicator_value(meter, indic, v);
}

static void set_value_2(void * indic, int32_t v)
{
    lv_meter_set_indicator_value(meter, indic, v);
}

static void set_value_3(void * indic, int32_t v)
{
    lv_meter_set_indicator_value(meter, indic, v);
}

/**
 * A simple meter
 */
void lv_example_meter_5(void)
{
    meter = lv_meter_create(lv_scr_act());
    lv_obj_center(meter);
    lv_obj_set_size(meter, 220, 220);

    /*Add a scale first*/
    lv_meter_scale_t * scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 41, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter, scale, 8, 4, 15, lv_color_black(), 10);

    lv_meter_indicator_t * indic_1;
    lv_meter_indicator_t * indic_2;
    lv_meter_indicator_t * indic_3;

//-------
    /*Add a blue arc to the start*/
    indic_1 = lv_meter_add_arc(meter, scale, 2, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_meter_set_indicator_start_value(meter, indic_1, 0);
    lv_meter_set_indicator_end_value(meter, indic_1, 20);

    /*Make the tick lines blue at the start of the scale*/
    indic_1 = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE), false, 0);
    lv_meter_set_indicator_start_value(meter, indic_1, 0);
    lv_meter_set_indicator_end_value(meter, indic_1, 20);

    /*Add a red arc to the end*/
    indic_1 = lv_meter_add_arc(meter, scale, 2, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(meter, indic_1, 80);
    lv_meter_set_indicator_end_value(meter, indic_1, 100);

    /*Make the tick lines red at the end of the scale*/
    indic_1 = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_GREY), lv_palette_main(LV_PALETTE_YELLOW), false, 0);
    lv_meter_set_indicator_start_value(meter, indic_1, 20);
    lv_meter_set_indicator_end_value(meter, indic_1, 80);

    /*Make the tick lines red at the end of the scale*/
    indic_1 = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 0);
    lv_meter_set_indicator_start_value(meter, indic_1, 80);
    lv_meter_set_indicator_end_value(meter, indic_1, 100);
//-------

    /*Add a needle line indicator*/
    indic_1 = lv_meter_add_needle_line(meter, scale, 4, lv_palette_main(LV_PALETTE_GREY), -10);
    indic_2 = lv_meter_add_needle_line(meter, scale, 6, lv_palette_main(LV_PALETTE_RED), -20);
    indic_3 = lv_meter_add_needle_line(meter, scale, 8, lv_palette_main(LV_PALETTE_YELLOW), -30);

    /*Create an animation to set the value*/
    lv_anim_t a_1;
    lv_anim_init(&a_1);
    lv_anim_set_exec_cb(&a_1, set_value_1);
    lv_anim_set_var(&a_1, indic_1);
    lv_anim_set_values(&a_1, 0, 100);
    lv_anim_set_time(&a_1, 2000);
    lv_anim_set_repeat_delay(&a_1, 100);
    lv_anim_set_playback_time(&a_1, 500);
    lv_anim_set_playback_delay(&a_1, 100);
    lv_anim_set_repeat_count(&a_1, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a_1);

    lv_anim_t a_2;
    lv_anim_init(&a_2);
    lv_anim_set_exec_cb(&a_2, set_value_2);
    lv_anim_set_var(&a_2, indic_2);
    lv_anim_set_values(&a_2, 46, 54);
    lv_anim_set_time(&a_2, 1500);
    lv_anim_set_repeat_delay(&a_2, 100);
    lv_anim_set_playback_time(&a_2, 1500);
    lv_anim_set_playback_delay(&a_2, 100);
    lv_anim_set_repeat_count(&a_2, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a_2);

    lv_anim_t a_3;
    lv_anim_init(&a_3);
    lv_anim_set_exec_cb(&a_3, set_value_3);
    lv_anim_set_var(&a_3, indic_3);
    lv_anim_set_values(&a_3, 36, 64);
    lv_anim_set_time(&a_3, 3300);
    lv_anim_set_repeat_delay(&a_3, 100);
    lv_anim_set_playback_time(&a_3, 3300);
    lv_anim_set_playback_delay(&a_3, 100);
    lv_anim_set_repeat_count(&a_3, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a_3);
}
