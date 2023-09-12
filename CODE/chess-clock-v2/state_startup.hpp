#pragma once

#include "state.hpp"
#include "context.hpp"

struct StateStartup : State
{
  StateStartup(Context* ctx)
    : State(ctx) {}

  virtual void start() override;
  virtual void update() override;
};
