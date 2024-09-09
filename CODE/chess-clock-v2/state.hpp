#pragma once

#include "context.hpp"

namespace chess_clock
{
    class State
    {
    public:
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
    protected:
        Context& ctx;
    };
}
