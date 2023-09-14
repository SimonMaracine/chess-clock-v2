#pragma once

#include <Arduino.h>

enum CharactersList
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
