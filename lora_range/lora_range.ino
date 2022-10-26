void setup()
{

 Serial1.begin(9600);
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
}

void loop()
{
 Serial1.println("AT+SEND =" + String("123"));
 delay(2000);
}
