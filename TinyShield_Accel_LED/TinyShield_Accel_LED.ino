#include <Wire.h>
#include "BMA250.h"


#if defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#else
#define SerialMonitorInterface Serial
#endif
BMA250 accel;

void LedOn(int ledNum)
{
  for(int i=5;i<10;i++){
    pinMode(i, INPUT);
    digitalWrite(i, LOW);
  };
  if(ledNum<1 || ledNum>16) return;
  char highpin[16]={5,6,5,7,6,7,6,8,5,8,8,7,9,7,9,8};
  char lowpin[16]= {6,5,7,5,7,6,8,6,8,5,7,8,7,9,8,9};
  ledNum--;
  digitalWrite(highpin[ledNum],HIGH);
  digitalWrite(lowpin[ledNum],LOW);
  pinMode(highpin[ledNum],OUTPUT);
  pinMode(lowpin[ledNum],OUTPUT);
}

void setup()
{
  SerialMonitorInterface.begin(9600);
  Wire.begin();
  accel.begin(BMA250_range_2g, BMA250_update_time_64ms);//This sets up the BMA250 accelerometer

  LedOn(0);//Pass a zero to turn all LEDs off
  
}

void loop()
{  
  accel.read();//This function gets new data from the accelerometer
  SerialMonitorInterface.print("accel.X = ");
  SerialMonitorInterface.print(accel.X);
  SerialMonitorInterface.print("  ");
  SerialMonitorInterface.print("accel.Y = ");
  SerialMonitorInterface.print(accel.Y);
  SerialMonitorInterface.print("  ");
  SerialMonitorInterface.print("accel.Z = ");
  SerialMonitorInterface.print(accel.Z);
  SerialMonitorInterface.println((accel.rawTemp*0.5)+24.0,1);
   

      for(int i=1;i<16;i++){
    LedOn(i);
    delay(abs(accel.X));
  };
  for(int i=16;i>1;i--){
    LedOn(i);
    delay(abs(accel.X));
  };
  delay(64);//We'll make sure we're over the 64ms update time set on the BMA250 
}
