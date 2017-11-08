#pragma once

#include <stdint.h>

enum class RCC_RESULT {
    OK                  = 0,            // Операция успешна произведена.
    ERROR_CFG_NUMBER    = 1,
    ERROR_CLK_INIT      = 2,
    ERROR_OSC_INIT      = 3
};

class rcc_base {
public:
    virtual RCC_RESULT set_cfg ( uint32_t number_cfg_set ) const = 0;
};
