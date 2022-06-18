#ifndef LVGL_INIT_F407_H_
#define LVGL_INIT_F407_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TFT_EXT_FB		0  /*Frame buffer is located into an external SDRAM*/
#define TFT_USE_GPU		0  /*Enable hardware accelerator*/

void lv_lcd_init(void);

#ifdef __cplusplus
}
#endif

#endif /* LVGL_INIT_F407_H_ */
