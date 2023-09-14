#pragma once

#include <stddef.h>

#define PIN_RS 2
#define PIN_E 3
#define PIN_D4 4
#define PIN_D5 5
#define PIN_D6 6
#define PIN_D7 7

#define BUZZER 9
#define LEFT_LED 11
#define RIGHT_LED 10

#define LEFT_PLAYER_BUTTON A0
#define RIGHT_PLAYER_BUTTON A1
#define START_STOP_BUTTON A2
#define SOFT_RESET_BUTTON A3
#define OK_BUTTON A4

enum ButtonList
{
    LeftPlayerButton,
    RightPlayerButton,
    StartStopButton,
    SoftResetButton,
    OkButton
};

enum StateList
{
    StartupState,
    MenuState,
    ModesState,
    TimeState,
    PreTimeState,
    DecisecondsState,
    TwoClockUpState,
    TwoClockDownState,
    OneClockUpState,
    OneClockDownState,
    DiceState
};

enum class Menu
{
    Modes,
    Time,
    Deciseconds,
    Start,

    MenuCount
};

// Uses more memory :P
constexpr int MENU_CURSOR[static_cast<size_t>(Menu::MenuCount)] = {
    2, 6, 10, 14
};

enum class Mode
{
    TwoClockUp,
    TwoClockDown,
    OneClockUp,
    OneClockDown,
    DiceOne,
    DiceTwo,

    ModeCount
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

#define DEGREE_CHARACTER 176

struct Match
{
    Player player = Player::Right;

    unsigned long left_player_time = 0;  // Deciseconds
    unsigned long right_player_time = 0;

    bool paused = true;
    bool ended = false;
    bool end_flag = false;  // One time flag
};

struct MatchOneTimer
{
    unsigned long time = 0;  // Deciseconds

    bool paused = true;
    bool ended = false;
    bool end_flag = false;  // One time flag
};
