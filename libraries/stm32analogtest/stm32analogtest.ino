// This script generates data for testing the linearity of the ADC on the STM32 Blue Pill
// Voltage is place acrossed a 50K POT from G to 3.3V. the wiper is attached to analog pin "aPin".

const int aPin = PA0;  //This is the analog pin attached to the wiper of the POT
const int iLED = PC13; //Internal LED to give a visual indication that a loop has occured
int vsig =0;           //variable to hold the analog to digital conversion signal.


void setup() {
  // set up serial out put if needed
  Serial.begin(9600);

  //define the mode for internal led iLED
  pinMode(iLED, OUTPUT);

  //define the mode for the analog pin
  pinMode(aPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  vsig = bunch(aPin,100);
  Serial.println(vsig);
  blink();

}

int bunch(int myPin, int group){
  // this function averages out the noise of the ADC. Bunch size can vary.
  int mybunch = 0;
  for (int i=0; i < group; i++){
    mybunch += analogRead(myPin);
  }
  mybunch = int(mybunch/group);

  return mybunch;
}

void blink(){
  digitalWrite(iLED, HIGH);
  delay(500);
  digitalWrite(iLED, LOW);
  delay(500);
  
}
