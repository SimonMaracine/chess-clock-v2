#include "context.hpp"

#include <Arduino.h>

// #include "definitions.hpp"
#include "state.hpp"
// #include "characters.hpp"

namespace chess_clock {
    void Buttons::add_button(uint8_t port)
    {
        buttons[count].port = port;
        count++;
    }

    void Buttons::update()
    {
        for (size_t i {0}; i < count; i++)
        {
            Button& button {buttons[i]};

            button.previously_pressed = button.currently_pressed;
            button.currently_pressed = digitalRead(button.port);
        }
    }

    bool Buttons::is_button_pressed(size_t button) const
    {
        const Button state {buttons[button]};

        return state.currently_pressed && !state.previously_pressed;
    }

    bool Buttons::is_button_down(size_t button) const {
        const Button state {buttons[button]};

        return state.currently_pressed;
    }

    void Context::initialize(State& state, SetupLcd setup_lcd, void* user_data)
    {
        this->user_data = user_data;

        this->current = &state;
        this->current->start();

        setup_lcd(lcd);
    }

    void Context::update()
    {
        buttons.update();
        current->update();

        if (changed_state)
        {
            lcd.clear();
            this->current->stop();
            this->current = this->next;
            this->current->start();

            changed_state = false;
        }
    }

    void Context::add_state(State& state)
    {
        this->states[this->count] = &state;
        this->count++;
    }

    void Context::add_button(uint8_t port)
    {
        buttons.add_button(port);
    }

    void Context::change_state(size_t state)
    {
        this->next = this->states[state];
        this->changed_state = true;
    }
}
