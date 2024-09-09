#include "other.hpp"

#include <Arduino.h>

#include "characters.hpp"

static constexpr char ASCII_ZERO {'0'};

static void get_time(unsigned long time, unsigned long& minutes, unsigned long& seconds, unsigned long& deciseconds) {
    // Input time is in deciseconds
    const unsigned long time_seconds {
        static_cast<unsigned long>(static_cast<float>(time) / 10.0f)
    };

    minutes = time_seconds / 60;
    seconds = time_seconds % 60;
    deciseconds = time % 10;
}

void toggle_light(int light, bool on)
{
    digitalWrite(light, on ? HIGH : LOW);
}

void display_time(LiquidCrystal& lcd, unsigned long time, Player player, bool show_deciseconds)
{
    char output[8] {};  // Includes the null terminator

    unsigned long minutes, seconds, deciseconds;
    get_time(time, minutes, seconds, deciseconds);

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

    int x_position {player == Player::Left ? 0 : 9};

    if (!show_deciseconds)
    {
        x_position++;
    }

    lcd.setCursor(x_position, 1);
    lcd.print(output);
}

void display_time_one(LiquidCrystal& lcd, unsigned long time, bool show_deciseconds)
{
    char output[8] {};  // Includes the null terminator

    unsigned long minutes, seconds, deciseconds;
    get_time(time, minutes, seconds, deciseconds);

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

    const int x_position {show_deciseconds ? 4 : 5};

    lcd.setCursor(x_position, 1);
    lcd.print(output);
}

void display_progress_bar(LiquidCrystal& lcd, unsigned long time, unsigned long time_limit, Monotony monotony)
{
    static constexpr unsigned long CELLS_COUNT {16};

    unsigned long cells_filled {};

    switch (monotony)
    {
        case Monotony::Ascend:
        {
            const unsigned long value {mapt(time_limit - time, time_limit, 0ul, 0ul, time_limit)};
            cells_filled = mapt(value, 0ul, time_limit, 0ul, CELLS_COUNT);

            break;
        }
        case Monotony::Descend:
            cells_filled = mapt(time, 0ul, time_limit, 0ul, CELLS_COUNT);

            break;
    }

    lcd.setCursor(0, 0);

    for (unsigned long i {0}; i < cells_filled; i++)
    {
        lcd.write(CharacterFilledRectangle);
    }

    for (unsigned long i {cells_filled}; i < CELLS_COUNT; i++)
    {
        lcd.write(' ');
    }
}
