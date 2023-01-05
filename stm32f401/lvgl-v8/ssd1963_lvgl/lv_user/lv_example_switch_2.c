#include "../../lv_examples.h"

static void switch_1_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("switch 1: %s\n", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
    }
}

static void switch_2_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("switch 2: %s\n", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
    }
}

void lv_example_switch_2(lv_obj_t* parent)
{
  // lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);
  // lv_obj_set_flex_align(parent, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

  lv_obj_t * sw;

  sw = lv_switch_create(parent);
  // lv_obj_align(sw, LV_ALIGN_CENTER,  -30, 0);
  lv_obj_align_to(sw, parent, LV_ALIGN_CENTER, -50, 16);
  lv_obj_set_style_pad_all(sw, -8, LV_PART_KNOB); // knob size
  // lv_obj_add_state(sw, LV_STATE_CHECKED);
  lv_obj_add_event_cb(sw, switch_1_event_handler, LV_EVENT_ALL, NULL);

  sw = lv_switch_create(parent);
  // lv_obj_align(sw, LV_ALIGN_CENTER,  +30, 0);
  lv_obj_align_to(sw, parent, LV_ALIGN_CENTER, +50, 20);
  lv_obj_set_size(sw, LV_PCT(16), LV_PCT(12));
  lv_obj_set_style_pad_all(sw, -2, LV_PART_KNOB); // knob size
  // lv_obj_add_state(sw, LV_STATE_CHECKED);
  lv_obj_add_event_cb(sw, switch_2_event_handler, LV_EVENT_ALL, NULL);
}

