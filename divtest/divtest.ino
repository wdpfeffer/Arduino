void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0;i<2000;i++){
    Serial.println(1.0/(i+1));
    delay(100);
  }

}
