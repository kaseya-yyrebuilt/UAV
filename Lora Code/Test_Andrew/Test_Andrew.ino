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
  int water = 30005;
  int water1 = 6005;
  
  mDot.println("AT+SEND=" + String(water) + "," + String(water1));
  delay(5000);
}
