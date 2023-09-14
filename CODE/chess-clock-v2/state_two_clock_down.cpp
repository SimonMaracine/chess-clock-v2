#include "all_states.hpp"
#include "definitions.hpp"
#include "other.hpp"
#include "characters.hpp"
#include "melodies.hpp"

void StateTwoClockDown::start()
{
    match.left_player_time = ctx->time_limit;
    match.right_player_time = ctx->time_limit;

    match.player = Player::Right;

    match.paused = true;
    match.ended = false;
    toggle_light(RIGHT_LED, true);
    toggle_light(LEFT_LED, false);

    play_melody(START_MELODY);

    timer.reset();
}

void StateTwoClockDown::stop()
{
    toggle_light(RIGHT_LED, false);
    toggle_light(LEFT_LED, false);
}

void StateTwoClockDown::update()
{
    if (ctx->buttons.is_button_pressed(StartStopButton) && !match.ended)
    {
        match.paused = !match.paused;

        if (!match.paused)
        {
            play_melody(START_BEEP);
        }
    }

    if (ctx->buttons.is_button_pressed(SoftResetButton))
    {
        ctx->change_state(MenuState);
    }

    if (!match.paused && !match.ended)
    {
        if (ctx->buttons.is_button_pressed(LeftPlayerButton) && match.player == Player::Left)
        {
            match.player = Player::Right;
            toggle_light(RIGHT_LED, true);
            toggle_light(LEFT_LED, false);
        }
        else if (ctx->buttons.is_button_pressed(RightPlayerButton) && match.player == Player::Right)
        {
            match.player = Player::Left;
            toggle_light(RIGHT_LED, false);
            toggle_light(LEFT_LED, true);
        }

        if (timer.tick())
        {
            switch (match.player)
            {
                case Player::Left:
                    match.left_player_time--;
                    break;
                case Player::Right:
                    match.right_player_time--;
                    break;
            }

            if (match.left_player_time == 0 ||
                match.right_player_time == 0)
            {
                match.ended = true;
                match.end_flag = true;
            }
        }
    }

    // Pause indicator
    if (match.paused)
    {
        ctx->lcd.setCursor(6, 0);
        ctx->lcd.print('P');
    }
    else
    {
        ctx->lcd.setCursor(6, 0);
        ctx->lcd.print(' ');
    }

    // Left player indicator
    ctx->lcd.setCursor(0, 0);
    ctx->lcd.write(EmptyRectangle);

    // Right player indicator
    ctx->lcd.setCursor(15, 0);
    ctx->lcd.write(FilledRectangle);

    // Middle seperator
    ctx->lcd.setCursor(7, 0);
    ctx->lcd.write(RightPipe);
    ctx->lcd.setCursor(7, 1);
    ctx->lcd.write(RightPipe);

    ctx->lcd.setCursor(8, 0);
    ctx->lcd.write(LeftPipe);
    ctx->lcd.setCursor(8, 1);
    ctx->lcd.write(LeftPipe);

    // Turn indicator
    switch (match.player)
    {
        case Player::Left:
            ctx->lcd.setCursor(12, 0);
            ctx->lcd.print(' ');

            ctx->lcd.setCursor(3, 0);
            ctx->lcd.write(TurnIndicator);

            break;
        case Player::Right:
            ctx->lcd.setCursor(3, 0);
            ctx->lcd.print(' ');

            ctx->lcd.setCursor(12, 0);
            ctx->lcd.write(TurnIndicator);

            break;
    }

    // Player times
    display_time(ctx->lcd, match.left_player_time, Player::Left, ctx->show_deciseconds);
    display_time(ctx->lcd, match.right_player_time, Player::Right, ctx->show_deciseconds);

    if (match.ended)
    {
        if (match.end_flag)
        {
            play_melody(END_MELODY);
            end_timer.reset();

            match.end_flag = false;
        }

        if (end_timer.tick())
        {
            static bool on = true;
            on = !on;
            toggle_light(match.player == Player::Right ? RIGHT_LED : LEFT_LED, on);
        }
    }
}
