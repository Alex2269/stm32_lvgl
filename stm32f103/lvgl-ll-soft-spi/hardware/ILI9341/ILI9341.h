
#ifndef ILI9341_STM32_DRIVER_H
#define ILI9341_STM32_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#define MINIMUM_MEMORY

// #include "stm32f1xx_hal.h"


#include <stdbool.h>
#include <stddef.h>

#ifndef MINIMUM_MEMORY
#include "fonts.h"
#endif

#include "main.h"



#define HORIZONTAL_IMAGE	0
#define VERTICAL_IMAGE		1

#define ILI9341_SCREEN_HEIGHT 	240
#define ILI9341_SCREEN_WIDTH 	320

#define LCD_LOG_WIDTH ILI9341_SCREEN_WIDTH / 2
#define LCD_LOG_HEIGHT ILI9341_SCREEN_HEIGHT / 2

//SPI INSTANCE
// #define HSPI_INSTANCE	&hspi1
// extern SPI_HandleTypeDef hspi1;   //defined in main.c

#define BURST_MAX_SIZE 	500

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
#define ASSEMBLE_RGB(R, G, B)    ((((R)& 0xF8) << 8) | (((G) & 0xFC) << 3) | (((B) & 0xF8) >> 3))



#define SCREEN_VERTICAL_1		0
#define SCREEN_HORIZONTAL_1		1
#define SCREEN_VERTICAL_2		2
#define SCREEN_HORIZONTAL_2		3

#define LOW 0
#define HI 1

static inline void
write_pin(GPIO_TypeDef *GPIOx, uint32_t PinMask, uint16_t PinState)
{
  if (PinState != 0)
  {
    WRITE_REG(GPIOx->BSRR, (PinMask >> 8U) & 0x0000FFFFU);
  }
  else
  {
    WRITE_REG(GPIOx->BRR, (PinMask >> 8U) & 0x0000FFFFU);
  }
}

/**
static inline void
write_pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint16_t PinState)
{
  if (PinState != GPIO_PIN_RESET)
  {
    GPIOx->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOx->BSRR = (uint32_t)GPIO_Pin << 16u;
  }
}
**/

void ILI9341_SPI_Init(void);
void ILI9341_SPI_Send(unsigned char SPI_Data);
void ILI9341_Write_Command(uint8_t Command);
void ILI9341_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);
void ILI9341_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void ILI9341_Reset(void);
void ILI9341_Set_Rotation(uint8_t Rotation);
void ILI9341_Enable(void);
void ILI9341_Init(void);
void ILI9341_Fill_Screen(uint16_t Colour);
void ILI9341_Draw_Colour(uint16_t Colour);
void ILI9341_Draw_Pixel(uint16_t X,uint16_t Y,uint16_t Colour);
void ILI9341_Draw_Colour_Burst(uint16_t Colour, uint32_t Size);
void ILI9341_Write_Data(uint8_t Data);
void ILI9341_WriteData(uint8_t* buff, size_t buff_size);
void ILI9341_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t* data);
void ILI9341_Draw_Image(uint16_t x, uint16_t y,  uint16_t width, uint16_t height,const char* Image_Array, uint8_t Orientation);

#ifndef MINIMUM_MEMORY
void ILI9341_Draw_Rectangle(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint16_t Colour);
void ILI9341_Draw_Rectangle_Centered(uint16_t Width, uint16_t Height, uint16_t Colour);
void ILI9341_Draw_Hollow_Rectangle_Centered(uint16_t Width, uint16_t Height, uint16_t Colour);
void ILI9341_Draw_Hollow_Rectangle(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t Colour);

void ILI9341_Draw_Horizontal_Line(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Colour);
void ILI9341_Draw_Vertical_Line(uint16_t X, uint16_t Y, uint16_t Height, uint16_t Colour);
void ILI9341_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
void ILI9341_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
void ILI9341_InvertColors(bool invert);

/*----------------- GFX --------------------*/

void ILI9341_Draw_Hollow_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour);
void ILI9341_Draw_Filled_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour);
void ILI9341_Draw_Hollow_Rectangle_Coord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t Colour);
void ILI9341_Draw_Filled_Rectangle_Coord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t Colour);
void ILI9341_Draw_Char(char Character, uint8_t X, uint8_t Y, uint16_t Colour, uint16_t Size, uint16_t Background_Colour);
void ILI9341_Draw_Text(const char* Text, uint8_t X, uint8_t Y, uint16_t Colour, uint16_t Size, uint16_t Background_Colour);
void ILI9341_Draw_Filled_Rectangle_Size_Text(uint16_t X0, uint16_t Y0, uint16_t Size_X, uint16_t Size_Y, uint16_t Colour);

//USING CONVERTER: http://www.digole.com/tools/PicturetoC_Hex_converter.php
//65K colour (2Bytes / Pixel)
void ILI9341_Draw_Image(uint16_t width, uint16_t height,const char* Image_Array, uint8_t Orientation);

void ILI9341_LogToLCD(char* buff );
void ILI9341_Log_SetColors(uint16_t fcolor,uint16_t bcolor);
void ILI9341_Log_SetFColor(uint16_t fcolor);
void ILI9341_Log_SetBColor(uint16_t bcolor);
void ILI9341_Log_SetFontNr(uint8_t fontnr);
void ILI9341_Log_Init(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t bcolor, uint16_t fcolor, uint8_t fontnr);

#endif

#ifdef __cplusplus
}
#endif



#endif

