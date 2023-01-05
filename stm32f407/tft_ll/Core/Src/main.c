/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "gpio.h"
// #include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>

#include "fsmc_ll.h"
#include "ili9341.h"
#include "xpt2046.h"
#include "soft_spi_ts.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

//extern uint16_t tp_pressed;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

extern TS_Point p; // define on __xpt2046_H
volatile bool ts_pressed;
volatile uint32_t ts_divide;

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  // HAL_Init();

  /* USER CODE BEGIN Init */
  // HAL_Init();
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN); // __HAL_RCC_SYSCFG_CLK_ENABLE();
  SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN); // __HAL_RCC_PWR_CLK_ENABLE();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_FSMC_Init();
  /* USER CODE BEGIN 2 */

  lcdBacklightOn();

  lcdInit();
  lcdSetOrientation(LCD_ORIENTATION_PORTRAIT_MIRROR);
  lcdFillRGB(COLOR_BLUE);
  lcdSetTextFont(&Font20);
  lcdSetTextColor(COLOR_CYAN, COLOR_BLUE);
  lcdFillRoundRect(160, 32, 64, 48, 8, COLOR_RED);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)  {
    get_point(&p); // get coordinates x y z from xpt2046
    xpt2046_read();
    lcdSetCursor(5,5);
    lcdPrintf("X%02i Y%02i Z%02i\n", (uint16_t)p.x, (uint16_t)p.y, (uint16_t)p.z);
    // lcdPrintf("X:%02i: Y:%02i\n", 22,44);

    LL_mDelay(250);
    LCD_DrawSpectrum(0,   0, 180, 110,  50);
    LCD_DrawSpectrum(0, 110, 180, 110, 120);
    LCD_DrawSpectrum(0, 220, 180, 100, 240);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_5)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLP_DIV_2);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_SetSystemCoreClock(168000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void  HAL_GPIO_EXTI_Callback ( uint16_t GPIO_Pin)
{

	/*
	if (GPIO_Pin ==T_PEN_Pin){
		tp_pressed = 1;
		if(XPT2046_TouchPressed()){
			if(XPT2046_TouchGetCoordinates(&x, &y))	{
				flag1=1;

				lcdSetCursor(20,20);
				lcdPrintf("x:%03i: y:%02i", y, 320-x);
				lcdDrawPixel(y, 320-x, COLOR_RED);

			}
		}

	}
	*/
}

void LCD_DrawSpectrum(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t brightness) {

    float c = 0.0f;
    uint16_t red, green, blue = 0;
    float fIncrement = 1.0 / width;
    uint16_t sixTimes = brightness * 6; //1530=255*6

	for(uint16_t i = x; i <= (x + width); i++) {

		if(c >= 0 && c <= (1/6.f)){
			red = brightness;
			green = sixTimes * c;
			blue = 0;
		} else if( c > (1/6.f) && c <= (1/3.f) ){
			red = brightness - (sixTimes * (c - 1/6.f));
			green = brightness;
			blue = 0;
		} else if( c > (1/3.f) && c <= (1/2.f)){
			red = 0;
			green = brightness;
			blue = sixTimes * (c - 1/3.f);
		} else if(c > (1/2.f) && c <= (2/3.f)) {
			red = 0;
			green = brightness - ((c - 0.5f) * sixTimes);
			blue = brightness;
		} else if( c > (2/3.f) && c <= (5/6.f) ){
			red = (c - (2/3.f)) * sixTimes;
			green = 0;
			blue = brightness;
		} else if(c > (5/6.f) && c <= 1 ){
			red = brightness;
			green = 0;
			blue = brightness - ((c - (5/6.f)) * sixTimes);
		}

		lcdDrawVLine( i, y, y+height, lcdColor565(red, green, blue));
		// LL_mDelay(1);

	  c += fIncrement;
  }

  c=0.0;


}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
