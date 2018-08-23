#include "rcc.h"

#ifdef HAL_RCC_MODULE_ENABLED

RccResult Rcc::setCfg ( const uint32_t numberCfg ) {
	if ( numberCfg >= this->cfgCount ) return RccResult::errCfgNumber;

	HAL_RCC_DeInit();

	if ( HAL_RCC_OscConfig( ( RCC_OscInitTypeDef* )&this->cfg[ numberCfg ].osc ) != HAL_OK )
		return RccResult::errOscInit;

	if ( HAL_RCC_ClockConfig( ( RCC_ClkInitTypeDef* )&this->cfg[ numberCfg ].clk, this->cfg[ numberCfg ].fLatency ) != HAL_OK )
		return  RccResult::errClkInit;

	return RccResult::ok;
}

#endif
