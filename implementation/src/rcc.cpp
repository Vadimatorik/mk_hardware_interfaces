#include "rcc.h"

#ifdef HAL_RCC_MODULE_ENABLED

RccResult Rcc::setCfg ( const uint32_t numberCfg ) {
	if ( numberCfg >= this->cfgCount ) return RccResult::errCfgNumber;

	HAL_RCC_DeInit();

	if ( HAL_RCC_OscConfig( ( RCC_OscInitTypeDef* )&this->cfg[ numberCfg ].osc ) != HAL_OK ) {
		this->numberCfgSet = -1;
		return RccResult::errOscInit;
	}

	if ( HAL_RCC_ClockConfig( ( RCC_ClkInitTypeDef* )&this->cfg[ numberCfg ].clk,
								this->cfg[ numberCfg ].fLatency ) != HAL_OK ) {
		this->numberCfgSet = -1;
		return  RccResult::errClkInit;
	}

	this->numberCfgSet = static_cast< int >( numberCfg );
	return RccResult::ok;
}

RccResult Rcc::getCfgNumber ( uint32_t& cfgNumber ) {
	if ( this->numberCfgSet == -1 ) {
		return RccResult::errNoInit;
	}

	cfgNumber = static_cast< int >( this->numberCfgSet );

	return RccResult::ok;
}

#endif
