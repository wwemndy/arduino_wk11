/*
 * This program runs on Arduino Uno as a I2C slave
 */

#include <Wire.h>
const int SLAVE_ADDRESS = 1;
char incomingByte = 0;

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(onRequestEvent);
}

void loop() {
  delay(2000);
}

void onRequestEvent()
{  
  Wire.write("I am from slave...");
}




