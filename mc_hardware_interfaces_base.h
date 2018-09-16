#pragma once

#ifdef __cplusplus

#include <stdint.h>

namespace McHardwareInterfaces {

/*!
 * Стандартные ответы от методов
 * интерфейсов микроконтроллера.
 */
enum class BaseResult {
	ok				=	0,			/// Операция успешна произведена.
	errTimeOut		=	1,			/// Был произведён выход по истечении времени ожидания.
	errLength		=	2,			/// Попытка передать/принять пакет 0-й длины.
	errInit			=	3,			/// Ошибка инициализации/модуль не был ранее инициализирован.
	errNotData		=	4,			/// Нет запрашиваемых данных.
	errInputValue	=	5			/// Входящее значение ошибочно.
};

/*!
 * Шаблон позволяет прекратить последовательность
 * действий и выйти, если операция с интерфейсом
 * была произведена не удачно.
 */
#define		checkResult(baseResultVariable)												\
			if ( baseResultVariable != McHardwareInterfaces::BaseResult::ok ) return baseResultVariable;

}

#endif
