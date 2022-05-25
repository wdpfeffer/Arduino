/*Example sketch to control a stepper motor with A4988 stepper motor driver, AccelStepper library and Arduino: number of steps or revolutions. More info: https://www.makerguides.com */

// Include the AccelStepper library:
#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
byte dirPin = PB8;
byte stepPin = PB9;
byte motorInterfaceType = 1;
byte led = PC13;

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  // Set the maximum speed in steps per second:
  stepper.setMaxSpeed(100);
  pinMode(led,OUTPUT);
  
}

void loop() {
  // Set the current position to 0:
  stepper.setCurrentPosition(0);

  // Run the motor forward at 200 steps/second until the motor reaches 400 steps (2 revolutions):
  digitalWrite(led, LOW);
  while(stepper.currentPosition() != 400)
    {
    stepper.setSpeed(200);
    stepper.runSpeed();
    }
  
  delay(1000);
  
  // Reset the position to 0:
  stepper.setCurrentPosition(0);
  digitalWrite(led, HIGH);
  // Run the motor backwards at 600 steps/second until the motor reaches -200 steps (1 revolution):
  while(stepper.currentPosition() != -200)
    {
    stepper.setSpeed(-600);
    stepper.runSpeed();
    }
  
  delay(1000);

  // Reset the position to 0:
  stepper.setCurrentPosition(0);
  
  // Run the motor forward at 400 steps/second until the motor reaches 600 steps (3 revolutions):
  while(stepper.currentPosition() != 600)
    {
    stepper.setSpeed(400);
    stepper.runSpeed();
    }
  
  delay(3000);
}
