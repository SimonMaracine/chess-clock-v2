#include <Arduino.h>

#include "all_states.hpp"
#include "definitions.hpp"
#include "other.hpp"
#include "characters.hpp"

void StateMenu::start()
{

}

void StateMenu::update()
{
  if (ctx->buttons.is_button_pressed(LeftPlayerButton))
  {
    ctx->lcd.setCursor(static_cast<int>(ctx->menu), 1);
    ctx->lcd.print(' ');

    if (ctx->menu == Menu::Modes)
    {
      ctx->menu = Menu::Start;
    }
    else
    {
      ctx->menu = static_cast<Menu>(static_cast<int>(ctx->menu) - 4);
    }
  }
  else if (ctx->buttons.is_button_pressed(RightPlayerButton))
  {
    ctx->lcd.setCursor(static_cast<int>(ctx->menu), 1);
    ctx->lcd.print(' ');

    if (ctx->menu == Menu::Start)
    {
      ctx->menu = Menu::Modes;
    }
    else
    {
      ctx->menu = static_cast<Menu>(static_cast<int>(ctx->menu) + 4);
    }
  }
  else if (ctx->buttons.is_button_pressed(OkButton))
  {
    switch (ctx->menu)
    {
      case Menu::Modes:
        ctx->change_state(ModesState);
        break;
      case Menu::Time:
        ctx->change_state(PreTimeState);
        break;
      case Menu::Deciseconds:
        ctx->change_state(DecisecondsState);
        break;
      case Menu::Start:
        switch (ctx->mode)
        {
          case Mode::TwoClockUp:
            ctx->change_state(TwoClockUpState);
            break;
          case Mode::TwoClockDown:
            // setup_two_clock_down();
            // make_sound(START_MELODY, 4);
            // CHANGE_MODE(mode_two_clock_down)
            break;
          case Mode::OneClockUp:
            // setup_one_clock_up();
            // make_sound(START_MELODY, 4);
            // CHANGE_MODE(mode_one_clock_up)
            break;
          case Mode::OneClockDown:
            // setup_one_clock_down();
            // make_sound(START_MELODY, 4);
            // CHANGE_MODE(mode_one_clock_down)  
            break;
          case Mode::Dice:
            // setup_dice();
            // make_sound(START_MELODY, 4);
            // CHANGE_MODE(mode_dice)
            break;
        }
    }
  }

  ctx->lcd.setCursor(3, 0);
  ctx->lcd.print("Setup Menu");

  ctx->lcd.setCursor(1, 1);
  ctx->lcd.print('M');
  ctx->lcd.setCursor(5, 1);
  ctx->lcd.print('T');
  ctx->lcd.setCursor(9, 1);
  ctx->lcd.print('D');
  ctx->lcd.setCursor(13, 1);
  ctx->lcd.write(StartFlag);

  ctx->lcd.setCursor(static_cast<int>(ctx->menu), 1);
  ctx->lcd.write(TurnIndicator);
}
