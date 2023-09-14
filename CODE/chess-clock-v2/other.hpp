#pragma once

#include "stddef.h"

#include <LiquidCrystal.h>

#include "context.hpp"

struct Note
{
  Note(unsigned int frequency, unsigned long duration, unsigned long delay)
    : frequency(frequency), duration(duration), delay(delay) {}

  unsigned int frequency {};
  unsigned long duration {};
  unsigned long delay {};
};

template<size_t Size>
struct Melody
{
  const Note* get() const
  {
    return notes;
  }

  constexpr size_t get_size() const
  {
    return Size;
  }

  Note notes[Size];
};

struct Timer
{
  Timer(unsigned long tick_milliseconds)
    : tick_milliseconds(tick_milliseconds) {}

  void reset();
  bool tick();

  unsigned long tick_milliseconds = 0;
  unsigned long last_time = 0;
};

enum class Monotony
{
  Ascend,
  Descend
};

void toggle_light(int light, bool on);
void play_sound(const Note* notes, size_t size);
void display_time(LiquidCrystal& lcd, unsigned long player_time, Player player, bool show_deciseconds);
void display_time_one(LiquidCrystal& lcd, unsigned long time, bool show_deciseconds);
void display_progress_bar(LiquidCrystal& lcd, unsigned long time, unsigned long time_limit, Monotony monotony);

template<size_t Size>
void play_melody(const Melody<Size>& melody)
{
  play_sound(melody.get(), melody.get_size());
}
