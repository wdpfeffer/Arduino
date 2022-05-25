#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#define GPIO_ADDR     0x27
LiquidCrystal_I2C lcd(GPIO_ADDR, 16, 2); // set address & 16 chars / 2 lines

//define analog pin
int G1 = A0;

//define softserial
const int Rx=3;
const int Tx=2;
SoftwareSerial mySerial(Rx,Tx);

//define A/D values
float maxValue = 1023.0;
float volts;
float pressure;
float pValue = 0.0;
float avgpValue;
int n=1000; //value to average number by

//static char spressure[4];
//static char svolts[5];

void setup() {
  //setup serial
  pinMode(Rx, INPUT);
  pinMode(Tx, OUTPUT);
  mySerial.begin(9600);

  
  //setup lcd
  lcd.init();                           // initialize the lcd
  lcd.backlight();                      // Print a message to the LCD.
  lcd.clear();
  lcd.home();
  lcd.print("WMS Press Gauge");
  delay(500);
   
}
void loop() {

  //average the data
  for (int i=0;i<n;i++){
    pValue += analogRead(G1);
    delay(10);
  }
  avgpValue=pValue/n;

  //convert to volts
  volts = avgpValue/maxValue;

  //convert to pressure
  pressure = GetPressure(volts);

   //display on lcd
  lcd.clear();
  lcd.home();
  lcd.print("P = ");
  lcd.print(pressure);
  lcd.print(" psi");
  lcd.setCursor(0,1);
  lcd.print("v = ");
  lcd.print(volts);
  lcd.print(" volts");

  //output to serial
  mySerial.print("Pressure = ");
  mySerial.print(pressure);
  mySerial.print(" volts = ");
  mySerial.println(volts,3);

  //reset read value
  pValue=0;
}

float GetPressure(float v){
  float p = 101.5*pow(v,2)-62.59*v + 9.377;
  if (p < 0.0){
    p=0;
  }
  return p;
}
