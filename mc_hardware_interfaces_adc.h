#pragma once

#include <stdint.h>

/*!
 * Класс предназначен для использования одного канала ADC
 * в режиме непрерывного преобразования.
 */
class AdcOneChannelBase {
public:
	/*!
	 * Сбрасывает текущие настройки ADC и инициализирует его заново.
	 * После инициализации ADC остается отключенным.
	 */
	virtual bool		reinit							( void )	= 0;

	/*!
	 * Инициирует непрерывное преобразование на канале.
	 * \return		{	true	-	последовательность преобразований
	 *								была успешно начата.
	 *					false	-	в противном случае.	}
	 */
	virtual bool		startContinuousConversion		( void )	= 0;

	/// Останавливает непрерывное преобразование на канале.
	virtual void		stopContinuousConversion		( void )	= 0;

	/// Возвращает результат измерения.
	/// \return		{	Результат измерения напряжения на канале.	}
	virtual uint32_t	getMeasurement					( void )	= 0;
};
