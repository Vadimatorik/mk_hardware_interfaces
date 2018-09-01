#include "timer.h"

#ifdef HAL_TIM_MODULE_ENABLED

extern void clkTimInit ( TIM_TypeDef* tim );

TimPwmOneChannel::TimPwmOneChannel ( const timPwmOneChannelCfg* const cfg ) : cfg( cfg ) {
	this->tim.Instance						= this->cfg->tim;

	this->tim.Init.ClockDivision			= TIM_CLOCKDIVISION_DIV1;
	this->tim.Init.CounterMode				= TIM_COUNTERMODE_UP;

	this->timCh.OCMode						= TIM_OCMODE_PWM2;
	this->timCh.OCPolarity					= this->cfg->polarity;
}

BaseResult TimPwmOneChannel::reinit ( uint32_t numberCfg ) {
	if ( numberCfg >= this->cfg->countCfg )
		return BaseResult::errInputValue;

	this->tim.Init.Period					= this->cfg->cfg[ numberCfg ].period;
	this->tim.Init.Prescaler				= this->cfg->cfg[ numberCfg ].prescaler;

	clkTimInit( this->cfg->tim );

	if ( HAL_TIM_PWM_DeInit( &this->tim ) != HAL_OK )
		return BaseResult::errInit;

	if ( HAL_TIM_PWM_Init( &this->tim ) != HAL_OK )
		return BaseResult::errInit;

	if ( HAL_TIM_PWM_ConfigChannel( &this->tim, &this->timCh, this->cfg->outChannel ) != HAL_OK )
		return BaseResult::errInit;

	return BaseResult::ok;
}

BaseResult TimPwmOneChannel::on ( void ) {
	if ( this->tim.State == HAL_TIM_STATE_RESET )
		return BaseResult::errInit;

	HAL_TIM_PWM_Start( &this->tim, this->cfg->outChannel );

	return BaseResult::ok;
}

void TimPwmOneChannel::off ( void ) {
	HAL_TIM_PWM_Stop( &this->tim, this->cfg->outChannel );
}

void TimPwmOneChannel::setDuty ( float duty ) {
	__HAL_TIM_SET_COMPARE( &this->tim, this->cfg->outChannel, this->cfg->tim->ARR * duty );
}

#endif
