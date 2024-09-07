#include "context.hpp"

#include <Arduino.h>

#include "state.hpp"

namespace chess_clock
{
    void Buttons::add_button(uint8_t port)
    {
        m_buttons[m_count].port = port;
        m_count++;
    }

    void Buttons::update()
    {
        for (size_t i {0}; i < m_count; i++)
        {
            Button& button {m_buttons[i]};

            button.previously_pressed = button.currently_pressed;
            button.currently_pressed = digitalRead(button.port);
        }
    }

    bool Buttons::is_button_pressed(size_t button) const
    {
        const Button state {m_buttons[button]};

        return state.currently_pressed && !state.previously_pressed;
    }

    bool Buttons::is_button_down(size_t button) const {
        const Button state {m_buttons[button]};

        return state.currently_pressed;
    }

    void Context::initialize(State& state, SetupLcd setup_lcd, void* user_data)
    {
        m_user_data = user_data;

        m_current = &state;
        m_current->start();

        setup_lcd(m_lcd);
    }

    void Context::update()
    {
        m_buttons.update();
        m_current->update();

        if (m_changed_state)
        {
            m_lcd.clear();
            m_current->stop();
            m_current = m_next;
            m_current->start();

            m_changed_state = false;
        }
    }

    void Context::add_state(State& state)
    {
        m_states[m_count] = &state;
        m_count++;
    }

    void Context::add_button(uint8_t port)
    {
        m_buttons.add_button(port);
    }

    void Context::change_state(size_t state)
    {
        m_next = m_states[state];
        m_changed_state = true;
    }

    bool Context::is_button_pressed(size_t button) const {
        return m_buttons.is_button_pressed(button);
    }

    bool Context::is_button_down(size_t button) const {
        return m_buttons.is_button_down(button);
    }
}
