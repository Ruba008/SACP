#include <Arduino.h>
#include <Wire.h>
#include "SHT31.h"
#include <math.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

SHT31 sht31 = SHT31();

const int ledPin=6;                 //Connect the LED Grove module to Pin12, Digital 12
const int thresholdvalue=10;         //The threshold for which the LED should turn on. 
float Rsensor; //Resistance of sensor in K

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("begin...");  
  sht31.begin();
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
    
  lcd.setRGB(colorR, colorG, colorB);
    
  // Print a message to the LCD.
  //lcd.print("hello, world!");

  delay(1000);
}

void loop() {
  float temp = sht31.getTemperature();
  float hum = sht31.getHumidity();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp = "); 
  lcd.print(temp);
  lcd.print(" C"); //The unit for  Celsius because original arduino don't support speical symbols
  lcd.setCursor(0, 1);
  lcd.print("Hum = "); 
  lcd.print(hum);
  lcd.print("%"); 

  int sensorValue = analogRead(0); 
  Rsensor=(float)(1024-sensorValue)*10/sensorValue;

  float lux=exp(float(sensorValue)/75.0);
  //float lux=log(Rsensor);
  Serial.println("the analog read data is ");
  Serial.println(lux);
  Serial.println("the sensor resistance is ");
  Serial.println(Rsensor,DEC);//show the light intensity on the serial monitor;
  delay(1000);
  /*if (Serial.available()) {
        // wait a bit for the entire message to arrive
        delay(100);
        // clear the screen
        lcd.clear();
        // read all the available characters
        while (Serial.available() > 0) {
            // display each character to the LCD
            lcd.write(Serial.read());
        }
    }*/

}
