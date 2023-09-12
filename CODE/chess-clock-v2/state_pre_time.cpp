#include <Arduino.h>

#include "all_states.hpp"
#include "definitions.hpp"
#include "other.hpp"
#include "characters.hpp"

void StatePreTime::start()
{

}

void StatePreTime::update()
{
  if (ctx->buttons.is_button_pressed(LeftPlayerButton) ||
      ctx->buttons.is_button_pressed(RightPlayerButton))
  {
    switch (ctx->time_mode)
    {
      case TimeMode::Minutes:
        ctx->time_mode = TimeMode::Seconds;
        break;
      case TimeMode::Seconds:
        ctx->time_mode = TimeMode::Minutes;
        break;
    }
  }

  if (ctx->buttons.is_button_pressed(OkButton))
  {
    switch (ctx->time_mode)
    {
      case TimeMode::Minutes:
        ctx->time_limit = THIRTY_MINUTES_D;
        break;
      case TimeMode::Seconds:
        ctx->time_limit = ONE_MINUTE_D;
        break;
    }

    ctx->change_state(TimeState);
  }

  ctx->lcd.setCursor(0, 0);
  ctx->lcd.print("Set time in:");
  
  ctx->lcd.setCursor(0, 1);
  switch (ctx->time_mode)
  {
    case TimeMode::Minutes:
      ctx->lcd.print("Minutes");
      break;
    case TimeMode::Seconds:
      ctx->lcd.print("Seconds");
      break;
  }
}
