#pragma once

#ifdef __cplusplus

#ifdef STM32F4
#include "stm32f4xx_hal_conf.h"
#endif

#ifdef STM32F2
#include "stm32f2xx_hal_conf.h"
#endif

#ifdef STM32F1
#include "stm32f1xx_hal_conf.h"
#endif

#ifdef HAL_DAC_MODULE_ENABLED

#ifdef STM32F4
#include "stm32f4xx_hal_dac.h"
#include "stm32f4xx_hal_rcc.h"
#endif

#ifdef STM32F2
#include "stm32f2xx_hal_dac.h"
#include "stm32f2xx_hal_rcc.h"
#endif

#ifdef STM32F1
#include "stm32f1xx_hal_dac.h"
#include "stm32f1xx_hal_rcc.h"
#endif


#include "mc_hardware_interfaces_dac.h"

struct DacCfg {
	uint32_t			buffer;				// DAC_OUTPUTBUFFER_ENABLE/DAC_OUTPUTBUFFER_DISABLE.
	uint32_t			defaultValue;		// Значение, выставляемое на выводы каналов Dac после инициализации.
};

class Dac : public DacBase {
public:
	Dac( const DacCfg* const cfg, const uint32_t countCfg );

	BASE_RESULT	reinit			( uint32_t numberCfg = 0 );
	BASE_RESULT	setValue		( const uint32_t ch, const uint32_t value );

private:
	void		clkEnable		( void );
	void		clkDisable		( void );

	const DacCfg*					const cfg;
	const uint32_t					countCfg;

	DAC_HandleTypeDef				dac;
	DAC_ChannelConfTypeDef			dacCh;
};

#endif

#endif
