#include "SoftwareSerial.h";

const int Rx=3;
const int Tx=2;
SoftwareSerial mySerial(Rx,Tx);
int count=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Rx, INPUT);
  pinMode(Tx, OUTPUT);
  mySerial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  mySerial.println(count);
  count++;
  delay(100);
  

}
