/*
 * This program runs on Arduino Uno as a I2C slave
 */

#include <Wire.h>
const int SLAVE_ADDRESS = 1;
char incomingByte = 0;

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(onReceiveEvent);
  Serial.begin(9600);
  Serial.println("Received Data: ");
}

void loop() {
}

void onReceiveEvent(int howMany)
{
  while (Wire.available())
  {
    for (int i=0; i < howMany; i++)
    {
      incomingByte = Wire.read();
      Serial.print(incomingByte);
    }
    Serial.println("");
  }
}




