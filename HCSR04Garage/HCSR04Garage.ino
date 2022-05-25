#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(5,6);//initialisation class HCSR04 (trig pin , echo pin)

int maxcount = 10;
int i=0;
float rd = 0.0;
float distance =0.0;
float avdist = 0.0;
int maxdist = 120;
int good = 8;
int warning = 9;
int danger = 10;
int gooddist = 50;
int warndist = 15;


void setup(){
  Serial.begin(9600);
  pinMode(good, OUTPUT);
  pinMode(warning, OUTPUT);
  pinMode(danger, OUTPUT);
  digitalWrite(good, HIGH);
  digitalWrite(warning, LOW);
  digitalWrite(danger, LOW);
  }

void loop(){
  distance = distanceSensor.measureDistanceCm();
  if (distance <= maxdist){
    rd += distance;  
  }else{
    rd += maxdist;
  }
  i+=1;
  if (i==maxcount){
    avdist = rd/maxcount;
    Serial.println(rd/maxcount);
    if(avdist > gooddist){
      digitalWrite(good, HIGH);
      digitalWrite(warning, LOW);
      digitalWrite(danger, LOW); 
    }else if (avdist > warndist && avdist <gooddist){
      digitalWrite(good, LOW);
      digitalWrite(warning, HIGH);
      digitalWrite(danger, LOW);
    }else if (avdist <= warndist){
      digitalWrite(good, LOW);
      digitalWrite(warning, LOW);
      digitalWrite(danger, HIGH);
    }else{
      digitalWrite(good, LOW);
      digitalWrite(warning, LOW);
      digitalWrite(danger, HIGH);
    }
    
    rd=0;
    i=0;  
  }  
}
