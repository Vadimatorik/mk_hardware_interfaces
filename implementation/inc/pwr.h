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

#ifdef HAL_PWR_MODULE_ENABLED

#include "mc_hardware_interfaces_pwr.h"
#include "user_os.h"

struct pwrCfg {
	const PWR_PVDTypeDef			cfg;
};

class Pwr : public PwrBase {
public:
	Pwr ( const pwrCfg* const cfg, const uint32_t countCfg = 1 )
		: cfg( cfg ), countCfg( countCfg ) {}

	BaseResult	reinit			( uint32_t numberCfg = 0 );

	void		pvdEnable		( void );
	void		pvdDisable		( void );

	void		irqHandler		( void );

private:
	const pwrCfg*							const cfg;
	const uint32_t							countCfg;

	uint32_t								nowCfg			=	0;
};

#endif

#endif
