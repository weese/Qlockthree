/**
 * Alarm.h
 * Klasse fuer die Weckfunktion.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.0
 * @created  22.1.2013
 *
 * Versionshistorie:
 * V 1.0:  - Erstellt.
 */
#ifndef ALARM_H
#define ALARM_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "TimeStamp.h"

class Alarm {
public:
  Alarm(byte speakerPin);

  TimeStamp* getAlarmTime();

  void activate();
  void deactivate();  
  void buzz(boolean on);
  
  byte getShowAlarmTimeTimer();
  void setShowAlarmTimeTimer(byte seconds);
  void decShowAlarmTimeTimer();
  
  boolean isActive();
  
private:
  TimeStamp *_alarmTime;
  boolean    _isActive;
  byte       _showAlarmTimeTimer;
  byte       _speakerPin;
};

#endif


