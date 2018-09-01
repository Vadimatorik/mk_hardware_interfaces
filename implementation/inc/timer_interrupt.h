#pragma once

#ifdef __cplusplus

#include "platform.h"

#ifdef HAL_TIM_MODULE_ENABLED

#include "mc_hardware_interfaces_timer_interrupt.h"

struct timInterruptCfg {
	TIM_TypeDef*					tim;
	const clkTimBaseCfg*			const cfg;
	uint32_t						countCfg;
};

class TimInterrupt : public TimInterruptBase {
public:
	TimInterrupt( const timInterruptCfg* const cfg );

	BaseResult		reinit							( uint32_t numberCfg = 0 );

	BaseResult		setState						(	bool	state	);

	BaseResult		on								( void );
	void			off								( void );

	void			clearInterruptFlag				( void );

private:
	const timInterruptCfg*			const cfg;

	TIM_HandleTypeDef				tim;
};

#endif

#endif
