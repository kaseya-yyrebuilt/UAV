#include <SoftwareSerial.h>

SoftwareSerial mDot(2, 3); // RX, TX


void setup()
{
  // Make sure the baud rate matches the configured 
  // baud setting of the mDot.
  
  mDot.begin(9600);
  //Serial.begin(9600);
  delay(500);
  mDot.println("AT+JOIN");
  
  
}

void loop()
{
  int water1 = 10;
  int water2 = 60;
  int water3 = 50;
  int water4 = 240;
  
  mDot.println("AT+SENDB=" + String(water1, HEX) + String(water2, HEX) + String(water3, HEX) + String(water4, HEX));
  delay(3000);
}
