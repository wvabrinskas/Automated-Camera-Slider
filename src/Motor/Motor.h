#include <AccelStepper.h>
#include "Configuration.h"

class Motor {
    private: 
    AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
    
    public:
    float speed;
    bool moving;

    Motor();
    void moveTo(int position, int speed);
    void move();
    void setSpeed(float speed);
    void setPosition(float position);
    void setup();
    void setSteppersEnabled(bool enabled);
    void toggleSteppers();
    void home();
    void run();
    void moveToPosition();
};