#define pinVolts 3 
#define baseline 51 //1 volt baseline 1/5*255
#define intval 0.1047 //pi divided by 30

float angle =0;
int volts;



void setup() {
  // put your setup code here, to run once:
  pinMode(pinVolts, OUTPUT);
  //Serial.begin(9600);


}

void loop() {
  //define voltage
  if (angle < 3.1415){
    volts = int(baseline + sin(angle)*12.75);  //signal is 1 v DC plus a 1/4 sinewave
    angle += intval;
  }else{
    angle = 0;
    volts = int(baseline + sin(angle)*12.75);  //signal is 1 v DC plus a 1/4 sinewave
  }

  //Serial.println(volts);
  analogWrite(pinVolts, volts);
  delay(30);

}
