#pragma once

#ifdef __cplusplus

#include <stdint.h>

/// Варианты ответа на вызов метода setCfg класса RccBase.
enum class RccResult {
	ok              = 0,            /// Операция успешна произведена.
	errCfgNumber    = 1,			/// Попытка установить неподдерживаемый режим работы.
	errClkInit      = 2,			/// Ошибка при настройке частоты.
	errOscInit      = 3				/// Ошибка при настройке источника тактового сигнала.
};

/*!
 * Класс предназначен для управления частотой
 * тактового сигнала аппаратных блоков
 * микроконтроллера.
 */
class RccBase {
public:
	/*!
	 * Сбрасывает текущие настройки RCC и инициализирует его заново
	 * согласно выбранному режиму.
	 *
	 * \param[in]	numberCfg		-	выбранный режим тактирования.
	 *
	 * \return		{Итог попытки смены режим работы RCC.}
	 */
	virtual	RccResult	setCfg			(	uint32_t	numberCfg = 0 )					= 0;
	virtual	uint32_t	getCfgNumber	(	void	)									= 0;
};

#endif
