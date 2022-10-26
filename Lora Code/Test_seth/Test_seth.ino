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
  
  
}

void loop()
{
  int water_value = 300;
  String packet = "AT+SEND=";
  packet += water_value;
  mDot.println(packet);
  
}
