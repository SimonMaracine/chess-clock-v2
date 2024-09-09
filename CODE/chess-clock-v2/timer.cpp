#include "timer.hpp"

#include <Arduino.h>

namespace chess_clock
{
    unsigned long get_current_time()
    {
        return millis();
    }
}
