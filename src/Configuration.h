
#define DEFAULT_SPEED 2000
#define DEFAULT_MAX_SPEED 5000
#define ACCELERATION 4000

//X AXIS MANAGEMENT
#define X_MAX 400 //in mm
#define X_MIN 0 //in mm
#define X_STEPS_PER_MM 400 //steps
#define X_DIR -1 //-1 = CW, 1 = CW

// Pins for X_AXIS the RAMPS board
#define X_STEP_PIN 54
#define X_DIR_PIN  55
#define X_ENABLE_PIN 38 // Active LOW

#define STEPPER_INVERTED false
#define ENCODER_STEPS_PER_NOTCH 40 
#define X_END_STOP_PIN 3
#define BTN_EN1 31          
#define BTN_EN2 33         
#define BTN_ENC 35         
#define POSITION_MENU_ITEM "Position: "
#define SPEED_MENU_ITEM "Speed: "
#define GO_TEXT "Start"
#define DISABLE_TEXT "Enable "
#define HOME_TEXT "Home"
#define RUNNING_TEXT "Running...."
#define SELECT_CHAR ">"
#define SPEED_STEPS 5
#define LCD_HEIGHT 4
#define LCD_WIDTH 20
#define ROWS 4
