/**
 * LedDriver.h
 * Abstrakte Klasse fuer einen LED-Treiber. Hiervon koennen andere Implementierungen
 * erben (75HC595, MAX7219, AS1130 etc.)
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.3
 * @created  18.1.2013
 * @updated  18.8.2013 
 *
 * Versionshistorie:
 * V 1.0:  - Erstellt.
 * V 1.1:  - printSignature() eingefuehrt.
 * V 1.2:  - Setzten und lesen von Pixel eingefuehrt.
 * V 1.3:  - Anpassung auf Helligkeit in Prozent.
 */
#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class LedDriver {
public:
  virtual void init();
  
  virtual void printSignature();
  
  virtual void writeScreenBufferToMatrix(word matrix[16], boolean onChange);

  virtual void setBrightness(unsigned int brightnessInPercent);
  
  virtual void setLinesToWrite(byte linesToWrite);
  
  virtual void shutDown();
  virtual void wakeUp();
  
  virtual void clearData();
  
  void    setPixelInScreenBuffer(byte x, byte y, word matrix[16]);
  boolean getPixelFromScreenBuffer(byte x, byte y, word matrix[16]);
};

#endif


