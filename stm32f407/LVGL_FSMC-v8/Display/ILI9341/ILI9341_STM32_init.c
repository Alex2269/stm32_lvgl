#include "ILI9341_STM32_init.h"

extern volatile uint16_t LCD_HEIGHT;
extern volatile uint16_t LCD_WIDTH;

void ILI9341_Write_Command(uint16_t data)
{
  ADDR_CMD = (data);
}

void ILI9341_Write_Data(uint16_t data)
{
  ADDR_DATA = (data);
}

uint16_t ILI9341_Read_Data(void)
{
  volatile uint16_t data;
  data=ADDR_DATA;
  return data;
}

void lcdDelay(uint32_t delayms)
{
  HAL_Delay(delayms);
}

void ILI9341_Reset(void)
{
  HAL_GPIO_WritePin(DISP_LED_GPIO_Port, DISP_LED_Pin, GPIO_PIN_RESET);
  ILI9341_Write_Command(0x01);
  lcdDelay(500);
  HAL_GPIO_WritePin(DISP_LED_GPIO_Port, DISP_LED_Pin, GPIO_PIN_SET);
}

void ILI9341_Init(void)
{
  DMA_Init();
  ILI9341_Enable();
  ILI9341_Reset();
  ILI9341_Write_Command(0xCB);
  ILI9341_Write_Data(0x39);
  ILI9341_Write_Data(0x2C);
  ILI9341_Write_Data(0x00);
  ILI9341_Write_Data(0x34);
  ILI9341_Write_Data(0x02);
  ILI9341_Write_Command(0xCF);
  ILI9341_Write_Data(0x00);
  ILI9341_Write_Data(0xC1);
  ILI9341_Write_Data(0x30);
  ILI9341_Write_Command(0xE8);
  ILI9341_Write_Data(0x85);
  ILI9341_Write_Data(0x00);
  ILI9341_Write_Data(0x78);
  ILI9341_Write_Command(0xEA);
  ILI9341_Write_Data(0x00);
  ILI9341_Write_Data(0x00);
  ILI9341_Write_Command(0xED);
  ILI9341_Write_Data(0x64);
  ILI9341_Write_Data(0x03);
  ILI9341_Write_Data(0x12);
  ILI9341_Write_Data(0x81);
  ILI9341_Write_Command(0xF7);
  ILI9341_Write_Data(0x20);
  ILI9341_Write_Command(0xC0);
  ILI9341_Write_Data(0x23);
  ILI9341_Write_Command(0xC1);
  ILI9341_Write_Data(0x10);
  ILI9341_Write_Command(0xC5);
  ILI9341_Write_Data(0x3E);
  ILI9341_Write_Data(0x28);
  ILI9341_Write_Command(0xC7);
  ILI9341_Write_Data(0x86);
  ILI9341_Write_Command(0x36);
  ILI9341_Write_Data(0x48);
  ILI9341_Write_Command(0x3A);
  ILI9341_Write_Data(0x55);
  ILI9341_Write_Command(0xB1);
  ILI9341_Write_Data(0x00);
  ILI9341_Write_Data(0x18);
  ILI9341_Write_Command(0xB6);
  ILI9341_Write_Data(0x08);
  ILI9341_Write_Data(0x82);
  ILI9341_Write_Data(0x27);
  ILI9341_Write_Command(0xF2);
  ILI9341_Write_Data(0x00);
  ILI9341_Write_Command(0x26);
  ILI9341_Write_Data(0x01);
  ILI9341_Write_Command(0xE0);
  ILI9341_Write_Data(0x0F);
  ILI9341_Write_Data(0x31);
  ILI9341_Write_Data(0x2B);
  ILI9341_Write_Data(0x0C);
  ILI9341_Write_Data(0x0E);
  ILI9341_Write_Data(0x08);
  ILI9341_Write_Data(0x4E);
  ILI9341_Write_Data(0xF1);
  ILI9341_Write_Data(0x37);
  ILI9341_Write_Data(0x07);
  ILI9341_Write_Data(0x10);
  ILI9341_Write_Data(0x03);
  ILI9341_Write_Data(0x0E);
  ILI9341_Write_Data(0x09);
  ILI9341_Write_Data(0x00);
  ILI9341_Write_Command(0xE1);
  ILI9341_Write_Data(0x00);
  ILI9341_Write_Data(0x0E);
  ILI9341_Write_Data(0x14);
  ILI9341_Write_Data(0x03);
  ILI9341_Write_Data(0x11);
  ILI9341_Write_Data(0x07);
  ILI9341_Write_Data(0x31);
  ILI9341_Write_Data(0xC1);
  ILI9341_Write_Data(0x48);
  ILI9341_Write_Data(0x08);
  ILI9341_Write_Data(0x0F);
  ILI9341_Write_Data(0x0C);
  ILI9341_Write_Data(0x31);
  ILI9341_Write_Data(0x36);
  ILI9341_Write_Data(0x0F);
  ILI9341_Write_Command(0x11);
  lcdDelay(120);
  ILI9341_Write_Command(0x29);
  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);

  lv_lcd_init();
}

void ILI9341_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
  ILI9341_Write_Command(0x2A);
  ILI9341_Write_Data(X1>>8);
  ILI9341_Write_Data(X1);
  ILI9341_Write_Data(X2>>8);
  ILI9341_Write_Data(X2);
  ILI9341_Write_Command(0x2B);
  ILI9341_Write_Data(Y1>>8);
  ILI9341_Write_Data(Y1);
  ILI9341_Write_Data(Y2>>8);
  ILI9341_Write_Data(Y2);
  ILI9341_Write_Command(0x2C);
}

void ILI9341_Set_Rotation(uint8_t Rotation)
{
  uint8_t screen_rotation = Rotation;
  ILI9341_Write_Command(0x36);
  lcdDelay(1);
  switch(screen_rotation)
  {
    case SCREEN_VERTICAL_1:
    ILI9341_Write_Data(0x40|0x08);
    LCD_WIDTH = 240;
    LCD_HEIGHT = 320;
    break;
    case SCREEN_HORIZONTAL_1:
    ILI9341_Write_Data(0x20|0x08);
    LCD_WIDTH = 320;
    LCD_HEIGHT = 240;
    break;
    case SCREEN_VERTICAL_2:
    ILI9341_Write_Data(0x80|0x08);
    LCD_WIDTH = 240;
    LCD_HEIGHT = 320;
    break;
    case SCREEN_HORIZONTAL_2:
    ILI9341_Write_Data(0x40|0x80|0x20|0x08);
    LCD_WIDTH = 320;
    LCD_HEIGHT = 240;
    break;
    default:
    break;
  }
}

void ILI9341_Enable(void)
{
}
