#pragma once

#ifdef __cplusplus

#include "platform.h"

#ifdef HAL_GPIO_MODULE_ENABLED

#include "pin.h"
#include "mc_hardware_interfaces_pin_multifunc.h"

class PinMultifunc : public Pin, public PinMultifuncBase {
public:
	PinMultifunc( const pinCfg* const cfg, uint32_t countCfg ) : Pin( cfg ), countCfg( countCfg ) {}
	bool	reinit			( uint32_t numberCfg );

protected:
	const uint32_t		countCfg;
};

#endif

#endif
