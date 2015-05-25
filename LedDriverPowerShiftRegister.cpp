/**
 * LedDriverPowerShiftRegister.cpp
 * Implementierung auf der Basis von TPICB595N.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.1
 * @created  13.8.2013
 * @updated  18.8.2013
 *
 * Versionshistorie:
 * V 1.0:  - Erstellt.
 * V 1.1:  - Anpassung auf Helligkeit 0-100%
 */
#include "LedDriverPowerShiftRegister.h"

// #define DEBUG
#include "Debug.h"

#include "Configuration.h"

/**
 * Initialisierung.
 * 
 * @param data Pin, an dem die Data-Line haengt.
 * @param clock Pin, an dem die Clock-Line haengt.
 * @param latch Pin, an dem die Latch-Line haengt.
 * @param outputEnable Pin, an dem OutputEnable haengt.
 */
LedDriverPowerShiftRegister::LedDriverPowerShiftRegister(byte data, byte clock, byte latch, byte outputEnable) {
  _outputEnable = outputEnable;
  _shiftRegister = new ShiftRegister(data, clock, latch);
}

/**
 * init() wird im Hauptprogramm in init() aufgerufen.
 * Hier sollten die LED-Treiber in eine definierten
 * Ausgangszustand gebracht werden.
 */
void LedDriverPowerShiftRegister::init() {
}

void LedDriverPowerShiftRegister::printSignature() {
  Serial.println(F("Power Shift Register (TPICB595N)"));
}

/**
 * Den Bildschirm-Puffer auf die LED-Matrix schreiben.
 * 
 * @param onChange: TRUE, wenn es Aenderungen in dem Bildschirm-Puffer gab,
 *                  FALSE, wenn es ein Refresh-Aufruf war.
 */
void LedDriverPowerShiftRegister::writeScreenBufferToMatrix(word matrix[16], boolean onChange) {
  if(onChange) {
    _shiftRegister->prepareShiftregisterWrite();
    
    // die letzten 6 Outputs sind frei - padding    
    for(byte p=0; p<6; p++) {
      _shiftRegister->shiftOutABit(false);
    }
    
    // dann Ecken...
    // unten links...
    _shiftRegister->shiftOutABit(getPixelFromScreenBuffer(11, 3, matrix));
    // unten rechts...
    _shiftRegister->shiftOutABit(getPixelFromScreenBuffer(11, 2, matrix));
    // oben rechts...
    _shiftRegister->shiftOutABit(getPixelFromScreenBuffer(11, 1, matrix));
    // oben links...    
    _shiftRegister->shiftOutABit(getPixelFromScreenBuffer(11, 0, matrix));
    
    // dann weiter...
    for(int x=10; x>=0; x--) {
      for(int y=9; y>=0; y--) {
        _shiftRegister->shiftOutABit(getPixelFromScreenBuffer(x, y, matrix));
      }
    }
    
    _shiftRegister->finishShiftregisterWrite();
  }
}

/**
 * Die Helligkeit des Displays anpassen.
 * 
 * @param brightnessInPercent Die Helligkeit.
 */
void LedDriverPowerShiftRegister::setBrightness(unsigned int brightnessInPercent) {
  _brightness = brightnessInPercent;
  byte value = map(_brightness, 0, 100, 254, 0);
  DEBUG_PRINT(F("Value = "));
  DEBUG_PRINTLN(value);
  DEBUG_FLUSH();
  analogWrite(_outputEnable, value);
}

/**
 * Anpassung der Groesse des Bildspeichers.
 * 
 * @param linesToWrite Wieviel Zeilen aus dem Bildspeicher sollen 
 *                     geschrieben werden?
 */
void LedDriverPowerShiftRegister::setLinesToWrite(byte linesToWrite) {
    _linesToWrite = linesToWrite;
}

/**
 * Das Display ausschalten.
 */
void LedDriverPowerShiftRegister::shutDown() {
  digitalWrite(_outputEnable, HIGH);
}

/**
 * Das Display einschalten.
 */
void LedDriverPowerShiftRegister::wakeUp() {
  byte value = map(_brightness, 0, 100, 254, 0);
  analogWrite(_outputEnable, value);
}

/**
 * Den Dateninhalt des LED-Treibers loeschen.
 */
void LedDriverPowerShiftRegister::clearData() {
  for(int sr=0; sr<15; sr++) {
    _shiftRegister->shiftOut(0);
  }  
}

