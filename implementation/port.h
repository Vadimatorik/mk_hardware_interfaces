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

#include "mc_hardware_interfaces_port.h"

#ifdef HAL_GPIO_MODULE_ENABLED

#include "pin.h"

class GlobalPort : public GlobalPortBase {
public:
	GlobalPort( const pinCfg* const cfg, uint32_t countCfg ) : cfg( cfg ), countCfg( countCfg ) {}
	BASE_RESULT	reinitAllPorts		( void );

private:
	const pinCfg*				const cfg;
	const uint32_t				countCfg;
};

#endif

#endif
