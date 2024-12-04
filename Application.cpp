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
    aread = analogRead(0); 
    Rsensor=(float)(1024-aread)*10/aread;
    lum=exp(float(aread)/75.0);
}

float Luminosity::readLum(){
    return lum;
}

void Luminosity::Update(){
    aread = analogRead(0); 
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
  PinBuzzer=3;
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

