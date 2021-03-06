#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 3
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
 
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
}
 
 
void loop()
{
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.print("T1: ");
  Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"?
// You can have more than one IC on the same bus.
// 0 refers to the first IC on the wire
 
}
