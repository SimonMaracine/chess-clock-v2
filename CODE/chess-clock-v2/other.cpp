#include "stddef.h"

#include <LiquidCrystal.h>
#include <Arduino.h>

#include "other.hpp"
#include "context.hpp"

void Timer::reset()
{
  last_time = millis();
}

bool Timer::tick()
{
  const unsigned long current_time = millis();

  if (current_time - last_time > tick_milliseconds)
  {
      last_time = current_time;

      return true;
  }

  return false;
}

void toggle_light(int light, bool on)
{
  digitalWrite(light, on ? HIGH : LOW);
}

void play_sound(const Note* notes, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    tone(BUZZER, notes[i].frequency);
    delay(notes[i].duration);
    noTone(BUZZER);
    delay(notes[i].delay);
  }
}

void display_time(LiquidCrystal& lcd, unsigned long player_time, Player player, bool show_deciseconds)
{
  const char ASCII_ZERO = '0';
  char output[8] {};  // Includes the null terminator

  const unsigned long player_time_seconds = (
    static_cast<unsigned long>(static_cast<float>(player_time) / 10.0f)
  );

  const unsigned long minutes = player_time_seconds / 60;
  const unsigned long seconds = player_time_seconds % 60;
  const unsigned long deciseconds = player_time % 10;

  output[0] = ASCII_ZERO + minutes / 10;
  output[1] = ASCII_ZERO + minutes % 10;
  output[2] = ':';
  output[3] = ASCII_ZERO + seconds / 10;
  output[4] = ASCII_ZERO + seconds % 10;

  if (show_deciseconds)
  {
    output[5] = '.';
    output[6] = ASCII_ZERO + deciseconds;
    output[7] = 0;
  }
  else
  {
    output[5] = 0;
    // The rest of output doesn't matter
  }

  int x_position = player == Player::Left ? 0 : 9;

  if (!show_deciseconds)
  {
    x_position++;
  }

  lcd.setCursor(x_position, 1);
  lcd.print(output);
}
