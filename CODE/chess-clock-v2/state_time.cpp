#include <Arduino.h>

#include "all_states.hpp"
#include "definitions.hpp"
#include "other.hpp"

void StateTime::update()
{
    unsigned long lower_limit;
    unsigned long upper_limit;
    unsigned long step;

    switch (ctx->time_mode)
    {
        case TimeMode::Minutes:
            lower_limit = ONE_MINUTE_D;
            upper_limit = NINETY_MINUTES_D;
            step = ONE_MINUTE_D;

            break;
        case TimeMode::Seconds:
            lower_limit = ONE_SECOND_D;
            upper_limit = THREE_MINUTES_D;
            step = ONE_SECOND_D;

            break;
    }

    const int DELAY = 200;

    if (ctx->buttons.is_button_down(LeftPlayerButton))
    {
        if (ctx->time_limit > lower_limit)
        {
            ctx->time_limit -= step;
            delay(DELAY);
        }
    }

    if (ctx->buttons.is_button_down(RightPlayerButton))
    {
        if (ctx->time_limit < upper_limit)
        {
            ctx->time_limit += step;
            delay(DELAY);
        }
    }

    if (ctx->buttons.is_button_pressed(OkButton))
    {
        ctx->change_state(MenuState);
    }

    ctx->lcd.setCursor(0, 0);
    ctx->lcd.print("Set time limit:");

    ctx->lcd.setCursor(0, 1);
    switch (ctx->time_mode)
    {
        case TimeMode::Minutes:
            ctx->lcd.print(ctx->time_limit / ONE_MINUTE_D);
            break;
        case TimeMode::Seconds:
            ctx->lcd.print(ctx->time_limit / ONE_SECOND_D);
            break;
    }

    // Clear the last digit when there are't three digits
    ctx->lcd.print(" ");
}
