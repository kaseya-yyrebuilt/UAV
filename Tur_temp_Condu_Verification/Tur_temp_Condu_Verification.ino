#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Wire.h> //for Turbidity
#include "max6675.h" // for Thermocouple
#define TdsSensorPin A2
#define VREF 5.0      // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point
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

int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,temperature = 25;
// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin); //for GSP
MAX6675 ktc(ktcCLK, ktcCS, ktcSO); // for Thermocouple


void setup()
{

 Serial1.begin(9600);
 pinMode(TdsSensorPin,INPUT);
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
      //displayInfo();
      turbidityInfo();
      thermocoupleInfo();
      TDSInfo();
      delay(1000);
  
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
    Serial.print(F(" Turbidity: "));
    Serial.print(ntu);
    Serial.print(" NTU");
   // delay(5000);
    
}
 
float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
  Serial.println();
 // delay(5000);
}

void thermocoupleInfo() {
  // basic readout test
  
   Serial.print(F(" Temperature: "));
   Serial.print("Deg C = "); 
   Serial.print(ktc.readCelsius());
   Serial.print("Deg F = ");
   Serial.print(ktc.readFahrenheit());
 
   //delay(500);
}

void TDSInfo() {
  static unsigned long analogSampleTimepoint = millis();
   if(millis()-analogSampleTimepoint > 40U)     //every 40 milliseconds,read the analog value from the ADC
   {
     analogSampleTimepoint = millis();
     analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
     analogBufferIndex++;
     if(analogBufferIndex == SCOUNT) 
         analogBufferIndex = 0;
   }   
   static unsigned long printTimepoint = millis();
   if(millis()-printTimepoint > 800U)
   {
      printTimepoint = millis();
      for(copyIndex=0;copyIndex<SCOUNT;copyIndex++)
        analogBufferTemp[copyIndex]= analogBuffer[copyIndex];
      averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
      float compensationCoefficient=1.0+0.02*(temperature-25.0);    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
      float compensationVolatge=averageVoltage/compensationCoefficient;  //temperature compensation
      tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; //convert voltage value to tds value
      Serial.print("  TDS Value:");
      Serial.print(tdsValue,0);
      Serial.println("ppm");
    }
}

int getMedianNum(int bArray[], int iFilterLen) 
{
      int bTab[iFilterLen];
      for (byte i = 0; i<iFilterLen; i++)
      bTab[i] = bArray[i];
      int i, j, bTemp;
      for (j = 0; j < iFilterLen - 1; j++) 
      {
      for (i = 0; i < iFilterLen - j - 1; i++) 
          {
        if (bTab[i] > bTab[i + 1]) 
            {
        bTemp = bTab[i];
            bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
         }
      }
      }
      if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
      else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
      return bTemp;
}
