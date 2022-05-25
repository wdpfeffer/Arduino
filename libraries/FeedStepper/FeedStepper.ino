
#include <AccelStepper.h>
#define HALFSTEPFEED 4
#define HALFSTEPSTIR 4

// Motor pin definitions for FeedStepper
#define motorPin1 8 // IN1 on the ULN2003 driver 1
#define motorPin2 9 // IN2 on the ULN2003 driver 1
#define motorPin3 10 // IN3 on the ULN2003 driver 1
#define motorPin4 11 // IN4 on the ULN2003 driver 1

//Motor pin for StirStepper
#define motorPin1_2 4 // IN1 on the ULN2003 driver 1
#define motorPin2_2 5 // IN2 on the ULN2003 driver 1
#define motorPin3_2 6 // IN3 on the ULN2003 driver 1
#define motorPin4_2 7 // IN4 on the ULN2003 driver 1

int stirCount = 10;
int loopCount =0;
volatile boolean load = false;
const byte loadingPin =A0; //pin that show loading is occuring
const byte interruptPin = 2; //pin used with button to begin a load

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper feed(HALFSTEPFEED, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stir(HALFSTEPSTIR, motorPin1_2, motorPin2_2, motorPin3_2, motorPin4_2);

void setup() {
  Serial.begin(9600);
  // Set the maximum speed in steps per second:
  feed.setMaxSpeed(1000);
  stir.setMaxSpeed(1000);

  //setup pins;
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(loadingPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin),loader,LOW);
  
}
void loop() { 
  //load?
  if (load){
    loopCount=0;
    Serial.println("Loading");
    digitalWrite(loadingPin, HIGH);
    //run feed relatively quickly for 10000
    while (load){
      //run load conditions
      feed.setSpeed(400);
      feed.runSpeed();
    }
  }
  digitalWrite(loadingPin, LOW);
  // Set the feed current position to 0
  Serial.print("Loop Count ");
  Serial.println(loopCount);
  Serial.println("Backwards");
  feed.setCurrentPosition(0);
  // Run the motor backwared the motor reaches 400 steps:
  while(feed.currentPosition() != -400 && !load)
  {
    feed.setSpeed(-50);
    feed.runSpeed();
  }
  delay(100);
  
  // Reset the position to 0:
  Serial.println("forward");
  feed.setCurrentPosition(0);
  // Run the motor forwards until the motor reaches 2000 steps:
  while(feed.currentPosition() != 2000 && !load) 
  {
    feed.setSpeed(200);
    feed.runSpeed();
  }
  delay(100);

  
  //Stir the cell?
  if (loopCount == stirCount){
    //run the stirrer
    Serial.println("Stirring");
    stir.setCurrentPosition(0);
    while (stir.currentPosition() != 400){
      stir.setSpeed(200);
      stir.runSpeed();
    }
    delay(100);
    loopCount=0;
  }else{
    loopCount +=1;
  }
  
}

void loader(){
  if (load){
    load=false;
  }else{
    load=true;
  }
}
