#pragma once

#include <stdint.h>

enum class BASE_RESULT {
    OK                  = 0,            // Операция успешна произведена.
    TIME_OUT            = 1,            // Был произведён выход по истечении времени ожидания.
    LENGTH_ERROR        = 2,            // Попытка передать/принять пакет 0-й длины.
    ERROR_INIT          = 3,
	NOT_DATA			= 4,			// Нет запрашиваемых данных.
};
