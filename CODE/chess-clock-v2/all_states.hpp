#pragma once

#include "state.hpp"
#include "context.hpp"
#include "other.hpp"

struct StateStartup : State
{
  StateStartup(Context* ctx)
    : State(ctx) {}

  virtual void start() override;
  virtual void update() override;

  Timer timer {ONE_SECOND_M};
};

struct StateMenu : State
{
  StateMenu(Context* ctx)
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

struct StateDeciseconds : State
{
  StateDeciseconds(Context* ctx)
    : State(ctx) {}

  virtual void start() override;
  virtual void update() override;
};

struct StateTwoClockUp : State
{
  StateTwoClockUp(Context* ctx)
    : State(ctx) {}

  virtual void start() override;
  virtual void update() override;

  Timer timer {ONE_DECISECOND_M};
  Timer end_timer {TWO_DECISECONDS_M};
  Match match;
};
