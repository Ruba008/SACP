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

class TempHum {
  float temp;
  float hum;

  public:

  TempHum(){}

  void Initialize(){
    sht31.begin();
    temp=sht31.getTemperature();
    hum=sht31.getHumidity();
  }

  float readTemp(){
    return temp;
  }

  float readHum(){
    return hum;
  }

  void Update(){
    temp=sht31.getTemperature();
    hum=sht31.getHumidity();
  }



};

void TempHum::Initialize(){
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
class Luminosity {

  float lum;
  float Rsensor;
  int aread;

  public:

  Luminosity(){}

  void Initialize(){
    aread = analogRead(0); 
    Rsensor=(float)(1024-aread)*10/aread;
    lum=exp(float(aread)/75.0);
  }

  float readLum(){
    return lum;
  }

  void Update(){
    aread = analogRead(0); 
    Rsensor=(float)(1024-aread)*10/aread;
    lum=exp(float(aread)/75.0);
  }
};

class Lcd{
  bool isOn=0;
  int colorR = 255;
  int colorG = 0;
  int colorB = 0;
  string data;
  string error;

  public:

  Lcd();

  void Initialize(){
    isOn=1;
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
  }

  void Update(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(data);  
    lcd.setCursor(0, 1);
    lcd.print(error);  
  }

};