#include "../../lv_examples.h"

static void mask_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    static int16_t mask_top_id = -1;
    static int16_t mask_bottom_id = -1;

    if (code == LV_EVENT_COVER_CHECK) {
        lv_event_set_cover_res(e, LV_COVER_RES_MASKED);

    } else if (code == LV_EVENT_DRAW_MAIN_BEGIN) {
        /* add mask */
        const lv_font_t * font = lv_obj_get_style_text_font(obj, LV_PART_MAIN);
        lv_coord_t line_space = lv_obj_get_style_text_line_space(obj, LV_PART_MAIN);
        lv_coord_t font_h = lv_font_get_line_height(font);

        lv_area_t roller_coords;
        lv_obj_get_coords(obj, &roller_coords);

        lv_area_t rect_area;
        rect_area.x1 = roller_coords.x1;
        rect_area.x2 = roller_coords.x2;
        rect_area.y1 = roller_coords.y1;
        rect_area.y2 = roller_coords.y1 + (lv_obj_get_height(obj) - font_h - line_space) / 2;

        lv_draw_mask_fade_param_t * fade_mask_top = lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));
        lv_draw_mask_fade_init(fade_mask_top, &rect_area, LV_OPA_TRANSP, rect_area.y1, LV_OPA_COVER, rect_area.y2);
        mask_top_id = lv_draw_mask_add(fade_mask_top, NULL);

        rect_area.y1 = rect_area.y2 + font_h + line_space - 1;
        rect_area.y2 = roller_coords.y2;

        lv_draw_mask_fade_param_t * fade_mask_bottom =lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));
        lv_draw_mask_fade_init(fade_mask_bottom, &rect_area, LV_OPA_COVER, rect_area.y1, LV_OPA_TRANSP, rect_area.y2);
        mask_bottom_id = lv_draw_mask_add(fade_mask_bottom, NULL);

    } else if (code == LV_EVENT_DRAW_POST_END) {
        lv_draw_mask_fade_param_t * fade_mask_top = lv_draw_mask_remove_id(mask_top_id);
        lv_draw_mask_fade_param_t * fade_mask_bottom = lv_draw_mask_remove_id(mask_bottom_id);
        lv_draw_mask_free_param(fade_mask_top);
        lv_draw_mask_free_param(fade_mask_bottom);
        lv_mem_buf_release(fade_mask_top);
        lv_mem_buf_release(fade_mask_bottom);
        mask_top_id = -1;
        mask_bottom_id = -1;
    }
}

/**
 * Add a fade mask to roller.
 */
void lv_example_roller_4(lv_obj_t* parent, int16_t pos_x, int16_t pos_y)
{
    // lv_obj_remove_style_all(parent);

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_bg_color(&style, lv_color_black());
    lv_style_set_text_font(&style, &arial_20);
    lv_style_set_text_letter_space(&style, 4);
    lv_style_set_text_line_space(&style, 8);
    /*lv_style_set_text_decor(&style, LV_TEXT_DECOR_UNDERLINE);*/
    /*lv_style_set_text_decor(&style, LV_TEXT_DECOR_STRIKETHROUGH);*/
    lv_style_set_text_color(&style, lv_palette_darken(LV_PALETTE_YELLOW,1));
    // lv_style_set_text_color(&style, lv_color_white());


    lv_style_set_border_width(&style, 4); // 8
    lv_style_set_pad_all(&style, 0);
    lv_obj_add_style(parent, &style, 0);

    lv_obj_t *roller1 = lv_roller_create(parent);
    lv_obj_t *roller2 = lv_roller_create(parent);
    lv_obj_t *roller3 = lv_roller_create(parent);
    lv_obj_t *roller4 = lv_roller_create(parent);

    lv_obj_add_style(roller1, &style, 0);
    lv_obj_add_style(roller2, &style, 0);
    lv_obj_add_style(roller3, &style, 0);
    lv_obj_add_style(roller4, &style, 0);

    lv_obj_set_style_bg_opa(roller1, LV_OPA_TRANSP, LV_PART_SELECTED);
    lv_obj_set_style_bg_opa(roller2, LV_OPA_TRANSP, LV_PART_SELECTED);
    lv_obj_set_style_bg_opa(roller3, LV_OPA_TRANSP, LV_PART_SELECTED);
    lv_obj_set_style_bg_opa(roller4, LV_OPA_TRANSP, LV_PART_SELECTED);

    lv_roller_set_options(roller1, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9",
                          LV_ROLLER_MODE_NORMAL);
    lv_roller_set_options(roller2, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9",
                          LV_ROLLER_MODE_NORMAL);
    lv_roller_set_options(roller3, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9",
                          LV_ROLLER_MODE_NORMAL);
    lv_roller_set_options(roller4, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9",
                          LV_ROLLER_MODE_NORMAL);

    lv_obj_center(roller1);
    lv_obj_center(roller2);
    lv_obj_center(roller3);
    lv_obj_center(roller4);

    lv_roller_set_visible_row_count(roller1, 1);
    lv_roller_set_visible_row_count(roller2, 1);
    lv_roller_set_visible_row_count(roller3, 1);
    lv_roller_set_visible_row_count(roller4, 1);

    // lv_obj_align(roller1, LV_ALIGN_CENTER, -80, 80); // force: 100
    lv_obj_align_to(roller1, parent, LV_ALIGN_CENTER,     pos_x , pos_y);
    lv_obj_align_to(roller2, parent, LV_ALIGN_CENTER,  40+pos_x , pos_y);
    lv_obj_align_to(roller3, parent, LV_ALIGN_CENTER,  80+pos_x , pos_y);
    lv_obj_align_to(roller4, parent, LV_ALIGN_CENTER,  120+pos_x, pos_y);

    lv_obj_add_event_cb(roller1, mask_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(roller2, mask_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(roller3, mask_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(roller4, mask_event_cb, LV_EVENT_ALL, NULL);
}

