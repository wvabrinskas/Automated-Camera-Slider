
#include "Screen.h"
#include "TimerOne.h"

const char* menu[ROWS] = { SPEED_MENU_ITEM, GO_TEXT };

ClickEncoder *encoder = new ClickEncoder(BTN_EN1, BTN_EN2, BTN_ENC);

int16_t lastRow, lastValue, value, row = 0;
int16_t lastPosition, lastSpeed;
bool moving = false;

bool inRowMode = true;

void interrupt() {
    encoder->service();
}
Screen::Screen() {
    
}

void Screen::start() {
    this->speed = DEFAULT_SPEED;

    lcd.begin(20, 4);
    lcd.noCursor();
    lcd.noAutoscroll();
    lcd.noBlink();

    lcd.home();
    buildMenu();
    Timer1.initialize(1000);
    Timer1.attachInterrupt(interrupt); 
  
    lastValue = -1;
    lastRow = -1;

    encoder->setAccelerationEnabled(true);   
    pinMode(X_END_STOP_PIN, INPUT_PULLUP);

}

void Screen::buildMenu() {
    int selCharLen = strlen(SELECT_CHAR);

    for (int i = 0; i < sizeof(menu) / sizeof(const char*); i++) {
        lcd.setCursor(selCharLen, i);
        const char* menuItem = menu[i];
        write(menuItem);
    }

    //set default value for Speed. 
    //not a great way to do this for works for now
    char str[8];
    itoa(this->speed, str, 10);
    lcd.setCursor(columnForRow(), row);
    write(str);

    updateCursor();
}

void Screen::clearCursor() {
    lcd.setCursor(0, lastRow);
    lcd.write(" ");
}

void Screen::updateCursor() {
    lcd.setCursor(0,row);
    lcd.write(SELECT_CHAR);
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

void Screen::setSpeed(float speed) {
    this->speed = speed;
}

void Screen::updateSelectionForRow() {
    int16_t newValue = encoder->getValue();

    if (row == 0) {  
        this->speed += newValue;
        this->speed = max(this->speed, 0);

        if (this->speed != lastSpeed) {
            
            lcd.setCursor(columnForRow(), row);
            lastSpeed = this->speed;

            char str[8];
            itoa(speed, str, 10);
            strcat(str, " ");
            write(str);
        }
    }
}


int Screen::columnForRow() {
    if (sizeof(menu) / sizeof(const char*) > row) {
        const char* menuItem = menu[row];
        return strlen(menuItem);
    }
    return 0;
}

void Screen::move() {
    int endStop = digitalRead(X_END_STOP_PIN);

    if (this->speed > 0 && moving && endStop == HIGH) {
        motor.setSpeed(this->speed);
        motor.move();
        lcd.setCursor(0, 3);
        write("Running...");
        lcd.setCursor(1, 1);
        write("Stop  ");
    } else {
        moving = false;
        lcd.setCursor(0, 3);
        write("          ");
        lcd.setCursor(1, 1);
        write("Start");
    }
}

void Screen::update() {
    if (inRowMode) {
        clearCursor();
        row += encoder->getValue();
        row = max(min(ROWS - 1, row), 0);

        if (row != lastRow) {
            lastRow = row;
            lcd.setCursor(columnForRow() - 1, row);
        }
        updateCursor();
    } else {
        updateSelectionForRow();
    }

    ClickEncoder::Button b = encoder->getButton();

    if (b != ClickEncoder::Open) {
        switch (b) {
        case ClickEncoder::Clicked:
            if (row == 1) {
                moving = !moving;
            } else {
                inRowMode = !inRowMode;
            }
            break;
        }
    }    

    move();
}