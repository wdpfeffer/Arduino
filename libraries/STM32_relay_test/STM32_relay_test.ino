byte Relay1 = PB6;
byte Relay2 = PB5;
byte led = PC13; 
int oldMillis;
bool relayOn = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(led,OUTPUT);
  oldMillis = millis();
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis()-oldMillis > 2000){
    relayOn=!relayOn;
    oldMillis=millis();
  }

  if (relayOn){
    digitalWrite(Relay1, HIGH);
      digitalWrite(Relay2, LOW);
    digitalWrite(led, LOW);
    Serial.println("Relay1 ON");
  }else{
    digitalWrite(Relay1, LOW);
    digitalWrite(Relay2, HIGH);
    digitalWrite(led, HIGH); 
  }

}
