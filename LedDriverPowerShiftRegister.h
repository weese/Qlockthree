/**
 * LedDriverPowerShiftRegister.h
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
#ifndef LED_DRIVER_POWER_SHIFT_REGISTER_H
#define LED_DRIVER_POWER_SHIFT_REGISTER_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "LedDriver.h"
#include "ShiftRegister.h"

class LedDriverPowerShiftRegister: public LedDriver {
public:
  LedDriverPowerShiftRegister(byte data, byte clock, byte latch, byte outputEnable);

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
    byte _outputEnable;
    ShiftRegister *_shiftRegister;
};

#endif


