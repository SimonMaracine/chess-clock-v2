#include "states.hpp"

#include "definitions.hpp"
#include "melodies.hpp"
#include "characters.hpp"
#include "data.hpp"

void StartupState::start()
{
    timer.reset();
}

void StartupState::stop()
{
    toggle_light(RIGHT_LED, false);
    toggle_light(LEFT_LED, false);
}

void StartupState::update()
{
    const bool pressed {
        ctx.is_button_pressed(ButtonLeftPlayer) ||
        ctx.is_button_pressed(ButtonRightPlayer) ||
        ctx.is_button_pressed(ButtonStartStop) ||
        ctx.is_button_pressed(ButtonSoftReset) ||
        ctx.is_button_pressed(ButtonOk)
    };

    if (pressed)
    {
        ctx.change_state(StateMenu);
    }

    if (timer.tick())
    {
        static bool on {true};
        on = !on;
        toggle_light(RIGHT_LED, on);
        toggle_light(LEFT_LED, !on);
    }

    static const char* show {
        analogRead(A5) % 2 == 0 ? "By Tudor & Simon" : "By Simon & Tudor"
    };

    ctx.lcd().setCursor(0, 0);
    ctx.lcd().print("Chess Clock v2.0");
    ctx.lcd().setCursor(0, 1);
    ctx.lcd().print(show);
}

void MenuState::update()
{
    Data& data {ctx.user_data<Data>()};

    if (ctx.is_button_pressed(ButtonLeftPlayer))
    {
        ctx.lcd().setCursor(MENU_CURSOR[data.menu], 1);
        ctx.lcd().print(' ');

        data.menu = wrapped_subtract(data.menu, Menu_Count);
    }

    if (ctx.is_button_pressed(ButtonRightPlayer))
    {
        ctx.lcd().setCursor(MENU_CURSOR[data.menu], 1);
        ctx.lcd().print(' ');

        data.menu = wrapped_add(data.menu, Menu_Count);
    }

    if (ctx.is_button_pressed(ButtonOk))
    {
        switch (data.menu)
        {
            case MenuModes:
                ctx.change_state(StateModes);
                break;
            case MenuTime:
                ctx.change_state(StatePreTime);
                break;
            case MenuDeciseconds:
                ctx.change_state(StateDeciseconds);
                break;
            case MenuStart:
                switch (data.mode)
                {
                    case ModeTwoClockUp:
                        ctx.change_state(StateTwoClockUp);
                        break;
                    case ModeTwoClockDown:
                        ctx.change_state(StateTwoClockDown);
                        break;
                    case ModeOneClockUp:
                        ctx.change_state(StateOneClockUp);
                        break;
                    case ModeOneClockDown:
                        ctx.change_state(StateOneClockDown);
                        break;
                    case ModeDiceOne:
                        ctx.change_state(StateDice);
                        break;
                    case ModeDiceTwo:
                        ctx.change_state(StateDice);
                        break;
                }
            }
    }

    ctx.lcd().setCursor(3, 0);
    ctx.lcd().print("Setup Menu");

    ctx.lcd().setCursor(1, 1);
    ctx.lcd().print('M');
    ctx.lcd().setCursor(5, 1);
    ctx.lcd().print('T');
    ctx.lcd().setCursor(9, 1);
    ctx.lcd().print('D');
    ctx.lcd().setCursor(13, 1);
    ctx.lcd().write(CharacterStartFlag);

    ctx.lcd().setCursor(MENU_CURSOR[data.menu], 1);
    ctx.lcd().write(CharacterTurnIndicator);
}

void ModesState::update()
{
    Data& data {ctx.user_data<Data>()};

    if (ctx.is_button_pressed(ButtonLeftPlayer))
    {
        data.mode = wrapped_subtract(data.mode, Mode_Count);
    }

    if (ctx.is_button_pressed(ButtonRightPlayer))
    {
        data.mode = wrapped_add(data.mode, Mode_Count);
    }

    if (ctx.is_button_pressed(ButtonOk))
    {
        ctx.change_state(StateMenu);
    }

    ctx.lcd().setCursor(0, 0);
    ctx.lcd().print("Set mode:");

    ctx.lcd().setCursor(0, 1);
    switch (data.mode)
    {
        case ModeTwoClockUp:
            ctx.lcd().print("Two Clock ");
            ctx.lcd().write(CharacterUpArrow);
            break;
        case ModeTwoClockDown:
            ctx.lcd().print("Two Clock ");
            ctx.lcd().write(CharacterDownArrow);
            break;
        case ModeOneClockUp:
            ctx.lcd().print("One Clock ");
            ctx.lcd().write(CharacterUpArrow);
            break;
        case ModeOneClockDown:
            ctx.lcd().print("One Clock ");
            ctx.lcd().write(CharacterDownArrow);
            break;
        case ModeDiceOne:
            ctx.lcd().print("Dice One   ");
            break;
        case ModeDiceTwo:
            ctx.lcd().print("Dice Two   ");
            break;
    }
}

void TimeState::update()
{
    Data& data {ctx.user_data<Data>()};

    unsigned long lower_limit {};
    unsigned long upper_limit {};
    unsigned long step {};

    switch (data.time_mode)
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

    static constexpr int DELAY {200};

    if (ctx.is_button_down(ButtonLeftPlayer))
    {
        if (data.time_limit > lower_limit)
        {
            data.time_limit -= step;
            delay(DELAY);
        }
    }

    if (ctx.is_button_down(ButtonRightPlayer))
    {
        if (data.time_limit < upper_limit)
        {
            data.time_limit += step;
            delay(DELAY);
        }
    }

    if (ctx.is_button_pressed(ButtonOk))
    {
        ctx.change_state(StateMenu);
    }

    ctx.lcd().setCursor(0, 0);
    ctx.lcd().print("Set time limit:");

    ctx.lcd().setCursor(0, 1);
    switch (data.time_mode)
    {
        case TimeMode::Minutes:
            ctx.lcd().print(data.time_limit / ONE_MINUTE_D);
            break;
        case TimeMode::Seconds:
            ctx.lcd().print(data.time_limit / ONE_SECOND_D);
            break;
    }

    // Clear the last digit when there are't three digits
    ctx.lcd().print(" ");
}

void PreTimeState::update()
{
    Data& data {ctx.user_data<Data>()};

    const bool pressed {
        ctx.is_button_pressed(ButtonLeftPlayer) ||
        ctx.is_button_pressed(ButtonRightPlayer)
    };

    if (pressed)
    {
        switch (data.time_mode)
        {
            case TimeMode::Minutes:
                data.time_mode = TimeMode::Seconds;
                break;
            case TimeMode::Seconds:
                data.time_mode = TimeMode::Minutes;
                break;
        }        
    }

    if (ctx.is_button_pressed(ButtonOk))
    {
        if (data.time_mode != previous_time_mode)
        {
            switch (data.time_mode)
            {
                case TimeMode::Minutes:
                    data.time_limit = THIRTY_MINUTES_D;
                    break;
                case TimeMode::Seconds:
                    data.time_limit = ONE_MINUTE_D;
                    break;
            }

            previous_time_mode = data.time_mode;
        }

        ctx.change_state(StateTime);
    }

    ctx.lcd().setCursor(0, 0);
    ctx.lcd().print("Set time in:");

    ctx.lcd().setCursor(0, 1);
    switch (data.time_mode)
    {
        case TimeMode::Minutes:
            ctx.lcd().print("Minutes");
            break;
        case TimeMode::Seconds:
            ctx.lcd().print("Seconds");
            break;
    }
}

void DecisecondsState::update()
{
    Data& data {ctx.user_data<Data>()};

    if (ctx.is_button_pressed(ButtonLeftPlayer))
    {
        data.show_deciseconds = !data.show_deciseconds;
    }

    if (ctx.is_button_pressed(ButtonRightPlayer))
    {
        data.show_deciseconds = !data.show_deciseconds;
    }

    if (ctx.is_button_pressed(ButtonOk))
    {
        ctx.change_state(StateMenu);
    }

    ctx.lcd().setCursor(0, 0);
    ctx.lcd().print("Show fractions:");

    ctx.lcd().setCursor(0, 1);
    if (data.show_deciseconds)
    {
        ctx.lcd().print("On ");
    }
    else
    {
        ctx.lcd().print("Off");
    }
}

void TwoClockUpState::start()
{
    match.time_left = 0;
    match.time_right = 0;

    match.player = Player::Right;

    match.paused = true;
    match.ended = false;
    toggle_light(RIGHT_LED, true);
    toggle_light(LEFT_LED, false);

    play_melody(START_MELODY);

    timer.reset();
}

void TwoClockUpState::stop()
{
    toggle_light(RIGHT_LED, false);
    toggle_light(LEFT_LED, false);
}

void TwoClockUpState::update()
{
    const Data& data {ctx.user_data<Data>()};

    if (ctx.is_button_pressed(ButtonStartStop) && !match.ended)
    {
        match.paused = !match.paused;

        if (!match.paused)
        {
            play_melody(START_BEEP);
        }
    }

    if (ctx.is_button_pressed(ButtonSoftReset))
    {
        ctx.change_state(StateMenu);
    }

    if (!match.paused && !match.ended)
    {
        if (ctx.is_button_pressed(ButtonLeftPlayer) && match.player == Player::Left)
        {
            match.player = Player::Right;
            toggle_light(RIGHT_LED, true);
            toggle_light(LEFT_LED, false);
        }
        else if (ctx.is_button_pressed(ButtonRightPlayer) && match.player == Player::Right)
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
                    match.time_left++;
                    break;
                case Player::Right:
                    match.time_right++;
                    break;
            }

            if (match.time_left == data.time_limit || match.time_right == data.time_limit)
            {
                match.ended = true;
                match.end_flag = true;
            }
        }
    }

    // Pause indicator
    if (match.paused)
    {
        ctx.lcd().setCursor(6, 0);
        ctx.lcd().print('P');
    }
    else
    {
        ctx.lcd().setCursor(6, 0);
        ctx.lcd().print(' ');
    }

    // Left player indicator
    ctx.lcd().setCursor(0, 0);
    ctx.lcd().write(CharacterEmptyRectangle);

    // Right player indicator
    ctx.lcd().setCursor(15, 0);
    ctx.lcd().write(CharacterFilledRectangle);

    // Middle seperator
    ctx.lcd().setCursor(7, 0);
    ctx.lcd().write(CharacterRightPipe);
    ctx.lcd().setCursor(7, 1);
    ctx.lcd().write(CharacterRightPipe);

    ctx.lcd().setCursor(8, 0);
    ctx.lcd().write(CharacterLeftPipe);
    ctx.lcd().setCursor(8, 1);
    ctx.lcd().write(CharacterLeftPipe);

    // Turn indicator
    switch (match.player)
    {
        case Player::Left:
            ctx.lcd().setCursor(12, 0);
            ctx.lcd().print(' ');

            ctx.lcd().setCursor(3, 0);
            ctx.lcd().write(CharacterTurnIndicator);

            break;
        case Player::Right:
            ctx.lcd().setCursor(3, 0);
            ctx.lcd().print(' ');

            ctx.lcd().setCursor(12, 0);
            ctx.lcd().write(CharacterTurnIndicator);

            break;
    }

    // Player times
    display_time(ctx.lcd(), match.time_left, Player::Left, data.show_deciseconds);
    display_time(ctx.lcd(), match.time_right, Player::Right, data.show_deciseconds);

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
            static bool on {true};
            on = !on;
            toggle_light(match.player == Player::Right ? RIGHT_LED : LEFT_LED, on);
        }
    }
}

void TwoClockDownState::start()
{
    const Data& data {ctx.user_data<Data>()};

    match.time_left = data.time_limit;
    match.time_right = data.time_limit;

    match.player = Player::Right;

    match.paused = true;
    match.ended = false;
    toggle_light(RIGHT_LED, true);
    toggle_light(LEFT_LED, false);

    play_melody(START_MELODY);

    timer.reset();
}

void TwoClockDownState::stop()
{
    toggle_light(RIGHT_LED, false);
    toggle_light(LEFT_LED, false);
}

void TwoClockDownState::update()
{
    const Data& data {ctx.user_data<Data>()};

    if (ctx.is_button_pressed(ButtonStartStop) && !match.ended)
    {
        match.paused = !match.paused;

        if (!match.paused)
        {
            play_melody(START_BEEP);
        }
    }

    if (ctx.is_button_pressed(ButtonSoftReset))
    {
        ctx.change_state(StateMenu);
    }

    if (!match.paused && !match.ended)
    {
        if (ctx.is_button_pressed(ButtonLeftPlayer) && match.player == Player::Left)
        {
            match.player = Player::Right;
            toggle_light(RIGHT_LED, true);
            toggle_light(LEFT_LED, false);
        }
        else if (ctx.is_button_pressed(ButtonRightPlayer) && match.player == Player::Right)
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
                    match.time_left--;
                    break;
                case Player::Right:
                    match.time_right--;
                    break;
            }

            if (match.time_left == 0 || match.time_right == 0)
            {
                match.ended = true;
                match.end_flag = true;
            }
        }
    }

    // Pause indicator
    if (match.paused)
    {
        ctx.lcd().setCursor(6, 0);
        ctx.lcd().print('P');
    }
    else
    {
        ctx.lcd().setCursor(6, 0);
        ctx.lcd().print(' ');
    }

    // Left player indicator
    ctx.lcd().setCursor(0, 0);
    ctx.lcd().write(CharacterEmptyRectangle);

    // Right player indicator
    ctx.lcd().setCursor(15, 0);
    ctx.lcd().write(CharacterFilledRectangle);

    // Middle seperator
    ctx.lcd().setCursor(7, 0);
    ctx.lcd().write(CharacterRightPipe);
    ctx.lcd().setCursor(7, 1);
    ctx.lcd().write(CharacterRightPipe);

    ctx.lcd().setCursor(8, 0);
    ctx.lcd().write(CharacterLeftPipe);
    ctx.lcd().setCursor(8, 1);
    ctx.lcd().write(CharacterLeftPipe);

    // Turn indicator
    switch (match.player)
    {
        case Player::Left:
            ctx.lcd().setCursor(12, 0);
            ctx.lcd().print(' ');

            ctx.lcd().setCursor(3, 0);
            ctx.lcd().write(CharacterTurnIndicator);

            break;
        case Player::Right:
            ctx.lcd().setCursor(3, 0);
            ctx.lcd().print(' ');

            ctx.lcd().setCursor(12, 0);
            ctx.lcd().write(CharacterTurnIndicator);

            break;
    }

    // Player times
    display_time(ctx.lcd(), match.time_left, Player::Left, data.show_deciseconds);
    display_time(ctx.lcd(), match.time_right, Player::Right, data.show_deciseconds);

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
            static bool on {true};
            on = !on;
            toggle_light(match.player == Player::Right ? RIGHT_LED : LEFT_LED, on);
        }
    }
}

void OneClockUpState::start()
{
    match.time = 0;
    match.paused = true;
    match.ended = false;

    play_melody(START_MELODY);

    timer.reset();
}

void OneClockUpState::stop()
{
    toggle_light(RIGHT_LED, false);
    toggle_light(LEFT_LED, false);
}

void OneClockUpState::update()
{
    const Data& data {ctx.user_data<Data>()};

    if (ctx.is_button_pressed(ButtonStartStop) && !match.ended)
    {
        match.paused = !match.paused;

        if (!match.paused)
        {
            play_melody(START_BEEP);
        }
    }

    if (ctx.is_button_pressed(ButtonSoftReset))
    {
        ctx.change_state(StateMenu);
    }

    if (ctx.is_button_pressed(ButtonOk))
    {
        match.time = 0;
        match.paused = true;
        match.ended = false;

        ctx.lcd().clear();

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

            if (match.time == data.time_limit)
            {
                match.ended = true;
                match.end_flag = true;
            }
        }
    }

    // Pause indicator
    if (match.paused)
    {
        ctx.lcd().setCursor(2, 1);
        ctx.lcd().print('P');
    }
    else
    {
        ctx.lcd().setCursor(2, 1);
        ctx.lcd().print(' ');
    }

    display_time_one(ctx.lcd(), match.time, data.show_deciseconds);

    display_progress_bar(ctx.lcd(), match.time, data.time_limit, Monotony::Ascend);

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
            static bool on {true};
            on = !on;
            toggle_light(RIGHT_LED, on);
            toggle_light(LEFT_LED, on);
        }
    }
}

void OneClockDownState::start()
{
    const Data& data {ctx.user_data<Data>()};

    match.time = data.time_limit;
    match.paused = true;
    match.ended = false;

    play_melody(START_MELODY);

    timer.reset();
}

void OneClockDownState::stop()
{
    toggle_light(RIGHT_LED, false);
    toggle_light(LEFT_LED, false);
}

void OneClockDownState::update()
{
    const Data& data {ctx.user_data<Data>()};

    if (ctx.is_button_pressed(ButtonStartStop) && !match.ended)
    {
        match.paused = !match.paused;

        if (!match.paused)
        {
            play_melody(START_BEEP);
        }
    }

    if (ctx.is_button_pressed(ButtonSoftReset))
    {
        ctx.change_state(StateMenu);
    }

    if (ctx.is_button_pressed(ButtonOk))
    {
        match.time = data.time_limit;
        match.paused = true;
        match.ended = false;

        ctx.lcd().clear();

        toggle_light(RIGHT_LED, false);
        toggle_light(LEFT_LED, false);

        play_melody(GENTLE_RESET_BEEP);

        timer.reset();
    }

    if (!match.paused && !match.ended)
    {
        if (timer.tick())
        {
            match.time--;

            if (match.time == 0)
            {
                match.ended = true;
                match.end_flag = true;
            }
        }
    }

    // Pause indicator
    if (match.paused)
    {
        ctx.lcd().setCursor(2, 1);
        ctx.lcd().print('P');
    }
    else
    {
        ctx.lcd().setCursor(2, 1);
        ctx.lcd().print(' ');
    }

    display_time_one(ctx.lcd(), match.time, data.show_deciseconds);

    display_progress_bar(ctx.lcd(), match.time, data.time_limit, Monotony::Descend);

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
            static bool on {true};
            on = !on;
            toggle_light(RIGHT_LED, on);
            toggle_light(LEFT_LED, on);
        }
    }
}

static const char* DICE_ANIMATION[2] {
    "<", ">"
};

void DiceState::start()
{
    Data& data {ctx.user_data<Data>()};

    randomSeed(micros() / 4);

    dice[0] = 0;
    dice[1] = 0;

    switch (data.mode)
    {
        case ModeDiceOne:
            data.dice_count = 1;
            break;
        case ModeDiceTwo:
            data.dice_count = 2;
            break;
    }
}

void DiceState::update()
{
    const Data& data {ctx.user_data<Data>()};

    const bool pressed {
        ctx.is_button_pressed(ButtonLeftPlayer) ||
        ctx.is_button_pressed(ButtonRightPlayer)
    };

    if (pressed)
    {
        for (size_t i {0}; i < 2; i++)
        {
            dice[i] = random(1, 7);
        }

        for (size_t i {0}; i < 8; i++)
        {
            ctx.lcd().clear();
            ctx.lcd().setCursor(7, 0);
            ctx.lcd().print(DICE_ANIMATION[i % 2]);

            if (data.dice_count == 2)
            {
                ctx.lcd().setCursor(7, 1);
                ctx.lcd().print(DICE_ANIMATION[i % 2]);
            }

            static bool on {false};
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

    if (ctx.is_button_pressed(ButtonSoftReset))
    {
        ctx.change_state(StateMenu);
    }

    if (dice[0] != 0)
    {
        ctx.lcd().setCursor(0, 0);
        ctx.lcd().print("***");
        ctx.lcd().setCursor(0, 1);
        ctx.lcd().print("***");
        ctx.lcd().setCursor(13, 0);
        ctx.lcd().print("***");
        ctx.lcd().setCursor(13, 1);
        ctx.lcd().print("***");

        // The dice
        ctx.lcd().setCursor(7, 0);
        ctx.lcd().print(dice[0]);

        if (data.dice_count == 2)
        {
            ctx.lcd().setCursor(7, 1);
            ctx.lcd().print(dice[1]);
        }
    }
    else
    {
        ctx.lcd().setCursor(1, 0);
        ctx.lcd().print("Roll the dice!");
    }
}
