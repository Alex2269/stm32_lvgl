
#ifndef ILI9341_H_
#define ILI9341_H_

#include "main.h"
// #include "colors.h"
#include "registers.h"
#include <stdbool.h>

#define LCD_BASE0        		((uint32_t)0x60000000)
#define LCD_BASE1        		((uint32_t)0x60000000+(2<<18)) // sets FSMC_A18

#define LCD_CmdWrite(command)	*(volatile uint16_t *) (LCD_BASE0) = (command)
#define LCD_DataWrite(data)		*(volatile uint16_t *) (LCD_BASE1) = (data)
#define	LCD_StatusRead()		*(volatile uint16_t *) (LCD_BASE0) // if use read  Mcu interface DB0~DB15 needs increase pull high
#define	LCD_DataRead()			*(volatile uint16_t *) (LCD_BASE1) // if use read  Mcu interface DB0~DB15 needs increase pull high

#define swap(a, b) { int16_t t = a; a = b; b = t; }

#define ASSEMBLE_RGB(R, G, B)    ((((R)& 0xF8) << 8) | (((G) & 0xFC) << 3) | (((B) & 0xF8) >> 3))

// Any LCD needs to implement these common methods, which allow the low-level
// initialisation and pixel-setting details to be abstracted away from the
// higher level drawing and graphics code.

typedef enum
{
  LCD_ORIENTATION_PORTRAIT 			= 0,
  LCD_ORIENTATION_LANDSCAPE 		= 1,
  LCD_ORIENTATION_PORTRAIT_MIRROR 	= 2,
  LCD_ORIENTATION_LANDSCAPE_MIRROR 	= 3
} lcdOrientationTypeDef;

static void lcdReset(void);
static void lcdWriteCommand(unsigned char command);
static void lcdWriteData(unsigned short data);
static unsigned short lcdReadData(void);
void lcdInit(void);
void lcdBacklightOn(void);
void lcdDrawPixel(uint16_t x, uint16_t y, uint16_t color);
void lcdFillRGB(uint16_t color);
void lcdSetOrientation(lcdOrientationTypeDef value);
void lcdSetWindow(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1);

#endif /* ILI9341_H_ */

