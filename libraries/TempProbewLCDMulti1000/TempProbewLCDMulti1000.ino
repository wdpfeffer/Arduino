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
DeviceAddress probe1, probe2;

void setup(void) {
  Serial.begin(9600);
  lcd.begin (16,2);

  delay(100);
 //set up one wire devices
  Serial.println("Willow Mountain Scientific Kiotee Recorder");

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
  if (!sensors.getAddress(probe1, 0)) Serial.println("Unable to find address for Device 0"); 
  if (!sensors.getAddress(probe2, 1)) Serial.println("Unable to find address for Device 1"); 

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
  Serial.print("Device 0 Address: ");
  printAddress(probe1);
  Serial.println();
  delay(100);
  
  Serial.print("Device 1 Address: ");
  printAddress(probe2);
  Serial.println();
  delay(100);

  // set the resolution to 9 bit per device
  sensors.setResolution(probe1, TEMPERATURE_PRECISION);
  sensors.setResolution(probe2, TEMPERATURE_PRECISION);

  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(probe1), DEC); 
  Serial.println();
  delay(100);

  Serial.print("Device 1 Resolution: ");
  Serial.print(sensors.getResolution(probe2), DEC); 
  Serial.println();
  delay(100);
// Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();
  lcd.print("Num Devices = ");
  lcd.print(NumOfDevices);
  delay(3000);
  lcd.clear();
  lcd.home();
  if (NumOfDevices>0){
    lcd.print("Probe 1 Address");
    lcd.setCursor(0,1);
    printAddressLCD(probe1);
    delay(20000);
    if (NumOfDevices==2){
      lcd.clear();
      lcd.home();
      lcd.print("Probe 2 Address");
      lcd.setCursor(0,1);
      printAddressLCD(probe2);
      delay(20000);
    }
  }
}

void loop(void) {
 //get the temperatures
 sensors.requestTemperatures();
 float temp1 = sensors.getTempC(probe1);
 float temp2 = sensors.getTempC(probe2);

 // send data  to serial port

 if (NumOfDevices>1){
  Serial.print("T1,");
  Serial.print(temp1);
  Serial.print(",T2,");
  Serial.println(temp2);
 }
 else{
  Serial.print(",T1,");
  Serial.println(temp1);
 }


 //display info on lcd
 lcd.clear();
 lcd.home ();                   // go home
 if(NumOfDevices>1){
  lcd.print("T1 = ");
  lcd.print(temp1);
  lcd.setCursor(0,1);             //go to line 2
  lcd.print("T2 = ");
  lcd.print(temp2); 
 }
 else{
  lcd.print("T1 = ");
  lcd.print(temp1);
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
void printAddressLCD(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    lcd.print(deviceAddress[i], HEX);
  }
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.print(DallasTemperature::toFahrenheit(tempC));
}

// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress)
{
  Serial.print("Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();    
}

// main function to print information about a device
void printData(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
}
