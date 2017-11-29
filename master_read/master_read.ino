/*
 * This program runs on Linkit7697 as a I2C master
 */

#include <Wire.h>
const int SLAVE_ADDRESS = 1;
char incomingByte = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Received Data: ");
}

void loop() {
  Wire.requestFrom(SLAVE_ADDRESS, 17);
  while (Wire.available())
  {
    incomingByte = Wire.read();
    Serial.print(incomingByte);
  }
  Serial.println("");
  delay(2000);
}


