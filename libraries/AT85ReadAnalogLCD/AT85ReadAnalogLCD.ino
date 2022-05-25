#include <Wire.h>                  // I2C Master lib for ATTinys which use USI - comment this out to use with standard arduinos
#include <LiquidCrystal_I2C.h>          // for LCD w/ GPIO MODIFIED for the ATtiny85

#define GPIO_ADDR     0x27
LiquidCrystal_I2C lcd(GPIO_ADDR, 16, 2); // set address & 16 chars / 2 lines
int aPin = A3;
int analogSig;
int newSpeed=0;

void setup() {                    
  lcd.init();                           // initialize the lcd
  lcd.backlight();                      // Print a message to the LCD.
  lcd.clear();
  lcd.home();
  lcd.print("Name: Dimitris");
  delay(100);
}

void loop(){
  analogSig=analogRead(aPin);
  lcd.setCursor(0,1);
  newSpeed=int(analogSig*0.98);
  lcd.print(newSpeed);
  lcd.print("   ");
  delay(500);
}
