#pragma once

#include <stddef.h>
#include <stdint.h>

#include <LiquidCrystal.h>

// #include "definitions.hpp"

#define PIN_RS 2
#define PIN_E 3
#define PIN_D4 4
#define PIN_D5 5
#define PIN_D6 6
#define PIN_D7 7

namespace chess_clock {
    struct State;

    struct Button
    {
        bool currently_pressed {false};
        bool previously_pressed {false};

        uint8_t port {};
    };

    struct Buttons
    {
        static constexpr size_t MAX_BUTTONS {16};

        void add_button(uint8_t port);
        void update();
        bool is_button_pressed(size_t button) const;
        bool is_button_down(size_t button) const;

        Button buttons[MAX_BUTTONS] {};
        size_t count {0};
    };

    struct Context
    {
        static constexpr size_t MAX_STATES {16};

        using SetupLcd = void(*)(LiquidCrystal& lcd);

        Context()
            : lcd(PIN_RS, PIN_E, PIN_D4, PIN_D5, PIN_D6, PIN_D7) {}

        void initialize(State& state, SetupLcd setup_lcd, void* user_data);
        void update();

        void add_state(State& state);
        void add_button(uint8_t port);
        void change_state(size_t state);

        template<typename T>
        T& get_user_data()
        {
            return *static_cast<T*>(user_data);
        }

        LiquidCrystal lcd;
        Buttons buttons;

        State* current {nullptr};
        State* next {nullptr};

        State* states[MAX_STATES] {};
        size_t count {0};
        bool changed_state {false};

        void* user_data {nullptr};

        // Menu menu {Menu::Modes};
        // Mode mode {Mode::TwoClockUp};
        // TimeMode time_mode {TimeMode::Minutes};
        // unsigned long time_limit {THIRTY_MINUTES_D};  // Deciseconds
        // size_t dice_count {1};
        // bool show_deciseconds {false};
    };
}
