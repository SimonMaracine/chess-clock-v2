#pragma once

#include <stddef.h>

#include "definitions.hpp"

struct Data {
    Menu menu {MenuModes};
    Mode mode {ModeTwoClockUp};
    TimeMode time_mode {TimeMode::Minutes};
    unsigned long time_limit {THIRTY_MINUTES_D};  // Deciseconds
    size_t dice_count {1};
    bool show_deciseconds {false};
};
