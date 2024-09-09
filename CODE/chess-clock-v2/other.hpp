#pragma once

#include <LiquidCrystal.h>

#include "definitions.hpp"

enum class Monotony
{
    Ascend,
    Descend
};

void toggle_light(int light, bool on);
void display_time(LiquidCrystal& lcd, unsigned long player_time, Player player, bool show_deciseconds);
void display_time_one(LiquidCrystal& lcd, unsigned long time, bool show_deciseconds);
void display_progress_bar(LiquidCrystal& lcd, unsigned long time, unsigned long time_limit, Monotony monotony);

template<typename E, typename U>
E wrapped_add(E enumeration, U count)
{
    return static_cast<E>(
        (static_cast<int>(enumeration) + 1) % static_cast<int>(count)
    );
}

template<typename E, typename U>
E wrapped_subtract(E enumeration, U count)
{
    const int current {static_cast<int>(enumeration)};

    return static_cast<E>(
        current == 0 ? (static_cast<int>(count) - 1) : current - 1
    );
}

template<typename T>
T mapt(T x, T in_min, T in_max, T out_min, T out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
