/*
 * This program runs on Linkit7697 as a I2C master
 */

#include <Wire.h>
const int SLAVE_ADDRESS = 1;

void setup() {
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write("I am from master...");
  Wire.endTransmission();
}


