/*

@startuml

namespace McHardwareInterfaces {

interface TimInterrupt {
	{abstract}{method}+	BaseResult		reinit				( uint32_t	cfgNumber = 0 )
	{abstract}{method}+	BaseResult		setState			( bool	state )
	{abstract}{method}+	BaseResult		on				( void )
	{abstract}{method}+	void			off				( void )
	{abstract}{method}+	void			clearInterruptFlag	( void )
}

}

@enduml

*/

#pragma once

#ifdef __cplusplus

#include "mc_hardware_interfaces_base.h"

namespace McHardwareInterfaces {

/*!
 * Класс предназначен для генерации прерываний средствами аппаратного таймера.
 */
class TimInterrupt {
public:
	/*!
	 * Сбрасывает текущие настройки таймера и инициализирует его заново.
	 * После инициализации таймер остается отключенным.
	 *
	 * Замечание: управление тактовым сигналом аппаратного
	 * модуля осуществляется внутри метода автоматически.
	 *
	 * \param[in]	cfgNumber		-	выбранная конфигурация таймера.
	 *
	 * \return		{	BASE_RESULT::OK					-	инициализация прошла успешно.
	 *					BASE_RESULT::INPUT_VALUE_ERROR	-	несуществующий номер конфигурации.
	 *					BASE_RESULT::ERROR_INIT			-	ошибка инициализации.
	 */
	virtual	BaseResult		reinit					( uint32_t cfgNumber = 0 )						= 0;

	virtual	BaseResult		setState						(	bool	state	)	=	0;
	/*!
	 * Запускает таймера.
	 *
	 * \return		{	BASE_RESULT::OK					-	передача прошла успешно.
	 *					BASE_RESULT::ERROR_INIT			-	SPI не был инициализирован ранее.	}
	 */
	virtual	BaseResult		on						( void )										= 0;

	/// Останавливает таймер.
	virtual	void			off						( void )										= 0;

	/*
	 * Сбрасывает флаг прерывания и совершает все необходимые
	 * действия чтобы можно было успешно выйти из прерывания.
	 */
	virtual void			clearInterruptFlag		( void )										= 0;

};

}

#endif
