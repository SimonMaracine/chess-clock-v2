#pragma once

#include <stddef.h>
#include <stdint.h>

namespace chess_clock
{
    struct Note
    {
        constexpr Note(unsigned int frequency, unsigned long duration, unsigned long delay)
            : frequency(frequency), duration(duration), delay(delay) {}

        unsigned int frequency {};
        unsigned long duration {};
        unsigned long delay {};
    };

    // Must be a struct
    template<size_t Size>
    struct Melody
    {
        constexpr const Note* get() const
        {
            return m_notes;
        }

        constexpr size_t size() const
        {
            return Size;
        }

        Note m_notes[Size];
    };

    void play_sound(const Note* notes, size_t size, uint8_t pin);

    template<uint8_t Pin, size_t Size>
    void play_melody(const Melody<Size>& melody)
    {
        play_sound(melody.get(), melody.size(), Pin);
    }
}
