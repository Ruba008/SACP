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
    Plant(float zones[3][4]);//le constructeur à utiliser de préférance pour un lcd fonctionnel
    array<float, 4> zoneJauneLum(array<float, 2> req, float zone) override;
    array<float, 4> zoneJauneHum(array<float, 2> req, float zone) override;
    array<float, 4> zoneJauneTemp(array<float, 2> req, float zone) override;
    array<float, 4> RzoneJauneLum();//notre retour de variable pour déterminer les dépassements
    array<float, 4> RzoneJauneHum();
    array<float, 4> RzoneJauneTemp();
    Plant & operator = (const Plant & plantEquals);//on simplifie les opérateurs = pour une rédaction plus net sur controlleur
  private:
    string specie;
    string color;
    bool isDisead;
    array<float, 4> Res;
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
    TempHum();
    float readTemp();//fonction de renvoie simple
    float readHum();
    void Update();//fonction mettant à jour les valeurs de temp et Hum
  private:
    float hum;
    float temp;
    SHT31 sht31;//bibliothèque sht31
};

class Luminosity{
  public:
    Luminosity();
    float readLum();//fonction de renvoie simple
    void Update();//fonction mettant à jour les valeurs de temp et Hum
  private:
    float lum;
    float Rsensor;//calcul de la résistance observer pourraitêtre utile pour une valeur fine
    int aread;//bit mesuré
};

class Button{// le bouton est là pour désactivé le buzzer par son signal d'entrée
  public:
    Button(); 
    int Pressed();//HIGH si préssé et LOW sinon
  private:
    int isOn;
    int PinButton;//D6
};

// Acteurs
class Led{//la led sert à avertir qu'on est pas dans des conditions optimales
  public:
    Led();
    void ToggleLed();//clignote la led
    void LedOff();//forcage off de la led
  private:
    bool isOn;
    int PinLed;//D5
};

class Buzzer{//le buzzer lui est là pour signaler un danger potentiel pour la plante
  public:
    Buzzer();
    void ToggleBuz();
    void BuzOff();
  private:
    bool isOn;
    int PinBuzzer;//D8
};

class Lcd{
  public:
    Lcd();
    void SetData(char * datae);//mise des chaines de characteres du haut
    void SetError(char * errore);//celle du bas
    void Update();//on rafrechis le lcd
  private:
    bool isOn=0;
    int colorR = 255;//couleur par défaut rouge
    int colorG = 0;
    int colorB = 0;
    char data[16];//le haut de l'affichage valeur
    char error[16];//le bas donnera les erreurs
};

//Controller
class Controller{
  public:
    Controller(Plant plantController);//initialisation pour savoir à quelle plante il est relié
    float verifyValue(array<float, 4> req, float value);//on renvoie la différence pour les alerte (>0 jaune <0 rouge et =0 ok)
    void verifyUrgence(int num);//on vérifie l'urgence de chaque paramètre et instancie le mserror correspondant
    void Update();//on update tout et on tient compte des alarmes
  private:
    char MsgData[3][16];//tableau de 3 chaîne de charactère
    char MsError[3][16];
    char Buffer[255];//un buffer évitant les erreurs de segmentation lors de la conversion des float
    float Alarm;//le résultat de verify value
    char Value[8];//la valeur du float current en string
    int Defile;
    bool AlarmJaune[3];//nos trois alarmes possibles jaune et leur source se déduit du numéro du tableau
    bool AlarmRouge[3];//nos trois alarmes possibles rouge et leur source se déduit du numéro du tableau
    bool Arme[3];//un système d'armement du buzzer pour que lorsqu'on le désactive pour une cause les autres l'active toujours
    Plant plantC;//nos composants du systèmes
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