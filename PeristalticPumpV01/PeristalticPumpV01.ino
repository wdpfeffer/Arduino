//*Example sketch to control a stepper motor with A4988 stepper motor driver, AccelStepper library and Arduino: continuous rotation. More info: https://www.makerguides.com */

// Include the AccelStepper library:
#include <AccelStepper.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#include <LiquidCrystal_I2C.h>


// Define LCD
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 20 chars and 4 line display

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 6
#define stepPin 7
#define motorInterfaceType 1

//Define Encoder
#define ENCODER_PIN_BUTTON 4
#define ENCODER_PIN_A 3
#define ENCODER_PIN_B 2
ClickEncoder *encoder;
int16_t last, value, rCount, iSpeed;
boolean vRun, rSpeed;

void timerIsr() {
  encoder->service();
}

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
// Set the maximum speed in steps per second:
  Serial.begin(9600);
  
  encoder = new ClickEncoder(ENCODER_PIN_B, ENCODER_PIN_A, ENCODER_PIN_BUTTON); //(Encoder A, Encoder B, PushButton)

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 
  last = -1;
  
  stepper.setMaxSpeed(8000);
  //stepper.setAcceleration(5000);
  vRun = false;
  rSpeed =false;

  //init LCD
  lcd.init();
  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.home();
  lcd.print("PPump Init");
  delay(1000);
  lcd.clear();
  lcd.home();
}

void loop() {

  if (!vRun){
    value += 10*encoder->getValue();
  }
    
  if (value != last && !vRun) {
    
    // Set the speed in steps per second:
    Serial.print("Encoder Value: ");
    Serial.println(value);
    last = value;
    lcd.setCursor(0, 0);
    lcd.print("Speed           ");
    lcd.setCursor(7, 0);
    lcd.print(value);
    lcd.setCursor(0,1);
    lcd.print("Stopped");
  }

  if (vRun){
      stepper.runSpeed();
  }
  
  
  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    Serial.print("Button: ");
    #define VERBOSECASE(label) case label: Serial.println(#label); break;
    switch (b) {
      VERBOSECASE(ClickEncoder::Pressed);
      VERBOSECASE(ClickEncoder::Held)
      VERBOSECASE(ClickEncoder::Released)
      //VERBOSECASE(ClickEncoder::Clicked)
      case ClickEncoder::Clicked:
          Serial.println("Clicked");
          if (vRun){
              vRun = false;
              lcd.setCursor(0,1);
              lcd.print("Stopped");
          }else{
              stepper.setSpeed(value);
              vRun = true;
              lcd.setCursor(0,1);
              lcd.print("Running");
              rSpeed = false;
          }
          break;
       case
          ClickEncoder::DoubleClicked:
          value = 0;
          last = 0;
          vRun = false;
          lcd.setCursor(7, 0);
          lcd.print("0     ");
          lcd.setCursor(0, 1);
          lcd.print("Reset");
          Serial.println("ClickEncoder::DoubleClicked");
          encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
          Serial.print("  Acceleration is ");
          Serial.println((encoder->getAccelerationEnabled()) ? "enabled" : "disabled");
        break;
    }
  }
  //delay(100);    
}
