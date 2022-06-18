#include "ili9341.h"
#include "main.h"
#include "lvgl_init_f407.h"
#include "lv_conf.h"
#include "lvgl/lvgl.h"
#include <string.h>
#include "stm32f4xx.h"

// DMA2_Stream0

static void lcd_flush_cb(lv_disp_draw_buf_t * drv, const lv_area_t * area, lv_color_t * color_p);
static void DMA_TransferComplete(void);
static lv_disp_drv_t disp_drv;

static volatile uint32_t t_saved = 0;

#define USE_DBL_BUFF 1
#define BUFF_LINES (LV_HOR_RES_MAX / 8 ) // 20 for double buffer, 40 for single buffer (to fit to RAM)
#define USE_DMA 1
#define USE_DMA_IRQ 1

void hal_dma_irqhandler(DMA_TypeDef *DMAx)
{
  /* Transfer Complete Interrupt management ***********************************/
  if(READ_BIT(DMA2->LISR ,DMA_LISR_TCIF0)==(DMA_LISR_TCIF0)) // Get Stream 0 transfer complete flag.
  {
    // Check if Transfer complete interrup is enabled. LL_DMA_IsEnabledIT_TC
    if(READ_BIT(DMA2_Stream0->CR, DMA_SxCR_TCIE) == DMA_SxCR_TCIE)
    {
      /* Clear the transfer complete flag */
      WRITE_REG(DMA2->LIFCR , DMA_LIFCR_CTCIF0); // Clear Stream 0 transfer complete flag.
      if((READ_BIT(DMA2->LISR ,DMA_LISR_HTIF0)==(DMA_LISR_HTIF0)))
      {
        /* Transfer complete callback */
        DMA_TransferComplete();
      }
    }
  }
}

  // (READ_BIT(DMAx->LISR ,DMA_LISR_HTIF0)==(DMA_LISR_HTIF0)); // Get Stream 0 half transfer flag. */
  // (READ_BIT(DMAx->LISR ,DMA_LISR_TCIF0)==(DMA_LISR_TCIF0)); // Get Stream 0 transfer complete flag. */
  // (READ_BIT(DMAx->LISR ,DMA_LISR_TEIF0)==(DMA_LISR_TEIF0)); // Get Stream 0 transfer error flag.
  // (READ_BIT(DMAx->LISR ,DMA_LISR_DMEIF0)==(DMA_LISR_DMEIF0)); // Get Stream 0 direct mode error flag.
  // (READ_BIT(DMAx->LISR ,DMA_LISR_FEIF0)==(DMA_LISR_FEIF0)); // Get Stream 0 FIFO error flag.
  //  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CHTIF0); // Clear Stream 0 half transfer flag.
  //  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CTCIF0); // Clear Stream 0 transfer complete flag.
  //  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CTEIF0); // Clear Stream 0 transfer error flag.
  //  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CDMEIF0); // Clear Stream 0 direct mode error flag.
  //  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CFEIF0); // Clear Stream 0 FIFO error flag.

void hal_dma_start(uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
  /* calculate DMA base and stream number */
  // DMA_Base_Registers *regs = (DMA_Base_Registers *)DMA2_BASE;

  /* Configure the source, destination address and the data length */
  // DMA_SetConf(SrcAddress, DstAddress, DataLength);

  /* Clear DBM bit */
  DMA2_Stream0->CR &= (uint32_t)(~DMA_SxCR_DBM);
  /* Configure DMA Stream data length */
  DMA2_Stream0->NDTR = DataLength;
  /* Configure DMA Stream source address */
  DMA2_Stream0->PAR = SrcAddress;
  /* Configure DMA Stream destination address */
  DMA2_Stream0->M0AR = DstAddress;

  // /* Clear all interrupt flags at correct offset within the register */
  // // regs->IFCR = 0x3FU << DMA2_BASE;
  WRITE_REG(DMA2->LIFCR , DMA_LIFCR_CTCIF0); // Clear Stream 0 transfer complete flag.
  WRITE_REG(DMA2->LIFCR , DMA_LIFCR_CHTIF0); // Clear Stream 0 half transfer flag.
  WRITE_REG(DMA2->LIFCR , DMA_LIFCR_CTEIF0); // Clear Stream 0 transfer error flag.

  /* Enable interrupts:
   * Transfer error interrupt. DMA_SxCR_TEIE
   * Transfer complete interrupt. DMA_SxCR_TCIE
   * Direct mode error interrupt. DMA_SxCR_DMEIE */
  // DMA2_Stream0->CR |= DMA_SxCR_TCIE | DMA_SxCR_TEIE | DMA_SxCR_DMEIE;

  /* Enable the Peripheral */
  // __HAL_DMA_ENABLE(hdma); // DMA_EnableStream(DMA2, 0);
  DMA2_Stream0->CR |= DMA_SxCR_EN;
  // SET_BIT(DMA2_Stream0->CR, DMA_SxCR_DBM);
}

void hal_dma_start_it(uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
  // LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_0);

  /* calculate DMA base and stream number */
  // DMA_Base_Registers *regs = (DMA_Base_Registers *)DMA2_BASE;

  /* Configure the source, destination address and the data length */
  // DMA_SetConf(SrcAddress, DstAddress, DataLength);

  /* Clear DBM bit */
  DMA2_Stream0->CR &= (uint32_t)(~DMA_SxCR_DBM);
  /* Configure DMA Stream data length */
  DMA2_Stream0->NDTR = DataLength;
  /* Configure DMA Stream source address */
  DMA2_Stream0->PAR = SrcAddress;
  /* Configure DMA Stream destination address */
  DMA2_Stream0->M0AR = DstAddress;

  /* Clear all interrupt flags at correct offset within the register */
  // regs->IFCR = 0x3FU << DMA2_BASE;
  WRITE_REG(DMA2->LIFCR , DMA_LIFCR_CTCIF0); // Clear Stream 0 transfer complete flag.
  WRITE_REG(DMA2->LIFCR , DMA_LIFCR_CHTIF0); // Clear Stream 0 half transfer flag.
  WRITE_REG(DMA2->LIFCR , DMA_LIFCR_CTEIF0); // Clear Stream 0 transfer error flag.

  /* Enable interrupts:
  * Transfer error interrupt. DMA_SxCR_TEIE
  * Transfer complete interrupt. DMA_SxCR_TCIE
  * Direct mode error interrupt. DMA_SxCR_DMEIE */
  DMA2_Stream0->CR |= DMA_SxCR_TCIE | DMA_SxCR_TEIE | DMA_SxCR_DMEIE;

  /* Enable the Peripheral */
  // __HAL_DMA_ENABLE(hdma); // DMA_EnableStream(DMA2, 0);
  DMA2_Stream0->CR |= DMA_SxCR_EN;
  // SET_BIT(DMA2_Stream0->CR, DMA_SxCR_DBM);
}

void monitor_cb(lv_disp_drv_t * d, uint32_t t, uint32_t p)
{
  t_saved = t;
}

void lv_lcd_init()
{
  /* define & init buffers */
  static lv_disp_draw_buf_t buf;
  #if USE_DBL_BUFF
    static lv_color_t disp_buf1[LV_HOR_RES_MAX * BUFF_LINES];
    static lv_color_t disp_buf2[LV_HOR_RES_MAX * BUFF_LINES];
    lv_disp_draw_buf_init(&buf, disp_buf1, disp_buf2, LV_HOR_RES_MAX * BUFF_LINES);
  #else
    static lv_color_t disp_buf1[LV_HOR_RES_MAX * BUFF_LINES];
    lv_disp_draw_buf_init(&buf, disp_buf1, NULL, LV_HOR_RES_MAX * BUFF_LINES);
  #endif
  lcdInit(); /* Init LCD hardware */
  lcdSetOrientation(LCD_ORIENTATION_PORTRAIT_MIRROR);
  lv_disp_drv_init(&disp_drv); /*Basic driver initialization*/
  disp_drv.draw_buf = &buf; /*Set an initialized buffer*/
  disp_drv.flush_cb = lcd_flush_cb; /*Set a flush callback to draw to the display*/
  disp_drv.monitor_cb = monitor_cb;
  disp_drv.full_refresh = 0;
  lv_disp_drv_register(&disp_drv);
  // register DMA IRQ callback
  #if USE_DMA_IRQ
    DMA_TransferComplete;
  #endif
}

/**
* Flush a color buffer
* @param x1 left coordinate of the rectangle
* @param x2 right coordinate of the rectangle
* @param y1 top coordinate of the rectangle
* @param y2 bottom coordinate of the rectangle
* @param color_p pointer to an array of colors
*/
static void lcd_flush_cb(lv_disp_draw_buf_t * drv, const lv_area_t * area, lv_color_t * color_p)
{
  /*Truncate the area to the screen*/
  int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
  int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
  int32_t act_x2 = area->x2 > LV_HOR_RES_MAX - 1 ? LV_HOR_RES_MAX - 1 : area->x2;
  int32_t act_y2 = area->y2 > LV_VER_RES_MAX - 1 ? LV_VER_RES_MAX - 1 : area->y2;

  lcdSetWindow(act_x1,act_y1,act_x2,act_y2);

  #if !USE_DMA // Without DMA
  int32_t x, y;
  for(y = act_y1; y <= act_y2; y++)
  {
    for(x = act_x1; x <= act_x2; x++)
    {
      // lcdDrawPixel(x,y, color_p->full);
      *(uint16_t *)(LCD_BASE1) = color_p->full;
      color_p++;
    }
  }
  lv_disp_flush_ready(&disp_drv);
  #else
  #if USE_DMA_IRQ // Using DMA with IRQ
   hal_dma_start_it( (uint32_t)color_p, (uint32_t)LCD_BASE1, (act_x2 - act_x1 + 1) * (act_y2 - act_y1 + 1));
  /* lv_disp_flush_ready(&disp_drv) is located in DMA_TransferComplete() callback */
  #else // Using DMA without IRQ
   hal_dma_start((uint32_t)color_p, (uint32_t)LCD_BASE1, (act_x2 - act_x1 + 1) * (act_y2 - act_y1 + 1));
   lv_disp_flush_ready(&disp_drv);
  #endif
  #endif
}

// DMA Interrupt Transfer complete callback
static void DMA_TransferComplete(void)
{
  // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6); // toggle LED on interrupt
  lv_disp_flush_ready(&disp_drv);
}

