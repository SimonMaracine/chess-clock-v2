#include "context.hpp"
#include "state_startup.hpp"
#include "state_menu.hpp"

static Context ctx;

void setup()
{
  Serial.begin(9600);

  // Allocate all states
  StateStartup startup {&ctx};
  StateMenu menu {&ctx};

  ctx.add_state(&startup);
  ctx.add_state(&menu);

  ctx.add_button(LEFT_PLAYER_BUTTON);
  ctx.add_button(RIGHT_PLAYER_BUTTON);
  ctx.add_button(START_STOP_BUTTON);
  ctx.add_button(SOFT_RESET_BUTTON);
  ctx.add_button(OK_BUTTON);

  ctx.initialize(&startup);
}

void loop()
{
  ctx.update();
  delay(2);
}
