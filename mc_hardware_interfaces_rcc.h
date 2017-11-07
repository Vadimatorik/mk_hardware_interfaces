#pragma once

#include <stdint.h>

enum class RCC_RESULT {
    OK                  = 0,            // Операция успешна произведена.
};

class rcc_base {
public:
    virtual RCC_RESULT set_cfg ( uint32_t number_cfg_set ) const = 0;
};
