/*

@startuml

namespace McHardwareInterfaces {

interface GlobalPort {
	{abstract}{method}+	BaseResult		reinitAllPorts	( void )
}

}

@enduml

*/

#pragma once

#ifdef __cplusplus

#include "mc_hardware_interfaces_base.h"

namespace McHardwareInterfaces {

/*!
 * Класс предназначен для работы со всеми
 * используемыми в проекте выводами одновременно.
 */
class GlobalPort {
public:
	/*!
	 * Сбрасывает настройки всех выводов,
	 * после чего инициализирует их заново.
	 *
	 * Замечание: Управление тактовыми сигналами
	 * портов ввода/вывода осуществляется внутри
	 * метода автоматически.
	 *
	 * \return		{	BASE_RESULT::OK			-	инициализация прошла успешно.
	 *					BASE_RESULT::ERROR_INIT	-	в противном случае.	}
	 */
	virtual BaseResult		reinitAllPorts	( void )					= 0;
};

}

#endif
