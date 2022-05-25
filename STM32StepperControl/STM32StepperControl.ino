/*Example sketch to control a stepper motor with A4988 stepper motor driver, AccelStepper library and Arduino: continuous rotation. More info: https://www.makerguides.com */

// Include the AccelStepper library:
#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin PB10
#define stepPin PB11
#define motorInterfaceType 1
const int aPin = PA0;
int maxA = 4096;
int readA = 0;
int stepperSpeed = 0;
int maxDelay = 60000;
int runDelay = 0;

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  // Set the maximum speed in steps per second:
  stepper.setMaxSpeed(1000);
  stepperSpeed=-400 ;

  pinMode(PC13, OUTPUT);

}

void loop() {
  
  digitalWrite(PC13, HIGH);
  stepper.enableOutputs();
  //Read the analog voltage
  readA = analogRead(aPin);
  runDelay=maxDelay*readA/maxA;
  //Run stepper forward 1000 steps
  stepper.setCurrentPosition(0);
  while (stepper.currentPosition()!= -50){
    // Set the speed in steps per second:
    stepper.setSpeed(stepperSpeed);
    // Step the motor with a constant speed as set by setSpeed():
    stepper.runSpeed();
  }
  //Run stepper backwards for 200 steps
  stepper.setCurrentPosition(0);
  while (stepper.currentPosition()!= 10){
    stepper.setSpeed(stepperSpeed*-1);
    stepper.runSpeed();
  }
  stepper.disableOutputs();
  digitalWrite(PC13, LOW);
  delay(100);
  delay(runDelay);
}
