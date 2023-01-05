#include "stm32_tick.h"
// #include "core_cm3.h"

uint32_t sys_tick_config(uint32_t reload)
{
  if ((reload - 1UL) > 1e6L)
  {
    return (1UL); /* Reload value impossible */
  }

  NVIC_SetPriority(SysTick_IRQn, 7UL);  /* set Priority for Systick Interrupt */
  SysTick->CTRL = 0b0110;
  SysTick->LOAD = reload;
  // SysTick->VAL  = 0x0UL;
  SysTick->CTRL = 0b0111;

  return (0UL);                         /* Function successful */
}

void ticks_init(void)
{
  sys_tick_config(SystemCoreClock / (uint32_t)1e3L); // system tick 1ms
  SCB_DEMCR   |= 0x01000000;
  DWT_CONTROL &= ~1; // disable the counter
  DWT_CYCCNT   = 0xF0000000ul;
  DWT_CONTROL |= 1; // enable the counter
}

void delay_us(volatile uint32_t us)
{
  for(volatile uint32_t i = (SystemCoreClock / (uint32_t)10e6L) * us; i; i--)
  {
    __asm volatile ("nop");
  }
}

void delay_ms(volatile uint32_t ms)
{
  for(volatile uint32_t i = (SystemCoreClock / (uint32_t)10e3L) * ms; i; i--)
  {
    __asm volatile ("nop");
  }
}

void delay(volatile uint32_t ms)
{
  for(volatile uint32_t i = (SystemCoreClock / (uint32_t)10e3L) * ms; i; i--)
  {
    __asm volatile ("nop");
  }
}

