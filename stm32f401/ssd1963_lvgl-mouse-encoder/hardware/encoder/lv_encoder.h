
#ifndef LVGL_INIT_ENCODER_H_
#define LVGL_INIT_ENCODER_H_

#include "main.h"
#include "lvgl.h"
#include "lvgl/lvgl.h"
#include "stm32f4xx.h"
#include "exti_encoder.h"
#include "lv_conf.h"

#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void encoder_init(void);
void Interrupt_EncoderChange(void);
void Interrupt_ButtonPressed(void);

#ifdef __cplusplus
}
#endif

#endif /* LVGL_INIT_ENCODER_H_ */
