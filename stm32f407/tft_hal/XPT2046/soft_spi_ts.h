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

// #define GPIO_Read(port,pin) HAL_GPIO_ReadPin(port,pin)
// #define GPIO_Write(port,pin,state) HAL_GPIO_WritePin(port,pin,state)
// #define ReadInputPin(port,pin) HAL_GPIO_ReadPin(port,pin)
// #define WriteOutputPin(port,pin,state) HAL_GPIO_WritePin(port,pin,state)


static inline
uint16_t ReadInputPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint16_t bitstatus;

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
void WriteOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinMask, int state)
{
  // pin_out(GPIOx, PinMask);

  if(state)
  {
    GPIOx->ODR |= PinMask;
    // SetOutputPin(GPIOx, PinMask);
  }
  else
  {
    GPIOx->ODR &= ~PinMask;
    // ResetOutputPin(GPIOx, PinMask);
  }
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

