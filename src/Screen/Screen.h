#include <Wire.h>
#include <LiquidCrystal.h>
#include <ClickEncoder.h>

#define BTN_EN1 31          // Encoder left direction, connected to Gadgets3D shield S_E1
#define BTN_EN2 33          // Encoder right direction, connected to Gadgets3D shield S_E2
#define BTN_ENC 35          // Encoder Click, connected to Gadgets3D shield S_EC
#define POSITION_MENU_ITEM "Position: "
#define SPEED_MENU_ITEM "Speed: "
#define GO_TEXT "Start"
#define ROWS 3


class Screen {
    private: 
    LiquidCrystal lcd = LiquidCrystal(16, 17, 23, 25, 27, 29);  
    void buildMenu();
    int columnForRow();
    void updateMenu();

    public:
    int speed;
    int position;

    Screen();
    void start();
    void clear();
    void setSpeed(int speed);
    void setPosition(int position);
    void write(const char* text);
    void update();
};