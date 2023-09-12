#pragma once

#include "state.hpp"
#include "context.hpp"

struct StateMenu : State
{
  StateMenu(Context* ctx)
    : State(ctx) {}

  virtual void start() override;
  virtual void update() override;
};
