#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 4 on the Arduino
#define ONE_WIRE_BUS 4
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
#include <SoftwareSerial.h>

SoftwareSerial mDot(2, 3); // RX, TX


void setup()
{
  // Make sure the baud rate matches the configured 
  // baud setting of the mDot.
  
  mDot.begin(9600);
  //Serial.begin(9600);
  delay(1000);
  mDot.println("AT+JOIN");
  

  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();

  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(), DEC); 
  Serial.println();

  sensors.setResolution(10);
}

  
  
void loop()
{
  sensors.requestTemperatures(); // Send the command to get temperatures
 
  Serial.print("Temp: ");
  int sensor_value = sensors.getTempCByIndex(0);
  int sensor_test = 99;
  Serial.println(sensor_test);
  
  String packet = "AT+SEND=";
  packet += sensor_test;
  mDot.println(packet);
  delay(1000);
  
}
