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

#ifdef HAL_ADC_MODULE_ENABLED

#ifdef STM32F4
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_rcc.h"
#endif

#ifdef STM32F2
#include "stm32f2xx_hal_adc.h"
#include "stm32f2xx_hal_rcc.h"
#endif

#ifdef STM32F1
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_rcc.h"
#endif

#include "mc_hardware_interfaces_adc.h"

struct AdcOneChannelCfg {
	ADC_TypeDef*		ADCx;
	uint32_t			clockPrescaler;								// ADC_ClockPrescaler
	uint32_t			resolution;									// ADC_Resolution
	uint32_t			dataAlign;									// ADC_Data_align
	uint32_t			channel;									// ADC_channels
	uint32_t			samplingTime;								// ADC_sampling_times
};

class AdcOneChannel : public AdcOneChannelBase {
public:
	AdcOneChannel( const AdcOneChannelCfg* const cfg, const uint32_t countCfg );

	BASE_RESULT		reinit								( uint32_t numberCfg = 0 );

	BASE_RESULT		startContinuousConversion			( void );
	void			stopContinuousConversion			( void );
	uint32_t		getMeasurement						( void );

	void			irqHandler							( void );

private:
	void			clkEnable							( void );
	void			clkDisable							( void );


	const AdcOneChannelCfg*			const cfg;
	const uint32_t					countCfg;

	ADC_HandleTypeDef				adc;
	ADC_ChannelConfTypeDef			channelCfg;
};

#endif

#endif
