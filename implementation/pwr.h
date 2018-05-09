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

#ifdef HAL_PWR_MODULE_ENABLED

#include "mc_hardware_interfaces_pwr.h"
#include "user_os.h"

struct pwrCfg {
	const PWR_PVDTypeDef			cfg;
};

class Pwr : public PwrBase {
public:
	Pwr ( const pwrCfg* const cfg, const uint32_t countCfg )
		: cfg( cfg ), countCfg( countCfg ),
		nowCfg( 0 ) {}

	BASE_RESULT	reinit			( uint32_t numberCfg = 0 );

	void		pvdEnable		( void );
	void		pvdDisable		( void );

	void		irqHandler		( void );

private:
	const pwrCfg*							const cfg;
	const uint32_t							countCfg;

	uint32_t								nowCfg;
};

#endif

#endif
