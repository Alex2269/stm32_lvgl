#include "soft_spi.h"
#include <ILI9341.h>

void spiWrite(uint8_t data)
{
  uint16_t size = sizeof(data)<<3;
  bool flagSet;
  uint16_t mask = 1;

  for(uint16_t i = 1; i < size; i++, mask <<= 1);

  for(uint16_t i = 0; i < size; i++)
  {
    (mask & data) ? (flagSet = 1 ) : (flagSet = 0);
    data = data << 1;

    if(flagSet)  LL_GPIO_SetOutputPin(MOSI_GPIO_Port, MOSI_Pin);
    else LL_GPIO_ResetOutputPin(MOSI_GPIO_Port, MOSI_Pin);

    LL_GPIO_ResetOutputPin(SCK_GPIO_Port, SCK_Pin);
    LL_GPIO_SetOutputPin(SCK_GPIO_Port, SCK_Pin);
  }
}

void SPI_Transmit(SPI_TypeDef *SPIx, uint8_t *pData, uint32_t Size)
{
  (void)(SPIx);
  while(Size--)
  {
    spiWrite(*pData);
    pData++;
  }
}

/* static void Send_Data8(SPI_TypeDef *SPIx, uint8_t data)
{
  while(!LL_SPI_IsActiveFlag_TXE(SPIx))
  {
  }
  LL_SPI_TransmitData8(SPIx, data);
  // while(!LL_SPI_IsActiveFlag_RXNE(SPIx)) {}
  // (void) SPIx->DR; // fake Rx read;
  while(LL_SPI_IsActiveFlag_BSY(SPIx));
} */

/* static void Send_Data16(SPI_TypeDef *SPIx, uint16_t data)
{
  while(!LL_SPI_IsActiveFlag_TXE(SPIx)) {}
  LL_SPI_TransmitData16(SPIx, data);
  while(!LL_SPI_IsActiveFlag_RXNE(SPIx)) {}
  // (void) SPIx->DR; // fake Rx read;
  // while(LL_SPI_IsActiveFlag_BSY(SPIx));
} */

/* static void SPI_Transmit(SPI_TypeDef *SPIx, uint8_t *pData, uint32_t Size)
{
  while(Size--)
  {
    Send_Data8(SPIx, *pData);
    pData++;
  }
} */
