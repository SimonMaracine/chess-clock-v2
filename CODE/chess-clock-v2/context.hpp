#pragma once

#include <stddef.h>
#include <stdint.h>

#include <LiquidCrystal.h>

#define PIN_RS 2
#define PIN_E 3
#define PIN_D4 4
#define PIN_D5 5
#define PIN_D6 6
#define PIN_D7 7

namespace chess_clock
{
    class State;

    struct Button
    {
        bool currently_pressed {false};
        bool previously_pressed {false};

        uint8_t port {};
    };

    class Buttons
    {
    public:
        static constexpr size_t MAX_BUTTONS {16};

        void add_button(uint8_t port);
        void update();
        bool is_button_pressed(size_t button) const;
        bool is_button_down(size_t button) const;
    private:
        Button m_buttons[MAX_BUTTONS] {};
        size_t m_count {0};
    };

    class Context
    {
    public:
        static constexpr size_t MAX_STATES {16};

        using SetupLcd = void(*)(LiquidCrystal& lcd);

        Context()
            : m_lcd(PIN_RS, PIN_E, PIN_D4, PIN_D5, PIN_D6, PIN_D7) {}

        void initialize(State& state, SetupLcd setup_lcd, void* user_data);
        void update();

        void add_state(State& state);
        void add_button(uint8_t port);
        void change_state(size_t state);

        bool is_button_pressed(size_t button) const;
        bool is_button_down(size_t button) const;        

        LiquidCrystal& lcd()
        {
            return m_lcd;
        }

        template<typename T>
        T& user_data()
        {
            return *static_cast<T*>(m_user_data);
        }
    private:
        LiquidCrystal m_lcd;
        Buttons m_buttons;

        State* m_current {nullptr};
        State* m_next {nullptr};

        State* m_states[MAX_STATES] {};
        size_t m_count {0};
        bool m_changed_state {false};

        void* m_user_data {nullptr};
    };
}
