/*

@startuml

interface PinMultifuncBase {
	{abstract}{method}+	bool	reinit		( uint32_t	cfgNumber = 0 )
}

@enduml

*/

#pragma once

#ifdef __cplusplus

#include <stdint.h>

/*!
 * Класс предназначен для смены назначение вывода
 * в процессе выполнения программы.
 */
class PinMultifuncBase {
public:
	/*!
	 * Изменяет назначение вывода на согласно требуемому режиму.
	 * \param[in]	numberCfg	-	номер требуемого режима.
	 * \return		{	true	-	если требуемый режим существует
	 *								и был успешно выбран.
	 *					false	-	в противном случае.	}
	 */
	virtual bool	reinit			( uint32_t cfgNumber = 0 )		= 0;

};

#endif
