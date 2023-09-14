#include <stddef.h>
#include <stdint.h>

#include "definitions.hpp"
#include "buttons.hpp"
#include "state.hpp"
#include "context.hpp"
#include "characters.hpp"

void Context::initialize(State* state)
{
    this->state.current = state;
    this->state.current->start();

    lcd.begin(16, 2);
    lcd.createChar(EmptyRectangle, CHARACTERS[EmptyRectangle]);
    lcd.createChar(FilledRectangle, CHARACTERS[FilledRectangle]);
    lcd.createChar(LeftPipe, CHARACTERS[LeftPipe]);
    lcd.createChar(RightPipe, CHARACTERS[RightPipe]);
    lcd.createChar(TurnIndicator, CHARACTERS[TurnIndicator]);
    lcd.createChar(StartFlag, CHARACTERS[StartFlag]);
    lcd.createChar(UpArrow, CHARACTERS[UpArrow]);
    lcd.createChar(DownArrow, CHARACTERS[DownArrow]);
}

void Context::update()
{
    buttons.update();
    state.current->update();

    if (state.changed_state)
    {
        lcd.clear();
        this->state.current->stop();
        this->state.current = this->state.next;
        this->state.current->start();

        state.changed_state = false;
    }
}

void Context::add_state(State* state)
{
    this->state.states[this->state.count] = state;
    this->state.count++;
}

void Context::add_button(uint8_t port)
{
    buttons.add_button(port);
}

void Context::change_state(size_t state)
{
    this->state.next = this->state.states[state];
    this->state.changed_state = true;
}
