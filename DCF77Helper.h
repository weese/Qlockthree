/**
 * DCF77Helper.h
 * Klasse um die Qualitaet der DCF77-Samples zu verbessern. Dazu wird der Minutenabstand
 * zwischen den empfangenen DCF77-Samples mit Hilfe der DS1307 Echtzeituhr verglichen.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.7
 * @created  19.3.2011
 * @updated  21.1.2013
 *
 * Versionshistorie:
 * V 1.1:  - Fehler in der Initialisierung behoben.
 * V 1.2:  - Umstellung auf TimeStamps und Verbesserung des Plausibilitaetstests.
 * V 1.3:  - Fehler im samplesOk() behoben.
 * V 1.4:  - Kompatibilitaet zu Arduino-IDE 1.0 hergestellt.
 * V 1.5:  - Strings in PROGMEM ausgelagert.
 * V 1.6:  - Optimierung hinsichtlich Speicherbedarf.
 * V 1.7:  - Verbessertes Debugging.
 */
#ifndef DCF77HELPER_H
#define DCF77HELPER_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "DS1307.h"
#include "MyDCF77.h"
#include "TimeStamp.h"
#include "Configuration.h"

class DCF77Helper {
public:
  DCF77Helper();

  void addSample(MyDCF77 dcf77, DS1307 ds1307);
  boolean samplesOk();

private:
  byte _cursor;
  TimeStamp *_zeitstempelDcf77[DCF77HELPER_MAX_SAMPLES];
  TimeStamp *_zeitstempelRtc[DCF77HELPER_MAX_SAMPLES];
};

#endif

