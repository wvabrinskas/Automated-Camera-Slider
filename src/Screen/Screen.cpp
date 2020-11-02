
#include "Screen.h"
#include "TimerOne.h"
#include "Configuration.h"
#include "Scheduler.h"
#include <EEPROM.h>

const char* menu[ROWS] = { SPEED_MENU_ITEM, GO_TEXT, HOME_TEXT,  DISABLE_TEXT };
ClickEncoder *encoder = new ClickEncoder(BTN_EN1, BTN_EN2, BTN_ENC, ENCODER_STEPS_PER_NOTCH);
Motor motor = Motor();

int16_t lastRow, lastValue, value, row = 0;
int16_t lastPosition, lastSpeed;
long homePosition = 0;

bool moving = false;
bool inRowMode = true;
int addr = 0;
long lastKnownPosition = X_MIN;


void homeMotor() {
    int endStop = digitalRead(X_END_STOP_PIN);
    while (endStop == HIGH) {
        motor.stepper.setSpeed(HOMING_SPEED);
        endStop = digitalRead(X_END_STOP_PIN);
        motor.stepper.run();
    }
    homePosition = motor.stepper.currentPosition();
}

void run() {
    //safety home first
    homeMotor();
    delay(500);

    float pos = (((float)X_MAX * (float)X_STEPS_PER_MM) * X_DIR) + homePosition;

    motor.setPosition(pos);
    Serial.println(pos);

    while (motor.stepper.distanceToGo() != 0 && moving) {
        motor.stepper.setSpeed(motor.speed);
        motor.moveToPosition();
    }
    moving = false;
}

void interrupt() {
    encoder->service();
}

Screen::Screen() {
    
}

void Screen::start() {
    motor.setup();

    //setup default speeds;
    this->speed = DEFAULT_SPEED;
    motor.speed = this->speed;

    lcd.begin(LCD_WIDTH, LCD_HEIGHT);
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

    lastKnownPosition = EEPROM.read(0);
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
        this->speed =  min(max(this->speed, DEFAULT_MIN_SPEED), DEFAULT_MAX_SPEED);

        if (this->speed != lastSpeed) {
            
            lcd.setCursor(columnForRow(), row);
            lastSpeed = this->speed;
            motor.speed = this->speed;

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

void Screen::displayMessage(char* message) {
    lcd.setCursor(0, 3);
    write(message);
}

void Screen::clearMessage() {
    lcd.setCursor(0, 3);
    write("                    ");
}

void Screen::updateMovingStatus() {
    if (this->speed > 0 && moving) {
        lcd.setCursor(1, 1);
        write("Stop  ");
    } else {
        moving = false;
        lcd.setCursor(1, 1);
        write("Start");
    }
}

void Screen::setSteppersEnabled(bool enabled) {
    int stepperEnabled = digitalRead(X_ENABLE_PIN);
    if (enabled) {
        lcd.setCursor(1, 3);
        write("Disable");
        motor.setSteppersEnabled(true);
    } else {
        lcd.setCursor(1, 3);
        write("Enable ");
        motor.setSteppersEnabled(false);
    }
}

void Screen::toggleSteppers() {
    int stepperEnabled = digitalRead(X_ENABLE_PIN);
    setSteppersEnabled(stepperEnabled == HIGH);
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
        //START
        if (row == 1) {
            moving = !moving;
            if (moving) {
                setSteppersEnabled(true);
            }
            updateMovingStatus();
            run();
        //HOME
        } else if (row == 2) {
            if (!moving) {
                setSteppersEnabled(true);
                homeMotor();
            }
        //ENABLE / DISABLE STEPPERS
        } else if (row == 3) {
            if (!moving) {
                toggleSteppers();
            }
        //CHANGE SPEED
        } else {
            inRowMode = !inRowMode;
        }
        break;
        }
    }    
    updateMovingStatus();

    EEPROM.write(addr, motor.stepper.currentPosition());
}