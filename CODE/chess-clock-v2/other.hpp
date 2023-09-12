#pragma once

#include "context.hpp"

void toggle_light(bool on, int light);
void do_every(unsigned long milliseconds, Context* ctx, void(*work)(Context*));
