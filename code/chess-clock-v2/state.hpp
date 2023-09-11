#pragma once

struct Context;

struct State
{
  State(Context* ctx)
    : ctx(ctx) {}

  virtual ~State() = default;

  virtual void start() = 0;
  virtual void update() = 0;

  Context* ctx = nullptr;
};
