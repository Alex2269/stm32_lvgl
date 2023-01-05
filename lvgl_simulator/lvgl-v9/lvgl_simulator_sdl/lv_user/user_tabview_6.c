#include "lvgl/lvgl.h"
#include "user_tabview_6.h"

/**********************
* STATIC VARIABLES
**********************/
static const lv_font_t * font_normal;

static lv_style_t style_btn;
static lv_style_t style_bg, style_fg;
static lv_style_t style_tab;

/**********************
* GLOBAL FUNCTIONS
**********************/
static lv_obj_t *tabview;
static void tab1_create(lv_obj_t* parent);
static void tab2_create(lv_obj_t* parent);
static void tab3_create(lv_obj_t* parent);
static void tab4_create(lv_obj_t* parent);
static void tab5_create(lv_obj_t* parent);
static void tab6_create(lv_obj_t* parent);
static void tab7_create(lv_obj_t* parent);


static void user_test_button(lv_obj_t* parent, lv_coord_t x, lv_coord_t y, const char* symbol, const char* text);

static void meter_3_indicators(lv_obj_t* parent);

/**********************
* FUNCTIONS
**********************/
/*Will be called when the styles of the base theme are already added
to add new styles*/
static void user_theme_apply_cb(lv_theme_t * th, lv_obj_t * obj)
{
  LV_UNUSED(th);
  if(lv_obj_check_type(obj, &lv_btn_class))
  {
    lv_obj_add_style(obj, &style_btn, 0);
  }
}

static void user_tabview_init(void)
{
  // tabview theme
  /*Initialize the styles*/
  lv_style_init(&style_tab);
  lv_style_set_border_width(&style_tab, 4);
  // lv_style_set_radius(&style_tab, 4);
  lv_style_set_bg_opa(&style_tab, LV_OPA_50);
  lv_style_set_bg_color(&style_tab, lv_palette_main(LV_PALETTE_LIME));
  // lv_style_set_bg_color_filtered(&style_tab, lv_palette_main(LV_PALETTE_LIME));
  lv_style_set_border_color(&style_tab, lv_palette_main(LV_PALETTE_LIME));
  // lv_style_set_border_color_filtered(&style_tab, lv_palette_main(LV_PALETTE_LIME));

  lv_style_set_text_font(&style_tab, &arial_14);
  lv_style_set_text_letter_space(&style_tab, -1);

  tabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 40);
  lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);
  lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
  lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
  lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_BOTTOM, LV_PART_ITEMS | LV_STATE_CHECKED);
  // lv_obj_clear_flag(lv_tabview_get_content(tabview), LV_OBJ_FLAG_SCROLLABLE);

  // tabs theme
  /*Initialize the styles*/
  lv_style_init(&style_bg);
  lv_style_set_border_color(&style_bg, lv_palette_main(LV_PALETTE_RED));
  lv_style_set_border_width(&style_bg, 4);
  lv_style_set_text_font(&style_bg, &arial_14);
  lv_style_set_pad_all(&style_bg, 8); /*To make the indicator smaller*/
  lv_style_set_radius(&style_bg, 16);
  lv_style_set_anim_time(&style_bg, 1000);

  lv_style_init(&style_fg);
  lv_style_set_bg_opa(&style_fg, LV_OPA_COVER);
  // lv_style_set_bg_color(&style_fg, lv_palette_main(LV_PALETTE_CYAN));
  lv_style_set_bg_color(&style_fg, lv_palette_darken(LV_PALETTE_CYAN, LV_PCT(4)));
  lv_style_set_text_font(&style_fg, &arial_14);
  lv_style_set_radius(&style_fg, 16);
}

static void user_theme_init_and_set(void)
{
  // buttons theme
  /*Initialize the styles*/
  lv_style_init(&style_btn);
  lv_style_set_bg_color(&style_btn, lv_palette_main(LV_PALETTE_YELLOW));
  lv_style_set_bg_opa(&style_btn, 255);
  lv_style_set_border_color(&style_btn, lv_palette_darken(LV_PALETTE_ORANGE, 2));
  lv_style_set_border_width(&style_btn, 4);
  lv_style_set_text_font(&style_btn, &arial_14);
  lv_style_set_text_letter_space(&style_btn, -2);
  lv_style_set_text_align(&style_btn, LV_TEXT_ALIGN_CENTER);
  lv_style_set_text_color(&style_btn, lv_palette_main(LV_PALETTE_PINK));
  lv_style_set_text_opa(&style_btn, 255); // opa opacity
  lv_style_set_opa(&style_btn, 255);

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

static void event_handler(lv_event_t* e)
{
  static lv_obj_t* text_Button;
  static lv_obj_t* currentButton = NULL;
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t* obj = lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED)
  {
    LV_LOG_USER("Clicked: %s", lv_list_get_btn_text(text_Button, obj));
    if (currentButton == obj)
    {
      currentButton = NULL;
    }
    else
    {
      currentButton = obj;
    }
    /*** lv_obj_t* parent = lv_obj_get_parent(obj);
    uint32_t i;
    for (i = 0; i < lv_obj_get_child_cnt(parent); i++)
    {
      lv_obj_t* child = lv_obj_get_child(parent, i);
      if (child == currentButton)
      {
        lv_obj_add_state(child, LV_STATE_CHECKED);
      }
      else
      {
        lv_obj_clear_state(child, LV_STATE_CHECKED);
      }
    }
    ***/
  }
}

void user_tabview_6(void)
{
  // static lv_obj_t *tabview;
  static lv_obj_t* tab1;
  static lv_obj_t* tab2;
  static lv_obj_t* tab3;
  static lv_obj_t* tab4;
  static lv_obj_t* tab5;
  static lv_obj_t* tab6;
  static lv_obj_t* tab7;

  user_tabview_init();

  tab1 = lv_tabview_add_tab(tabview, "Один");
  tab2 = lv_tabview_add_tab(tabview, "Два");
  tab3 = lv_tabview_add_tab(tabview, "Три");
  tab4 = lv_tabview_add_tab(tabview, "Чотири");
  tab5 = lv_tabview_add_tab(tabview, "П'ять");
  tab6 = lv_tabview_add_tab(tabview, "Шість");
  tab7 = lv_tabview_add_tab(tabview, "Сім");

  user_theme_init_and_set();

  lv_obj_add_style(tabview, &style_tab, 0);

  lv_obj_add_style(tab1, &style_bg, 0);
  lv_obj_add_style(tab1, &style_fg, 0);
  lv_obj_add_style(tab2, &style_bg, 0);
  lv_obj_add_style(tab2, &style_fg, 0);
  lv_obj_add_style(tab3, &style_bg, 0);
  lv_obj_add_style(tab3, &style_fg, 0);
  lv_obj_add_style(tab4, &style_bg, 0);
  lv_obj_add_style(tab4, &style_fg, 0);
  lv_obj_add_style(tab5, &style_bg, 0);
  lv_obj_add_style(tab5, &style_fg, 0);
  lv_obj_add_style(tab6, &style_bg, 0);
  lv_obj_add_style(tab6, &style_fg, 0);
  lv_obj_add_style(tab7, &style_bg, 0);
  lv_obj_add_style(tab7, &style_fg, 0);

  tab1_create(tab1);
  tab2_create(tab2);
  tab3_create(tab3);
  tab4_create(tab4);
  tab5_create(tab5);
  tab6_create(tab6);
  tab7_create(tab7);
}

static void tab1_create(lv_obj_t* parent)
{
  user_test_button(parent, 4, 0, LV_SYMBOL_AUDIO, "1");
  user_test_button(parent, 4, 56, LV_SYMBOL_VIDEO, "2");
  user_test_button(parent, 4, 112, LV_SYMBOL_LIST, "3");
  user_test_button(parent, 98, 0, LV_SYMBOL_OK, "4");
  user_test_button(parent, 98, 56, LV_SYMBOL_CLOSE, "5");
  user_test_button(parent, 98, 112, LV_SYMBOL_POWER, "6");
  user_test_button(parent, 192, 0, LV_SYMBOL_SETTINGS, "7");
  user_test_button(parent, 192, 56, LV_SYMBOL_HOME, "8");
  user_test_button(parent, 192, 112, LV_SYMBOL_DOWNLOAD, "9");
}

static void tab2_create(lv_obj_t* parent)
{
  // lv_example_btnmatrix_4(parent);
  lv_example_switch_2(parent);
  lv_example_keybrd(parent);
}

static void tab3_create(lv_obj_t* parent)
{
  lv_example_spinbox_2(parent, 0, -45);
  lv_example_spinbox_3(parent, 0, +45);
}

static void tab4_create(lv_obj_t* parent)
{
  sliders_vertical(parent);
  lv_example_roller_4(parent, -280, 0);
}

static void tab5_create(lv_obj_t* parent)
{
  sliders_horisontal(parent);
}

static void tab6_create(lv_obj_t* parent)
{
  lv_example_meter_5a(parent, -200, 0);
  lv_example_meter_5b(parent, +200, 0);
  // lv_example_textarea_6(parent);
}

static void tab7_create(lv_obj_t* parent)
{
  lv_example_clock_1(parent);
}

static void user_test_button(lv_obj_t* parent, lv_coord_t x, lv_coord_t y, const char* symbol, const char* text)
{
  lv_obj_t* btn = lv_btn_create(parent);
  lv_obj_set_size(btn, 80, 44);
  lv_obj_set_pos(btn, x, y);
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_ALL, NULL);
  lv_obj_set_style_radius(btn, 24, 0);

  // set shadow
  lv_obj_set_style_shadow_width(btn, 4, 0); // dissolution - dust
  lv_obj_set_style_shadow_ofs_x(btn, 2, 0);
  lv_obj_set_style_shadow_ofs_y(btn, 2, 0);
  lv_obj_set_style_shadow_spread(btn, 4, 0); // size
  lv_obj_set_style_shadow_color(btn, lv_palette_lighten(LV_PALETTE_BLUE,2), 0);
  lv_obj_set_style_shadow_opa(btn, 255, 0);

  lv_obj_set_style_outline_width(btn, 2, 0);
  lv_obj_set_style_outline_color(btn, lv_palette_darken(LV_PALETTE_PINK,1), 0);
  lv_obj_set_style_outline_opa(btn, 255, 0);
  lv_obj_set_style_outline_pad(btn, 2, 0);

  // Button label
  lv_obj_t* label = lv_label_create(btn);

  // lv_label_set_text_fmt(label, "%s", text);
  // lv_style_set_text_font(label, &arial_14);
  lv_label_set_text_fmt(label, "%s %s", symbol, text);
  lv_obj_center(label);
}

