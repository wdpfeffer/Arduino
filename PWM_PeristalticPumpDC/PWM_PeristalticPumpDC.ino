/* Control Speed of a DC Motor from serial monitor
   More info: http://www.ardumotive.com/how-to-drive-a-dc-motor-with-transistor.html
   Dev: Vasilakis Michalis // Date: 13/7/2015 // www.ardumotive.com */

//Transistor 'Base' pin or input pin of motor driver ic to Arduino PWM Digital Pin 3
const int motorPin = 3;
const int speedPin = A0;

int Speed =0; //Variable to store Speed, by defaul 0 PWM
int oldSpeed =0;
int flag;

void setup()
{
  pinMode(motorPin, OUTPUT); //Set pin 3 as an OUTPUT
  Serial.begin(9600); //Init serial communication
    //Print a message:
}
void loop(){
  Speed = analogRead(speedPin)*255.0/1023.0;

  //Send PWM value with analogWrite to Arduino pin 3 and print a message to serial monitor
  if (Speed != oldSpeed){
    analogWrite(motorPin, Speed);
    //Print message only once
    Serial.print("Motor spinning with ");
    Serial.print(Speed);
    Serial.println(" PWM");
    oldSpeed=Speed;
  }
  delay(1000);
}
