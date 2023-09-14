#include <stddef.h>
#include <stdint.h>

#include <Arduino.h>

#include "buttons.hpp"

void Buttons::add_button(uint8_t port)
{
    buttons[count].port = port;
    count++;
}

void Buttons::update()
{
    for (size_t i = 0; i < count; i++)
    {
        Button& button = buttons[i];

        button.previously_pressed = button.currently_pressed;
        button.currently_pressed = digitalRead(button.port);
    }
}

bool Buttons::is_button_pressed(size_t button) const
{
    const Button state = buttons[button];

    return state.currently_pressed && !state.previously_pressed;
}

bool Buttons::is_button_down(size_t button) const {
    const Button state = buttons[button];

    return state.currently_pressed;
}
