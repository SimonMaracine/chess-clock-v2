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

static chess_clock::Context g_ctx;
static Data g_data;

void setup()
{
    Serial.begin(9600);

    // Allocate all states
    StartupState startup {g_ctx};
    MenuState menu {g_ctx};
    ModesState modes {g_ctx};
    TimeState time {g_ctx};
    PreTimeState pre_time {g_ctx};
    DecisecondsState deciseconds {g_ctx};
    TwoClockUpState two_clock_up {g_ctx};
    TwoClockDownState two_clock_down {g_ctx};
    OneClockUpState one_clock_up {g_ctx};  // FIXME progress bar not working
    OneClockDownState one_clock_down {g_ctx};
    DiceState dice {g_ctx};

    g_ctx.add_state(startup);
    g_ctx.add_state(menu);
    g_ctx.add_state(modes);
    g_ctx.add_state(time);
    g_ctx.add_state(pre_time);
    g_ctx.add_state(deciseconds);
    g_ctx.add_state(two_clock_up);
    g_ctx.add_state(two_clock_down);
    g_ctx.add_state(one_clock_up);
    g_ctx.add_state(one_clock_down);
    g_ctx.add_state(dice);

    g_ctx.add_button(BUTTON_LEFT_PLAYER);
    g_ctx.add_button(BUTTON_RIGHT_PLAYER);
    g_ctx.add_button(BUTTON_START_STOP);
    g_ctx.add_button(BUTTON_SOFT_RESET);
    g_ctx.add_button(BUTTON_OK);

    g_ctx.initialize(startup, setup_lcd, &g_data);

    pinMode(BUZZER, OUTPUT);
    pinMode(LED_LEFT, OUTPUT);
    pinMode(LED_RIGHT, OUTPUT);
}

void loop()
{
    g_ctx.update();
}
