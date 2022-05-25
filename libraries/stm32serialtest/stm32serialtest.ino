const int intLED = PC13;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  pinMode(PC13, OUTPUT);

  

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello from 0");
  Serial.println("Hello from 1");
  Serial.println("Hello from 2");
  Serial.println("Hello from 3");
  digitalWrite(intLED, HIGH);
  delay(1000);
  digitalWrite(intLED, LOW);
  delay(1000);

}
