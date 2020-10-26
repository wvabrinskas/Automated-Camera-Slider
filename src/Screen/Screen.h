#include <Wire.h>
#include <LiquidCrystal.h>
#include <ClickEncoder.h>
#include <Motor/Motor.h>

class Screen {
    private: 
    LiquidCrystal lcd = LiquidCrystal(16, 17, 23, 25, 27, 29);  

    void buildMenu();
    int columnForRow();
    void updateCursor();
    void clearCursor();
    void updateSelectionForRow();
    void move();
    void home();
    void displayMessage(char* message);
    void clearMessage();
    void toggleSteppers(); 
    void setSteppersEnabled(bool enabled);
    
    public:
    float speed;
    int position;

    Screen();
    void start();
    void clear();
    void setSpeed(float speed);
    void setPosition(int position);
    void write(const char* text);
    void update();
};