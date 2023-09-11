#include <Arduino.h>

#include "other.hpp"
#include "context.hpp"

void toggle_light(bool on, int light)
{
  digitalWrite(light, on ? HIGH : LOW);
}

void do_every(unsigned long milliseconds, Context* ctx, void(*work)(Context*))
{
  static unsigned long last_time = 0;

  if (millis() - last_time > milliseconds)
  {
      work(ctx);
      last_time = millis();
  }
}
