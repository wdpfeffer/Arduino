#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x3F  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

// setup the input pins. they are arrange in terms of creating a 1 bit number 0000, 0001, 00010, 0011, 010
int io4 = 4;
int io3 = 5;
int io2 = 6;
int io1 = 7;
int blight =8;

//set delay time and corresponding counting loop integer
int loopDelay=0;
int loopCount=0;

//set up back light counting loop fo
int blightCount=10;

//String myByte="";
//set the delay byte integer equivalent
int intByte=0;

//define an array to hold the average temperatures
float temp[4];
float lcdTemps[4][3];

int n = 1;
int NumOfDevices=0;

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

// Data wire is plugged into port 3 on the Arduino
#define ONE_WIRE_BUS 3
#define TEMPERATURE_PRECISION 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
//DeviceAddress probe1, probe2, probe3, probe4;
// array to hold device addresses
DeviceAddress probe[4];

void setup(void) {
  Serial.begin(9600);
  lcd.begin (16,2);

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
    Serial.println();
  }
  
//set up the LCD
// Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();
  lcd.print("Willow Mountain Scientific");
  lcd.setCursor(0,1);
  lcd.print("Kiote T-Watcher v. 0.02");
  delay(1000);
  lcd.home();
  lcd.print("Num Devices = ");
  lcd.print(NumOfDevices);
  delay(3000);
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
      delay(3000);
      //set initial value in temp array.
      temp[k]=0;  
    }
  }
  lcd.setBacklightPin(BACKLIGHT_PIN,NEGATIVE);
}

void loop(void) {
  //define a temp variable
  loopCount+=1;

  // Show realtime values on LCD.
  sensors.requestTemperatures();
   //clear the LCD and move cursor to home
  lcd.clear();
  lcd.home ();                   // go home

  for(int i=0; i<NumOfDevices; i++){
    float thisTemp=0;
    float tmpTemp=0;
    //read temps
    tmpTemp=sensors.getTempC(probe[i]);
    temp[i]+=tmpTemp;
    //thisTemp=getLCDTemp(i,tmpTemp);
    thisTemp=tmpTemp;
      switch (i) {
              case 0:
                // do something
                  lcd.print("T0:");
                  lcd.print(thisTemp);
                  break;
              case 1:
                  // do something
                  lcd.setCursor(8,0);
                  lcd.print("T1:");
                  lcd.print(thisTemp);
                  break;
              case 2:
                  // do something
                  lcd.setCursor(0,1);
                  lcd.print("T2:");
                  lcd.print(thisTemp);
                  break;
                case 3:
                  // do something
                  lcd.setCursor(8,1);
                  lcd.print("T3:");
                  lcd.print(thisTemp);
                  break;    
              default:
                // do something
               break;
           }
  }
  if(loopCount==loopDelay){
    //get the temperatures
    // First check to see if Num of Sensors>0
      if (NumOfDevices>0){
        Serial.print("T,");
      // read the temperatures
       for(int j=0; j<NumOfDevices; j++){
           //Serial.print("T");
           //Serial.print(j);
           //Serial.print(",");
           if(j==NumOfDevices-1){
               // statement
              Serial.println(temp[j]/loopCount);
           } else {
               // statement
               Serial.print(temp[j]/loopCount);
               Serial.print(",");
           }
           temp[j]=0;
       }
     }else{
        lcd.clear();
        lcd.home();
        lcd.print("No probes detected");
     }
    loopCount=0;  
  }

  //check to see if backlight button pushed
  //Serial.println(digitalRead(blight));
  if(!digitalRead(blight)==1){
      blightCount=0;
  }

  //turn on backlight
  if (blightCount<10){
    blightCount+=1;
    lcd.setBacklightPin(BACKLIGHT_PIN,NEGATIVE);
  }else{
    lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  }
  
  delay(1000); //update every 1 seconds
 
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

float getLCDTemp(int pNo, float T){
  int boxcar=5;
  float sumT=0;
  float avgT=0;
  // boxcar value of 3
  for(int i=0; i<boxcar; i++){
      if(i!=boxcar-1){
          // statement
          lcdTemps[pNo][i]=lcdTemps[pNo][i+1];
      } else {
          // statement
          lcdTemps[pNo][i]=T;
      }
  }
  for(int i=0; i<boxcar; i++){
    sumT+=lcdTemps[pNo][i];
  }
  return sumT/boxcar;
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
