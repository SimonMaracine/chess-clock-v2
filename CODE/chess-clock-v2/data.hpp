#pragma once

struct Data {
    Menu menu {Menu::Modes};
    Mode mode {Mode::TwoClockUp};
    TimeMode time_mode {TimeMode::Minutes};
    unsigned long time_limit {THIRTY_MINUTES_D};  // Deciseconds
    size_t dice_count {1};
    bool show_deciseconds {false};
};
