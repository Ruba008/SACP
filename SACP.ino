#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include <string>
#include "Application.h"

using namespace std;

/*Buzzer buz;
TempHum TempH;
Luminosity Lum;*/

Controller App;

void setup() {
  /*Serial.begin(115200);
  while(!Serial);
  Serial.println("begin..."); 

  TempH.Initialize(); 
  buz.Initialize();
  Lum.Initialize();

  delay(1000);*/
}

void loop() {
  /*Serial.print("Temp = "); 
  Serial.print(TempH.readTemp());
  Serial.println(" C"); 

  Serial.print("Hum = "); 
  Serial.print(TempH.readHum());
  Serial.println("%"); 

  Serial.print("Lum = "); 
  Serial.println(Lum.readLum());

  buz.ToggleBuz();
  TempH.Update();
  Lum.Update();*/

  App.Update();
  
  delay(1000);
    

}
