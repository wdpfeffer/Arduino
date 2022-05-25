int Vout = 9;      // Voltage out to digital pin 9

int AnalogVin = 3;   // potentiometer connected to analog pin 3

int val = 0;         // variable to store the read value
int count=0;        //counting varialbe
double vScale=0;

float pi=0;



void setup()

{

  Serial.begin(9600);
  pinMode(Vout, OUTPUT);   // sets the pin as output

}



void loop()

{

  pi=(float)count/360*2*3.14;
  //Serial.println(pi);
  vScale=127*sin(pi)+ 127;
  //Serial.println(vScale);
  analogWrite(Vout, (int)vScale);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
  val = analogRead(AnalogVin);   // read the input pin
  Serial.println(val);
  if (count <361){
    count++;
  }
  else{
    count=0;
  }

  delay(100);

}
