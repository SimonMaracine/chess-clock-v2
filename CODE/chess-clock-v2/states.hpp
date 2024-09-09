#pragma once

#include "state.hpp"
#include "context.hpp"
#include "other.hpp"
#include "definitions.hpp"
#include "timer.hpp"

struct Match
{
    unsigned long time_left {0};  // Deciseconds
    unsigned long time_right {0};

    Player player {Player::Right};

    bool paused {true};
    bool ended {false};
    bool end_flag {false};  // One time flag
};

struct MatchOneTimer
{
    unsigned long time {0};  // Deciseconds

    bool paused {true};
    bool ended {false};
    bool end_flag {false};  // One time flag
};

struct StartupState : chess_clock::State
{
    explicit StartupState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void start() override;
    void stop() override;
    void update() override;

    chess_clock::Timer<ONE_SECOND_M> timer;
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

    chess_clock::Timer<ONE_DECISECOND_M> timer;
    chess_clock::Timer<TWO_DECISECONDS_M> end_timer;
    Match match;
};

struct TwoClockDownState : chess_clock::State
{
    explicit TwoClockDownState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void start() override;
    void stop() override;
    void update() override;

    chess_clock::Timer<ONE_DECISECOND_M> timer;
    chess_clock::Timer<TWO_DECISECONDS_M> end_timer;
    Match match;
};

struct OneClockUpState : chess_clock::State
{
    explicit OneClockUpState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void start() override;
    void stop() override;
    void update() override;

    chess_clock::Timer<ONE_DECISECOND_M> timer;
    chess_clock::Timer<TWO_DECISECONDS_M> end_timer;
    MatchOneTimer match;
};

struct OneClockDownState : chess_clock::State
{
    explicit OneClockDownState(chess_clock::Context& ctx)
        : chess_clock::State(ctx) {}

    void start() override;
    void stop() override;
    void update() override;

    chess_clock::Timer<ONE_DECISECOND_M> timer;
    chess_clock::Timer<TWO_DECISECONDS_M> end_timer;
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
