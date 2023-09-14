#include "stddef.h"

#include <LiquidCrystal.h>
#include <Arduino.h>

#include "other.hpp"
#include "context.hpp"
#include "characters.hpp"

void Timer::reset()
{
    last_time = millis();
}

bool Timer::tick()
{
    const unsigned long current_time = millis();

    if (current_time - last_time > tick_time)
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

    int x_position = player == Player::Left ? 0 : 9;

    if (!show_deciseconds)
    {
        x_position++;
    }

    lcd.setCursor(x_position, 1);
    lcd.print(output);
}

void display_time_one(LiquidCrystal& lcd, unsigned long time, bool show_deciseconds)
{
    const char ASCII_ZERO = '0';
    char output[8] {};  // Includes the null terminator

    const unsigned long time_seconds = (
        static_cast<unsigned long>(static_cast<float>(time) / 10.0f)
    );

    const unsigned long minutes = time_seconds / 60;
    const unsigned long seconds = time_seconds % 60;
    const unsigned long deciseconds = time % 10;

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

    const int x_position = show_deciseconds ? 4 : 5;

    lcd.setCursor(x_position, 1);
    lcd.print(output);
}

void display_progress_bar(LiquidCrystal& lcd, unsigned long time, unsigned long time_limit, Monotony monotony)
{
    const long CELLS_COUNT = 16;

    long cells_filled;

    switch (monotony)
    {
        case Monotony::Ascend:
        {
            const unsigned long value = map(time_limit - time, time_limit, 0, 0, time_limit);
            cells_filled = map(value, 0, time_limit, 0, CELLS_COUNT);

            break;
        }
        case Monotony::Descend:
            cells_filled = map(time, 0, time_limit, 0, CELLS_COUNT);

            break;
    }

    lcd.setCursor(0, 0);

    for (long i = 0; i < cells_filled; i++)
    {
        lcd.write(FilledRectangle);
    }

    for (long i = cells_filled; i < CELLS_COUNT; i++)
    {
        lcd.write(' ');
    }
}
