#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include <string>
#include "Application.h"

using namespace std;

/*Buzzer buz;
TempHum TempH;
Luminosity Lum;*/


void setup() {
  float Cacparam[3][4]={{17.8, 23.4, 27.9, 32.8}, {20.3, 32.1, 74.3, 98.3}, {12, 543, 1000000, 1200000}};
  /*Cacparam[0] = {17.8, 23.4, 27.9, 32.8};
  Cacparam[1] = {20.3, 32.1, 74.3, 98.3};
  Cacparam[2] = {12, 543, 1000000, 1200000};*/
  Plant cactus(Cacparam);
  Controller App(cactus);
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
