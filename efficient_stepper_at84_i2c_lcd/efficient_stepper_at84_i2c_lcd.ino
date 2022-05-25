//WARNING, THIS CODE HAS NOT BEEN TESTED. JUST SEEING IF LIBRARIES ARE COMPATIBLE.
#include <AccelStepper.h>
#include <Wire.h>                  // I2C Master lib for ATTinys which use USI - comment this out to use with standard arduinos
#include <LiquidCrystal_I2C.h>          // for LCD w/ GPIO MODIFIED for the ATtiny85
#define STEPSIZE 4

#define GPIO_ADDR     0x27
LiquidCrystal_I2C lcd(GPIO_ADDR, 16, 2); // set address & 16 chars / 2 lines

// Motor pin definitions
#define motorPin1  0     // IN1 on the ULN2003 driver 1
#define motorPin2  1     // IN2 on the ULN2003 driver 1
#define motorPin3  2     // IN3 on the ULN2003 driver 1
#define motorPin4  3     // IN4 on the ULN2003 driver 1

#define motorPin12  5   // IN1 on the ULN2003 driver 2
#define motorPin22  6    // IN2 on the ULN2003 driver 2
#define motorPin32  7   // IN3 on the ULN2003 driver 2
#define motorPin42  8    // IN4 on the ULN2003 driver 2

int sensePin = A4;
int count=0;
int stepSpeed =100;
int sensorValue=0;
int newSpeed=stepSpeed;
int maxSpeed=1000;

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(STEPSIZE, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(STEPSIZE, motorPin12, motorPin32, motorPin22, motorPin42);

void setup() {
  //Serial.begin(9600);
  stepper1.setMaxSpeed(maxSpeed);
  stepper1.setAcceleration(100);
  stepper1.setSpeed(100);

  stepper2.setMaxSpeed(maxSpeed);
  stepper2.setAcceleration(100);
  stepper2.setSpeed(-100);

  lcd.init();                           // initialize the lcd
  lcd.backlight();                      // Print a message to the LCD.
  lcd.clear();
  lcd.home();
  lcd.print("Name: Dimitris");
  delay(100);

}//--(end setup )---

void loop() {
  count++;
  if (count==1000){
    sensorValue=analogRead(sensePin);
    newSpeed=int(sensorValue*0.977);    
    //Serial.println(newSpeed);
    count=0;
  }
  
  stepper1.setSpeed(newSpeed);
  stepper1.run();
  stepper2.setSpeed(-1*newSpeed);
  stepper2.run();
}
