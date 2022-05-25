String test;

void setup() {                
// Turn the Serial Protocol ON
  Serial.begin(9600);
  

}


void loop() {
  
 Serial.write("http://www.homedepot.com/p/Alexandria-Moulding-5-8-in-x-3-4-in-x-96-in-Oak-Nose-Cove-Moulding-01670-40096/204757760\498484654654646546465464441112\n");
 delay(1000);
 if(Serial.available()){
 	test=Serial.read();
 	Serial.write(test);
 }

}
