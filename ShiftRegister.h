/**
 * ShiftRegister
 * Mit der ShiftRegister-Klasse wird das Ausgeben der Bitmuster auf die 
 * 74HC595-Shift-Register gekapselt.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @autor    David Weese / dave.weese _AT_ gmail _DOT_ com
 * @version  2.0
 * @created  24.02.2011
 * @updated  22.11.2015
 *
 * Versionshistorie:
 * V 1.1:  - Schnelle DigitalWrite-Methoden eingefuehrt.
 *           Ueber die Definition von SHIFTREGISTER_TURBO
 *           kann es eingeschaltet werden.
 * V 1.2:  - Kompatibilitaet zu Arduino-IDE 1.0 hergestellt.
 * V 1.3:  - Optimierung hinsichtlich Speicherbedarf.
 * V 1.4:  - Verbessertes Debugging.
 * V 1.5:  - optimiertes Schreiben fuer die Faelle data==0 und data==65535.
 * V 1.6:  - shiftOutABit eiungefuehrt.
 * V 1.7:  - Unterstuetzung fuer die alte Arduino-IDE (bis 1.0.6) entfernt.
 * V 2.0:  - Rewrite. Langsame Membervariablen durch C++-Template Konstanten ersetzt für bessere Optimierung 
 *           durch Compiler. shiftOut() mittels Toggling beschleunigt. Unbenutzte Funktionen entfernt.
 */
#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

#include "Arduino.h"
#include "Configuration.h"

// #define DEBUG
#include "Debug.h"


template <uint32_t dataPin, uint32_t clockPin, uint32_t latchPin>
class ShiftRegister 
{
  public:

  /**
   * Initialisierung mit den Pins fuer Serial-Data, Serial-Clock und Store-Clock (Latch)
   */
  ShiftRegister() {
    DEBUG_PRINTLN(F("ShiftRegister initialization."));
    DEBUG_FLUSH();

    DPIN_OUTPUT(dataPin);
    DPIN_OUTPUT(clockPin);
    DPIN_OUTPUT(latchPin);
  }

  /**
   * Ein WORD (16 Bit) ausgeben
   */
  static void shiftOut(word data) {
    DPIN_LOW(dataPin);
    DPIN_LOW(clockPin);
    data ^= data << 1;
    for (byte b = 16; b; --b, data >>= 1) 
    {
      if (data & 1)
        DPIN_TOGGLE(dataPin);
      DPIN_TOGGLE(clockPin);
      DPIN_TOGGLE(clockPin);
    }
  }

  /**
   * Vorbereitung fuer die Ausgabe
   */
  static void prepareShiftregisterWrite() {
    DPIN_LOW(latchPin);
  }

  /**
   * Abschliessen der Ausgabe
   */
  static void finishShiftregisterWrite() {
    DPIN_HIGH(latchPin);
  }

};

#endif

