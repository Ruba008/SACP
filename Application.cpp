#include <Arduino.h>
#include <Wire.h>
#include "SHT31.h"
#include <math.h>
#include <string.h>
#include "rgb_lcd.h"
#include "Application.h"

using namespace std;

rgb_lcd lcd;

//SHT31 sht31 = SHT31();
Plant::Plant(){
  for (int i=0; i<4; i++){
    zoneJTemp[i] = -1;
    zoneJHum[i] = -1;
    zoneJLum[i] = -1; 
  }
}
Plant::Plant(float zones[3][4]){
  for (int i=0; i<4; i++){
    zoneJTemp[i] = zones[0][i];
    zoneJHum[i] = zones[1][i];
    zoneJLum[i] = zones[2][i]; 
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

array<float, 4> Plant::RzoneJauneHum() {
  for (int i=0; i<4; i++){
    Res[i] = zoneJHum[i]; 
  }
  return Res;
}

array<float, 4> Plant::RzoneJauneLum(){
  for (int i=0; i<4; i++){
    Res[i] = zoneJLum[i]; 
  }
  return Res;
}

array<float, 4> Plant::RzoneJauneTemp(){
  for (int i=0; i<4; i++){
    Res[i] = zoneJTemp[i];
  }
  return Res;
}

Plant & Plant::operator= (const Plant & plantEquals){
  
  for (int i=0; i<4; i++){
    (*this).zoneJTemp[i] = plantEquals.zoneJTemp[i];
    (*this).zoneJHum[i] = plantEquals.zoneJHum[i];
    (*this).zoneJLum[i] = plantEquals.zoneJLum[i]; 
  }
  return (*this);
}

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
    strcpy(data,"HELLO WORLD");
    strcpy(error,"SACP");
}
void Lcd::SetData(char *datae){
    strcpy(data,datae);
}

void Lcd::SetError(char *errore){
  strcpy(error,errore);
}

void Lcd::Update(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(data);  
  lcd.setCursor(0, 1);
  lcd.print(error);  
}

Buzzer::Buzzer(){
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

Led::Led(){
  isOn=0;
  PinLed=D5;
  pinMode(PinLed,OUTPUT);
}


void Led::ToggleLed(){
    if (isOn==0){
      digitalWrite(PinLed,HIGH);
      isOn=1;
    }
    else{
      digitalWrite(PinLed,LOW);
      isOn=0;
    }
}

void Led::LedOff(){
  digitalWrite(PinLed,LOW);
  isOn=0;
}

Button::Button(){
  isOn=0;
  PinButton=D6;
  pinMode(PinButton,INPUT);
}

int Button::Pressed(){
  isOn=digitalRead(PinButton);
  return isOn;
}

Controller::Controller(Plant plantController){
  //bool errorFlag = false;
  plantC = plantController;
  Defile=0;
  for(int i=0;i<3;i++){
    AlarmJaune[i]=false;
    AlarmRouge[i]=false;
    Arme[i]=true;
  }
  Serial.begin(115200);
  while(!Serial);
  Serial.println("begin...");
  Serial.println(plantC.RzoneJauneTemp()[0]) ;
  lcd.Initialize();
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

void Controller::verifyUrgence(int num){

  if (num==0){
    Alarm=verifyValue(plantC.RzoneJauneTemp(),tempHum.readTemp());
    strcpy(MsError[num],"Temp");
  }
  else if(num==1){
    Alarm=verifyValue(plantC.RzoneJauneHum(),tempHum.readHum());
    strcpy(MsError[num],"Hum");
  }
  else {
    Alarm=verifyValue(plantC.RzoneJauneLum(),lum.readLum());
    strcpy(MsError[num],"Lum");
  }

  if (Alarm==0){
    AlarmJaune[num]=false;
    AlarmRouge[num]=false;
    strcat(MsError[num]," Bon");
  }
  else if(Alarm>0){
    AlarmJaune[num]=true;
    AlarmRouge[num]=false;
    strcat(MsError[num]," Jaune");
  }
  else {
    AlarmRouge[num]=true;
    AlarmJaune[num]=false;
    strcat(MsError[num]," Rouge");
  }
}

void Controller::Update(){
  Defile++;
  if(Defile>2){Defile=0;}
  strcpy(MsgData[0],"Temp=");
  sprintf(Buffer,"%.2f",tempHum.readTemp());
  for(int i=0;i<5;i++){
    Value[i]=Buffer[i];
  } 
  strcat(MsgData[0],Value);
  strcat(MsgData[0],"C");

  strcpy(MsgData[1],"Hum=");
  sprintf(Buffer,"%.2f",tempHum.readHum());
  for(int i=0;i<5;i++){
    Value[i]=Buffer[i];
  } 
  strcat(MsgData[1],Value);
  strcat(MsgData[1],"%"); 

  strcpy(MsgData[2],"Lum="); 
  sprintf(Buffer,"%.2f",lum.readLum());
  for(int i=0;i<8;i++){
    Value[i]=Buffer[i];
  } 
  strcat(MsgData[2],Value);
  strcat(MsgData[2],"lux");

  verifyUrgence(Defile);

  bool AlJaune=AlarmJaune[0]||AlarmJaune[1]||AlarmJaune[2];

  if(AlJaune){
    led.ToggleLed();
  }
  else{
    led.LedOff();
  }

  if(button.Pressed()==HIGH){
    for(int j=0;j<3;j++){
      if(AlarmRouge[j]){
        Arme[j]=false;
      }
    }
  }

  bool AlRouge=(Arme[0]&&AlarmRouge[0])||(Arme[1]&&AlarmRouge[1])||(Arme[2]&&AlarmRouge[2]);

  if(AlRouge){
      buzzer.ToggleBuz();
  }
  else {
    buzzer.BuzOff();
  }

  lcd.SetData(MsgData[Defile]);
  lcd.SetError(MsError[Defile]);

  lcd.Update();
  tempHum.Update();
  lum.Update();
  //delay(1000);
}

