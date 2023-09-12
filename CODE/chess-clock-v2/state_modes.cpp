#include <Arduino.h>

#include "all_states.hpp"
#include "definitions.hpp"
#include "other.hpp"
#include "characters.hpp"

void StateModes::start()
{

}

void StateModes::update()
{
  if (ctx->buttons.is_button_pressed(LeftPlayerButton))
  {
    switch (ctx->mode)
    {
      case Mode::TwoClockUp:
        ctx->mode = Mode::Dice;
        break;
      case Mode::TwoClockDown:
        ctx->mode = Mode::TwoClockUp;
        break;
      case Mode::OneClockUp:
        ctx->mode = Mode::TwoClockDown;
        break;
      case Mode::OneClockDown:
        ctx->mode = Mode::OneClockUp;
        break;
      case Mode::Dice:
        ctx->mode = Mode::OneClockDown;
        break;
    }
  }
  else if (ctx->buttons.is_button_pressed(RightPlayerButton))
  {
    switch (ctx->mode)
    {
      case Mode::TwoClockUp:
        ctx->mode = Mode::TwoClockDown;
        break;
      case Mode::TwoClockDown:
        ctx->mode = Mode::OneClockUp;
        break;
      case Mode::OneClockUp:
        ctx->mode = Mode::OneClockDown;
        break;
      case Mode::OneClockDown:
        ctx->mode = Mode::Dice;
        break;
      case Mode::Dice:
        ctx->mode = Mode::TwoClockUp;
        break;
    }
  }
  else if (ctx->buttons.is_button_pressed(OkButton))
  {
    if (ctx->mode == Mode::Dice)
    {
      // CHANGE_MODE(mode_submenu_dice)  // FIXME
      // ctx->change_state()
    }

    ctx->change_state(MenuState);
  }

  ctx->lcd.setCursor(0, 0);
  ctx->lcd.print("Set game mode:");

  ctx->lcd.setCursor(0, 1);
  switch (ctx->mode)
  {
    case Mode::TwoClockUp:
      ctx->lcd.print("Two Clock ");
      ctx->lcd.write(UpArrow);
      break;
    case Mode::TwoClockDown:
      ctx->lcd.print("Two Clock ");
      ctx->lcd.write(DownArrow);
      break;
    case Mode::OneClockUp:
      ctx->lcd.print("One Clock ");
      ctx->lcd.write(UpArrow);
      break;
    case Mode::OneClockDown:
      ctx->lcd.print("One Clock ");
      ctx->lcd.write(DownArrow);
      break;
    case Mode::Dice:
      ctx->lcd.print("Dice       ");
      break;
  }
}
