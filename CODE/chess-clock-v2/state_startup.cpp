#include <Arduino.h>

#include "all_states.hpp"
#include "definitions.hpp"
#include "other.hpp"

void StateStartup::start()
{
  timer.reset();
}

void StateStartup::update()
{
  const bool ok = (
    ctx->buttons.is_button_pressed(LeftPlayerButton) ||
    ctx->buttons.is_button_pressed(RightPlayerButton) ||
    ctx->buttons.is_button_pressed(StartStopButton) ||
    ctx->buttons.is_button_pressed(SoftResetButton) ||
    ctx->buttons.is_button_pressed(OkButton)
  );

  if (ok)
  {
      toggle_light(RIGHT_LED, false);
      toggle_light(LEFT_LED, false);
      ctx->change_state(MenuState);
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

  ctx->lcd.setCursor(0, 0);
  ctx->lcd.print("Chess Clock v2.0");
  ctx->lcd.setCursor(0, 1);
  ctx->lcd.print(show);
}
