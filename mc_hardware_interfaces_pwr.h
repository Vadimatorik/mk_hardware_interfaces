/*

@startuml

namespace McHardwareInterfaces {

interface Pwr {
	{abstract}{method}+	BaseResult		reinit			( uint32_t cfgNumber = 0 )
	{abstract}{method}+	void			pvdEnable		( void )
	{abstract}{method}+	void			pvdDisable		( void )
}

}

@enduml

*/

#pragma once

#ifdef __cplusplus

#include "mc_hardware_interfaces_base.h"

namespace McHardwareInterfaces {

class Pwr {
public:
	/*!
	 * Сбрасывает текущие настройки Pwr и инициализирует его заново
	 * согласно выбранному режиму.
	 *
	 * \param[in]	cfgNumber		-	выбранный режим.
	 *
	 * \return		{	BASE_RESULT::OK					-	инициализация прошла успешно.
	 *					BASE_RESULT::INPUT_VALUE_ERROR	-	несуществующий номер конфигурации.
	 */
	virtual	BaseResult	reinit			( uint32_t cfgNumber = 0 )				= 0;

	/*!
	 * Запускает контроль за напряжением питания согласно конфигурации.
	 */
	virtual	void		pvdEnable		( void )								= 0;

	/*!
	 * Отключает контроль за напряжением питания согласно конфигурации.
	 */
	virtual	void		pvdDisable		( void )								= 0;
};

}

#endif
