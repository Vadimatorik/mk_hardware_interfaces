#pragma once

#include <stdint.h>

#ifdef __cplusplus

/*!
 * Стандартные ответы от методов
 * интерфейсов микроконтроллера.
 */
enum class BASE_RESULT {
	OK					=	0,			/// Операция успешна произведена.
	TIME_OUT			=	1,			/// Был произведён выход по истечении времени ожидания.
	LENGTH_ERROR		=	2,			/// Попытка передать/принять пакет 0-й длины.
	ERROR_INIT			=	3,			/// Ошибка инициализации/модуль не был ранее инициализирован.
	NOT_DATA			=	4,			/// Нет запрашиваемых данных.
};

/*!
 * Шаблон позволяет прекратить последовательность
 * действий и выйти, если операция с интерфейсом
 * была произведена не удачно.
 */
#define	checkResult( baseResultVariable )											\
		if ( baseResultVariable != BASE_RESULT::OK ) return baseResultVariable;

#endif
