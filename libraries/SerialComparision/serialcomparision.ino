/*
  Serial Event example

 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and
 clears it.

 A good test for this is to try it with a GPS receiver
 that sends out NMEA 0183 sentences.

 Created 9 May 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialEvent

 */
int inbyte=0;
unsigned long inputNum=0;        // a string to hold incoming data
boolean entryComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
}

void loop() {
  // print the string when a newline arrives:
  if (entryComplete) {
    //for debugging purposes, print output.
    //Serial.println(inputNum);
    switch (inputNum) {
        case 500:
          // send reader details
          Serial.println("Reader detials");
          break;
        case 510:
          // send header, comma delimited
          Serial.println("Header information");
          break;
        case 520:
          // send probe numbers, comma delimited
          Serial.println("probe numbers");
          break;
        case 530:
          // send time and date
          Serial.println("time and date");
          break;
        case 540:
          // send temperatures
          Serial. println("temperatures");
          break;
    }
    
    // clear the string:
    inputNum = 0;
    entryComplete = false;
  }
  delay(10);
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  //inputNum=0;
  while (Serial.available()) {
    // get the new byte:
    inbyte = Serial.read();
    //Serial.println(inbyte);
    //inputNum=inputNum*10+inbyte-'0';
    //Serial.print(inbyte);
    // add it to the inputString:
     if (inbyte != 10 && inbyte!=13){
       inputNum=inputNum*10+inbyte-48;
       //Serial.print("added");
     }
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
     if (inbyte == 10 || inbyte==13) {
       entryComplete = true;
       //Serial.print("done");
     }
    //inbyte=0;
  }
  inbyte=0;
}
