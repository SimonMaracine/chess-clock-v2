#pragma once

#define PIN_RS 2
#define PIN_E 3
#define PIN_D4 4
#define PIN_D5 5
#define PIN_D6 6
#define PIN_D7 7

#define BUZZER 9
#define LED_LEFT 11
#define LED_RIGHT 10

#define BUTTON_LEFT_PLAYER A0
#define BUTTON_RIGHT_PLAYER A1
#define BUTTON_START_STOP A2
#define BUTTON_SOFT_RESET A3
#define BUTTON_OK A4

enum Button
{
    ButtonLeftPlayer,
    ButtonRightPlayer,
    ButtonStartStop,
    ButtonSoftReset,
    ButtonOk
};

enum State
{
    StateStartup,
    StateMenu,
    StateModes,
    StateTime,
    StatePreTime,
    StateDeciseconds,
    StateTwoClockUp,
    StateTwoClockDown,
    StateOneClockUp,
    StateOneClockDown,
    StateDice
};

enum Menu
{
    MenuModes,
    MenuTime,
    MenuDeciseconds,
    MenuStart,

    Menu_Count
};

// Uses more memory :P
static constexpr int MENU_CURSOR[4] {
    2, 6, 10, 14
};

enum Mode
{
    ModeTwoClockUp,
    ModeTwoClockDown,
    ModeOneClockUp,
    ModeOneClockDown,
    ModeDiceOne,
    ModeDiceTwo,

    Mode_Count
};

enum class TimeMode
{
    Minutes,
    Seconds
};

enum class Player
{
    Left,
    Right
};

// Defined in deciseconds
#define NINETY_MINUTES_D 54000
#define THIRTY_MINUTES_D 18000
#define THREE_MINUTES_D 1800
#define ONE_MINUTE_D 600
#define ONE_SECOND_D 10

// Defined in milliseconds
#define ONE_SECOND_M 1000
#define ONE_DECISECOND_M 100
#define TWO_DECISECONDS_M 200
