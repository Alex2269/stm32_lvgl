#include "ili9341.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "ili9341.h"

static uint16_t tft_W;
static uint16_t tft_H;

static void lcdReset(void)
{
  WriteOutputPin(LCD_RST_GPIO_Port, LCD_RST_Pin, 0);
  LL_mDelay(250);
  WriteOutputPin(LCD_RST_GPIO_Port, LCD_RST_Pin, 1);
  lcdWriteCommand(ILI9341_SOFTRESET);
  LL_mDelay(50);
}

// Write an 8 bit command to the IC driver
static void lcdWriteCommand(unsigned char command)
{
  LCD_CmdWrite(command);
}

// Write an 16 bit data word to the IC driver
static void lcdWriteData(unsigned short data)
{
  LCD_DataWrite(data);
}

static unsigned short lcdReadData(void)
{
  return LCD_DataRead();
}

void lcdInit(void)
{
  lcdReset();
  lcdWriteCommand(0x01); // Software Reset
  LL_mDelay(1);
  lcdWriteCommand(0xCB); // Power Control A
  lcdWriteData(0x39);
  lcdWriteData(0x2C);
  lcdWriteData(0x00);
  lcdWriteData(0x34);
  lcdWriteData(0x02);
  LL_mDelay(1);
  lcdWriteCommand(0xCF); // Power Control B
  lcdWriteData(0x00);
  lcdWriteData(0xC1);
  lcdWriteData(0x30);
  LL_mDelay(1);
  lcdWriteCommand(0xE8); // Driver timing control A
  lcdWriteData(0x85);
  lcdWriteData(0x00);
  lcdWriteData(0x78);
  LL_mDelay(1);
  lcdWriteCommand(0xEA); // Driver timing control B
  lcdWriteData(0x00);
  lcdWriteData(0x00);
  LL_mDelay(1);
  lcdWriteCommand(0xED); // Power on Sequence control
  lcdWriteData(0x64);
  lcdWriteData(0x03);
  lcdWriteData(0x12);
  lcdWriteData(0x81);
  LL_mDelay(1);
  lcdWriteCommand(0xF7); // Pump ratio control
  lcdWriteData(0x20);
  LL_mDelay(1);
  lcdWriteCommand(0xC0); // Power Control 1
  lcdWriteData(0x10);
  LL_mDelay(1);
  lcdWriteCommand(0xC1); // Power Control 2
  lcdWriteData(0x10);
  LL_mDelay(1);
  lcdWriteCommand(0xC5); // VCOM Control 1
  lcdWriteData(0x3E);
  lcdWriteData(0x28);
  LL_mDelay(1);
  lcdWriteCommand(0xC7); // VCOM Control 2
  lcdWriteData(0x86);
  LL_mDelay(1);
  lcdWriteCommand(0x3A); // Pixel Format Set
  lcdWriteData(0x55); // 16bit
  LL_mDelay(1);
  lcdWriteCommand(0xB1);
  lcdWriteData(0x00);
  lcdWriteData(0x18); // Частота кадров 79 Гц
  LL_mDelay(1);
  lcdWriteCommand(0xB6); // Display Function Control
  lcdWriteData(0x08);
  lcdWriteData(0x82);
  lcdWriteData(0x27); // 320 строк
  LL_mDelay(1);
  lcdWriteCommand(0xF2); // Enable 3G
  lcdWriteData(0x00); // не включаем
  LL_mDelay(1);
  lcdWriteCommand(0x26); // Gamma set
  lcdWriteData(0x01); // Gamma Curve (G2.2) (Кривая цветовой гаммы)
  LL_mDelay(1);
  lcdWriteCommand(0xE0); // Positive Gamma Correction
  lcdWriteData(0x0F);
  lcdWriteData(0x31);
  lcdWriteData(0x2B);
  lcdWriteData(0x0C);
  lcdWriteData(0x0E);
  lcdWriteData(0x08);
  lcdWriteData(0x4E);
  lcdWriteData(0xF1);
  lcdWriteData(0x37);
  lcdWriteData(0x07);
  lcdWriteData(0x10);
  lcdWriteData(0x03);
  lcdWriteData(0x0E);
  lcdWriteData(0x09);
  lcdWriteData(0x00);
  LL_mDelay(1);
  lcdWriteCommand(0xE1); // Negative Gamma Correction
  lcdWriteData(0x00);
  lcdWriteData(0x0E);
  lcdWriteData(0x14);
  lcdWriteData(0x03);
  lcdWriteData(0x11);
  lcdWriteData(0x07);
  lcdWriteData(0x31);
  lcdWriteData(0xC1);
  lcdWriteData(0x48);
  lcdWriteData(0x08);
  lcdWriteData(0x0F);
  lcdWriteData(0x0C);
  lcdWriteData(0x31);
  lcdWriteData(0x36);
  lcdWriteData(0x0F);
  LL_mDelay(1);
  lcdWriteCommand(0x11); // Выйдем из спящего режим
  LL_mDelay(150);
  LL_mDelay(1);
  lcdWriteCommand(0x29); // Включение дисплея
  lcdWriteData(0x2C);
  // lcdSetOrientation(0);
}

void lcdBacklightOn(void)
{
  WriteOutputPin(LCD_BL_GPIO_Port, LCD_BL_Pin, 1);
}

void lcdBacklightOff(void)
{
  WriteOutputPin(LCD_BL_GPIO_Port, LCD_BL_Pin, 0);
}

void lcdDrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
  // Clip
  if ((x < 0) || (y < 0) || (x >= tft_W) || (y >= tft_H)) return;
  lcdSetWindow(x, y, x, y);
  lcdWriteData(color);
}

void lcdFillRGB(uint16_t color)
{
  lcdSetWindow(0, 0, tft_W - 1, tft_H - 1);
  int dimensions = tft_W * tft_H;
  while(dimensions--)
  {
    lcdWriteData(color);
  }
}

void lcdSetOrientation(lcdOrientationTypeDef value)
{
  // static uint16_t tft_W;
  // static uint16_t tft_H;
  lcdWriteCommand(0x36);
  switch(value)
  {
    case LCD_ORIENTATION_PORTRAIT:
    lcdWriteData(0x40|0x08);
    tft_W = 240;
    tft_H = 320;
    break;
    case LCD_ORIENTATION_LANDSCAPE:
    lcdWriteData(0x20|0x08);
    tft_W = 320;
    tft_H = 240;
    break;
    case LCD_ORIENTATION_PORTRAIT_MIRROR:
    lcdWriteData(0x80|0x08);
    tft_W = 240;
    tft_H = 320;
    break;
    case LCD_ORIENTATION_LANDSCAPE_MIRROR:
    lcdWriteData(0x40|0x80|0x20|0x08);
    tft_W = 320;
    tft_H = 240;
    break;
  }
  lcdSetWindow(0, 0, tft_W - 1, tft_H - 1);
}

/**
* \brief Sets window address
*
* \param x0 Left top window x-coordinate
* \param y0 Left top window y-coordinate
* \param x1 Rigth bottom window x-coordinate
* \param y1 Rigth bottom window y-coordinate
*
* \return void
*/
void lcdSetWindow(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1)
{
  lcdWriteCommand(ILI9341_COLADDRSET);
  lcdWriteData((x0 >> 8) & 0xFF);
  lcdWriteData(x0 & 0xFF);
  lcdWriteData((x1 >> 8) & 0xFF);
  lcdWriteData(x1 & 0xFF);
  lcdWriteCommand(ILI9341_PAGEADDRSET);
  lcdWriteData((y0 >> 8) & 0xFF);
  lcdWriteData(y0 & 0xFF);
  lcdWriteData((y1 >> 8) & 0xFF);
  lcdWriteData(y1 & 0xFF);
  lcdWriteCommand(ILI9341_MEMORYWRITE);
}

