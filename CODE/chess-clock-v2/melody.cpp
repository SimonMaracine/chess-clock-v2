#include "melody.hpp"

#include <Arduino.h>

namespace chess_clock
{
    void play_sound(const Note* notes, size_t size, uint8_t pin)
    {
        for (size_t i {0}; i < size; i++)
        {
            tone(pin, notes[i].frequency);
            delay(notes[i].duration);
            noTone(pin);
            delay(notes[i].delay);
        }
    }
}
