#include "all_states.hpp"
#include "definitions.hpp"
#include "other.hpp"
#include "characters.hpp"

void StateModes::update()
{
    if (ctx->buttons.is_button_pressed(LeftPlayerButton))
    {
        ctx->mode = wrapped_subtract(ctx->mode, Mode::ModeCount);
    }
    
    if (ctx->buttons.is_button_pressed(RightPlayerButton))
    {
        ctx->mode = wrapped_add(ctx->mode, Mode::ModeCount);
    }
    
    if (ctx->buttons.is_button_pressed(OkButton))
    {
        ctx->change_state(MenuState);
    }

    ctx->lcd.setCursor(0, 0);
    ctx->lcd.print("Set mode:");

    ctx->lcd.setCursor(0, 1);
    switch (ctx->mode)
    {
        case Mode::TwoClockUp:
            ctx->lcd.print("Two Clock ");
            ctx->lcd.write(UpArrow);
            break;
        case Mode::TwoClockDown:
            ctx->lcd.print("Two Clock ");
            ctx->lcd.write(DownArrow);
            break;
        case Mode::OneClockUp:
            ctx->lcd.print("One Clock ");
            ctx->lcd.write(UpArrow);
            break;
        case Mode::OneClockDown:
            ctx->lcd.print("One Clock ");
            ctx->lcd.write(DownArrow);
            break;
        case Mode::DiceOne:
            ctx->lcd.print("Dice One   ");
            break;
        case Mode::DiceTwo:
            ctx->lcd.print("Dice Two   ");
            break;
    }
}
