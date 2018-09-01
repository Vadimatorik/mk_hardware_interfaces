/*!
 *	@startuml
 *
 *	class AdcOneChannel {
 *		{field}-
 *		{field}-
 *		{field}-
 *		{field}-
 *		__Constructor__
 *		{method}+
 *		__Public methods__
 *		{method}+
 *		__Private methods__
 *		{method}-
 *		{method}-
 *	}
 *
 *	@enduml
 */

#pragma once

#ifdef __cplusplus

#include "platform.h"

#ifdef HAL_GPIO_MODULE_ENABLED

#include "pin.h"
#include "mc_hardware_interfaces_pin_multifunc.h"

class PinMultifunc : public Pin, public PinMultifuncBase {
public:
	PinMultifunc( const pinCfg* const cfg, uint32_t cfgCount ) : Pin( cfg ), cfgCount( cfgCount ) {}
	bool	reinit			( uint32_t cfgNumber );

protected:
	const uint32_t		cfgCount;
};

#endif

#endif
