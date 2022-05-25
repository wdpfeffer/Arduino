/*
  */

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
float avg = 0;
int count = 1;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  avg += voltage;
  if (count == 100){
    avg = avg /100;
    float temp = avg*avg*(-18.7206) + avg*57.346 + 58.446;
    Serial.println(temp);
    count = 1;
    avg = 0;  
  }
  count += 1;
  delay(1);
}
