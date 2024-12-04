#include <Arduino.h>
#include <Wire.h>
//#include "SHT31.h"
#include <math.h>
#include <string>
//#include "rgb_lcd.h"
#include "Application.h"

using namespace std;

/*rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

SHT31 sht31 = SHT31();*/

Buzzer a;

/*const int ledPin=6;                 //Connect the LED Grove module to Pin12, Digital 12
const int thresholdvalue=10;         //The threshold for which the LED should turn on. 
float Rsensor; //Resistance of sensor in K*/

/*class TempHum {
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

  float getLum(){
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

};*/


void setup() {
  /*Serial.begin(9600);
  while(!Serial);
  Serial.println("begin...");  
  sht31.begin();
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
    
  lcd.setRGB(colorR, colorG, colorB);*/
  a.Initialize();
    
  // Print a message to the LCD.
  //lcd.print("hello, world!");

  delay(1000);
}

void loop() {
  /*float temp = sht31.getTemperature();
  float hum = sht31.getHumidity();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp = "); 
  lcd.print(temp);
  lcd.print(" C"); 
  lcd.setCursor(0, 1);
  lcd.print("Hum = "); 
  lcd.print(hum);
  lcd.print("%"); 

  int sensorValue = analogRead(0); 
  Rsensor=(float)(1024-sensorValue)*10/sensorValue;

  float lux=exp(float(sensorValue)/75.0);*/
  a.ToggleBuz();
  //float lux=log(Rsensor);
  /*Serial.println("the analog read data is ");
  Serial.println(lux);
  Serial.println("the sensor resistance is ");
  Serial.println(Rsensor,DEC);//show the light intensity on the serial monitor;*/
  delay(5000);
    

}
