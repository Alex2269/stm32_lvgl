#include "../../lv_examples.h"
#if LV_USE_KEYBOARD && LV_BUILD_EXAMPLES

#define UP LV_BTNMATRIX_CTRL_POPOVER

void lv_example_keyboard_3(void)
{
    /*Create an AZERTY keyboard map*/
    static const char * kb_map[] = {"A", "Z", "E", "R", "T", "Y", "U", "I", "O", "P", LV_SYMBOL_BACKSPACE, "\n",
                                    "Q", "S", "D", "F", "G", "J", "K", "L", "M",  LV_SYMBOL_NEW_LINE, "\n",
                                    "W", "X", "C", "V", "B", "N", ",", ".", ":", "!", "?", "\n",
                                    LV_SYMBOL_CLOSE, " ",  " ", " ", LV_SYMBOL_OK, NULL
                                   };

   /* Если вы используете пользовательскую раскладку клавиатуры,
    * установите LV_BTNMATRIX_CTRL_POPOVER флаг для всех клавиш,
    * которые вы хотите показать во всплывающем окне. */
    /*Set the relative width of the buttons and other controls*/
    static const lv_btnmatrix_ctrl_t kb_ctrl[] = {
                                                  UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, 2,
                                                  UP, UP, UP, UP, UP, UP, UP, UP, UP, 2,
                                                  UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP,
                                                  1, LV_BTNMATRIX_CTRL_HIDDEN | 1, 3, LV_BTNMATRIX_CTRL_HIDDEN | 1, 1
                                                 };


    /*Create a keyboard and add the new map as USER_1 mode*/
    lv_obj_t * kb = lv_keyboard_create(lv_scr_act());

    lv_keyboard_set_map(kb, LV_KEYBOARD_MODE_USER_1, kb_map, kb_ctrl);
    lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_USER_1);
    lv_keyboard_set_popovers(kb, true);

    /*Create a text area. The keyboard will write here*/
    lv_obj_t * ta;
    ta = lv_textarea_create(lv_scr_act());
    lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 10);
    lv_obj_set_size(ta, lv_pct(90), 80);
    lv_obj_add_state(ta, LV_STATE_FOCUSED);

    lv_keyboard_set_textarea(kb, ta);
}
#endif
