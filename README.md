![INSA](https://www.insa-toulouse.fr/wp-content/uploads/2023/05/Logo_INSAToulouse-quadri.png)
# SACP
#### Système d'Analyse et Contrôle de Plant.

Developpé par: DOS REIS RUBA Nathan et SANCHEZ Marc.
Institut National des Sciences Appliquées de Toulouse

## Description
Le projet est un système de contrôle et d'analyse de la santé des plantes à partir des conditions ambiantes locales, telles que la température,
l'humidité et la luminosité. Le projet a été développé en utilisant le microcontrôleur ESP8266 et il peut servir comme un prototype pour un
système utilisé dans le secteur domestique ou de production (serres).

## Composants utilisés
  1. ESP8266;
  2. USB Cable;
  3. SHT31 Sensor (temperature et huminité);  i2C1
  4. Buzzer;                                  D8
  5. Button;                                  D6
  6. Led;                                     D5
  7. LCD RGB backlight;                       i2C2
  8. Grove-Light Sensor v1.2                  A0

  ##Compilation

Pour utiliser ce code assurer vous d'avoir la bibliothèque de L'esp8266
Sinon télécharger la sur Arduino IDE
Sélectionner le NodeMCU 1.0(ESP-12)
Dans l'arduino IDE aller dans sketch->include Library-> Add .zip library
Selectionner les deux fichier zip ci-joint (la bibliothèque pour SHT31 et pour le lcd)
si vous avez respecter le branchement vous pouvez téléverser ce code dans votre contrôleur

##Plantes supportées

Cette version ne supporte que les cactus

##Utilisation

Un bouton physique permet à l’utilisateur de désactiver le buzzer en cas d’alerte. 
Cela rend le système moins intrusif tout en maintenant les indicateurs visuels.

L’utilisateur peut consulter les valeurs environnementales actuelles via le défilement
automatique sur l’écran LCD.