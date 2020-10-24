
#include "Screen.h"
#include "TimerOne.h"

const char* menu[ROWS] = { POSITION_MENU_ITEM, SPEED_MENU_ITEM, GO_TEXT };

ClickEncoder *encoder = new ClickEncoder(BTN_EN1, BTN_EN2, BTN_ENC);
int16_t lastRow, lastValue, value, row;
bool inRowMode = true;

void interrupt() {
    encoder->service();
}

Screen::Screen() {
    
}

void Screen::start() {
    lcd.begin(20, 4);
    lcd.cursor();
    lcd.noAutoscroll();
    lcd.noBlink();

    lcd.home();
    buildMenu();
    Timer1.initialize(1000);
    Timer1.attachInterrupt(interrupt); 
  
    lastValue = -1;
    lastRow = -1;
    this->speed = 100;
    this->position = 1000;
}

void Screen::buildMenu() {

    for (int i = 0; i < sizeof(menu) / sizeof(const char*); i++) {
        lcd.setCursor(0, i);
        const char* menuItem = menu[i];
        write(menuItem);
    }
}

void Screen::updateMenu() {
    lcd.setCursor(0, 0);
    write(POSITION_MENU_ITEM);

    lcd.setCursor(0, 1);
    write(SPEED_MENU_ITEM);

    lcd.setCursor(0, 2);
    write(GO_TEXT);
}

void Screen::write(const char* text) {
    lcd.print(text);
}

void Screen::clear() {
    lcd.clear();
}

void Screen::setPosition(int position) {
    this->position = position;
}

void Screen::setSpeed(int speed) {
    this->speed = speed;
}

int Screen::columnForRow() {
    if (sizeof(menu) / sizeof(const char*) > row) {
        const char* menuItem = menu[row];
        return strlen(menuItem);
    }
    return 0;
}

void Screen::update() {
    if (inRowMode) {
        row += encoder->getValue();
        row = max(min(ROWS - 1, row), 0);

        if (row != lastRow) {
            char str[8];
            itoa(row, str, 10);
            lastRow = row;
            lcd.setCursor(columnForRow() - 1, row);
        }

    } else {
        value += encoder->getValue();
        value = max(value, 0);

        if (value != lastValue) {
            char str[8];
            itoa(value, str, 10);
            lastValue = value;
            lcd.setCursor(columnForRow() - 1 , row);
            write(str);
        }
    }


    ClickEncoder::Button b = encoder->getButton();

    if (b != ClickEncoder::Open) {
        switch (b) {
        case ClickEncoder::Clicked:
            inRowMode = !inRowMode;
            if (inRowMode) {
                row = 0;
                lcd.noBlink();
            } else {
                lcd.blink();
            }
            break;
        }
    }    

}