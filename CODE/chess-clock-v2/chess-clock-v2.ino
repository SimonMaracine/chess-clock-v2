#include "context.hpp"
#include "definitions.hpp"
#include "states.hpp"
#include "characters.hpp"
#include "data.hpp"

static void setup_lcd(LiquidCrystal& lcd)
{
    lcd.begin(16, 2);
    lcd.createChar(CharacterEmptyRectangle, CHARACTERS[CharacterEmptyRectangle]);
    lcd.createChar(CharacterFilledRectangle, CHARACTERS[CharacterFilledRectangle]);
    lcd.createChar(CharacterLeftPipe, CHARACTERS[CharacterLeftPipe]);
    lcd.createChar(CharacterRightPipe, CHARACTERS[CharacterRightPipe]);
    lcd.createChar(CharacterTurnIndicator, CHARACTERS[CharacterTurnIndicator]);
    lcd.createChar(CharacterStartFlag, CHARACTERS[CharacterStartFlag]);
    lcd.createChar(CharacterUpArrow, CHARACTERS[CharacterUpArrow]);
    lcd.createChar(CharacterDownArrow, CHARACTERS[CharacterDownArrow]);
}

static chess_clock::Context ctx;
static Data data;

void setup()
{
    Serial.begin(9600);

    // Allocate all states
    StartupState startup {ctx};
    MenuState menu {ctx};
    ModesState modes {ctx};
    TimeState time {ctx};
    PreTimeState pre_time {ctx};
    DecisecondsState deciseconds {ctx};
    TwoClockUpState two_clock_up {ctx};
    TwoClockDownState two_clock_down {ctx};
    OneClockUpState one_clock_up {ctx};
    OneClockDownState one_clock_down {ctx};
    DiceState dice {ctx};

    ctx.add_state(startup);
    ctx.add_state(menu);
    ctx.add_state(modes);
    ctx.add_state(time);
    ctx.add_state(pre_time);
    ctx.add_state(deciseconds);
    ctx.add_state(two_clock_up);
    ctx.add_state(two_clock_down);
    ctx.add_state(one_clock_up);
    ctx.add_state(one_clock_down);
    ctx.add_state(dice);

    ctx.add_button(BUTTON_LEFT_PLAYER);
    ctx.add_button(BUTTON_RIGHT_PLAYER);
    ctx.add_button(BUTTON_START_STOP);
    ctx.add_button(BUTTON_SOFT_RESET);
    ctx.add_button(BUTTON_OK);

    ctx.initialize(startup, setup_lcd, &data);

    pinMode(BUZZER, OUTPUT);
    pinMode(LED_LEFT, OUTPUT);
    pinMode(LED_RIGHT, OUTPUT);
}

void loop()
{
    ctx.update();
}
