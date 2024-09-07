#include "states.hpp"

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
    const bool ok = (
        ctx.buttons.is_button_pressed(LeftPlayerButton) ||
        ctx.buttons.is_button_pressed(RightPlayerButton) ||
        ctx.buttons.is_button_pressed(StartStopButton) ||
        ctx.buttons.is_button_pressed(SoftResetButton) ||
        ctx.buttons.is_button_pressed(OkButton)
    );

    if (ok)
    {
        ctx.change_state(MenuState);
    }

    if (timer.tick())
    {
        static bool on = true;
        on = !on;
        toggle_light(RIGHT_LED, on);
        toggle_light(LEFT_LED, !on);
    }

    static const char* show = (
        analogRead(A5) % 2 == 0 ? "By Tudor & Simon" : "By Simon & Tudor"
    );

    ctx.lcd.setCursor(0, 0);
    ctx.lcd.print("Chess Clock v2.0");
    ctx.lcd.setCursor(0, 1);
    ctx.lcd.print(show);
}

void MenuState::update()
{
    if (ctx.buttons.is_button_pressed(LeftPlayerButton))
    {
        ctx.lcd.setCursor(MENU_CURSOR[static_cast<size_t>(ctx.menu)], 1);
        ctx.lcd.print(' ');

        ctx.menu = wrapped_subtract(ctx.menu, Menu::MenuCount);
    }

    if (ctx.buttons.is_button_pressed(RightPlayerButton))
    {
        ctx.lcd.setCursor(MENU_CURSOR[static_cast<size_t>(ctx.menu)], 1);
        ctx.lcd.print(' ');

        ctx.menu = wrapped_add(ctx.menu, Menu::MenuCount);
    }

    if (ctx.buttons.is_button_pressed(OkButton))
    {
        switch (ctx.menu)
        {
            case Menu::Modes:
                ctx.change_state(ModesState);
                break;
            case Menu::Time:
                ctx.change_state(PreTimeState);
                break;
            case Menu::Deciseconds:
                ctx.change_state(DecisecondsState);
                break;
            case Menu::Start:
                switch (ctx.mode)
                {
                    case Mode::TwoClockUp:
                        ctx.change_state(TwoClockUpState);
                        break;
                    case Mode::TwoClockDown:
                        ctx.change_state(TwoClockDownState);
                        break;
                    case Mode::OneClockUp:
                        ctx.change_state(OneClockUpState);
                        break;
                    case Mode::OneClockDown:
                        ctx.change_state(OneClockDownState);
                        break;
                    case Mode::DiceOne:
                        ctx.change_state(DiceState);
                        break;
                    case Mode::DiceTwo:
                        ctx.change_state(DiceState);
                        break;
                }
            }
    }

    ctx.lcd.setCursor(3, 0);
    ctx.lcd.print("Setup Menu");

    ctx.lcd.setCursor(1, 1);
    ctx.lcd.print('M');
    ctx.lcd.setCursor(5, 1);
    ctx.lcd.print('T');
    ctx.lcd.setCursor(9, 1);
    ctx.lcd.print('D');
    ctx.lcd.setCursor(13, 1);
    ctx.lcd.write(StartFlag);

    ctx.lcd.setCursor(MENU_CURSOR[static_cast<size_t>(ctx.menu)], 1);
    ctx.lcd.write(TurnIndicator);
}

void ModesState::update()
{
    if (ctx.buttons.is_button_pressed(LeftPlayerButton))
    {
        ctx.mode = wrapped_subtract(ctx.mode, Mode::ModeCount);
    }

    if (ctx.buttons.is_button_pressed(RightPlayerButton))
    {
        ctx.mode = wrapped_add(ctx.mode, Mode::ModeCount);
    }

    if (ctx.buttons.is_button_pressed(OkButton))
    {
        ctx.change_state(MenuState);
    }

    ctx.lcd.setCursor(0, 0);
    ctx.lcd.print("Set mode:");

    ctx.lcd.setCursor(0, 1);
    switch (ctx.mode)
    {
        case Mode::TwoClockUp:
            ctx.lcd.print("Two Clock ");
            ctx.lcd.write(UpArrow);
            break;
        case Mode::TwoClockDown:
            ctx.lcd.print("Two Clock ");
            ctx.lcd.write(DownArrow);
            break;
        case Mode::OneClockUp:
            ctx.lcd.print("One Clock ");
            ctx.lcd.write(UpArrow);
            break;
        case Mode::OneClockDown:
            ctx.lcd.print("One Clock ");
            ctx.lcd.write(DownArrow);
            break;
        case Mode::DiceOne:
            ctx.lcd.print("Dice One   ");
            break;
        case Mode::DiceTwo:
            ctx.lcd.print("Dice Two   ");
            break;
    }
}

void TimeState::update()
{
    unsigned long lower_limit;
    unsigned long upper_limit;
    unsigned long step;

    switch (ctx.time_mode)
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

    if (ctx.buttons.is_button_down(LeftPlayerButton))
    {
        if (ctx.time_limit > lower_limit)
        {
            ctx.time_limit -= step;
            delay(DELAY);
        }
    }

    if (ctx.buttons.is_button_down(RightPlayerButton))
    {
        if (ctx.time_limit < upper_limit)
        {
            ctx.time_limit += step;
            delay(DELAY);
        }
    }

    if (ctx.buttons.is_button_pressed(OkButton))
    {
        ctx.change_state(MenuState);
    }

    ctx.lcd.setCursor(0, 0);
    ctx.lcd.print("Set time limit:");

    ctx.lcd.setCursor(0, 1);
    switch (ctx.time_mode)
    {
        case TimeMode::Minutes:
            ctx.lcd.print(ctx.time_limit / ONE_MINUTE_D);
            break;
        case TimeMode::Seconds:
            ctx.lcd.print(ctx.time_limit / ONE_SECOND_D);
            break;
    }

    // Clear the last digit when there are't three digits
    ctx.lcd.print(" ");
}

void PreTimeState::update()
{
    if (ctx.buttons.is_button_pressed(LeftPlayerButton) ||
        ctx.buttons.is_button_pressed(RightPlayerButton))
    {
        switch (ctx.time_mode)
        {
            case TimeMode::Minutes:
                ctx.time_mode = TimeMode::Seconds;
                break;
            case TimeMode::Seconds:
                ctx.time_mode = TimeMode::Minutes;
                break;
        }        
    }

    if (ctx.buttons.is_button_pressed(OkButton))
    {
        if (ctx.time_mode != previous_time_mode)
        {
            switch (ctx.time_mode)
            {
                case TimeMode::Minutes:
                    ctx.time_limit = THIRTY_MINUTES_D;
                    break;
                case TimeMode::Seconds:
                    ctx.time_limit = ONE_MINUTE_D;
                    break;
            }

            previous_time_mode = ctx.time_mode;
        }

        ctx.change_state(TimeState);
    }

    ctx.lcd.setCursor(0, 0);
    ctx.lcd.print("Set time in:");

    ctx.lcd.setCursor(0, 1);
    switch (ctx.time_mode)
    {
        case TimeMode::Minutes:
            ctx.lcd.print("Minutes");
            break;
        case TimeMode::Seconds:
            ctx.lcd.print("Seconds");
            break;
    }
}

void DecisecondsState::update()
{
    Data& data {ctx.get_user_data<Data>()};

    if (ctx.buttons.is_button_pressed(ButtonLeftPlayer))
    {
        data.show_deciseconds = !data.show_deciseconds;
    }

    if (ctx.buttons.is_button_pressed(ButtonRightPlayer))
    {
        data.show_deciseconds = !data.show_deciseconds;
    }

    if (ctx.buttons.is_button_pressed(ButtonOk))
    {
        ctx.change_state(StateMenu);
    }

    ctx.lcd.setCursor(0, 0);
    ctx.lcd.print("Show fractions:");

    ctx.lcd.setCursor(0, 1);
    if (data.show_deciseconds)
    {
        ctx.lcd.print("On ");
    }
    else
    {
        ctx.lcd.print("Off");
    }
}

void TwoClockUpState::start()
{
    match.left_player_time = 0;
    match.right_player_time = 0;

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
    if (ctx.buttons.is_button_pressed(StartStopButton) && !match.ended)
    {
        match.paused = !match.paused;

        if (!match.paused)
        {
            play_melody(START_BEEP);
        }
    }

    if (ctx.buttons.is_button_pressed(SoftResetButton))
    {
        ctx.change_state(MenuState);
    }

    if (!match.paused && !match.ended)
    {
        if (ctx.buttons.is_button_pressed(LeftPlayerButton) && match.player == Player::Left)
        {
            match.player = Player::Right;
            toggle_light(RIGHT_LED, true);
            toggle_light(LEFT_LED, false);
        }
        else if (ctx.buttons.is_button_pressed(RightPlayerButton) && match.player == Player::Right)
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
                    match.left_player_time++;
                    break;
                case Player::Right:
                    match.right_player_time++;
                    break;
            }

            if (match.left_player_time == ctx.time_limit ||
                match.right_player_time == ctx.time_limit)
            {
                match.ended = true;
                match.end_flag = true;
            }
        }
    }

    // Pause indicator
    if (match.paused)
    {
        ctx.lcd.setCursor(6, 0);
        ctx.lcd.print('P');
    }
    else
    {
        ctx.lcd.setCursor(6, 0);
        ctx.lcd.print(' ');
    }

    // Left player indicator
    ctx.lcd.setCursor(0, 0);
    ctx.lcd.write(EmptyRectangle);

    // Right player indicator
    ctx.lcd.setCursor(15, 0);
    ctx.lcd.write(FilledRectangle);

    // Middle seperator
    ctx.lcd.setCursor(7, 0);
    ctx.lcd.write(RightPipe);
    ctx.lcd.setCursor(7, 1);
    ctx.lcd.write(RightPipe);

    ctx.lcd.setCursor(8, 0);
    ctx.lcd.write(LeftPipe);
    ctx.lcd.setCursor(8, 1);
    ctx.lcd.write(LeftPipe);

    // Turn indicator
    switch (match.player)
    {
        case Player::Left:
            ctx.lcd.setCursor(12, 0);
            ctx.lcd.print(' ');

            ctx.lcd.setCursor(3, 0);
            ctx.lcd.write(TurnIndicator);

            break;
        case Player::Right:
            ctx.lcd.setCursor(3, 0);
            ctx.lcd.print(' ');

            ctx.lcd.setCursor(12, 0);
            ctx.lcd.write(TurnIndicator);

            break;
    }

    // Player times
    display_time(ctx.lcd, match.left_player_time, Player::Left, ctx.show_deciseconds);
    display_time(ctx.lcd, match.right_player_time, Player::Right, ctx.show_deciseconds);

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

void TwoClockDownState::start()
{
    match.left_player_time = ctx.time_limit;
    match.right_player_time = ctx.time_limit;

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
    if (ctx.buttons.is_button_pressed(StartStopButton) && !match.ended)
    {
        match.paused = !match.paused;

        if (!match.paused)
        {
            play_melody(START_BEEP);
        }
    }

    if (ctx.buttons.is_button_pressed(SoftResetButton))
    {
        ctx.change_state(MenuState);
    }

    if (!match.paused && !match.ended)
    {
        if (ctx.buttons.is_button_pressed(LeftPlayerButton) && match.player == Player::Left)
        {
            match.player = Player::Right;
            toggle_light(RIGHT_LED, true);
            toggle_light(LEFT_LED, false);
        }
        else if (ctx.buttons.is_button_pressed(RightPlayerButton) && match.player == Player::Right)
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
        ctx.lcd.setCursor(6, 0);
        ctx.lcd.print('P');
    }
    else
    {
        ctx.lcd.setCursor(6, 0);
        ctx.lcd.print(' ');
    }

    // Left player indicator
    ctx.lcd.setCursor(0, 0);
    ctx.lcd.write(EmptyRectangle);

    // Right player indicator
    ctx.lcd.setCursor(15, 0);
    ctx.lcd.write(FilledRectangle);

    // Middle seperator
    ctx.lcd.setCursor(7, 0);
    ctx.lcd.write(RightPipe);
    ctx.lcd.setCursor(7, 1);
    ctx.lcd.write(RightPipe);

    ctx.lcd.setCursor(8, 0);
    ctx.lcd.write(LeftPipe);
    ctx.lcd.setCursor(8, 1);
    ctx.lcd.write(LeftPipe);

    // Turn indicator
    switch (match.player)
    {
        case Player::Left:
            ctx.lcd.setCursor(12, 0);
            ctx.lcd.print(' ');

            ctx.lcd.setCursor(3, 0);
            ctx.lcd.write(TurnIndicator);

            break;
        case Player::Right:
            ctx.lcd.setCursor(3, 0);
            ctx.lcd.print(' ');

            ctx.lcd.setCursor(12, 0);
            ctx.lcd.write(TurnIndicator);

            break;
    }

    // Player times
    display_time(ctx.lcd, match.left_player_time, Player::Left, ctx.show_deciseconds);
    display_time(ctx.lcd, match.right_player_time, Player::Right, ctx.show_deciseconds);

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
    if (ctx.buttons.is_button_pressed(StartStopButton) && !match.ended)
    {
        match.paused = !match.paused;

        if (!match.paused)
        {
            play_melody(START_BEEP);
        }
    }

    if (ctx.buttons.is_button_pressed(SoftResetButton))
    {
        ctx.change_state(MenuState);
    }

    if (ctx.buttons.is_button_pressed(OkButton))
    {
        match.time = 0;
        match.paused = true;
        match.ended = false;

        ctx.lcd.clear();

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

            if (match.time == ctx.time_limit)
            {
                match.ended = true;
                match.end_flag = true;
            }
        }
    }

    // Pause indicator
    if (match.paused)
    {
        ctx.lcd.setCursor(2, 1);
        ctx.lcd.print('P');
    }
    else
    {
        ctx.lcd.setCursor(2, 1);
        ctx.lcd.print(' ');
    }

    display_time_one(ctx.lcd, match.time, ctx.show_deciseconds);

    display_progress_bar(ctx.lcd, match.time, ctx.time_limit, Monotony::Ascend);

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

void OneClockDownState::start()
{
    match.time = ctx.time_limit;
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
    if (ctx.buttons.is_button_pressed(StartStopButton) && !match.ended)
    {
        match.paused = !match.paused;

        if (!match.paused)
        {
            play_melody(START_BEEP);
        }
    }

    if (ctx.buttons.is_button_pressed(SoftResetButton))
    {
        ctx.change_state(MenuState);
    }

    if (ctx.buttons.is_button_pressed(OkButton))
    {
        match.time = ctx.time_limit;
        match.paused = true;
        match.ended = false;

        ctx.lcd.clear();

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
        ctx.lcd.setCursor(2, 1);
        ctx.lcd.print('P');
    }
    else
    {
        ctx.lcd.setCursor(2, 1);
        ctx.lcd.print(' ');
    }

    display_time_one(ctx.lcd, match.time, ctx.show_deciseconds);

    display_progress_bar(ctx.lcd, match.time, ctx.time_limit, Monotony::Descend);

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

static const char* DICE_ANIMATION[2] {
    "<", ">"
};

void DiceState::start()
{
    randomSeed(micros() / 4);

    dice[0] = 0;
    dice[1] = 0;

    Data& data {ctx.get_user_data<Data>()};

    switch (data.mode)
    {
        case Mode::DiceOne:
            data.dice_count = 1;
            break;
        case Mode::DiceTwo:
            data.dice_count = 2;
            break;
    }
}

void DiceState::update()
{
    if (ctx.buttons.is_button_pressed(ButtonLeftPlayer) ||
        ctx.buttons.is_button_pressed(ButtonRightPlayer))
    {
        for (size_t i = 0; i < 2; i++)
        {
            dice[i] = random(1, 7);
        }

        for (size_t i = 0; i < 8; i++)
        {
            ctx.lcd.clear();
            ctx.lcd.setCursor(7, 0);
            ctx.lcd.print(DICE_ANIMATION[i % 2]);

            if (ctx.dice_count == 2)
            {
                ctx.lcd.setCursor(7, 1);
                ctx.lcd.print(DICE_ANIMATION[i % 2]);
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

    if (ctx.buttons.is_button_pressed(SoftResetButton))
    {
        ctx.change_state(MenuState);
    }

    if (dice[0] != 0)
    {
        ctx.lcd.setCursor(0, 0);
        ctx.lcd.print("***");
        ctx.lcd.setCursor(0, 1);
        ctx.lcd.print("***");
        ctx.lcd.setCursor(13, 0);
        ctx.lcd.print("***");
        ctx.lcd.setCursor(13, 1);
        ctx.lcd.print("***");

        // The dice
        ctx.lcd.setCursor(7, 0);
        ctx.lcd.print(dice[0]);

        if (ctx.dice_count == 2)
        {
            ctx.lcd.setCursor(7, 1);
            ctx.lcd.print(dice[1]);
        }
    }
    else
    {
        ctx.lcd.setCursor(1, 0);
        ctx.lcd.print("Roll the dice!");
    }
}
