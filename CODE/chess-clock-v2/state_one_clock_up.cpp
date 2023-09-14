#include "all_states.hpp"
#include "definitions.hpp"
#include "other.hpp"
#include "melodies.hpp"

void StateOneClockUp::start()
{
    match.time = 0;
    match.paused = true;
    match.ended = false;

    play_melody(START_MELODY);

    timer.reset();
}

void StateOneClockUp::stop()
{
    toggle_light(RIGHT_LED, false);
    toggle_light(LEFT_LED, false);
}

void StateOneClockUp::update()
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

    if (ctx->buttons.is_button_pressed(OkButton))
    {
        match.time = 0;
        match.paused = true;
        match.ended = false;

        ctx->lcd.clear();

        toggle_light(RIGHT_LED, false);
        toggle_light(LEFT_LED, false);

        play_melody(GENTLE_RESET_BEEP);

        timer.reset();
    }

    if (!match.paused && !match.ended)
    {
        if (timer.tick())
        {
            match.time++;

            if (match.time == ctx->time_limit)
            {
                match.ended = true;
                match.end_flag = true;
            }
        }
    }

    // Pause indicator
    if (match.paused)
    {
        ctx->lcd.setCursor(2, 1);
        ctx->lcd.print('P');
    }
    else
    {
        ctx->lcd.setCursor(2, 1);
        ctx->lcd.print(' ');
    }
    
    display_time_one(ctx->lcd, match.time, ctx->show_deciseconds);

    display_progress_bar(ctx->lcd, match.time, ctx->time_limit, Monotony::Ascend);

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
            toggle_light(RIGHT_LED, on);
            toggle_light(LEFT_LED, on);
        }
    }
}
