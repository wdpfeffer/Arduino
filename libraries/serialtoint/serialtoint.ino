int myint=-1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    myint=Serial.parseInt();
  }
  if (myint>0){
    Serial.println(myint);
    myint=-1;
  }

}
