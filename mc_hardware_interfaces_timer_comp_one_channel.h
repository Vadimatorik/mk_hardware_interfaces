#pragma once

#ifdef __cplusplus

#include "mc_hardware_interfaces_base.h"

/*!
 * Класс предназначен для для генерации прямоугольных
 * импульсов на одном канале средствами аппаратного таймера.
 */
class TimCompOneChannelBase {
public:
	/*!
	 * Сбрасывает текущие настройки таймера и инициализирует его заново.
	 * После инициализации таймер остается отключенным.
	 *
	 * Замечание: управление тактовым сигналом аппаратного
	 * модуля осуществляется внутри метода автоматически.
	 *
	 * \param[in]	numberCfg		-	выбранная конфигурация таймера.
	 *
	 * \return		{	BASE_RESULT::OK					-	инициализация прошла успешно.
	 *					BASE_RESULT::INPUT_VALUE_ERROR	-	несуществующий номер конфигурации.
	 *					BASE_RESULT::ERROR_INIT			-	ошибка инициализации.
	 */
	virtual BaseResult		reinit					( uint32_t numberCfg = 0 )						= 0;

	/*!
	 * Запускает таймера.
	 *
	 * \return		{	BASE_RESULT::OK					-	передача прошла успешно.
	 *					BASE_RESULT::ERROR_INIT			-	SPI не был инициализирован ранее.	}
	 */
	virtual	BaseResult		on						( void )										= 0;

	/// Останавливает таймер.
	virtual	void			off						( void )										= 0;

};

#endif
