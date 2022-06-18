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
#include "rtc.h"
#include "gpio.h"
// #include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fsmc_ll.h"
#include "ili9341.h"
#include <stdio.h>
#include <string.h>
#include "lvgl/lvgl.h"
#include "lvgl_init_f407.h"

#include "touchpad.h"

#include "lv_demo_conf.h"

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

// RTC_TimeTypeDef rtcTime;
// RTC_DateTypeDef rtcDate;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern void initialise_monitor_handles(void);
// extern TS_Point p; // define on __xpt2046_H

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
#ifdef SEMIHOSTING_ENABLE
  initialise_monitor_handles();
#endif
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/

  /* USER CODE BEGIN Init */
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
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */

  // ---------------------
  lcdBacklightOn();

  // lcdInit();
  lv_init();
  lv_lcd_init();

    // LCD_ORIENTATION_PORTRAIT 		= 0,
    // LCD_ORIENTATION_LANDSCAPE 		= 1,
    // LCD_ORIENTATION_PORTRAIT_MIRROR 	= 2,
    // LCD_ORIENTATION_LANDSCAPE_MIRROR = 3
  lcdSetOrientation(LCD_ORIENTATION_LANDSCAPE);
  // lcdFillRGB(0);
  // LL_mDelay(250);

  lv_touchpad_init();
  // ---------------------

  // ---------------------

  // lv_example_arc_1();
  // lv_example_arc_2();

  // lv_example_animimg_1();

  // lv_example_bar_1();
  // lv_example_bar_2();
  // lv_example_bar_3();
  // lv_example_bar_4();
  // lv_example_bar_5();
  // lv_example_bar_6();

  // lv_example_btn_1();
  // lv_example_btn_2();
  // lv_example_btn_3();

  // lv_example_btnmatrix_1();
  // lv_example_btnmatrix_2();
  // lv_example_btnmatrix_3();

  // lv_example_calendar_1();

  // lv_example_canvas_1();
  // lv_example_canvas_2();

  // lv_example_chart_1();
  // lv_example_chart_2();
  // lv_example_chart_3();
  // lv_example_chart_4();
  // lv_example_chart_5();
  // lv_example_chart_6();
  // lv_example_chart_7();
  // lv_example_chart_8();
  // lv_example_chart_9();

  // lv_example_checkbox_1();
  // lv_example_checkbox_2();

  // lv_example_colorwheel_1();

  // lv_example_dropdown_1();
  // lv_example_dropdown_2();
  // lv_example_dropdown_3();

  // lv_example_img_1();
  // lv_example_img_2();
  // lv_example_img_3();
  // lv_example_img_4();

  // lv_example_imgbtn_1();

  // lv_example_keyboard_1();

  // lv_example_label_1();
  // lv_example_label_2();
  // lv_example_label_3();
  // lv_example_label_4();

  // lv_example_led_1();

  // lv_example_line_1();

  // lv_example_list_1();
  // lv_example_list_2();

  // lv_example_menu_1();
  // lv_example_menu_2();
  // lv_example_menu_3();
  // lv_example_menu_4();
  // lv_example_menu_5();

  // lv_example_meter_1();
  // lv_example_meter_2();
  // lv_example_meter_3(); // clock with dial
  // lv_example_meter_4();

  // lv_example_msgbox_1();

  // lv_example_obj_1();
  // lv_example_obj_2();

  // lv_example_roller_1();
  // lv_example_roller_2();
  // lv_example_roller_3();

  // lv_example_slider_1();
  // lv_example_slider_2();
  // lv_example_slider_3();

  // lv_example_spinbox_1();

  // lv_example_spinner_1();

  // lv_example_switch_1();

  // lv_example_table_1();
  // lv_example_table_2();

  // lv_example_tabview_1();
  // lv_example_tabview_2();

  // lv_example_textarea_1();
  // lv_example_textarea_2();
  // lv_example_textarea_3();

  // lv_example_tileview_1();

  // lv_example_win_1();

  // lv_example_span_1();

  // ---------------------

  // ---------------------
   lv_demo_widgets();
  // lv_demo_stress();
  // lv_demo_benchmark();
  // lv_demo_music();

  // ---------------------

  // ---------------------
  // lv_example_style_11();
  // lv_example_scroll_1();
  // lv_example_flex_1();
  // lv_example_flex_6();
  // lv_example_event_1();
  // ---------------------


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)  {
    lv_task_handler();
    LL_mDelay(5);
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
  LL_PWR_EnableBkUpAccess();
  LL_RCC_LSE_Enable();

   /* Wait till LSE is ready */
  while(LL_RCC_LSE_IsReady() != 1)
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
  LL_Init1msTick(168000000);
  LL_SetSystemCoreClock(168000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /*
  if (GPIO_Pin == MY_Pin)
  { ... }
  */
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

