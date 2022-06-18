#ifndef __TIM_ENCODER_H__
#define __TIM_ENCODER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

extern int32_t encoder_data;
void EXTI_Callbac(void);

#ifdef __cplusplus
}
#endif

#endif /* __TIM_ENCODER_H__ */

