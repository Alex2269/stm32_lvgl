/**
 * @file lv_user_keypad_encoder.c
 *
**/

/*********************
* INCLUDES
*********************/

#include "lv_demo_keypad_encoder.h"
#if LV_USE_DEMO_KEYPAD_AND_ENCODER
/*********************
* DEFINES
*********************/

/**********************
* TYPEDEFS
**********************/
// lv_theme_default.c
// #define BORDER_WIDTH            lv_disp_dpx(theme.disp, 2)
// #define OUTLINE_WIDTH           lv_disp_dpx(theme.disp, 3)
/**********************
* STATIC PROTOTYPES
**********************/
static void button_style(void);
static void lv_btnmatrix1(lv_obj_t * parent);
static void lv_btnmatrix2(lv_obj_t * parent);
static void lv_btnmatrix3(lv_obj_t * parent);
static void lv_btnmatrix4(lv_obj_t * parent);

/**********************
* STATIC VARIABLES
**********************/
static lv_group_t * g;
static lv_obj_t * tv;
static lv_obj_t * t1;
static lv_obj_t * t2;
static lv_obj_t * t3;
static lv_obj_t * t4;


/**********************
* MACROS
**********************/
static lv_style_t style_btn;

/**********************
* STATIC FUNCTIONS
**********************/

/*Will be called when the styles of the base theme are already added
to add new styles*/
static void user_theme_apply_cb(lv_theme_t * th, lv_obj_t * obj)
{
  LV_UNUSED(th);
  if(lv_obj_check_type(obj, &lv_btnmatrix_class))
  {
    lv_obj_remove_style(obj, &style_btn, LV_PART_MAIN);
    lv_obj_add_style(obj, obj, 0);
  }
}

static void event_cb(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = lv_event_get_target(e);
  lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);

  if(code == LV_EVENT_DRAW_PART_BEGIN)
  {
    dsc->rect_dsc->radius = 48;

    if(dsc->id)
    {
      if(lv_btnmatrix_get_selected_btn(obj) == (dsc->id))
      {
        dsc->label_dsc->color = lv_palette_darken(LV_PALETTE_BLUE, 3);
        dsc->rect_dsc->bg_color = lv_palette_lighten(LV_PALETTE_GREEN, 1);
      }
      else
      {
        dsc->label_dsc->color = lv_palette_lighten(LV_PALETTE_PINK, 1);
        dsc->rect_dsc->bg_color = lv_palette_darken(LV_PALETTE_GREY, 2);
      }
    }
  }

  if(code == LV_EVENT_DRAW_PART_END) if(dsc->id) NULL;
}

/**********************
* GLOBAL FUNCTIONS
**********************/
void lv_user_keypad_encoder2(void)
{
  g = lv_group_create();
  lv_group_set_default(g);
  lv_indev_t * cur_drv = NULL;

  for(;;) 
  {
    cur_drv = lv_indev_get_next(cur_drv);
    if(!cur_drv) 
    {
      break;
    }
    if(cur_drv->driver->type == LV_INDEV_TYPE_KEYPAD) 
    {
      lv_indev_set_group(cur_drv, g);
    }
    if(cur_drv->driver->type == LV_INDEV_TYPE_ENCODER) 
    {
      lv_indev_set_group(cur_drv, g);
    }
  }

  tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 60);

  lv_obj_t * btnm = lv_tabview_get_tab_btns(tv);
  lv_obj_set_style_pad_left(btnm, 100, 0);
  lv_obj_set_style_pad_right(btnm, 100, 0);

  lv_obj_set_style_outline_width(btnm, 0, LV_STATE_FOCUS_KEY);
  lv_obj_set_style_outline_width(btnm, 0, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);

  t1 = lv_tabview_add_tab(tv, "Table 1");
  t2 = lv_tabview_add_tab(tv, "Table 2");
  t3 = lv_tabview_add_tab(tv, "Table 3");
  t4 = lv_tabview_add_tab(tv, "Table 4");

  button_style();

  lv_obj_add_style(tv, &style_btn, 0);
  lv_obj_add_style(t1, &style_btn, 0);
  lv_obj_add_style(t2, &style_btn, 0);
  lv_obj_add_style(t3, &style_btn, 0);
  lv_obj_add_style(t4, &style_btn, 0);

  lv_btnmatrix1(t1);
  lv_btnmatrix2(t2);
  lv_btnmatrix3(t3);
  lv_btnmatrix4(t4);
}

/**********************
* STATIC ARRAYS
**********************/
static const char * btnm_map1[] =
{
  "1", "2", "3", "4", "5", "\n",
  "6", "7", "8", "9", "0", "\n",
  "Action1", "Action2", ""
};

static const char * btnm_map2[] =
{
  "21", "22", "23", "\n",
  "24", "25", "26", "\n",
  "27", "28", "29", "\n",
  "b0", "b1", "b2", ""
};

static const char * btnm_map3[] =
{
  "31", "32", "33", "\n",
  "34", "35", "36", "\n",
  "37", "38", "39", "\n",
  "c0", "c1", "c2", ""
};

static const char * btnm_map4[] =
{
  "41", "42", "43", "\n",
  "44", "45", "46", "\n",
  "47", "48", "49", "\n",
  "d0", "d1", "d2", ""
};

/**********************
* STATIC FUNCTIONS
**********************/
static void button_style(void)
{
  // buttons theme
  /*Initialize the styles*/
  lv_obj_remove_style_all(&style_btn);
  lv_obj_remove_style(&style_btn, &style_btn, LV_PART_MAIN);

  lv_style_init(&style_btn);
  lv_style_set_opa(&style_btn, 255);
  lv_style_set_bg_opa(&style_btn, 255);
  lv_style_set_bg_color(&style_btn, lv_palette_darken(LV_PALETTE_GREY, 4));

  lv_style_set_radius(&style_btn, 8);
  lv_style_set_border_width(&style_btn, 4);
  lv_style_set_outline_width(&style_btn, 4);
  lv_style_set_outline_pad(&style_btn, 0);

  lv_style_set_border_color(&style_btn, lv_palette_lighten(LV_PALETTE_RED, 2));
  lv_style_set_outline_color(&style_btn, lv_palette_darken(LV_PALETTE_BLUE, 2));

  lv_style_set_text_opa(&style_btn, 255); // opa opacity
  // lv_style_set_text_color(&style_btn, lv_palette_main(LV_PALETTE_PINK));
  lv_style_set_text_font(&style_btn, &arial_20);
  lv_style_set_text_letter_space(&style_btn, 2);
  lv_style_set_text_align(&style_btn, LV_TEXT_ALIGN_CENTER);


  /*Initialize the new theme from the current theme*/
  lv_theme_t * th_act = lv_disp_get_theme(NULL);
  static lv_theme_t th_new;
  th_new = *th_act;
  /*Set the parent theme and the style apply callback for the new theme*/
  lv_theme_set_parent(&th_new, th_act);
  lv_theme_set_apply_cb(&th_new, user_theme_apply_cb);
  /*Assign the new theme the the current display*/
  lv_disp_set_theme(NULL, &th_new);
}

static void lv_btnmatrix1(lv_obj_t * parent)
{
  lv_obj_t * btnmatrix_1 = lv_btnmatrix_create(parent);
  lv_btnmatrix_set_map(btnmatrix_1, btnm_map1);
  lv_obj_set_size(btnmatrix_1, 380, 300);
  // lv_obj_set_content_width(btnmatrix_1, 400);
  // lv_obj_set_content_height(btnmatrix_1, 200);
  lv_obj_add_style(btnmatrix_1, &style_btn, 0);
  lv_obj_set_style_radius(btnmatrix_1, 24, 0);
  lv_obj_set_style_pad_row(btnmatrix_1, 10, LV_PART_MAIN);
  lv_obj_set_style_pad_column(btnmatrix_1, 10, LV_PART_MAIN);
  lv_obj_align(btnmatrix_1, LV_ALIGN_CENTER, 0, 30);
  lv_obj_add_event_cb(btnmatrix_1, event_cb, LV_EVENT_ALL, NULL);
  lv_obj_center(btnmatrix_1);
  lv_obj_add_flag(btnmatrix_1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
}

static void lv_btnmatrix2(lv_obj_t * parent)
{
  lv_obj_t * btnmatrix_2 = lv_btnmatrix_create(parent);
  lv_btnmatrix_set_map(btnmatrix_2, btnm_map2);
  lv_obj_set_size(btnmatrix_2, 380, 300);
  // lv_obj_set_content_width(btnmatrix_2, 400);
  // lv_obj_set_content_height(btnmatrix_2, 200);
  lv_obj_add_style(btnmatrix_2, &style_btn, 0);
  lv_obj_set_style_radius(btnmatrix_2, 24, 0);
  lv_obj_set_style_pad_row(btnmatrix_2, 10, LV_PART_MAIN);
  lv_obj_set_style_pad_column(btnmatrix_2, 10, LV_PART_MAIN);
  lv_obj_align(btnmatrix_2, LV_ALIGN_CENTER, 0, 30);
  lv_obj_add_event_cb(btnmatrix_2, event_cb, LV_EVENT_ALL, NULL);
  lv_obj_center(btnmatrix_2);
  lv_obj_add_flag(btnmatrix_2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
}

static void lv_btnmatrix3(lv_obj_t * parent)
{
  lv_obj_t * btnmatrix_3 = lv_btnmatrix_create(parent);
  lv_btnmatrix_set_map(btnmatrix_3, btnm_map3);
  lv_obj_set_size(btnmatrix_3, 780, 400);
  // lv_obj_set_content_width(btnmatrix_3, 400);
  // lv_obj_set_content_height(btnmatrix_3, 200);
  lv_obj_add_style(btnmatrix_3, &style_btn, 0);
  lv_obj_set_style_radius(btnmatrix_3, 24, 0);
  lv_obj_set_style_pad_row(btnmatrix_3, 10, LV_PART_MAIN);
  lv_obj_set_style_pad_column(btnmatrix_3, 10, LV_PART_MAIN);
  lv_obj_align(btnmatrix_3, LV_ALIGN_CENTER, 0, 30);
  lv_obj_add_event_cb(btnmatrix_3, event_cb, LV_EVENT_ALL, NULL);
  lv_obj_center(btnmatrix_3);
  lv_obj_add_flag(btnmatrix_3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
}

static void lv_btnmatrix4(lv_obj_t * parent)
{
  lv_obj_t * btnmatrix_4 = lv_btnmatrix_create(parent);
  lv_btnmatrix_set_map(btnmatrix_4, btnm_map4);
  lv_obj_set_size(btnmatrix_4, 780, 400);
  // lv_obj_set_content_width(btnmatrix_4, 400);
  // lv_obj_set_content_height(btnmatrix_4, 200);
  lv_obj_add_style(btnmatrix_4, &style_btn, 0);
  lv_obj_set_style_radius(btnmatrix_4, 24, 0);
  lv_obj_set_style_pad_row(btnmatrix_4, 10, LV_PART_MAIN);
  lv_obj_set_style_pad_column(btnmatrix_4, 10, LV_PART_MAIN);
  lv_obj_align(btnmatrix_4, LV_ALIGN_CENTER, 0, 30);
  lv_obj_add_event_cb(btnmatrix_4, event_cb, LV_EVENT_ALL, NULL);
  lv_obj_center(btnmatrix_4);
  lv_obj_add_flag(btnmatrix_4, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
}

#endif
