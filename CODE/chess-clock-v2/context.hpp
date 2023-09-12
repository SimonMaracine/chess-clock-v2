#pragma once

#include <stddef.h>
#include <stdint.h>

#include <LiquidCrystal.h>

#include "definitions.hpp"
#include "buttons.hpp"
#include "state.hpp"

struct Context
{
  Context()
    : lcd(RS, E, D4, D5, D6, D7) {}

  void initialize(State* state);
  void update();

  void add_state(State* state);
  void add_button(uint8_t port);
  void change_state(size_t state);

  LiquidCrystal lcd;
  unsigned long last_time = 0;  // Milliseconds
  Buttons buttons;

  struct
  {
    State* current = nullptr;

    bool changed_state = false;
    State* next = nullptr;

    State* states[16] {};
    size_t count = 0;
  } state;

  Menu menu = Menu::Modes;
  Mode mode = Mode::TwoClockUp;

  TimeMode time_mode = TimeMode::Minutes;
  unsigned long time_limit = THIRTY_MINUTES_D;  // Deciseconds
  bool show_deciseconds = false;
};
