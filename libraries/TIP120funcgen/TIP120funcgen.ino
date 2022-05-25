#define fadePin 9

const byte up=1;
const byte down=0;
const byte interruptPin=2;
unsigned long newTime=0;
unsigned long oldTime=0;
unsigned long difTime;
bool doCount=false;
int count=0;

void setup(){
  Serial.begin(9600);
  pinMode(fadePin, OUTPUT);
  pinMode(interruptPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), checkAction, RISING);
}
void loop(){
  if (doCount){
    count++;
  }  
  if(!doCount && count>0){
    Serial.println(count);
    count=0;
  }
}
void unLock(){
  ramp(up,1,10);
  powerUp(4,5);
  pulse(3,5);
  ramp(down,1,50);
  Serial.println("unlock");
}
void lockUp(){
  powerDown(4, 5);
  pulse(3,5);
  ramp(down,1,30);
  Serial.println("lock");
}

//run this function during an interrupt
void checkAction(){
  newTime=millis();
  if(oldTime==0){
    oldTime=newTime;
  }
  difTime=newTime-oldTime;
  //debounce the interrupt
  if (difTime>200){
    if(!doCount){
      //start the count
      Serial.println("start count");
      doCount=true;
    }else if(doCount){
      //stop the count
      Serial.println("stop count");
      doCount=false;
    }
    oldTime=newTime;
  }
}

void powerUp(int numOfCycles,int dly){
  for(int j=0; j<numOfCycles;j++){
    analogWrite(fadePin,0);
    for(int i = 0; i<100; i++){
      float n2r = 0.06 * i;
  
      //calculate sin of angle as number between 0 and 255
      int sinOut = constrain(pow(2.302,n2r), 0, 255); 
  
      analogWrite(fadePin, sinOut);
  
      delay(dly);  
    }
  }
}

void powerDown(int numOfCycles,int dly){
  for(int j=0; j<numOfCycles;j++){
    analogWrite(fadePin,0);
    for(int i = 100; i>=0; i--){
      float n2r = 0.06 * i;
  
      //calculate sin of angle as number between 0 and 255
      int sinOut = constrain(pow(2.302,n2r), 0, 255); 
  
      analogWrite(fadePin, sinOut);
  
      delay(dly);  
    }
  }
}

void pulse(int numOfCycles, int dly){
  for(int j=0; j<numOfCycles;j++){
    for(int i = 0; i<360; i++){
    //convert 0-360 angle to radian (needed for sin function)
    float rad = DEG_TO_RAD * i;

    //calculate sin of angle as number between 0 and 255
    int sinOut = constrain((sin(rad) * 128) + 128, 0, 255); 

    analogWrite(fadePin, sinOut);

    delay(dly);
  }
    
  }
  
}

void ramp(byte direction, float slope, int dly){
  int increment,maxnum,minnum;
  
  if(direction==up){
    maxnum=255;
    minnum=0;
    increment=1;
    for(int i=minnum; i<=maxnum;i=i+increment){
      int rampOut=constrain(i*slope,0,255);
      //Serial.println(rampOut);
      analogWrite(fadePin, rampOut);
      delay(dly);
    }
    
  }else{
    maxnum=0;
    minnum=255;
    increment=-1;
    for(int i=minnum; i>=maxnum;i=i+increment){
      int rampOut=constrain(i*slope,0,255);
      //Serial.println(rampOut);
      analogWrite(fadePin, rampOut);
      delay(dly);
    }
  }
  
}

