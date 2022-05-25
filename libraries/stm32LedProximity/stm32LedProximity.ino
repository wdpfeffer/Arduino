
int readPin = PC14;
int ledPin = PC13;
byte rValue = 0;

void setup() {
    pinMode(readPin, INPUT);
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    rValue = digitalRead(readPin);
    if (rValue){
      Serial.println("Low");
      digitalWrite(ledPin,HIGH);
    }else{
      Serial.println("High");
      digitalWrite(ledPin,LOW
      );
    }
    
    delay(100);
}
