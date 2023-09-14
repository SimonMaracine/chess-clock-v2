#include <Arduino.h>

#include "all_states.hpp"
#include "definitions.hpp"
#include "other.hpp"

void StateDeciseconds::update()
{
  if (ctx->buttons.is_button_pressed(LeftPlayerButton))
  {
    ctx->show_deciseconds = !ctx->show_deciseconds;
  }
  else if (ctx->buttons.is_button_pressed(RightPlayerButton))
  {
    ctx->show_deciseconds = !ctx->show_deciseconds;
  }
  else if (ctx->buttons.is_button_pressed(OkButton))
  {
    ctx->change_state(MenuState);
  }
  
  ctx->lcd.setCursor(0, 0);
  ctx->lcd.print("Show fractions:");

  ctx->lcd.setCursor(0, 1);
  if (ctx->show_deciseconds)
  {
    ctx->lcd.print("On ");
  }
  else
  {
    ctx->lcd.print("Off");
  }
}
