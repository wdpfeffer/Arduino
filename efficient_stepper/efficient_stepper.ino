#include <AccelStepper.h>
#define HALFSTEPFEED 4


// Motor pin definitions for FeedStepper
#define motorPin1 PB12 // IN1 on the ULN2003 driver 1
#define motorPin2 PB13 // IN2 on the ULN2003 driver 1
#define motorPin3 PB14 // IN3 on the ULN2003 driver 1
#define motorPin4 PB15 // IN4 on the ULN2003 driver 1

int newspeed;
int noOfSteps;
bool incoming = false;


// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper feed(HALFSTEPFEED, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  // Set the maximum speed in steps per second:
  feed.setMaxSpeed(1000);
  Serial.begin(9600)
}
void loop() { 
  // Set the current position to 0:
  if (Serial.available()){
    newspeed = Serial.parseInt();
    noOfSteps = Serial.parseInt();
    incoming = true;
  }
  if (incoming){
    Serial.print("Speed ");
    Serial.println(newspeed);
    Serial.print("Steps ");
    Serial.println(noOfSteps);
  }
  
  /*feed.setSpeed(500);
  feed.runSpeed();
  */
}
