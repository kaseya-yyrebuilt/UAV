//Andrew Langevin
//Master's Project Arduino Code
//Code implements sampling hydrophone sensor at 500Hz and transmitting raw ADC
//data to The Things Network via LoRaWAN mDot and Arduino Mega
// Function prototypes
// - specify default values here
#include <SoftwareSerial.h>
SoftwareSerial mDot(2, 3); // RX, TX
bool takeAnalogReadings(uint16_t* p_numReadings = nullptr, uint16_t** p_analogVals = nullptr);
int i;
uint16_t size;

void setup() {
// put your setup code here, to run once:
Serial.begin(9600); //set baud rate
mDot.begin(9600);
Serial.println("\nBegin\n");
delay(2000); //wait 1 second before first data send
//Set up Multiconnect mDot for LoRaWAN communication
Serial.println("AT+TXP=?");
delay(1000); //wait 1 second before sending join command
mDot.read(); //read any msgs from mDot
delay(500);
Serial.println("AT+JOIN"); //send join command to mDot
delay(500);
mDot.read(); //read any msgs from mDot
Serial.println("AT+SEND=" + String("STARTING TX"));
}
//Main code
void loop()
{
// This is a way to both take readings *and* read out the values when the buffer is full
uint16_t numReadings;
uint16_t* analogVals;
bool readingsDone = takeAnalogReadings(&numReadings, &analogVals);
int Values;
if (readingsDone)
{
// Let's print them all out!
//Serial.print("numReadings = "); Serial.println(numReadings);
// Serial.print("analogVals = [");
// for (uint16_t i=0; i<numReadings; i++)
// {
// if (i!=0)
// {
// //Serial.print(", ");
// }
// Serial.print(analogVals[i]);
// }
// Serial.println("]");
// Sending the data to the mDot to transmit
Serial.println("AT+SEND=" + String(analogVals[0]) +"," + String(analogVals[1])+"," + String(analogVals[2])+","+ String(analogVals[3])+","+String(analogVals[4])+","+String(analogVals[5])+","+String(analogVals[6])+","+String(analogVals[7])+","+String(analogVals[8])+","+String(analogVals[9]));
delay(10000); //delay 10s before next transmission
// Serial.print("Number of TX Bytes = ");
//Serial.println(size); //Prints the number of bytes being transmitted
//Serial.println();
}
}
// Function definitions:
//---------------------------------------------------------------------------------------------------------------------
// Take analog readings to fill up a buffer.
// Once the buffer is full, return true so that the caller can read out the data.
// Optionally pass in a pointer to get access to the internal buffer in order to read out the data from outside
// this function.
//---------------------------------------------------------------------------------------------------------------------
bool takeAnalogReadings(uint16_t* p_numReadings, uint16_t** p_analogVals)
{
static const uint16_t NUM_READINGS = 200; //Number of samples taken
static uint16_t i = 0; // index
static uint16_t analogVals[NUM_READINGS];
size = sizeof(analogVals); //calculates the number of bytes being transmitted
const uint32_t SAMPLE_PD = 5; // ms; sample period (1/fs)
static uint32_t tStart = millis(); // ms; start time
bool bufferIsFull = false; // set to true each time NUM_READINGS have been taken
// Only take a reading once per SAMPLE_PD
uint32_t tNow = millis(); // ms; time now
if (tNow - tStart >= SAMPLE_PD)
{
//Serial.print("taking sample num "); Serial.println(i + 1);
tStart += SAMPLE_PD; // reset start time to take next sample at exactly the correct pd
analogVals[i] = analogRead(A0); //read the ADC output
i++;
if (i >= NUM_READINGS)
{
bufferIsFull = true;
i = 0; // reset to beginning of array, so you don't try to save readings outside of the bounds of the array
}
}
// Assign the user-passed-in pointers so that the user can retrieve the data if they so desire to do it this way
if (p_numReadings != nullptr)
{
*p_numReadings = NUM_READINGS;
}
if (p_analogVals != nullptr)
{
*p_analogVals = analogVals;
}
return bufferIsFull;
}
