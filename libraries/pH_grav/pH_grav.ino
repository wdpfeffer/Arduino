#include "ph_grav.h"

Gravity_pH pH = Gravity_pH(A0);

uint8_t user_bytes_received = 0;
const uint8_t bufferlen = 32;
char user_data[bufferlen];


void parse_cmd(char* string) {
  strupr(string);
  if (strcmp(string, "CAL,4") == 0) {
    pH.cal_low();
    Serial.println("LOW CALIBRATED");
  }
  else if (strcmp(string, "CAL,7") == 0) {
    pH.cal_mid();
    Serial.println("MID CALIBRATED");
  }
  else if (strcmp(string, "CAL,10") == 0) {
    pH.cal_high();
    Serial.println("HIGH CALIBRATED");
  }
}

void setup() {
  Serial.begin(9600);
  delay(200);
  Serial.println(F("Use commands \"CAL,4\", \"CAL,7\", and \"CAL,10\" to calibrate \nthe circuit to those respective values"));
  if(pH.begin()){
    Serial.println("Loaded EEPROM");
  }
  
}

void loop() {
  if (Serial.available() > 0) {
    user_bytes_received = Serial.readBytesUntil(13, user_data, sizeof(user_data));
  }

  if (user_bytes_received) {
    parse_cmd(user_data);
    user_bytes_received = 0;
    memset(user_data, 0, sizeof(user_data));
  }
  
  Serial.println(getph());
  delay(500);
}

float getph(){
  float myph = 0;
  for (int i=0; i<=9;i++){
    myph += pH.read_ph();
    delay(50
    );
  }
  // get the average
  myph = myph/10.0;
  return myph;
}
