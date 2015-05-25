/**
 * Button.cpp
 * Kleine Klasse zum Entprellen der Tasten.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.5
 * @created  18.2.2011
 * @updated  12.2.2013
 *
 * Versionshistorie:
 * V 1.1:  - Kompatibilitaet zu Arduino-IDE 1.0 hergestellt.
 * V 1.2:  - Optimierung hinsichtlich Speicherbedarf.
 * V 1.3:  - Verbessertes Debugging.
 * V 1.4:  - Doppel-Tasten-Abfrage ermoeglicht.
 * V 1.5:  - Ueberlauf in millis() beruecksichtigt.
 */
#include "Button.h"

// #define DEBUG
#include "Debug.h"

#include "Configuration.h"

/**
 * Initialisierung mit dem Pin, an dem der Taster haengt.
 */
Button::Button(byte pin) {
  _pin1 = pin;
  _lastPressTime = 0;
  _doubleMode = false;
  pinMode(_pin1, INPUT);
}

/**
 * Initialisierung mit den zwei Pins, an denen die Taster haengen, die man gleichzeitig abfragen moechte.
 */
Button::Button(byte pin1, byte pin2) {
  _pin1 = pin1;
  _pin2 = pin2;
  _lastPressTime = 0;
  _doubleMode = true;
  pinMode(_pin1, INPUT);
  pinMode(_pin2, INPUT);
}

/**
 * Wurde der Taster gedrueckt?
 */
boolean Button::pressed() {
  boolean _retVal = false;
  
  if(millis() < _lastPressTime) {
    // wir hatten einen Ueberlauf...
    _lastPressTime = millis();
  }

  if(!_doubleMode) {
    if ((digitalRead(_pin1) == HIGH) && (_lastPressTime + BUTTON_TRESHOLD < millis())) {
      _lastPressTime = millis();
      _retVal = true;
    } 
  } else {
    if ((digitalRead(_pin1) == HIGH) && (digitalRead(_pin2) == HIGH) && (_lastPressTime + BUTTON_TRESHOLD < millis())) {
      _lastPressTime = millis();
      _retVal = true;
    } 
  }
  
  return _retVal;
}


