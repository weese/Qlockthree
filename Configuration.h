/**
 * Configuration.h
 * Die Compiler-Einstellungen der Firmware an einer zentralen Stelle.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.4
 * @created  23.1.2013
 * @updated  20.8.2013
 *
 * Versionshistorie:
 * V 1.0:  - Erstellt
 * V 1.1:  - ENABLE_LDR und ENABLE_DCF entfernt.
 * V 1.2:  - PWM_DURATION von 50 auf 75 erhoeht.
 * V 1.3:  - MAX_BRIGHTNESS entfernt. Der LDR kann jetzt individuell skalieren.
 *         - PWM_DURATION zurueck auf 50. 
 * V 1.4:  - ENABLE_ALARM jetzt im EEPROM.
 *         - PWM_DURATION an neue LDR-Klasse angepasst. 
 *         - DCF77_SIGNAL_IS_INVERTED jetzt im EEPROM.
 */
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

/*
 * Alarmfunktion einschalten?
 * Dazu muss ein Lautsprecher an D13 und GND und eine weitere 'Eck-LED' an die 5te Reihe.
 * Dann gibt es einen neuen Modus, direkt nach der normalen Zeitanzeige. Die neue LED
 * blinkt nach dem Moduswechsel und der Alarm ist eingeschaltet. Drueckt man jetzt M+ oder H+ stellt man
 * die Alarmzeit ein, angedeutet durch die blinkende Alarm-LED. Druckt man 10 Sekunden
 * keine Taste, hoert das Blinken auf und die normale Zeit wird wieder angezeigt.
 * Bei erreichen des Alarms piept der Lautpsrecher auf D13. Zum Ausschalten muss der
 * Modus-Taster gedrueckt werden.
 * Weiter unten kommen drei weitere DEFINEs:
 * - SPEAKER ist der Pin, an dem der Lautsprecher haengt.
 * - SPEAKER_FREQUENCY ist die Tonhoehe, wenn der Speaker ein Lautpsrecher ist.
 * - SPEAKER_IS_BUZZER: wenn einkommentiert wird davon ausgegangen, dass am Pin SPEAKER ein Buzzer haengt (Reichelt: SUMMER TDB 05).
 */
   #define SPEAKER_FREQUENCY 200000
   #define MAX_BUZZ_TIME_IN_MINUTES 10
   #define SPEAKER_IS_BUZZER 

/*
 * Die Status-LEDs koennen hier durch auskommentieren ausgeschaltet werden.
 * Default: eingeschaltet 
 */
   #define ENABLE_DCF_LED
   #define ENABLE_SQW_LED
   
/*
 * Welcher LED-Treiber soll benutzt werden?
 */
   #define LED_DRIVER_DEFAULT
// #define LED_DRIVER_UEBERPIXEL
// #define LED_DRIVER_POWER_SHIFT_REGISTER

/*
 *
 * Seltener zu aendernde Einstellungen...
 *
 */
 
// ------------------ Default Display Driver ---------------------
/*
 * Dieser Schalter erhoeht die Helligkeit bei der Verwendung des Default-LED-Treibers (Shift-Register und UDN2981A), 
 * indem er nicht beleuchtete Zeilen ueberspringt. (Tipp von Johannes)
 * Default: ausgeschaltet
 */
// #define SKIP_BLANK_LINES
/*
 * Die Zeit, die mit LDR::MAX_BRIGHTNESS multipliziert auf 
 * eine Zeile aufgeteilt wird in Mikrosekunden.
 * (default = 8)
 */
#define PWM_DURATION 8
/*
 * Dieser Schalter stellt die Anzeige auf den Kopf, falls man die Kabel beim Anoden-
 * multiplexer nicht kreuzen moechte oder es vergessen hat.
 * Default: ausgeschaltet
 */
// #define UPSIDE_DOWN
/*
 * Schnelle Datenausgabe?
 * Default: Eingeschaltet.
 */
   #define SHIFTREGISTER_TURBO
/*
 * Noch optimiertes Schreiben von 0 und FFFF?
 * Default: Ausgeschaltet
 */
   #define OPTIMIZED_FOR_DARKNESS

// ------------------ Tasten --------------------- 
/*
 * Die Zeit in Millisekunden, innerhalb derer Prellungen der Taster nicht als Druecken zaehlen.
 * (Und damit auch die Tastaturwiederholrate)
 * Default: 300
 */
  #define BUTTON_TRESHOLD 300

// ------------------ DCF77-Empfaenger ---------------------
/*
 * Fuer wieviele DCF77-Samples muessen die Zeitabstaende stimmen, damit das DCF77-Telegramm als gueltig zaehlt?
 * Default: 3 (min. 3 Minuten Synchronisationszeit).
 */
  #define DCF77HELPER_MAX_SAMPLES 3
/*
 * Bei einer Verwendung eines analogen Pins die naechsten zwei Zeilen einkommentieren.
 * Default: ausgeschaltet
 */
// #define MyDCF77_SIGNAL_IS_ANALOG
// #define MyDCF77_ANALOG_SIGNAL_TRESHOLD 600
/*
 * Die Timing-Werte fuer den DCF77-Empfaenger.
 * Default: 1700, 185, 85.
 */
  #define MYDCF77_SYNC_PAUSE_TRESHOLD 1700
  #define MYDCF77_200MS_TRESHOLD 185
  #define MYDCF77_100MS_TRESHOLD 85
/*
 * Die Telegrammlaenge.
 * Default: 59
 */
  #define MYDCF77_TELEGRAMMLAENGE 59
/*
 * Ist das Signal invertiert (z.B. ELV-Empfaenger)?
 * Default: ausgeschaltet.
 * Jetzt im EEPROM! Hier hat es keine Bedeutung mehr!
 * #define MYDCF77_SIGNAL_IS_INVERTED
 */
/*
 * Anzahl der Glaettungspunkte fuer das DCF77-Signal.
 * Default: 8
 */
  #define MYDCF77_DCF_MEAN_COUNT 8

// ------------------ Lichtabhaengiger Widerstand ---------------------
/*
 * Sollen die Grenzwerte vom LDR automatisch angepasst werden? Bei einem Neustart der QlockTwo kann
 * das Display flackern, dann muss man einmal ueber den LDR 'wischen', damit er verschiedene
 * Messwerte bekommt. Ohne AUTOSCALE werden die manuellen Min-/Max-Werte genommen.
 * Default: eingeschaltet.
 */
  #define LDR_AUTOSCALE
  #define LDR_MANUAL_MIN 0
  #define LDR_MANUAL_MAX 1023
/*
 * Die Menge der Werte fuer die Glaettung. Mehr Werte bringen bessere Ergebnisse aber
 * brauchen auch mehr Zeit (und mehr Speicher! / Gleitender Mittelwert)
 * Default: 32
 */
  #define LDR_MEAN_COUNT 32

#endif


