#ifndef ILI9341_STM32_init_H
#define ILI9341_STM32_init_H

#include "ILI9341_STM32_Driver.h"
#include "config.h"

#include "main.h"
#include "lv_conf.h"
#include "lvgl/lvgl.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"


void ILI9341_Write_Command(uint16_t data);
void ILI9341_Write_Data(uint16_t data);
uint16_t ILI9341_Read_Data(void);
void lcdDelay(uint32_t delayms);
void ILI9341_Reset(void);
void ILI9341_Init(void);
void ILI9341_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);
void ILI9341_Set_Rotation(uint8_t Rotation);
void ILI9341_Enable(void);

#endif // ILI9341_STM32_init_H

