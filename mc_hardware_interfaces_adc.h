#pragma once

#include <stdint.h>

namespace SPI {

enum class FUNC_RESULT {
    OK                          = 0,            // Операция успешна произведена.
    MEASUREMENT_IS_MISSING      = 1,            // Измерение отсутствует.
};

}

class adc_one_channel_base {
public:
    //**********************************************************************
    // Метод должен:
    // 1. Отключить ADC.
    // 2. Сконфигурировать ADC и его канал в заданный режим
    // (на один объект один канал и 1 ражим).
    // После переинициализации ADC должен остаться отключенным.
    //**********************************************************************
    virtual void reinit ( void ) const = 0;

    //**********************************************************************
    // Методы должены включать/отключать ADC (не перетерая поля регистров).
    //**********************************************************************
    virtual void on     ( void ) const = 0;
    virtual void off    ( void ) const = 0;

    //**********************************************************************
    // Метод должен инициировать новое измерение и выйти,
    // не дожидаясь его окончания.
    //**********************************************************************
    virtual void start_continuous_conversion ( void ) const = 0;

    //**********************************************************************
    // Метод получает результат измерения (если таковой доступен).
    // В противном случае сообщает о неудаче.
    //**********************************************************************
    virtual SPI::FUNC_RESULT get_measurement ( uint32_t& channel_measurement ) const = 0;
};
