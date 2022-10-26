#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 10, TXPin = 11;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{

Serial1.begin(9600);
//mDot.begin(9600);//set baud rate 
Serial1.println("\nBegin\n"); 
delay(1000); //wait 1 second before first data send

//Set up Multiconnect mDot for LoRaWAN communication 
Serial1.println("AT+TXP=?"); 
delay(1000); //wait 1 second before sending join command 
//mDot.read(); //read any msgs from mDot 
Serial1.println("AT+JOIN"); //send join command to mDot 
delay(500); 
Serial1.read(); //read any msgs from mDot 
Serial1.println("AT+SEND=" + String("STARTING TX"));
ss.begin(GPSBaud);
Serial.begin(9600);
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();



  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial1.println("AT+SEND= " +String("  No GPS detected: check wiring. "));
    // delay(5000); //code added delay the transission by 5 seconds
    while(true);
  }
}

void displayInfo()
{
  //Serial1.print("AT+SEND= " +String("  Location: "));
  Serial1.print("AT+SEND= " ); //code added
  Serial1.print(F("Location: "));
  //Serial1.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    float gps_location_lat = gps.location.lat();
    //Serial1.print(F(","));
    float gps_location_lng = gps.location.lng();
    //Serial1.print(F(" "));
  }
  else
  {
    //Serial1.print("AT+SEND= " ); //code added
    Serial1.print(F("INVALID"));
  }
  
  Serial1.print(F(" Date/Time: "));
  if (gps.date.isValid())
  {
    //Serial1.print("AT+SEND= " ); //code added
    Serial1.print(gps.date.month());
    Serial1.print("/");
    Serial1.print(gps.date.day());
    Serial1.print("/");
    Serial1.print(gps.date.year());
  }
  else
  {
    Serial1.print("INVALID");
  }

  Serial1.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial1.print(F("0"));
    Serial1.print(gps.time.hour());
    Serial1.print(F(":"));
    if (gps.time.minute() < 10) Serial1.print(F("0"));
    Serial1.print(gps.time.minute());
    Serial1.print(F(":"));
    if (gps.time.second() < 10) Serial1.print(F("0"));
    Serial1.print(gps.time.second());
    Serial1.print(F("."));
    if (gps.time.centisecond() < 10) Serial1.print(F("0"));
    Serial1.print(gps.time.centisecond());
  }
  else
  {
    Serial1.print(F("INVALID"));
  }

  Serial1.println();
  delay(5000);
}
