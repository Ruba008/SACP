#include <Arduino.h>
#include <Wire.h>
#include "SHT31.h"
#include <math.h>
#include <string.h>
#include "rgb_lcd.h"
#include "Application.h"

using namespace std;

rgb_lcd lcd;                //renommer la bibliothèque

//SHT31 sht31 = SHT31();
Plant::Plant(){
  for (int i=0; i<4; i++){
    zoneJTemp[i] = -1;
    zoneJHum[i] = -1;
    zoneJLum[i] = -1; 
  }
}
Plant::Plant(float zones[3][4]){//Constructeur que l'on veut utiliser
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

array<float, 4> Plant::RzoneJauneHum() {    //retour des valeurs nécessaire au contrôle de l'humidité
  for (int i=0; i<4; i++){
    Res[i] = zoneJHum[i]; 
  }
  return Res;
}

array<float, 4> Plant::RzoneJauneLum(){     //retour des valeurs nécessaire au contrôle de la luminosité
  for (int i=0; i<4; i++){
    Res[i] = zoneJLum[i]; 
  }
  return Res;
}

array<float, 4> Plant::RzoneJauneTemp(){    //retour des valeurs nécessaire au contrôle de la température
  for (int i=0; i<4; i++){
    Res[i] = zoneJTemp[i];
  }
  return Res;
}

Plant & Plant::operator= (const Plant & plantEquals){//on doit changer l'opérateur = pour faire une affectation des variables de contrôle
  
  for (int i=0; i<4; i++){
    (*this).zoneJTemp[i] = plantEquals.zoneJTemp[i];
    (*this).zoneJHum[i] = plantEquals.zoneJHum[i];
    (*this).zoneJLum[i] = plantEquals.zoneJLum[i]; 
  }
  return (*this);
}

TempHum::TempHum(){//constructeur de la mesure de température et d'humidité
  sht31 = SHT31();
  sht31.begin();
  temp=sht31.getTemperature();
  hum=sht31.getHumidity();
}

float TempHum::readTemp(){// on ne met pas de get pour éviter de surcharger le processeur car on l'utilise souvent
    return temp;
}

float TempHum::readHum(){//on ne met pas de get pour éviter de surcharger le processeur car on l'utilise souvent
    return hum;
}

void TempHum::Update(){//ici on met à jour les valeurs
    temp=sht31.getTemperature();
    hum=sht31.getHumidity();
}

Luminosity::Luminosity(){
  aread = analogRead(A0); 
  Rsensor=(float)(1024-aread)*10/aread;
  lum=exp(float(aread)/75.0);//on utilise une exponentiel pour convertir notre
}

float Luminosity::readLum(){
    return lum;
}

void Luminosity::Update(){//mêm principe que le sht31
    aread = analogRead(A0); 
    Rsensor=(float)(1024-aread)*10/aread;
    lum=exp(float(aread)/75.0);
}

Lcd::Lcd(){
  isOn=1;
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  strcpy(data,"HELLO WORLD");//test si on ne rentre pas dans loop
  strcpy(error,"SACP");

}

void Lcd::SetData(char *datae){//mise à jour de data
    strcpy(data,datae);
}

void Lcd::SetError(char *errore){//mise à jour de la borne d'erreur en dessous
  strcpy(error,errore);//celle ci nous donne l'état de la variable actuel
}

void Lcd::misRGB(int R, int G, int B){
  colorR=R;
  colorG=G;
  colorB=B;
}

void Lcd::Update(){//on met notre lcd à jour
  lcd.clear();
  lcd.setRGB(colorR, colorG, colorB);
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


void Buzzer::ToggleBuz(){//on fait une alternance entre le buzzer et le silence le son est un peu plus supportable
    if (isOn==0){
      digitalWrite(PinBuzzer,HIGH);
      isOn=1;
    }
    else{
      digitalWrite(PinBuzzer,LOW);
      isOn=0;
    }
}

void Buzzer::BuzOff(){//on met le buzzer à 0 et on s'assure qu'il reste à 0
  digitalWrite(PinBuzzer,LOW);
  isOn=0;
}

Led::Led(){//la led est construite similairement au buzzer
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

Button::Button(){//le bouton est un input simple on l'utilise pour lorsque on a connaissance de l'alarme on la désactive
  isOn=0;
  PinButton=D6;
  pinMode(PinButton,INPUT);
}

int Button::Pressed(){//fonction qui renvoie HIGH si il est préssé
  isOn=digitalRead(PinButton);
  return isOn;
}

Controller::Controller(Plant plantController){
  //bool errorFlag = false;
  plantC = plantController;//on met les variables de controle
  Defile=0;//on fera défiler les variables grâce à ça
  for(int i=0;i<3;i++){//on met les tableaux d'alarme à false
    AlarmJaune[i]=false;//aucune alarme initialisé
    AlarmRouge[i]=false;
    Arme[i]=true;//on arme le buzzer
  }
  Serial.begin(115200);
  while(!Serial);
  Serial.println("begin...");
  Serial.println(plantC.RzoneJauneTemp()[0]) ;//un test qu'on a fait sur le serial pour vérifier l'opérateur égal
  
  delay(1000);
}

float Controller::verifyValue(array<float, 4> zoneJ, float value){//une vérification de la valeur on renverra une valeur négative pour les rouge et positive sur les jaunes
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

void Controller::verifyUrgence(int num){//ici on vérifira sur notre tableau d'alarme notre niveau d'urgence pour chaque paramètre

  if (num==0){
    Alarm=verifyValue(plantC.RzoneJauneTemp(),tempHum.readTemp());//le niveau de température
    strcpy(MsError[num],"Temp");//on programme l'entête de erreur
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
    AlarmJaune[num]=false;//mise à jour des alarmes selon la situation
    AlarmRouge[num]=false;
    Arme[num]=true;//on réarme le contrôleur après qu'il aurait pu être désarmer
    strcat(MsError[num]," Bon");
    lcd.misRGB(0,255,0);//on colore l'écran selon la situation
  }
  else if(Alarm>0){
    AlarmJaune[num]=true;
    AlarmRouge[num]=false;
    Arme[num]=true;
    strcat(MsError[num]," Jaune");
    lcd.misRGB(255,100,0);
  }
  else {
    AlarmRouge[num]=true;
    AlarmJaune[num]=false;
    strcat(MsError[num]," Rouge");
    lcd.misRGB(255,0,0);
  }
}

void Controller::Update(){
  Defile++;//on incrémente le défilement
  if(Defile>2){Defile=0;}//on met une remise à zero pour éviter les out of bound

  strcpy(MsgData[0],"Temp=");//on créer le message de température
  sprintf(Buffer,"%.2f",tempHum.readTemp());//notre buffer absorbe la conversion d'un float en string
  for(int i=0;i<8;i++){
    Value[i]=Buffer[i];//on met ensuite précisement le nombre de charactère qu'on veut dans value
  } 
  strcat(MsgData[0],Value);//on attache ensuite cette conversion à la fin du message avec l'unité
  strcat(MsgData[0],"C");

  strcpy(MsgData[1],"Hum=");// on fait de même pour hum et lux
  sprintf(Buffer,"%.2f",tempHum.readHum());
  for(int i=0;i<8;i++){
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

  verifyUrgence(Defile); //on effectue la mise à jour des alarmes

  bool AlJaune=AlarmJaune[0]||AlarmJaune[1]||AlarmJaune[2];
//notre variables temporaire sert à activer la ledmême si dans la variables actuel nous ne sommes pas en erreur
  if(AlJaune){
    led.ToggleLed();//led activé
  }
  else{
    led.LedOff();
  }

  if(button.Pressed()==HIGH){//pression du bouton
    for(int j=0;j<3;j++){
      if(AlarmRouge[j]){//pour toutes les alarmes rouges
        Arme[j]=false;//on enlève le buzzer de ce fait l'alarme ne sonnera plus pour ces variables
      }
    }
  }

  bool AlRouge=(Arme[0]&&AlarmRouge[0])||(Arme[1]&&AlarmRouge[1])||(Arme[2]&&AlarmRouge[2]);
//on vérifie si il ya des alarmes rouges qui ne sont pas encore signalé à l'utilisateur avec notre arme
  if(AlRouge){
      buzzer.ToggleBuz();
  }
  else {
    buzzer.BuzOff();
  }

  lcd.SetData(MsgData[Defile]);//on met les messages qu'on a constituer avant
  lcd.SetError(MsError[Defile]);

  lcd.Update();//on update tout ce qui doit l'être
  tempHum.Update();
  lum.Update();
  //delay(1000);
}

