/***********************
 * @file  Apllication.h
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier header de l'application
 ***********************/
#ifndef APPLICATION_H_
#define APPLICATION_H_
#include <string>
#include <array>
#include <Arduino.h>
#include <Wire.h>
#include "SHT31.h"
#include <math.h>
#include <string>
//#include "rgb_lcd.h"
#include <Arduino.h>
#include <Wire.h>
//#include "SHT31.h"
#include <math.h>
#include <string>
//#include "rgb_lcd.h"

using namespace std;
/**
  * @class Application
  * @brief Classe Application 
*/
class plantBase{
  public:
    virtual array<float, 4> zoneJauneLum(array<float, 2> req, float zone) = 0;
    virtual array<float, 4> zoneJauneHum(array<float, 2> req, float zone) = 0;
    virtual array<float, 4> zoneJauneTemp(array<float, 2> req, float zone) = 0;
  protected:
    float JauneHum = 0.2;
    float JauneLum = 0.2;
    float JauneTemp = 0.2;
};
class Plant: public plantBase{
  public :
    Plant();
    Plant(float** zones);
    array<float, 4> zoneJauneLum(array<float, 2> req, float zone) override;
    array<float, 4> zoneJauneHum(array<float, 2> req, float zone) override;
    array<float, 4> zoneJauneTemp(array<float, 2> req, float zone) override;
    Plant & operator = (const Plant & plantEquals);
  private:
    string specie;
    string color;
    bool isDisead;
    array<float, 2> reqHumidity;
    array<float, 2> reqLuminosity;
    array<float, 2> reqTemperature;
    array<float, 4> zoneJHum;
    array<float, 4> zoneJLum;
    array<float, 4> zoneJTemp;
};

// Capteurs
class TempHum {
  public:
    void Initialize(); 
    float readTemp();
    float readHum();
    void Update();
  private:
    float hum;
    float temp;
    SHT31 sht31;
};
class Luminosity{
  public:
    void Initialize(); 
    float readLum();
    void Update();
  private:
    float lum;
    float Rsensor;
    int aread;
};

// Acteurs
class Led{
  public:
    bool toggleLed(bool isOn);
  private:
    bool isOn;
};
class Buzzer{
  public:
    void Initialize();
    void ToggleBuz();
    void BuzOff();
  private:
    bool isOn;
    int PinBuzzer;
};
class Lcd{
  public:
    void Initialize(); 
    void SetData(char * datae);
    void SetError(char * errore);
    void Update();
  private:
    bool isOn=0;
    int colorR = 255;
    int colorG = 0;
    int colorB = 0;
    char data[16];
    char error[16];
};
class Button{
  public:
    Button(); 
    void stopBuzzer();
  private:
    bool isOn;
};

//Controller
class Controller{
  public:
    Controller(Plant plantController);
    float verifyValue(array<float, 4> req, float value);
    void verifyUrgence();
    void Update();
  private:
    char MsgData[3][16];
    char MsError[3][16];
    char Buffer[255];
    char Value[8];
    int Defile;
    Plant plantC;
    Led led;
    Lcd lcd;
    Button button;
    Buzzer buzzer;
    TempHum tempHum;
    Luminosity lum;
};
/*class ErrorManagement{
  private:
  string message;
  public:
  ErrorManegement(string message);
  string getMessage();
};*/
#endif