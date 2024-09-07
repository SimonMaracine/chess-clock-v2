#pragma once

#include "context.hpp"

namespace chess_clock
{
    struct State
    {
        explicit State(Context& ctx)
            : ctx(ctx) {}
        virtual ~State() = default;

        State(const State&) = delete;
        State& operator=(const State&) = delete;
        State(State&&) = delete;
        State& operator=(State&&) = delete;

        virtual void start() {}
        virtual void stop() {}
        virtual void update() = 0;

        Context& ctx;
    };
}
