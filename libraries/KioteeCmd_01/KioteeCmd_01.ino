#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#define DS3231_I2C_ADDRESS 0x68

int NumOfDevices=0;
int inbyte=0;
unsigned long inputNum=0;        // a string to hold incoming data
boolean entryComplete = false;  // whether the string is complete
String probes="";
String temps="";


// setup the input pins. they are arrange in terms of creating a 1 bit number 0000, 0001, 00010, 0011, 010
int io4 = 4;
int io3 = 5;
int io2 = 6;
int io1 = 7;
int blight =8;

//set delay time and corresponding counting loop integer
int loopDelay=0;
int loopCount=0;
bool starting=true;

//set up back light counting loop fo
int blightCount=10;

//String myByte="";
//set the delay byte integer equivalent
int intByte=0;

//define an array to hold the average temperatures
float temp[4];
float lcdTemps[4][3];

int n = 1;

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 20 chars and 4 line display

// Data wire is plugged into port 3 on the Arduino
#define ONE_WIRE_BUS 3
#define TEMPERATURE_PRECISION 11

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
//DeviceAddress probe1, probe2, probe3, probe4;
// array to hold device addresses
DeviceAddress probe[4];

//Declarations for Real Time Clock
const byte numChars = 1;
char receivedChars[numChars];   // an array to store the received data
//int receivedChar;

boolean newData = false;
char readyToSend='s';


byte decToBcd(byte val){
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val){
  return( (val/16*10) + (val%16) );
}

void setup(void) {
  Serial.begin(9600);
  //Serial.println(readyToSend);
  lcd.init();

  //delay for stability
  delay(100);

    Serial.begin(9600);
  lcd.init();

// make the pushbutton's pin an input:
  pinMode(io4, INPUT_PULLUP);
  pinMode(io3, INPUT_PULLUP);
  pinMode(io2, INPUT_PULLUP);
  pinMode(io1, INPUT_PULLUP);
  pinMode(blight, INPUT_PULLUP);

  //delay for stability
    delay(100);

// read the input pin:
  int read4 = digitalRead(io4);
  int read3 = digitalRead(io3);
  int read2 = digitalRead(io2);
  int read1 = digitalRead(io1);

  //myByte=String(read1)+String(read2)+String(read3)+String(read4);
  // create integer equivalent of byte
  intByte=read4+2*read3+4*read2+8*read1;
  loopDelay=getDelay(intByte);    

 //set up one wire devices
  Serial.println("Willow Mountain Scientific");
  Serial.println("Kiotee T Watcher v 0.02");
  delay(1000);
  
  Serial.print("Loop Delay = ");
  Serial.println(loopDelay);
  delay(1000);
  // Start up the library
  sensors.begin();

  delay(100);
  Serial.print("Found ");
  NumOfDevices=sensors.getDeviceCount();
  Serial.print(NumOfDevices, DEC);
  Serial.println(" devices.");

  delay(100);
  // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  // Assign address manually. The addresses below will beed to be changed
  // to valid device addresses on your bus. Device address can be retrieved
  // by using either oneWire.search(deviceAddress) or individually via
  // sensors.getAddress(deviceAddress, index)
  //probe1 = { 0x28, 0x1D, 0x39, 0x31, 0x2, 0x0, 0x0, 0xF0 };
  //probe2   = { 0x28, 0x3F, 0x1C, 0x31, 0x2, 0x0, 0x0, 0x2 };

  // Search for devices on the bus and assign based on an index. Ideally,
  // you would do this to initially discover addresses on the bus and then 
  // use those addresses and manually assign them (see above) once you know 
  // the devices on your bus (and assuming they don't change).
  // 
  // method 1: by index
  for(int h=0; h<NumOfDevices; h++){
    if (!sensors.getAddress(probe[h],h)){
        Serial.print("Unable to find address for Device ");
        Serial.println(h);
      }   
  }
  //if (!sensors.getAddress(probe1, 0)) Serial.println("Unable to find address for Device 0"); 
  //if (!sensors.getAddress(probe2, 1)) Serial.println("Unable to find address for Device 1"); 

  // method 2: search()
  // search() looks for the next device. Returns 1 if a new address has been
  // returned. A zero might mean that the bus is shorted, there are no devices, 
  // or you have already retrieved all of them. It might be a good idea to 
  // check the CRC to make sure you didn't get garbage. The order is 
  // deterministic. You will always get the same devices in the same order
  //
  // Must be called before search()
  //oneWire.reset_search();
  // assigns the first address found to probe1
  //if (!oneWire.search(probe1)) Serial.println("Unable to find address for probe1");
  // assigns the seconds address found to probe2
  //if (!oneWire.search(probe2)) Serial.println("Unable to find address for probe2");

  // show the addresses we found on the bus

  for(int m=0; m<NumOfDevices; m++){
    Serial.print("Device ");
    Serial.print(m);
    Serial.print(" Address: ");
    printAddress(probe[m]);
    delay(100);  
  }
  
  // set the resolution to 9 bit per device
  for(int g=0; g<NumOfDevices; g++){
    sensors.setResolution(probe[g],TEMPERATURE_PRECISION);
    Serial.print("Device ");
    Serial.print(g);
    Serial.print(" Resolution: ");
    Serial.println(sensors.getResolution(probe[g]), DEC);
  }

  setupLCD();
 
}
void setupLCD(){
//set up the LCD
// Switch on the backlight
//lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();
  delay(10);
  lcd.print("Willow Mountain Scientific");
  lcd.setCursor(0,1);
  lcd.print("Kiote T-Watcher v. 0.02");
  delay(1000);
  lcd.home();
  lcd.print("Num Devices = ");
  lcd.print(NumOfDevices);
  delay(1000);
  lcd.clear();
  lcd.home();
  if (NumOfDevices>0){
    for(int k=0; k<NumOfDevices; k++){
      lcd.clear();
      lcd.home();
      lcd.print("Probe ");
      lcd.print(k);
      lcd.print(" Address: ");
      lcd.setCursor(0,1);
      printAddressLCD(probe[k]);
      delay(1000);
    }
  }
  lcd.clear();
}
void printReaderDetails(){
  delay(100);
  Serial.print("Found ");
  NumOfDevices=sensors.getDeviceCount();
  Serial.print(NumOfDevices, DEC);
  Serial.println(" devices.");

  delay(100);
  // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  // Assign address manually. The addresses below will beed to be changed
  // to valid device addresses on your bus. Device address can be retrieved
  // by using either oneWire.search(deviceAddress) or individually via
  // sensors.getAddress(deviceAddress, index)
  //probe1 = { 0x28, 0x1D, 0x39, 0x31, 0x2, 0x0, 0x0, 0xF0 };
  //probe2   = { 0x28, 0x3F, 0x1C, 0x31, 0x2, 0x0, 0x0, 0x2 };

  // Search for devices on the bus and assign based on an index. Ideally,
  // you would do this to initially discover addresses on the bus and then 
  // use those addresses and manually assign them (see above) once you know 
  // the devices on your bus (and assuming they don't change).
  // 
  // method 1: by index
  for(int h=0; h<NumOfDevices; h++){
    if (!sensors.getAddress(probe[h],h)){
        Serial.print("Unable to find address for Device ");
        Serial.println(h);
      }   
  }
  //if (!sensors.getAddress(probe1, 0)) Serial.println("Unable to find address for Device 0"); 
  //if (!sensors.getAddress(probe2, 1)) Serial.println("Unable to find address for Device 1"); 

  // method 2: search()
  // search() looks for the next device. Returns 1 if a new address has been
  // returned. A zero might mean that the bus is shorted, there are no devices, 
  // or you have already retrieved all of them. It might be a good idea to 
  // check the CRC to make sure you didn't get garbage. The order is 
  // deterministic. You will always get the same devices in the same order
  //
  // Must be called before search()
  //oneWire.reset_search();
  // assigns the first address found to probe1
  //if (!oneWire.search(probe1)) Serial.println("Unable to find address for probe1");
  // assigns the seconds address found to probe2
  //if (!oneWire.search(probe2)) Serial.println("Unable to find address for probe2");

  // show the addresses we found on the bus

  for(int m=0; m<NumOfDevices; m++){
    Serial.print("Device ");
    Serial.print(m);
    Serial.print(" Address: ");
    printAddress(probe[m]);
    Serial.println();
    delay(100);  
  }
  
  // set the resolution to 9 bit per device
  for(int g=0; g<NumOfDevices; g++){
    sensors.setResolution(probe[g],TEMPERATURE_PRECISION);
    Serial.print("Device ");
    Serial.print(g);
    Serial.print(" Resolution: ");
    Serial.println(sensors.getResolution(probe[g]), DEC);
  }
}
void showTempData(float tempData[]){
  //lcd.clear();
  lcd.home();
  for (int i=0; i < NumOfDevices; i++){
    float temp=tempData[i];
    switch (i) {
      case 0:
        // do something
        lcd.print("0:");
        lcd.print(temp);
        break;
      case 1:
        // do something
        lcd.setCursor(8,0);
        lcd.print("1:");
        lcd.print(temp);
        break;
      case 2:
        // do something
        lcd.setCursor(0,1);
        lcd.print("2:");
        lcd.print(temp);
        break;
      case 3:
        // do something
        lcd.setCursor(8,1);
        lcd.print("3:");
        lcd.print(temp);
        break;    
      default:
        // do something
      break;
    }
  }
}

void loop() {
  // print the string when a newline arrives:
  if (entryComplete) {
    //for debugging purposes, print output.
    //Serial.println(inputNum);
    switch (inputNum) {
        case 500:
          // send reader details
          Serial.println("Reader details");
          break;
        case 510:
          // send header, comma delimited
          Serial.println("Header information");
          break;
        case 520:
          // send probe numbers, comma delimited
          for(int m=0; m < NumOfDevices; m++){
            loadAddress(m);  
            if (m < NumOfDevices-1){
              probes+=",";  
            }
          }
          Serial.println(probes);
          delay(20);
          probes="";
          break;
        case 530:
          // send time and date
          Serial.println("time and date");
          break;
        case 540:
          // send temperatures
          //Serial. println("temperatures");
          getTemperatures();
          Serial.println(temps);
          delay(20);
          temps="";
          break;
    }
    
    // clear the string:
    inputNum = 0;
    entryComplete = false;
  }
  delay(100);
}

void getTemperatures() {
  //get the temperature data
  float temperatures[NumOfDevices];
  sensors.requestTemperatures();
  for(int i=0; i<NumOfDevices; i++){
    float thisTemp=0;
    float tmpTemp=0;
    //read temps
    temperatures[i]=sensors.getTempC(probe[i]);
  }
  //show the temperatures on the LCD
  showTempData(temperatures);
  //Check serial port for request to send data
  //recvWithEndMarker();
  //send new data if there is some
  for(int i=0;i<NumOfDevices;i++){
    temps+=(temperatures[i]);
    if (i < NumOfDevices-1){
      temps+=",";
    }
  }
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year){
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}

void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year){
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

void serialEvent() {
  //inputNum=0;
  while (Serial.available()) {
    // get the new byte:
    inbyte = Serial.read();
    //Serial.println(inbyte);
    //inputNum=inputNum*10+inbyte-'0';
    //Serial.print(inbyte);
    // add it to the inputString:
     if (inbyte != 10 && inbyte!=13){
       inputNum=inputNum*10+inbyte-48;
       //Serial.print("added");
     }
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
     if (inbyte == 10 || inbyte==13) {
       entryComplete = true;
       //Serial.print("done");
     }
    //inbyte=0;
  }
  inbyte=0;
}


void sendSerialData(float tempData[]){
  int n=sizeof(tempData);

  //print header
  Serial.print("date,time,");
  for(int j=0;j<n-1;j++){
    Serial.print("T");
    if(j==n-2){
      Serial.println(j);
    }else{
      Serial.print(j);
      Serial.print(",");
    }
  }
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);

  //retrieve data from temp probes

  // send it to the serial monitor
  // starting with date, make data comma delimited
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(",");

  // next send time
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute<10){
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10){
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(",");
  for(int i=0;i<n-1;i++){
    if (i==n-2){
      Serial.println(tempData[i]);
    }else{
      Serial.print(tempData[i]);
      Serial.print(",");
    }
  }

}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
  while (Serial.available() > 0 && newData == false) {
        //Serial.write("in loop");
        rc = Serial.read();
        
        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            //receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}
void checkSerial(float tempData[]) {
    if (newData == true) {
        Serial.println(receivedChars);
        Serial.println(readyToSend);
        newData = false;
        if (strcmp(readyToSend,receivedChars)==0){
          sendSerialData(tempData);
        }
    }
}
// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void loadAddress(int probeNo){
  
  
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (probe[probeNo][i] < 16) probes+="0";
    probes+=String(probe[probeNo][i], HEX);
  }  
}

// function to print a device address on lcd
void printAddressLCD(DeviceAddress deviceAddress){
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    lcd.print(deviceAddress[i], HEX);
  }
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress){
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.print(DallasTemperature::toFahrenheit(tempC));
}

// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress){
  Serial.print("Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();    
}

// main function to print information about a device
void printData(DeviceAddress deviceAddress){
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
}
void displayTime(){
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute<10){
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10){
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");
  switch(dayOfWeek){
  case 1:
    Serial.println("Sunday");
    break;
  case 2:
    Serial.println("Monday");
    break;
  case 3:
    Serial.println("Tuesday");
    break;
  case 4:
    Serial.println("Wednesday");
    break;
  case 5:
    Serial.println("Thursday");
    break;
  case 6:
    Serial.println("Friday");
    break;
  case 7:
    Serial.println("Saturday");
    break;
  }
  lcd.setBacklight(HIGH);
  lcd.home ();
  lcd.print(hour, DEC);
  lcd.print(":");
  if (minute<10){
    lcd.print("0");
  }
  lcd.print(minute, DEC);
  lcd.print(":");
  if (second<10){
    lcd.print("0");
  }
  lcd.print(second, DEC);
  lcd.print(" ");
  lcd.print(dayOfMonth, DEC);
  lcd.print("/");
  lcd.print(month, DEC);
  lcd.print("/");
  lcd.print(year, DEC);
}
//calculate delay based on switch settings.
int getDelay(int d){
  Serial.print(d);
  int thisdelay=0;
  switch (d) {
      case 0 :
        //1 sec read t
        thisdelay=1;
        break;
      case 1 :
        //10 sec read ti
        thisdelay=10;
        break;
      case 2:
        //30 sec read ti
        thisdelay=30;
        break;
      case 3:
        //1 min
        thisdelay=60;
        break;
      case 4:
        //2 minute
        thisdelay=120;
        break;
      case 5:
        //5 minute read tim
        thisdelay=300;
        break;
      case 6:
        //10 minute readtim
        thisdelay=600;
        break;
      case 7:
        //15 minute read tim
        thisdelay=900;
        break;
      case 8:
        //20 min read time
        thisdelay=1200;
        break;
      case 9:
        //30 min read time
        thisdelay=1800;
        break;
      case 10:
        //60 min read time
        thisdelay=3600;
        break;
      case 11:
        // 2 hr  read time
        thisdelay=7200;
        break;
      case 12:
        // 4 hr  read time

        thisdelay=14400;
        break;
      case 13:
        // 6 hr  read time

        thisdelay=21600;
        break;
      default:
        // do a one minute read by default  
        thisdelay=60;
        break;
    }
    return thisdelay;
}
