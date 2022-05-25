
// this constant won't change:
const byte  sensorPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

byte sensorState = 0;
bool startTest = true;
bool endTest = false;
unsigned long startTime;
unsigned long endTime;
unsigned long currentTime;
int minuteCount = 0;

void setup() {
  // initialize the button pin as a input:
  pinMode(sensorPin, INPUT_PULLUP);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  //is test starting?
  if (startTest){
    //read in the starting time
    startTime = millis();
    startTest=false;
    Serial.println("Starting Test");
  }
  
  // read the pushbutton input pin:
  sensorState = digitalRead(sensorPin);
  if (sensorState == 0){
    //not enough weight so keep counting
    currentTime = millis()-startTime;
    if (currentTime/1000.0 > 60){
      digitalWrite(ledPin, HIGH);
      //increment minuteCount and reset startTime
      minuteCount +=1;
      startTime=millis();
      Serial.print("Elapsed Time = ");
      Serial.print(minuteCount);
      Serial.println(" min");
      digitalWrite(ledPin, LOW);
    }
  }else{
    //weight pan moved -- end of test!
    if (!endTest){
      Serial.print("Test Ended after ");
      Serial.print(minuteCount);
      Serial.println(" min");
      endTest = true;
    }
  }
}
