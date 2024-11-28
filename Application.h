/***********************
 * @file  Apllication.h
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier header de l'application
 ***********************/
#ifndef APPLICATION_H_
#define APPLICATION_H_
#include <string>
#include <array>

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
    static const float zoneJauneHum = 0.2;
    static const float zoneJauneLum = 0.2;
    static const float zoneJauneTemp = 0.2;
};
class Plant: protected plantBase{
  public :
    Plant();
    array<float, 4> zoneJauneLum(array<float, 2> req, float zone) override;
    array<float, 4> zoneJauneLum(array<float, 2> req, float zone) override;
    array<float, 4> zoneJauneLum(array<float, 2> req, float zone) override; 
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
    float readTemp();
    float readHum();
    void update();
  private:
    float hum;
    float temp;
};
class Luminosity{
  public:
    float readlum();
    void update();
  private:
    float lum;
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
    bool toggleBuz(bool isOn);
  private:
    bool isOn;
};
class Lcd{
  public:
    bool writeData(bool isOn);
  private:
    bool isOn;
};
class Button{
  public:
    void stopBuzzer();
  private:
    bool isOn;
};

//Controller
class Controller{
  public:
    void initialize();
    float verifyValue(array<float, 2> req, float value);
    void verifyUrgence();
  private:
    Led led;
    Lcd lcd;
    Button button;
    Buzzer buzzer;
    TempHum tempHum;
    Luminosity lum;
};
#endif