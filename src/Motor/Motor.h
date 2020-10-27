#include <AccelStepper.h>
#include "Configuration.h"

class Motor {
    public:
    float speed;
    AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);

    Motor();
    void moveTo(int position, int speed);
    void move();
    void setSpeed(float speed);
    void setPosition(long position);
    void setup();
    void setSteppersEnabled(bool enabled);
    void toggleSteppers();
    void home();
    void run();
    void moveToPosition();
};