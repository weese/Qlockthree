/**
 * LedDriverDefault.h
 * Implementierung auf der Basis 74HC595 und UDN2981A.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.2
 * @created  18.1.2013
 * @updated  18.8.2013
 *
 * Versionshistorie:
 * V 1.0:  - Erstellt.
 * V 1.1:  - printSignature() eingefuehrt.
 *         - Benennung verbessert.
 * V 1.2:  - Anpassung Helligkeit 0-100%
 */
#ifndef LED_DRIVER_DEFAULT_H
#define LED_DRIVER_DEFAULT_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "ShiftRegister.h"
#include "LedDriver.h"

class LedDriverDefault: public LedDriver {
public:
  LedDriverDefault(byte data, byte clock, byte latch, byte outputEnable, byte linesToWrite);

  void init();
  
  void printSignature();
  
  void writeScreenBufferToMatrix(word matrix[16], boolean onChange);

  void setBrightness(unsigned int brightnessInPercent);
  
  void setLinesToWrite(byte linesToWrite);
  
  void shutDown();
  void wakeUp();
  
  void clearData();

protected:
    unsigned int _brightness;
    
    byte _linesToWrite;

private:
    byte _outputEnablePin;
        
    ShiftRegister *_shiftRegister;
};

#endif


