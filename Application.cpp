#include <Arduino.h>
#include <Wire.h>
#include "SHT31.h"
#include <math.h>
#include <string>
#include "rgb_lcd.h"
#include "Application.h"

using namespace std;

rgb_lcd lcd;

SHT31 sht31 = SHT31();

TempHum::Initialize(){
    sht31.begin();
    temp=sht31.getTemperature();
    hum=sht31.getHumidity();
}

TempHum::readTemp(){
    return temp;
}

TempHum::readHum(){
    return hum;
}

TempHum::Update(){
    temp=sht31.getTemperature();
    hum=sht31.getHumidity();
}


Luminosity::Initialize(){
    aread = analogRead(0); 
    Rsensor=(float)(1024-aread)*10/aread;
    lum=exp(float(aread)/75.0);
}

Luminosity::readLum(){
    return lum;
}

Luminosity::Update(){
    aread = analogRead(0); 
    Rsensor=(float)(1024-aread)*10/aread;
    lum=exp(float(aread)/75.0);
}

Lcd::Initialize(){
    isOn=1;
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
}

Lcd::Update(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(data);  
    lcd.setCursor(0, 1);
    lcd.print(error);  
  }