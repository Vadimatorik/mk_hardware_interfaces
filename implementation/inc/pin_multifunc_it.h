#pragma once

#ifdef __cplusplus

#include "platform.h"

#ifdef HAL_GPIO_MODULE_ENABLED

#include "pin_multifunc.h"
#include "mc_hardware_interfaces_pin_multifunc_it.h"

class PinMultifuncIt : public PinMultifunc, public PinMultifuncItBase {
public:
	/// exitPin - GPIO_PIN_x.
	PinMultifuncIt( const pinCfg* const cfg, uint32_t countCfg, uint32_t exitPin	) : PinMultifunc( cfg, countCfg ), exitPin( exitPin ) {}

	bool	checkIt			( void );
	void	clearIt			( void );

private:
	const uint32_t			exitPin;
};

#endif

#endif
