#pragma once

#include <stddef.h>
#include <stdint.h>

struct Button
{
  bool currently_pressed = false;
  bool previously_pressed = false;

  uint8_t port {};
};

struct Buttons
{
  void add_button(uint8_t port);
  void update();
  bool is_button_pressed(size_t button) const;
  bool is_button_down(size_t button) const;

  Button buttons[16] {};
  size_t count = 0;
};
