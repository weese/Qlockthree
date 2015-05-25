/**
 * Settings.h
 * Die vom Benutzer getaetigten Einstellungen werden hier verwaltet
 * und im EEPROM persistiert.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.2
 * @created  23.1.2013
 * @updated  20.8.2013
 *
 * Versionshistorie:
 * V 1.0:  - Erstellt.
 * V 1.1:  - LDR-Modus aufgenommen.
 * V 1.2:  - Brightness aufgenommen.
 *         - EnableAlarm aufgenommen.
 *         - DcfSignalIsInverted aufgenommen.
 *         - TimeShift aufgenommen.
 */
#ifndef SETTINGS_H
#define SETTINGS_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Settings {
public: 
  Settings();
  
  byte getLanguage();
  void setLanguage(byte language);
  
  boolean getRenderCornersCw();
  void setRenderCornersCw(boolean cw);
  
  boolean getUseLdr();
  void setUseLdr(boolean useLdr);
  
  byte getBrightness();
  void setBrightness(byte brightness);
  
  boolean getEnableAlarm();
  void setEnableAlarm(boolean enableAlarm);
  
  boolean getDcfSignalIsInverted();
  void setDcfSignalIsInverted(boolean dcfSignalIsInverted);
  
  char getTimeShift();
  void setTimeShift(char timeShift);
  
  void loadFromEEPROM();
  void saveToEEPROM();

private:
  byte _language;
  boolean _renderCornersCw;
  boolean _use_ldr;
  byte _brightness;
  boolean _enableAlarm;
  boolean _dcfSignalIsInverted;
  char _timeShift;
};
 
#endif
 

