/*Example sketch to control a stepper motor with A4988 stepper motor driver, AccelStepper library and Arduino: acceleration and deceleration. More info: https://www.makerguides.com */

// Include the AccelStepper library:
#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin PB6
#define stepPin PB7
#define motorInterfaceType 1

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
// Set the maximum speed and acceleration:
stepper.setMaxSpeed(50);
stepper.setAcceleration(30);
}

void loop() {
// Set the target position:
stepper.moveTo(3000);
// Run to target position with set speed and acceleration/deceleration:
stepper.runToPosition();

delay(1000);

// Move back to zero:
stepper.moveTo(-2000);
stepper.runToPosition();

delay(1000);
}
