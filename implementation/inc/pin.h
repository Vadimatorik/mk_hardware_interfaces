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

#include "mc_hardware_interfaces_pin.h"

#define PIN_COUNT(x) sizeof(x)/sizeof(x[0])

#define	PINS_ADC_MODE								\
		.Mode		=	GPIO_MODE_ANALOG,			\
		.Pull		=	GPIO_NOPULL,				\
		.Speed		=	GPIO_SPEED_FREQ_LOW,		\
		.Alternate	=	0

#define	PINS_INPUT_MODE								\
		.Mode		=	GPIO_MODE_INPUT,			\
		.Pull		=	GPIO_PULLUP,				\
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,	\
		.Alternate	=	0

#define	PINS_EXTI_MODE								\
		.Mode		=	GPIO_MODE_IT_FALLING,		\
		.Pull		=	GPIO_PULLUP,				\
		.Speed		=	GPIO_SPEED_FREQ_LOW,		\
		.Alternate	=	0

#define PINS_OUTPUT_PP_MODE							\
		.Mode		=	GPIO_MODE_OUTPUT_PP,		\
		.Pull		=	GPIO_NOPULL,				\
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,	\
		.Alternate	=	0

struct pinCfg {
	const GPIO_TypeDef*		 const GPIOx;
	const GPIO_InitTypeDef	init;
};

class Pin : public PinBase {
public:
	Pin( const pinCfg* const cfg ) : cfg( cfg ) {}

	void	init			( void );	// Перед инициализацией включается тактирование портов.

	void	set				( void );
	void	reset			( void );
	void	toggle			( void );

	void	set				( bool state );
	void	set				( int state );
	void	set				( uint8_t state );

	bool	read			( void );

protected:
	const pinCfg*			const cfg;

};

#endif

#endif
