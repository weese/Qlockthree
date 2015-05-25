/**
 * TimeStamp.h
 * Klasse fuer die Kapselung eines Zeitstempels. Dadurch lassen sich
 * Zeiten aus der Echtzeituhr (DS1307) und von dem DCF77-Empfaenger
 * leichter verarbeiten und vergleichen.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.6
 * @created  2.3.2011
 * @updated  21.1.2013
 *
 * Versionshistorie:
 * V 1.1:  - Fehler in toString() behoben.
 * V 1.2:  - Kompatibilitaet zu Arduino-IDE 1.0 hergestellt.
 * V 1.3:  - neuer Konstruktor, neue Methoden.
 * V 1.4:  - getMinutesOf12HoursDay eingefuehrt.
 * V 1.5:  - Optimierung hinsichtlich Speicherbedarf.
 * V 1.6:  - Verbessertes Debugging & leeren Konstruktor entfernt.
 */
#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MyDCF77.h"
#include "DS1307.h"

class TimeStamp {
public:
  TimeStamp(byte minutes, byte hours, byte date, byte dayOfWeek, byte month, byte year);
  TimeStamp(MyDCF77 dcf77);
  TimeStamp(DS1307 ds1307);

  void incMinutes();
  void incHours();

  byte getMinutes();
  unsigned int getMinutesOfDay();
  unsigned int getMinutesOf12HoursDay(int minutesDiff);
  byte getHours();

  byte getDate();
  byte getDayOfWeek();
  byte getMonth();
  byte getYear();

  void setFrom(MyDCF77 dcf77);
  void setFrom(DS1307 ds1307);
  void set(byte minutes, byte hours, byte date, byte dayOfWeek, byte month, byte year);

  char* asString();

private:
  byte _minutes;
  byte _hours;

  byte _date;
  byte _dayOfWeek;
  byte _month;
  byte _year;
  
  char _cDateTime[17];
};

#endif



