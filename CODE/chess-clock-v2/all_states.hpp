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

struct StateStartup : State
{
  StateStartup(Context* ctx)
    : State(ctx) {}

  virtual void start() override;
  virtual void update() override;
};

struct StateModes : State
{
  StateModes(Context* ctx)
    : State(ctx) {}

  virtual void start() override;
  virtual void update() override;
};

struct StateTime : State
{
  StateTime(Context* ctx)
    : State(ctx) {}

  virtual void start() override;
  virtual void update() override;
};

struct StatePreTime : State
{
  StatePreTime(Context* ctx)
    : State(ctx) {}

  virtual void start() override;
  virtual void update() override;
};
