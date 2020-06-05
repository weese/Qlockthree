# Qlockthree Setup

## General Information
- Part: Atmega328P
- Upload/debug baud rate: 115200
- Board: Arduino Uno


## Optiboot bootloader

Version used: 
- Optiboot 6.2 (optiboot_atmega328.hex) feature/bluetooth-support branch
- Commit ID: a09198fd402a01c91a0bea949bd4c0e779e85a52
- Date: Mon Dec 28 17:21:54 2015 -0800
- Speed: 115200

Set Fuses:
- (E:FD, H:DE, L:FF)
- `avrdude -p atmega328p -c avrispmkii -P usb -U lfuse:w:0xff:m -U hfuse:w:0xde:m -U efuse:w:0xFD:m`

#### Program via ISP:

`avrdude -p atmega328p -c avrispmkii -P usb -Uflash:w:optiboot_atmega328.hex`

#### Program using Makefile:

Ignore mismatching fuses/locks. Because of unused bits, avrdude gets confused

`LED=D4 ISPTOOL=avrispmkII ISPPORT="usb -V" make atmega328_isp`

## Sketch modifications for Bluetooth programming

To allow to flash a new sketch without manually resetting the board:
- make sure to use the same baud rate in your sketch that you use for your boot loader, e.g. 115200 for Optiboot 6.2
- add the following changes to your sketch:

```
// Do a manual reset, i.e. disable watchdog and interrupts, initialize stack pointer to 
// after-reset and jump to bootloader. We cannot use the watchdog for reset, as the 
// checks the reset reason and fast-starts the sketch if it was caused by watchdog.
void launchBootloader() {
    wdt_disable();
    __asm__ __volatile__ (
      "cli\n"
      "ldi r30, lo8(%[ramend])\n"
      "ldi r31, hi8(%[ramend])\n"
      "out __SP_L__, r30\n"
      "out __SP_H__, r31\n"
      "ldi r30, lo8(%[bootloader])\n"
      "ldi r31, hi8(%[bootloader])\n"
      "clr __zero_reg__\n"
      "ijmp\n"
      ::
      [ramend] "i" (RAMEND),
      [bootloader] "i" (0x7e00 >> 1)
    );
}

void loop() {
  //
  // Reset via serial command
  //
  if (Serial.available() > 0)
  {
    char cmd = Serial.read();
    if (cmd == 'R') // reboot on 'R'
    {
      launchBootloader();
    }
    if (cmd == '0')
    {
      for (int i = 0; i < 100; ++i) // repeat the check for a short peroid
      {
        if (Serial.available() > 0 && Serial.read() == ' ')
        {
          Serial.write(0x14); // reply two char to avrdude
          Serial.write(0x10); // for synchronization
          Serial.flush();     // wait the transmission
          launchBootloader();
        }
        delay(10);  // cannot repeat too fast here
      }
    }
  }

…
```

## Programming via Bluetooth

1. Get a bluetooth-to-serial adapter, e.g.:
    - Aukru HC-05 Wireless-Bluetooth-Host Serial-Transceiver-Modul Slave und Master RS232 mit 6 set kabel für Arduino
2. Program it to use:
    - 115200 baud rate
    - a proper name to identify your board
    - PIN 1234
3. Wire the adapter to board’s serial port
4. Connect with adapter, set port in Arduino IDE and select Arduino Uno board (it allows 115200 baud programming)
5. Upload sketch
