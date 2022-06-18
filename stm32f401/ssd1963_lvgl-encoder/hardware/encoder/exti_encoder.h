#ifndef __TIM_ENCODER_H__
#define __TIM_ENCODER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

extern int32_t encoder_data;
extern uint8_t encBtnFlag;
extern uint8_t ButtonCount;

void EXTI_Callbac_Encoder(void);
void EXTI_Callbac_Button(void);

#ifdef __cplusplus
}
#endif

#endif /* __TIM_ENCODER_H__ */
