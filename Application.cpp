#include <Arduino.h>
#include <Wire.h>
#include "SHT31.h"
#include <math.h>
#include <string>
#include "rgb_lcd.h"
#include "Application.h"

using namespace std;

rgb_lcd lcd;

//SHT31 sht31 = SHT31();

void TempHum::Initialize(){
    sht31 = SHT31();
    sht31.begin();
    temp=sht31.getTemperature();
    hum=sht31.getHumidity();
}

float TempHum::readTemp(){
    return temp;
}

float TempHum::readHum(){
    return hum;
}

void TempHum::Update(){
    temp=sht31.getTemperature();
    hum=sht31.getHumidity();
}


void Luminosity::Initialize(){
    aread = analogRead(A0); 
    Rsensor=(float)(1024-aread)*10/aread;
    lum=exp(float(aread)/75.0);
}

float Luminosity::readLum(){
    return lum;
}

void Luminosity::Update(){
    aread = analogRead(A0); 
    Rsensor=(float)(1024-aread)*10/aread;
    lum=exp(float(aread)/75.0);
}

void Lcd::Initialize(){
    isOn=1;
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
}

void Lcd::Update(){
  lcd.clear();
  lcd.setCursor(0, 0);
  //lcd.print(data);  
  lcd.setCursor(0, 1);
  //lcd.print(error);  
}

void Buzzer::Initialize(){
  isOn=0;
  PinBuzzer=D8;
  pinMode(PinBuzzer,OUTPUT);
}


void Buzzer::ToggleBuz(){
    if (isOn==0){
      digitalWrite(PinBuzzer,HIGH);
      isOn=1;
    }
    else{
      digitalWrite(PinBuzzer,LOW);
      isOn=0;
    }
}

void Buzzer::BuzOff(){
  digitalWrite(PinBuzzer,LOW);
  isOn=0;
}

array<float, 4> Plant::zoneJauneHum(array<float, 2> req, float zone) {
  float reqMin = req[0];
  float reqMax = req[1];
  float reqJauneMin = reqMin - reqMin*zone;
  float reqJauneMax = reqMax + reqMax*zone;
  return {reqJauneMin, reqMin, reqMax, reqJauneMax};
}

array<float, 4> Plant::zoneJauneLum(array<float, 2> req, float zone){
  float reqMin = req[0];
  float reqMax = req[1];
  float reqJauneMin = reqMin - reqMin*zone;
  float reqJauneMax = reqMax + reqMax*zone;
  return {reqJauneMin, reqMin, reqMax, reqJauneMax};
}

array<float, 4> Plant::zoneJauneTemp(array<float, 2> req, float zone){
  float reqMin = req[0];
  float reqMax = req[1];
  float reqJauneMin = reqMin - reqMin*zone;
  float reqJauneMax = reqMax + reqMax*zone;
  return {reqJauneMin, reqMin, reqMax, reqJauneMax};
}

Controller::Controller(){
  Serial.begin(115200);
  while(!Serial);
  Serial.println("begin..."); 
  
  buzzer.Initialize();
  tempHum.Initialize();
  lum.Initialize();
  
  delay(1000);
}

float Controller::verifyValue(array<float, 4> zoneJ, float value){
  float zoneBonMin = zoneJ[1];
  float zoneBonMax = zoneJ[2];

  float zoneJMin = zoneJ[0];
  float zoneJMax = zoneJ[3];

  if (value>=zoneBonMin && value<=zoneBonMax){
    return 0;
  }
  
  if (value>zoneJMin && value<zoneBonMin){
    return zoneBonMin-value;
  }

  if (value>zoneBonMax && value<zoneJMax){
    return value-zoneBonMax;
  }

  if (value<=zoneJMin){
    return -zoneBonMin+value;
  }

  if (value>=zoneJMin){
    return -value+zoneBonMax;
  }
  
  return -1;
}

void Controller::Update(){
  tempHum.Update();
  lum.Update();
}

void Controller::verifyUrgence(){

}

