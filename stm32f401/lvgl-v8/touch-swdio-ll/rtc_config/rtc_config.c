#include "rtc_config.h"
#include "rtc.h"

uint8_t aShowTime[24] = {0};
uint8_t aShowDate[24] = {0};

void TIME_Config(uint8_t Hours, uint8_t Minutes, uint8_t Seconds)
{
  LL_RTC_DisableWriteProtection(RTC);
  Enter_RTC_InitMode();
  LL_RTC_TIME_Config(RTC, LL_RTC_TIME_FORMAT_PM, Hours, Minutes, Seconds);
  Exit_RTC_InitMode();
  LL_RTC_EnableWriteProtection(RTC);
}

void DATE_Config(uint8_t WeekDay, uint8_t Day, uint8_t Month, int16_t Year)
{
  LL_RTC_DisableWriteProtection(RTC);
  Enter_RTC_InitMode();
  LL_RTC_DATE_Config(RTC, WeekDay, Day, Month, Year);
  Exit_RTC_InitMode();
  LL_RTC_EnableWriteProtection(RTC);
}

uint32_t Enter_RTC_InitMode(void)
{
  LL_RTC_EnableInitMode(RTC);
  while (LL_RTC_IsActiveFlag_INIT(RTC) != 1) __asm volatile ("nop");
  return RTC_ERROR_NONE;
}

uint32_t Exit_RTC_InitMode(void)
{
  LL_RTC_DisableInitMode(RTC);
  return (WaitForSynchro_RTC());
}

uint32_t WaitForSynchro_RTC(void)
{
  LL_RTC_ClearFlag_RS(RTC);
  while(LL_RTC_IsActiveFlag_RS(RTC) != 1) __asm volatile ("nop");
  return RTC_ERROR_NONE;
}

void Show_RTC_Calendar(void)
{
  sprintf((char*)aShowTime,"time: %.2d:%.2d:%.2d ",
         __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetHour(RTC)),
         __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetMinute(RTC)),
         __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetSecond(RTC)));
  printf("%s", aShowTime);

  sprintf((char*)aShowDate,"date: %.2d-%.2d-%.2d\n",
         __LL_RTC_CONVERT_BCD2BIN(LL_RTC_DATE_GetMonth(RTC)),
         __LL_RTC_CONVERT_BCD2BIN(LL_RTC_DATE_GetDay(RTC)),
         2000 + __LL_RTC_CONVERT_BCD2BIN(LL_RTC_DATE_GetYear(RTC)));
  printf("%s", aShowDate);
}
