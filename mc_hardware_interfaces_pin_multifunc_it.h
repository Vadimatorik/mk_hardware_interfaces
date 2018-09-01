#pragma once

#ifdef __cplusplus

#include <stdint.h>

/*!
 * Класс предназначен для работы с прерываниями,
 * возникающими на линии в режиме работы на вход.
 */
class PinMultifuncItBase {
public:
	/*!
	 * Возвращает флаг зафиксированного прерывания на выводе.
	 * \return		{	true	-	прерывание было зафиксировано.
	 *					false	-	в противном случае.	}
	 */
	virtual bool	checkIt			( void )					= 0;

	/// Сбрасывает флаг зафиксированного прерывания на выводе.
	virtual void	clearIt			( void )					= 0;
};

#endif
