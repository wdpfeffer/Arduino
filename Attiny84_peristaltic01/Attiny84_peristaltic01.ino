#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <PinChangeInterrupt.h>
#define encoder0PinA 7
#define encoder0PinB 8
#define encoder0Btn 5
int encoder0Pos = 0;
int valRotary=0;
int lastValRotary=0;
const byte interruptPinRot = 7;
const byte interruptPinBtn = 5;
int maxCount = 20000;
int minCount = 250;
bool forward = true;



// Define LCD
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 20 chars and 4 line display

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 9
#define stepPin 10
//#define motorInterfaceType 1
#define stepsPerRevolution 200
int mysteps;


// Create a new instance of the AccelStepper class:
//AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

bool run =false;
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 100;    // the debounce time; increase if the output flickers


void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  //setup encoder
  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
  pinMode(encoder0Btn, INPUT_PULLUP);
  attachPCINT(digitalPinToPCINT(interruptPinRot), doEncoder, CHANGE);
  attachPCINT(digitalPinToPCINT(interruptPinBtn), doButton, CHANGE);

  //stepper.setMaxSpeed(30000);

   //init LCD
  lcd.init();
  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.home();
  lcd.setCursor(0,0);
  lcd.print("Speed");
  lcd.setCursor(7,0);
  lcd.print(valRotary);
  delay(500);
}

void loop() {
  lastValRotary = getSpeed(valRotary);
  int aRot= abs(valRotary);
  if (aRot < 25){mysteps=50;};
  if (aRot > 25 && aRot < 50){mysteps=100;};
  if (aRot > 50 && aRot < 75){mysteps=150;};
  if (aRot > 75){mysteps = 200;}
  
  for (int i=0; i < mysteps; i++){
    // Set the spinning direction clockwise:
    if(run){
      if(forward){
        digitalWrite(dirPin, HIGH);        
      }
      else{
        digitalWrite(dirPin, LOW);        
      }
      // Spin the stepper motor revolutions fast:
      // These four lines result in 1 step:
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(lastValRotary);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(lastValRotary);
    }  
    else{
      //lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Speed");
      lcd.setCursor(7,0);
      lcd.print(valRotary);
      lcd.print("  ");
      lcd.setCursor(0,1);
      lcd.print("Stop");
      delay(500);
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Speed");
  lcd.setCursor(7,0);
  lcd.print(valRotary);
  lcd.print("  ");
  lcd.setCursor(0,1);
}
void doEncoder(void)
{
  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
    encoder0Pos++;
    if (encoder0Pos >250){
      encoder0Pos = 250;
    }
  }
  else{
    encoder0Pos--;
    if (encoder0Pos < -250){
      encoder0Pos = -250;
    }
  }
  valRotary = int(encoder0Pos/2.5);
}
void doButton(void){
  int btn = digitalRead(encoder0Btn);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (btn != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if(run){
      run = false;
      lcd.setCursor(0,1);
      lcd.print("Stop");
    }
    else{
      run = true;
      lcd.setCursor(0,1);
      lcd.print("Run ");
    }
  }
  delay(500);
}
int getSpeed(int r){
  if (r<0){
    r=abs(r);
    forward=false;
  }
  else{
    forward=true;
  }
  int ir = 100-r;
  int rs = ir*100+100;
  if (rs>5000) rs=5000;
  return rs; 
}
