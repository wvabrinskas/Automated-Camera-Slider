#include <AccelStepper.h>

#define DEFAULT_SPEED 1000
#define DEFAULT_MAX_SPEED 2000

// Pins for X_AXIS the RAMPS board
#define  X_STEP_PIN 54
#define  X_DIR_PIN  55
#define  X_ENABLE_PIN 38 // Active LOW

class Motor {
    private: 
    AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);

    public:
    Motor();
    void moveTo(int position, int speed);
    void move();
};