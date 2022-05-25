/* Control Speed of a DC Motor from serial monitor
   More info: http://www.ardumotive.com/how-to-drive-a-dc-motor-with-transistor.html
   Dev: Vasilakis Michalis // Date: 13/7/2015 // www.ardumotive.com */

//Transistor 'Base' pin or input pin of motor driver ic to Arduino PWM Digital Pin 3
const int motorPin = 1;
const int graphPin = 0;
const int downButton = 3;
const int upButton = 4;

//Button states
int upButtonState = HIGH;   //current up button reading
int downButtonState = HIGH; //current down button reading

unsigned long lastDBTup = 0;
unsigned long lastDBTdown = 0;
unsigned long dbDelay = 50;

bool upPushed = false;
bool downPushed = false;


int Speed =0; //Variable to store Speed, by defaul 0 PWM
int barLevel = 0;

void setup()
{
  pinMode(motorPin, OUTPUT); //Set pin 1 as an OUTPUT
  pinMode(graphPin, OUTPUT); //Set pin2 to OUTPUT for graph LED
  pinMode(upButton, INPUT_PULLUP); //Button to incease Speed
  pinMode(downButton, INPUT_PULLUP); //Button to decrease Speed
 
  
}

void loop()
{ 
  
  // get button states
  int upRead = digitalRead(upButton);
  int downRead = digitalRead(downButton);

  //debounce the buttons
  if (upRead != upButtonState){
    //reset Debounce timer
    lastDBTup = millis();
  }
  if (downRead != downButtonState){
    //reset Debounce timer
    lastDBTdown = millis();
  }

  // was button pushed?
  if ((millis() - lastDBTup) > dbDelay){
    // its a real pushed
    upPushed = true;
  }

  if ((millis() - lastDBTdown)> dbDelay){
    // real pushed
    downPushed = true;
  }
  //Valid range is from TBD

  if (upPushed || downPushed){
    // change the motor Speed
    if (upPushed && ((Speed-10) < 250)){
      Speed+=10;
      upPushed = false;
    }
    if (downPushed && ((Speed+10)>0)){
      Speed-=10;
      downPushed = false;
    };
    barLevel = int(Speed/255.0*180.0);

  }
  //Set the speed and bar graph
  if (Speed>=0 && Speed<=255){
    //Send PWM value with analogWrite to Arduino pin 3 and print a message to serial monitor
    analogWrite(motorPin, Speed);
  }
  analogWrite(graphPin, barLevel);
  
  upButtonState = upRead;
  downButtonState = downRead;
  
  delay(100);
}
//
