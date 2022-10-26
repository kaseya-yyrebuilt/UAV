#include <SoftwareSerial.h>

SoftwareSerial mDot(2, 3); // RX, TX

void setup()
{
  // Make sure the baud rate matches the configured 
  // baud setting of the mDot.
  mDot.begin(9600);
  Serial.begin(9600);
  delay(1000);
  mDot.write("AT+JOIN");
 

  
  
}

void loop()
{
  
  char c;
  if (Serial.available())
  { 
    c = Serial.read();
    mDot.write(c);
  }
  
  if (mDot.available())
  { 
    c = mDot.read();
    Serial.write(c);
  }
}
