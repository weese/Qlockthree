/**
 * LedDriverUeberPixel.h
 * Implementierung auf der Basis von 4 MAX7219 wie es der Ueberpixel verwendet.
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
 *         - Bennenung verbessert.
 * V 1.2:  - Anpassung auf Helligkeit 0-100%
 */
#ifndef LED_DRIVER_UEBERPIXEL_H
#define LED_DRIVER_UEBERPIXEL_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "LedControl.h"
#include "LedDriver.h"

class LedDriverUeberPixel: public LedDriver {
public:
  LedDriverUeberPixel(byte data, byte clock, byte load);

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
    
private:
  void setPixel(byte x, byte y, boolean state);

  LedControl *_ledControl;
};

#endif


