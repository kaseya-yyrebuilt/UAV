#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Wire.h> //for Turbidity
#include "max6675.h" // for Thermocouple
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 11, TXPin = 12; //for GSP
static const uint32_t GPSBaud = 9600; //for GSP

int sensorPin = A0; //for Turbidity
float volt; //for Turbidity
float ntu; //for Turbidity

int ktcSO = 10; // for Thermocouple
int ktcCS = 9; // for Thermocouple
int ktcCLK = 8; // for Thermocouple

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin); //for GSP
MAX6675 ktc(ktcCLK, ktcCS, ktcSO); // for Thermocouple


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
delay(500); 
Serial1.println("AT+JOIN"); //send join command to mDot 
delay(500); 
Serial1.read(); //read any msgs from mDot 
Serial1.println("AT+SEND=" + String("STARTING TX"));


  
  Serial.begin(9600);
  ss.begin(GPSBaud);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  if (ss.available() > 0)
    if (gps.encode(ss.read()))
      {displayInfo();
      turbidityInfo();
      thermocoupleInfo();
      delay(5000);
      }
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
     Serial1.println("AT+SEND= " +String("  No GPS detected: check wiring. "));
    //Serial1.print("AT+SEND= " ); //code added
    //Serial1.println(F("No GPS detected: check wiring."));
    // delay(5000); //code added delay the transission by 5 seconds
    //while(true);
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
    Serial1.print(gps.location.lat(), 6);
    Serial1.print(F(","));
    Serial1.print(gps.location.lng(), 6);
    Serial1.print(F(" "));
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

  //Serial1.print();
  //delay(5000);
}


void turbidityInfo()
{
    
    volt = 0;
    for(int i=0; i<800; i++)
    {
        volt += ((float)analogRead(sensorPin)/1023)*5;
    }
    volt = volt/800;
    volt = round_to_dp(volt,1);
    if(volt < 2.5){
      ntu = 3000;
    }else{
      ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
    }
    //lcd.clear();
    //lcd.setCursor(0,0);
    //Serial.print(volt);
    //Serial.print(" V");
 
    //lcd.setCursor(0,1);
    Serial1.print(F(" Turbidity: "));
    Serial1.print(ntu);
    Serial1.print(" NTU");
   // delay(5000);
    
}
 
float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
  Serial1.println();
 // delay(5000);
}

void thermocoupleInfo() {
  // basic readout test
  
   Serial1.print(F(" Temperature: "));
   Serial1.print("Deg C = "); 
   Serial1.print(ktc.readCelsius());
   Serial1.print("Deg F = ");
   Serial1.println(ktc.readFahrenheit());
 
   //delay(500);
}
