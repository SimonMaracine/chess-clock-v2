#pragma once

struct Context;

struct State
{
  State(Context* ctx)
    : ctx(ctx) {}

  virtual ~State() = default;

  virtual void start() {}
  virtual void stop() {}
  virtual void update() = 0;

  Context* ctx = nullptr;
};
