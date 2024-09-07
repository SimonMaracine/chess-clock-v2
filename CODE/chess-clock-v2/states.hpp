#pragma once

#include "state.hpp"
#include "context.hpp"
#include "other.hpp"

struct StartupState : chess_clock::State
{
    explicit StartupState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void start() override;
    void stop() override;
    void update() override;

    Timer timer {ONE_SECOND_M};
};

struct MenuState : chess_clock::State
{
    explicit MenuState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void update() override;
};

struct ModesState : chess_clock::State
{
    explicit ModesState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void update() override;
};

struct TimeState : chess_clock::State
{
    explicit TimeState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void update() override;
};

struct PreTimeState : chess_clock::State
{
    explicit PreTimeState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void update() override;

    TimeMode previous_time_mode = TimeMode::Minutes;
};

struct DecisecondsState : chess_clock::State
{
    explicit DecisecondsState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void update() override;
};

struct TwoClockUpState : chess_clock::State
{
    explicit TwoClockUpState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void start() override;
    void stop() override;
    void update() override;

    Timer timer {ONE_DECISECOND_M};
    Timer end_timer {TWO_DECISECONDS_M};
    Match match;
};

struct TwoClockDownState : chess_clock::State
{
    explicit TwoClockDownState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void start() override;
    void stop() override;
    void update() override;

    Timer timer {ONE_DECISECOND_M};
    Timer end_timer {TWO_DECISECONDS_M};
    Match match;
};

struct OneClockUpState : chess_clock::State
{
    explicit OneClockUpState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void start() override;
    void stop() override;
    void update() override;

    Timer timer {ONE_DECISECOND_M};
    Timer end_timer {TWO_DECISECONDS_M};
    MatchOneTimer match;
};

struct OneClockDownState : chess_clock::State
{
    explicit OneClockDownState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void start() override;
    void stop() override;
    void update() override;

    Timer timer {ONE_DECISECOND_M};
    Timer end_timer {TWO_DECISECONDS_M};
    MatchOneTimer match;
};

struct DiceState : chess_clock::State
{
    explicit DiceState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void start() override;
    void update() override;

    long dice[2] {};
};
