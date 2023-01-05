#ifndef _soft_spi_ts_H
#define _soft_spi_ts_H

#include "main.h"

#define LOW 0
#define HIGH 1

#define SPI_MSB_FIRST 12
#define SPI_LSB_FIRST 13

#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3

#define SPI_CLOCK_DIV2 2
#define SPI_CLOCK_DIV4 4
#define SPI_CLOCK_DIV8 8
#define SPI_CLOCK_DIV16 16
#define SPI_CLOCK_DIV32 32
#define SPI_CLOCK_DIV64 64
#define SPI_CLOCK_DIV128 128
#define SPI_CLOCK_DIV256 256

/* // for cortex m3
static inline
void SetPinMode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode)
{
  register uint32_t *pReg = (uint32_t *)((uint32_t)((uint32_t)(&GPIOx->CRL) + (Pin >> 24)));
  MODIFY_REG(*pReg, ((GPIO_CRL_CNF0 | GPIO_CRL_MODE0) << (POSITION_VAL(Pin) * 4U)), (Mode << (POSITION_VAL(Pin) * 4U)));
} */

static inline
void SetPinPull(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Pull)
{
  MODIFY_REG(GPIOx->PUPDR, (GPIO_PUPDR_PUPDR0 << (POSITION_VAL(Pin) * 2U)), (Pull << (POSITION_VAL(Pin) * 2U)));
}

static inline
void SetPinMode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode)
{
  MODIFY_REG(GPIOx->MODER, (3U << (POSITION_VAL(Pin) * 2U)), (Mode << (POSITION_VAL(Pin) * 2U)));
}

static inline
void pin_in(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
  /* GPIO Ports Clock Enable */
  if(GPIOx==GPIOA) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  if(GPIOx==GPIOB) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  if(GPIOx==GPIOC) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  if(GPIOx==GPIOD) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);

  // LL_GPIO_SetPinSpeed(GPIOx, GPIO_Pin, LL_GPIO_SPEED_FREQ_LOW);
  // LL_GPIO_SetPinOutputType(GPIOx, GPIO_Pin, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinMode(GPIOx, GPIO_Pin, LL_GPIO_MODE_INPUT);
}

static inline
void pin_out(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
  /* GPIO Ports Clock Enable */
  if(GPIOx==GPIOA) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  if(GPIOx==GPIOB) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  if(GPIOx==GPIOC) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  if(GPIOx==GPIOD) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);

  LL_GPIO_SetPinSpeed(GPIOx, GPIO_Pin, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinOutputType(GPIOx, GPIO_Pin, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinMode(GPIOx, GPIO_Pin, LL_GPIO_MODE_OUTPUT);
}

static inline
void SetOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  // WRITE_REG(GPIOx->BSRR, PinMask);
  SET_BIT(GPIOx->ODR, PinMask);
}

static inline
void ResetOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  // WRITE_REG(GPIOx->BSRR, (PinMask << 16));
  CLEAR_BIT(GPIOx->ODR, PinMask);
}

static inline
void WriteOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinMask, int state)
{
  // pin_out(GPIOx, PinMask);

  if(state)
  {
    // GPIOx->ODR |= PinMask;
    SetOutputPin(GPIOx, PinMask);
  }
  else
  {
    // GPIOx->ODR &= ~PinMask;
    ResetOutputPin(GPIOx, PinMask);
  }
}

static inline
uint32_t ReadInputPort(GPIO_TypeDef *GPIOx)
{
  return (uint32_t)(READ_REG(GPIOx->IDR));
}

static inline
uint32_t IsInputPinSet(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return (READ_BIT(GPIOx->IDR, PinMask) == (PinMask));
}

static inline
uint32_t ReadInputPin(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
  uint32_t bitstatus;

  if(GPIOx->IDR & GPIO_Pin)
  {
    bitstatus = 1;
  }
  else
  {
    bitstatus = 0;
  }
  return bitstatus;
}

static inline
void soft_spi_begin(void)
{
  pin_out(TOUCH_MOSI_GPIO_Port, TOUCH_MOSI_Pin);
  pin_in(TOUCH_MISO_GPIO_Port, TOUCH_MISO_Pin);
  pin_out(TOUCH_CLK_GPIO_Port, TOUCH_CLK_Pin);
  pin_out(TOUCH_CS_GPIO_Port, TOUCH_CS_Pin);
  ResetOutputPin(TOUCH_CS_GPIO_Port, TOUCH_CS_Pin);
}

static inline
void soft_spi_end(void)
{
  SetOutputPin(TOUCH_CS_GPIO_Port, TOUCH_CS_Pin);
  pin_in(TOUCH_MOSI_GPIO_Port, TOUCH_MOSI_Pin);
  pin_in(TOUCH_MISO_GPIO_Port, TOUCH_MISO_Pin);
  pin_in(TOUCH_CLK_GPIO_Port, TOUCH_CLK_Pin);
  // pin_in(TOUCH_CS_GPIO_Port, TOUCH_CS_Pin);
}

void delay_tics(uint32_t tics);
uint32_t reverse_bits(uint32_t value, uint32_t len);
void soft_spi_init(void);
void soft_spi_begin(void);
void soft_spi_end(void);
void soft_spi_set_bit_order(uint8_t order);
void soft_spi_set_data_mode(uint8_t mode);
void soft_spi_set_clock_divider(uint32_t div);
void soft_spi_clk(uint8_t count);
void soft_spi_write(uint16_t val, uint16_t len);
uint16_t soft_spi_read(uint16_t len);
uint16_t soft_spi_transfer(uint16_t data, uint16_t len);

#endif // _soft_spi_ts_H

