#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include <string>
#include "Application.h"

using namespace std;


/*
  On paramètre les valeurs des plantes en premier la température, l'humidité en % et la luminosité en lux
  On les met tel que Test[a][0] à Test[a][3] soit des valeurs supportables et Test[a][1] à Test[a][2]
sont les valeurs optimales de développement
*/
float Test[3][4]={{17.8, 23.4, 27.9, 32.8}, {20.3, 32.1, 60, 62}, {12, 543, 1000000, 1200000}};
float Cacparam[3][4]={{5, 10, 38, 43}, {40, 45, 65, 70}, {3000, 15000, 1000000, 1200000}};
//on initialise ensuite les plantes avec ces valeurs pour caractériser leur sensibilités
Plant cactus(Cacparam);
Plant Ptest(Test);

//Pour un fonctionnement optimal seul un controlleur doit s'update à la fois dans le loop
Controller App1(cactus);
Controller App(Ptest);

void setup() {
}

void loop() {
  App.Update();
  
  delay(1000);//se delay conditionne le temps d'affichage avant le défilement des valeurs sur le LCD
  //mais aussi le temps qu'on doit maintenir le bouton pour enregistrer la fin du buzzer
    

}
