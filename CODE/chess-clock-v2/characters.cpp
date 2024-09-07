#include "characters.hpp"

static const byte empty_rectangle[] {
    B00000,
    B11111,
    B10001,
    B10001,
    B10001,
    B10001,
    B11111,
    B00000
};

static const byte filled_rectangle[] {
    B00000,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B00000
};

static const byte left_pipe[] {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000
};

static const byte right_pipe[] {
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B00001
};

static const byte turn_indicator[] {
    B00000,
    B00000,
    B01110,
    B11111,
    B11111,
    B01110,
    B00000,
    B00000
};

static const byte start_flag[] {
    B10101,
    B01011,
    B10101,
    B01011,
    B00001,
    B00001,
    B00001,
    B00001
};

static const byte up_arrow[] {
    B00100,
    B01110,
    B11111,
    B00100,
    B00100,
    B00100,
    B00100,
    B00100
};

static const byte down_arrow[] {
    B00100,
    B00100,
    B00100,
    B00100,
    B00100,
    B11111,
    B01110,
    B00100
};

byte* CHARACTERS[Character_Count] {
    empty_rectangle,
    filled_rectangle,
    left_pipe,
    right_pipe,
    turn_indicator,
    start_flag,
    up_arrow,
    down_arrow
};
