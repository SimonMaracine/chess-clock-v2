#include <stddef.h>

#include "all_states.hpp"
#include "definitions.hpp"
#include "other.hpp"
#include "characters.hpp"

void StateMenu::update()
{
    if (ctx->buttons.is_button_pressed(LeftPlayerButton))
    {
        ctx->lcd.setCursor(MENU_CURSOR[static_cast<size_t>(ctx->menu)], 1);
        ctx->lcd.print(' ');

        ctx->menu = wrapped_subtract(ctx->menu, Menu::MenuCount);
    }

    if (ctx->buttons.is_button_pressed(RightPlayerButton))
    {
        ctx->lcd.setCursor(MENU_CURSOR[static_cast<size_t>(ctx->menu)], 1);
        ctx->lcd.print(' ');

        ctx->menu = wrapped_add(ctx->menu, Menu::MenuCount);
    }

    if (ctx->buttons.is_button_pressed(OkButton))
    {
        switch (ctx->menu)
        {
            case Menu::Modes:
                ctx->change_state(ModesState);
                break;
            case Menu::Time:
                ctx->change_state(PreTimeState);
                break;
            case Menu::Deciseconds:
                ctx->change_state(DecisecondsState);
                break;
            case Menu::Start:
                switch (ctx->mode)
                {
                    case Mode::TwoClockUp:
                        ctx->change_state(TwoClockUpState);
                        break;
                    case Mode::TwoClockDown:
                        ctx->change_state(TwoClockDownState);
                        break;
                    case Mode::OneClockUp:
                        ctx->change_state(OneClockUpState);
                        break;
                    case Mode::OneClockDown:
                        ctx->change_state(OneClockDownState);
                        break;
                    case Mode::DiceOne:
                        ctx->change_state(DiceState);
                        break;
                    case Mode::DiceTwo:
                        ctx->change_state(DiceState);
                        break;
                }
            }
    }

    ctx->lcd.setCursor(3, 0);
    ctx->lcd.print("Setup Menu");

    ctx->lcd.setCursor(1, 1);
    ctx->lcd.print('M');
    ctx->lcd.setCursor(5, 1);
    ctx->lcd.print('T');
    ctx->lcd.setCursor(9, 1);
    ctx->lcd.print('D');
    ctx->lcd.setCursor(13, 1);
    ctx->lcd.write(StartFlag);

    ctx->lcd.setCursor(MENU_CURSOR[static_cast<size_t>(ctx->menu)], 1);
    ctx->lcd.write(TurnIndicator);
}
