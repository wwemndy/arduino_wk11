#include <Servo.h>
#include <Wire.h>

const int SLAVE_ADDRESS = 1;
char incomingByte = 0;
Servo myservo;

int pos = 0;    // 設定 Servo 位置的變數

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(onReceiveEvent);
  myservo.attach(9);  // 將 servo 物件連接到 pin 9
  Serial.begin(9600);
}

void loop() {
}

void onReceiveEvent(int howMany)
{
  while (Wire.available())
  {
    incomingByte = Wire.read();
    if (incomingByte == 70)
    {
      myservo.write(180);
      delay(15);
    } 
    else if (incomingByte == 82) 
    {
      myservo.write(0);
      delay(15);
    }
  }
}


