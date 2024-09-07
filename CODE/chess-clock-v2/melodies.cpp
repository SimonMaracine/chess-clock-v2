#include "melodies.hpp"

const Melody<4> END_MELODY {
    Note(1000, 100, 50),
    Note(800, 100, 50),
    Note(600, 100, 50),
    Note(200, 400, 1)
};

const Melody<4> START_MELODY {
    Note(200, 100, 50),
    Note(600, 100, 50),
    Note(800, 100, 50),
    Note(1000, 150, 1)
};

const Melody<1> DICE_NOTE1 {
    Note(300, 25, 1)
};

const Melody<1> DICE_NOTE2 {
    Note(100, 25, 1)
};

const Melody<1> START_BEEP {
    Note(300, 150, 1)
};

const Melody<1> GENTLE_RESET_BEEP {
    Note(600, 150, 1)
};
