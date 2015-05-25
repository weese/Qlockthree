/**
 * MyDCF77.h
 * Klasse fuer die Auswertung des DCF77-Zeitsignals.
 * Diese Klasse geht von einem 'sauberen' Signal aus.
 * Bei schlechten Empfangsbedingungen muesste man eine
 * Unschaerfe zulassen.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.7
 * @created  1.11.2011
 * @updated  20.8.2013
 *
 * Versionshistorie:
 * V 1.1:   - Fehler in der Array-Laenge und in toString() behoben.
 * V 1.1.1: - signal() public gemacht.
 * V 1.2:   - Signal geglaettet.
 * V 1.3:   - Strings in PROGMEM ausgelagert.
 * V 1.4:   - Signal kann invertiert werden (fuer manche Empfaenger noetig) - danke an Dominik.
 * V 1.5:   - Optimierung hinsichtlich Speicherbedarf.
 * V 1.6:   - Verbessertes Debugging.
 * V 1.7:   - DCF77_SIGNAL_IS_INVERTED jetzt im EEPROM.
 */
#ifndef MYDCF77_H
#define MYDCF77_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Configuration.h"

class MyDCF77 {
public:
  MyDCF77(byte signalPin, byte statusLedPin);
  
  void statusLed(boolean on);

  boolean poll(boolean signalIsInverted);

  byte getMinutes();
  byte getHours();

  byte getDate();
  byte getDayOfWeek();
  byte getMonth();
  byte getYear();

  char* asString();

  boolean signal(boolean signalIsInverted);

private:
  byte _signalPin;
  byte _statusLedPin;
  boolean _meanvalues[MYDCF77_DCF_MEAN_COUNT];
  byte _meanpointer;

  byte _minutes;
  byte _hours;

  byte _date;
  byte _dayOfWeek;
  byte _month;
  byte _year;

  char _cDateTime[17];

  byte _bits[MYDCF77_TELEGRAMMLAENGE];
  byte _bitsPointer;

  boolean decode();

  // Hilfsvariablen fuer den Zustandsautomaten
  boolean _oldSignalState;
  unsigned long _signalStartedAtMillis;
  unsigned long _signalStoppedAtMillis;
};

#endif


