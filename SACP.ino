#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include <string>
#include "Application.h"

using namespace std;

Buzzer buz;
TempHum TempH;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("begin..."); 

  TempH.Initialize(); 
  buz.Initialize();

  delay(1000);
}

void loop() {
  Serial.print("Temp = "); 
  Serial.print(TempH.readTemp());
  Serial.println(" C"); 

  Serial.print("Hum = "); 
  Serial.print(TempH.readHum());
  Serial.println("%"); 

  buz.ToggleBuz();
  TempH.Update();
  
  delay(1000);
    

}
