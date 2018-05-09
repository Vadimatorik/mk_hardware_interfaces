#ifdef __cplusplus

#ifdef STM32F4
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_rcc.h"
#endif

#ifdef STM32F2
#include "stm32f2xx_hal_dma.h"
#include "stm32f2xx_hal_rcc.h"
#endif

#ifdef STM32F1
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_rcc.h"
#endif

#ifdef HAL_DMA_MODULE_ENABLED

void dmaClkOn ( DMA_Stream_TypeDef* dma);
void dmaIrqOn ( DMA_Stream_TypeDef* dma, uint32_t prio );

#endif

#endif
