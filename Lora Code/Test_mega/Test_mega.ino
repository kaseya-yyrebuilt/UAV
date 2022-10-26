//#include <SoftwareSerial.h>

//SoftwareSerial mDot(2, 3); // RX, TX

void setup()
{
  // Make sure the baud rate matches the configured 
  // baud setting of the mDot.
  Serial1.begin(9600);
  delay(500);
  Serial1.println("AT+JOIN");
  
}

void loop()
{
  int water_value = 400;
  int water = 500;
  Serial1.println("AT+SENDB=" + water_value + "," + water);
  delay(500);
}
