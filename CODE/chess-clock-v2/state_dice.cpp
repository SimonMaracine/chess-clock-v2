#include <stddef.h>

#include <Arduino.h>

#include "all_states.hpp"
#include "definitions.hpp"
#include "other.hpp"
#include "melodies.hpp"

static const char* DICE_ANIMATION[2] = {
    "<", ">"
};

void StateDice::start()
{
    randomSeed(micros() / 4);

    dice[0] = 0;
    dice[1] = 0;

    switch (ctx->mode)
    {
        case Mode::DiceOne:
            ctx->dice_count = 1;
            break;
        case Mode::DiceTwo:
            ctx->dice_count = 2;
            break;
    }
}

void StateDice::update()
{
    if (ctx->buttons.is_button_pressed(LeftPlayerButton) ||
        ctx->buttons.is_button_pressed(RightPlayerButton))
    {
        for (size_t i = 0; i < 2; i++)
        {
            dice[i] = random(1, 7);
        }

        for (size_t i = 0; i < 8; i++)
        {
            ctx->lcd.clear();
            ctx->lcd.setCursor(7, 0);
            ctx->lcd.print(DICE_ANIMATION[i % 2]);

            if (ctx->dice_count == 2)
            {
                ctx->lcd.setCursor(7, 1);
                ctx->lcd.print(DICE_ANIMATION[i % 2]);
            }

            static bool on = false;
            on = !on;
            toggle_light(RIGHT_LED, !on);
            toggle_light(LEFT_LED, on);

            delay(150);

            if (i % 2 == 0)
            {
                play_melody(DICE_NOTE1);
            }
            else
            {
                play_melody(DICE_NOTE2);
            }

            delay(150);
        }

        toggle_light(RIGHT_LED, false);
        toggle_light(LEFT_LED, false);
    }

    if (ctx->buttons.is_button_pressed(SoftResetButton))
    {
        ctx->change_state(MenuState);
    }

    if (dice[0] != 0)
    {
        ctx->lcd.setCursor(0, 0);
        ctx->lcd.print("***");
        ctx->lcd.setCursor(0, 1);
        ctx->lcd.print("***");
        ctx->lcd.setCursor(13, 0);
        ctx->lcd.print("***");
        ctx->lcd.setCursor(13, 1);
        ctx->lcd.print("***");

        // The dice
        ctx->lcd.setCursor(7, 0);
        ctx->lcd.print(dice[0]);

        if (ctx->dice_count == 2)
        {
            ctx->lcd.setCursor(7, 1);
            ctx->lcd.print(dice[1]);
        }
    }
    else
    {
        ctx->lcd.setCursor(1, 0);
        ctx->lcd.print("Roll the dice!");
    }
}
