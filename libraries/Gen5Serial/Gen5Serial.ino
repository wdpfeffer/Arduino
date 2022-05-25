/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,2); // RX, TX
int DTS = 7;
String message = "";

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  pinMode(DTS, OUTPUT);
  digitalWrite(DTS, HIGH);
  delay(100);
}

void loop() { // run over and over
  //Set pin high
  digitalWrite(DTS, HIGH);
  
  if (mySerial.available()) {
    message = "";
    while (mySerial.available()){
      char t=mySerial.read();
      message +=t;
      delay(10);
    }
    message +="\n";
    delay(10);
    Serial.print(message);
    //Serial.write('\n');
  }
  //delay(200);
  
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
  //delay(200);
}
