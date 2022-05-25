#include <AccelStepper.h>
#define HALFSTEPFEED 4


// Motor pin definitions for Stepper1
#define motorPin1 PB12 // IN1 on the ULN2003 driver 1
#define motorPin2 PB13 // IN2 on the ULN2003 driver 1
#define motorPin3 PB14 // IN3 on the ULN2003 driver 1
#define motorPin4 PB15 // IN4 on the ULN2003 driver 1

// Motor pin definitions for Stepper2
#define motorPin12 PA0 // IN1 on the ULN2003 driver 1
#define motorPin22 PA1 // IN2 on the ULN2003 driver 1
#define motorPin32 PA2 // IN3 on the ULN2003 driver 1
#define motorPin42 PA3 // IN4 on the ULN2003 driver 1

int newspeed =0;
int noOfSteps;
bool incoming = false;


// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEPFEED, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(HALFSTEPFEED, motorPin12, motorPin32, motorPin22, motorPin42);

void setup() {
  // Set the maximum speed in steps per second:
  stepper1.setMaxSpeed(1000);
  stepper1.setCurrentPosition(0);
  //stepper1.setAcceleration(80);
  stepper2.setMaxSpeed(1000);
  stepper2.setCurrentPosition(0);
  //stepper2.setAcceleration(80);
  Serial.begin(9600);
}
void loop() { 
  // Set the current position to 0:
  if (Serial.available()){
    newspeed = Serial.parseInt();
    noOfSteps = Serial.parseInt();
    incoming = true;
  }
//  if (incoming){
//    incoming=false;
//    Serial.print("New speed is ");
//    Serial.println(newspeed);
//    Serial.print("Num of Steps is ");
//    Serial.println(noOfSteps );
//  }
  if (incoming){
    Serial.print("Speed ");
    Serial.println(newspeed);
    Serial.print("Steps ");
    Serial.println(noOfSteps);
    stepper1.setCurrentPosition(0);
    stepper2.setCurrentPosition(0);
    stepper1.moveTo(noOfSteps);
    stepper2.moveTo(-1*noOfSteps);
    stepper1.setSpeed(newspeed);
    stepper2.setSpeed(-1*newspeed);
    incoming = false;
  }
  if(stepper1.currentPosition()!=noOfSteps){
    stepper1.setSpeed(newspeed);
    stepper1.runSpeed();
    stepper2.setSpeed(-1*newspeed);
    stepper2.runSpeed();    
  }
  
}
