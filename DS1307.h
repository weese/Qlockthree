/**
 * DS1307.h
 * Klasse fuer den Zugriff auf die DS1307 Echtzeituhr.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.6
 * @created  1.3.2011
 * @updated  21.1.2013
 *
 * Versionshistorie:
 * V 1.1:  - dayOfMonth nach date umbenannt.
 * V 1.2:  - Kompatibilitaet zu Arduino-IDE 1.0 hergestellt.
 * V 1.3:  - getMinutesOfDay eingefuehrt.
 * V 1.4:  - getMinutesOf12HoursDay eingefuehrt.
 * V 1.5:  - Optimierung hinsichtlich Speicherbedarf.
 * V 1.6:  - Verbessertes Debugging.
 */
#ifndef DS1307_H
#define DS1307_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class DS1307 {
public:
  DS1307(int address, byte statusLedPin);
  
  void statusLed(boolean on);

  void readTime();
  void writeTime();

  void setSeconds(byte seconds);
  void setMinutes(byte minutes);
  void incMinutes();
  void setHours(byte hours);
  void incHours();
  void setDayOfWeek(byte dayOfWeek);
  void setDate(byte date);
  void setMonth(byte month);
  void setYear(byte year);

  byte getSeconds();
  byte getMinutes();
  unsigned int getMinutesOfDay();
  unsigned int getMinutesOf12HoursDay();
  byte getHours();
  byte getDayOfWeek();
  byte getDate();
  byte getMonth();
  byte getYear();

private:
  int _address;
  byte _statusLedPin;

  byte _seconds;
  byte _minutes;
  byte _hours;
  byte _dayOfWeek;
  byte _date;
  byte _month;
  byte _year;

  byte decToBcd(byte val);
  byte bcdToDec(byte val);   
};

#endif


