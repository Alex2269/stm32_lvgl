#ifndef ILI9341_STM32_DRIVER_H
#define ILI9341_STM32_DRIVER_H


#include "ILI9341_STM32_init.h"
#include "config.h"

#include "main.h"
#include "lv_conf.h"
#include "lvgl/lvgl.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"


//----------------- address FSMS bus - has to be a volatile -----------------
// PD11   ------> FSMC_A16
// PD13   ------> FSMC_A18
#define ADDR_CMD  *(volatile uint16_t*)(0x60000000) // clears A18
// #define ADDR_DATA *(volatile uint16_t*)(0x60000000+(2<<16)) // sets FSMC_A16
#define ADDR_DATA *(volatile uint16_t*)(0x60000000+(2<<18)) // sets FSMC_A18
//---------------------------------------------------------------------------

#define swap(a,b) {int16_t t=a;a=b;b=t;}

// //------------------------------------------------
// #define convert24to16(x) (((x & 0x00F80000)>>8)|((x & 0x0000FC00)>>5)|((x & 0x000000F8)>>3))
// //------------------------------------------------

// #define		max(a,b)		(a>b)?a:b
// #define		min(a,b)		(a<b)?a:b
// #define		abs(a)			(a>=0)?a:(-a)

#define ILI9341_CMD_MEMORY_WRITE  0x2C
#define ILI9341_CMD_MEMORY_READ   0x2E

#define BURST_MAX_SIZE  500

#define BLACK       0x0000      
#define NAVY        0x000F      
#define DARKGREEN   0x03E0      
#define DARKCYAN    0x03EF      
#define MAROON      0x7800      
#define PURPLE      0x780F      
#define OLIVE       0x7BE0      
#define LIGHTGREY   0xC618      
#define DARKGREY    0x7BEF      
#define BLUE        0x001F      
#define GREEN       0x07E0      
#define CYAN        0x07FF      
#define RED         0xF800     
#define MAGENTA     0xF81F      
#define YELLOW      0xFFE0      
#define WHITE       0xFFFF      
#define ORANGE      0xFD20      
#define GREENYELLOW 0xAFE5     
#define PINK        0xF81F

#define SCREEN_VERTICAL_1     0
#define SCREEN_HORIZONTAL_1   1
#define SCREEN_VERTICAL_2     2
#define SCREEN_HORIZONTAL_2   3

void lv_lcd_init(void);
void monitor_cb(lv_disp_drv_t * d, uint32_t t, uint32_t p);
static void lcd_flush_cb(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_p);
void DMA_Init(void);
static void DMA_TransferComplete(DMA_HandleTypeDef *han);
static void DMA_TransferError(DMA_HandleTypeDef *han);

#endif

