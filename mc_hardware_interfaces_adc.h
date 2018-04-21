#pragma once

#ifdef __cplusplus

#include "mc_hardware_interfaces_base.h"

/*!
 * Класс предназначен для использования одного канала ADC
 * в режиме непрерывного преобразования.
 */
class AdcOneChannelBase {
public:
	/*!
	 * Сбрасывает текущие настройки ADC и инициализирует его заново.
	 * После инициализации ADC остается отключенным.
	 *
	 * Замечание: управление тактовым сигналом аппаратного
	 * модуля осуществляется внутри метода автоматически.
	 *
	 * 	\return		{	BASE_RESULT::OK			-	инициализация прошла успешно.
	 *					BASE_RESULT::ERROR_INIT	-	в противном случае.	}
	 */
	virtual BASE_RESULT		reinit								( void )	= 0;

	/*!
	 * Инициирует непрерывное преобразование на канале.
	 *
	 * \return		{	BASE_RESULT::OK			-	последовательность преобразований
	 *												была успешно начата.
	 *					BASE_RESULT::ERROR_INIT	-	в противном случае.	}
	 */
	virtual BASE_RESULT		startContinuousConversion			( void )	= 0;

	/// Останавливает непрерывное преобразование на канале.
	virtual void			stopContinuousConversion			( void )	= 0;

	/// Возвращает результат измерения.
	/// \return		{	Результат измерения напряжения на канале.	}
	virtual uint32_t		getMeasurement						( void )	= 0;
};

#endif
