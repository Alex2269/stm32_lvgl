#ifndef STM32F1xx_HAL_SPI_H
#define STM32F1xx_HAL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void spiWrite(uint8_t data);
void SPI_Transmit(SPI_TypeDef *SPIx, uint8_t *pData, uint32_t Size);

#ifdef __cplusplus
}
#endif

#endif /* STM32F1xx_HAL_SPI_H */
