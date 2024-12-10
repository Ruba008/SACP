#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include <string>
#include "Application.h"

using namespace std;



float Test[3][4]={{17.8, 23.4, 27.9, 32.8}, {20.3, 32.1, 60, 62}, {12, 543, 1000000, 1200000}};
float Cacparam[3][4]={{5, 10, 38, 43}, {40, 45, 65, 70}, {3000, 15000, 1000000, 1200000}};
Plant cactus(Cacparam);
Plant Ptest(Test)
//Controller App(cactus);
Controller App(Ptest);

void setup() {
}

void loop() {
  App.Update();
  
  delay(1000);
    

}
