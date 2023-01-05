#include "ILI9341_STM32_Driver.h"

volatile uint16_t LCD_HEIGHT = LV_VER_RES_MAX;
volatile uint16_t LCD_WIDTH = LV_HOR_RES_MAX;

extern DMA_HandleTypeDef hdma_memtomem_dma2_stream0;

uint16_t * lcdAddr = (uint16_t *) 0x60080000;

static lv_disp_drv_t disp_drv;
static volatile int32_t x1_flush;
static volatile int32_t y1_flush;
static volatile int32_t x2_flush;
static volatile int32_t y2_flush;
static volatile int32_t y_flush_act;
static volatile const lv_color_t * buf_to_flush;
static volatile bool refr_qry;
static volatile uint32_t t_last = 0;

void lv_lcd_init(void)
{
  static lv_color_t buf[LV_HOR_RES_MAX * FB_SIZE];
  static lv_disp_draw_buf_t disp_buf;
  lv_disp_draw_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * FB_SIZE);
  lv_disp_drv_init(&disp_drv);
  disp_drv.flush_cb = lcd_flush_cb;
  disp_drv.monitor_cb = monitor_cb;
  disp_drv.draw_buf = &disp_buf; /*Set an initialized buffer*/
  lv_disp_drv_register(&disp_drv);
}

void monitor_cb(lv_disp_drv_t * d, uint32_t t, uint32_t p)
{
  t_last = t;
}

static void lcd_flush_cb(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_p)
{
  int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
  int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
  int32_t act_x2 = area->x2 > LV_HOR_RES_MAX - 1 ? LV_HOR_RES_MAX - 1 : area->x2;
  int32_t act_y2 = area->y2 > LV_VER_RES_MAX - 1 ? LV_VER_RES_MAX - 1 : area->y2;
  x1_flush = act_x1;
  y1_flush = act_y1;
  x2_flush = act_x2;
  y2_flush = act_y2;
  y_flush_act = act_y1;
  buf_to_flush = color_p;
  HAL_StatusTypeDef err;
  ILI9341_Set_Address(x1_flush, y_flush_act, x2_flush, y_flush_act + 1);
  err = HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0,(uint32_t)buf_to_flush, (uint32_t)lcdAddr, (x2_flush - x1_flush + 1));
  if(err != HAL_OK)
  {
    while(1);
  }
}

void DMA_Init(void)
{
  __HAL_RCC_DMA2_CLK_ENABLE();
  hdma_memtomem_dma2_stream0.Instance = DMA2_Stream0;
  hdma_memtomem_dma2_stream0.Init.Channel = DMA_CHANNEL_0;
  hdma_memtomem_dma2_stream0.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma2_stream0.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma2_stream0.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma2_stream0.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  hdma_memtomem_dma2_stream0.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
  hdma_memtomem_dma2_stream0.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma2_stream0.Init.Priority = DMA_PRIORITY_VERY_HIGH;
  hdma_memtomem_dma2_stream0.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma2_stream0.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
  hdma_memtomem_dma2_stream0.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma2_stream0.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma2_stream0) != HAL_OK)
  {
    Error_Handler( );
  }

  HAL_DMA_RegisterCallback(&hdma_memtomem_dma2_stream0, HAL_DMA_XFER_CPLT_CB_ID, DMA_TransferComplete);
  HAL_DMA_RegisterCallback(&hdma_memtomem_dma2_stream0, HAL_DMA_XFER_ERROR_CB_ID, DMA_TransferError);
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}

static void DMA_TransferComplete(DMA_HandleTypeDef *han)
{
  y_flush_act ++;
  if(y_flush_act > y2_flush)
  {
    lv_disp_flush_ready(&disp_drv);
  }
  else
  {
    buf_to_flush += x2_flush - x1_flush + 1;
    HAL_StatusTypeDef err;
    ILI9341_Set_Address(x1_flush, y_flush_act, x2_flush, y_flush_act+1);
    err = HAL_DMA_Start_IT(han,(uint32_t)buf_to_flush, (uint32_t)lcdAddr, (x2_flush - x1_flush + 1));
    if( err != HAL_OK)
    {
      while(1);
    }
  }
}

static void DMA_TransferError(DMA_HandleTypeDef *han)
{
  while(1);
}

