#pragma once

#include <Arduino.h>

enum Character
{
    CharacterEmptyRectangle,
    CharacterFilledRectangle,
    CharacterLeftPipe,
    CharacterRightPipe,
    CharacterTurnIndicator,
    CharacterStartFlag,
    CharacterUpArrow,
    CharacterDownArrow,

    Character_Count
};

extern byte* CHARACTERS[Character_Count];
