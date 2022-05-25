/*MCP41010 Tutorial*/

#include <SPI.h>
const int CS = 10;
int PotWiperVoltage = A0;
int RawVoltage = 0;
int level =0;
float Voltage = 0;
 
void setup() {
  pinMode (CS, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  MCP41010Write(level);
}
 
void loop() {
  // Get level from read serial
  if (Serial.available()>0){
    level=Serial.readString().toInt();
  }
 
  MCP41010Write(level);
  delay(100);
  RawVoltage = analogRead(PotWiperVoltage);
  Voltage = (RawVoltage * 5.09)/ 1023.0;
  Serial.print("Level = " );
  Serial.print(level);
  Serial.print("\t Voltage = ");
  Serial.println(Voltage,3);
  delay(2000); // wait a couple seconds
}
void MCP41010Write(byte value)
{
  // Note that the integer vale passed to this subroutine
  // is cast to a byte
  
  digitalWrite(CS,LOW);
  SPI.transfer(B00010001); // This tells the chip to set the pot
  SPI.transfer(value); // This tells it the pot position
  digitalWrite(CS,HIGH);
}
