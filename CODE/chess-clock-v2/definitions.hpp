#pragma once

#define RS 2
#define E 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

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
  TwoClockUpState
};

enum class Menu
{
  Modes = 2,
  Time = 6,
  Deciseconds = 10,
  Start = 14
};

enum class Mode
{
  TwoClockUp,
  TwoClockDown,
  OneClockUp,
  OneClockDown,
  Dice
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
