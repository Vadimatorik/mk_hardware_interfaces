#pragma once

#ifdef __cplusplus

#include <stdint.h>

/*!
 * Класс предназначен для управления одной линией ввода/вывода.
 * Вывод должен быть заранее настроен на выход или вход с нужными
 * параметрами.
 */
class PinBase {
public:
	/// Устанавливает вывод в логическую единицу.
	virtual void	set				( void )					= 0;

	/// Устанавливает вывод в логический ноль.
	virtual void	reset			( void )					= 0;

	/// Инвертирует значение на выходе.
	virtual void	toggle			( void )					= 0;

	/// Устанавливает на выводе заданное состояние.
	/// \param[in]	state		-	устанавливаемое состояние.
	virtual void	set				( bool state )				= 0;

	/// Устанавливает на выводе заданное состояние.
	/// \param[in]	state		-	устанавливаемое состояние.
	virtual void	set				( int state )				= 0;

	/// Устанавливает на выводе заданное состояние.
	/// \param[in]	state		-	устанавливаемое состояние.
	virtual void	set				( uint8_t state )			= 0;

	/// Возвращает состояние на входе вывода.
	/// \return		{Состояние на входе вывода.}
	virtual bool	read			( void )					= 0;

};

#endif

