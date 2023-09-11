#include <Arduino.h>

#include "state_startup.hpp"
#include "definitions.hpp"
#include "other.hpp"

void StateStartup::start()
{

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
      toggle_light(false, RIGHT_LED);
      toggle_light(false, LEFT_LED);
      ctx->change_state(MenuState);
  }

  do_every(ONE_SECOND_M, ctx, [](Context*) {
      static bool on = true;
      on = !on;
      toggle_light(on, RIGHT_LED);
      toggle_light(!on, LEFT_LED);
  });

  static const char* show = (
    analogRead(A5) % 2 == 0 ? "By Tudor & Simon" : "By Simon & Tudor"
  );

  ctx->lcd.setCursor(0, 0);
  ctx->lcd.print("Chess Clock v1.0");
  ctx->lcd.setCursor(0, 1);
  ctx->lcd.print(show);
}
