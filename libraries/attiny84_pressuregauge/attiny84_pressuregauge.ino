#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define GPIO_ADDR     0x27
LiquidCrystal_I2C lcd(GPIO_ADDR, 16, 2); // set address & 16 chars / 2 lines

//define analog pin
int pPin = A0;

//define A/D values
float maxValue = 1023.0;
float volts;
int pValue = 0;

static char svolts[5];




void setup() {
  //setup serial
  // Serial.begin(9600);
  //delay(200);
  //Serial.println(F("Use commands \"CAL,4\", \"CAL,7\", and \"CAL,10\" to calibrate \nthe circuit to those respective values"));
  
  //setup lcd
  lcd.init();                           // initialize the lcd
  lcd.backlight();                      // Print a message to the LCD.
  lcd.clear();
  lcd.home();
  lcd.print("WMT Pressure");
  delay(500);
   
}

void loop() {
  pValue = analogRead(pPin);
  volts = pValue/maxValue;
  dtostrf(volts,5,3,svolts);
  lcd.setCursor(0,1);
  lcd.print(svolts);
  delay(200); 
  
}
