#define fadePin 9

void setup(){
  pinMode(fadePin, OUTPUT);  
}

void loop(){

  
  }

void powerUp(numOfCycles,dly){
  for(int j=0; j<numOfCycles;j++){
    for(int i = 0; i<100; i++){
      //convert 0-360 angle to radian (needed for sin function)
      float n2r = 0.06 * i;
  
      //calculate sin of angle as number between 0 and 255
      int sinOut = constrain(pow(2.302,n2r), 0, 255); 
  
      analogWrite(fadePin, sinOut);
  
      delay(dly);  
    }
  }
}

