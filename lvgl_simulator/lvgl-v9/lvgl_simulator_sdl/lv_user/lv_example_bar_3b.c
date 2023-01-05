#include "../../lv_examples.h"
#if LV_USE_BAR && LV_BUILD_EXAMPLES

static void set_temp(void * bar, int32_t temp)
{
    lv_bar_set_value(bar, temp, LV_ANIM_ON);
}

/**
 * A temperature meter example
 */
void lv_example_bar_3b(void)
{
    static lv_style_t style_indic;

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_bg_grad_color(&style_indic, lv_palette_darken(LV_PALETTE_GREY, 2));
    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_VER);

    lv_style_set_radius(&style_indic, 8);
    lv_style_set_pad_right(&style_indic, 0);

    lv_obj_t * bar = lv_bar_create(lv_scr_act());
    lv_obj_add_style(bar, &style_indic, LV_PART_MAIN);
    // lv_obj_add_style(bar, &style_indic, LV_PART_KNOB);
    lv_slider_set_mode(bar, LV_SLIDER_MODE_RANGE);

    lv_obj_set_size(bar, 60, 200);
    lv_obj_set_style_radius(bar, 8, 0);

    lv_obj_center(bar);
    lv_bar_set_range(bar, 0, 40);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_temp);
    lv_anim_set_time(&a, 3000);
    lv_anim_set_playback_time(&a, 3000);
    lv_anim_set_var(&a, bar);
    lv_anim_set_values(&a, 0, 40);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}


#endif
