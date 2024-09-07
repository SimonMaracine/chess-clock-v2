#pragma once

#include <Arduino.h>

enum Characters
{
    EmptyRectangle,
    FilledRectangle,
    LeftPipe,
    RightPipe,
    TurnIndicator,
    StartFlag,
    UpArrow,
    DownArrow,

    CharacterCount
};

extern byte* CHARACTERS[CharacterCount];
