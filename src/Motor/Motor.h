#include <AccelStepper.h>
#include "Configuration.h"

class Motor {
    private: 
    AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
    
    public:
    Motor();
    void moveTo(int position, int speed);
    void move();
    void setSpeed(float speed);
    void setup();
    void setSteppersEnabled(bool enabled);
    void toggleSteppers();
};