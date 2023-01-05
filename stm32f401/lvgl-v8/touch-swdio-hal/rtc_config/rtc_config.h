#ifndef rtc_config_h
#define rtc_config_h

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define RTC_ERROR_NONE 0

void TIME_Config(uint8_t Hours, uint8_t Minutes, uint8_t Seconds);
void DATE_Config(uint8_t WeekDay, uint8_t Day, uint8_t Month, int16_t Year);
uint32_t Enter_RTC_InitMode(void);
uint32_t Exit_RTC_InitMode(void);
uint32_t WaitForSynchro_RTC(void);
void Show_RTC_Calendar(void);

#ifdef __cplusplus
}
#endif

#endif /* rtc_config_h */

