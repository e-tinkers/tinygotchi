# tinyGotchi - A real Tamagotchi emulator for ATtiny3227

## Synopsis

**tinyGotchi** is based on [ArduinoGotchi](https://github.com/GaryZ88/ArduinoGotchi) created by Gary Kwok and modified/optimized to run on an ATtiny3227. **ArduinoGotchi** itself is a real [Tamagotchi P1](https://tamagotchi.fandom.com/wiki/Tamagotchi_(1996_Pet)) emulator running in Arduino UNO hardware. The emulation core is based on [TamaLib](https://github.com/jcrona/tamalib) with intensive optimization to make it fit into UNO's hardware that only comes with 32K Flash 2K RAM.

![Tamagotchi P1 Actual Devices](../main/images/TamaP1_devices.jpg)

## Fork Changes and Improvements
The repo adds a few changes and improvements over the original repo [GaryZ88/ArduinoGotchi](https://github.com/GaryZ88/ArduinoGotchi):
- `TamaRomConvert` is removed from the repo, `rom_12bit.h` is obtained from another fork [analolyc/Tamagotchi](https://github.com/anabolyc/Tamagotchi).
- [Remove several option Macros](https://github.com/e-tinkers/tinygotchi/commit/3e8c0d33c18567a59c36022a13324c0c2b89b3e8) and related codes to simplify the setup and reduce the unnecessary codes

## How to build

### Prerequisites

- **Git** - command line tool, please follows [Getting started installing Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git)
- **Arduino IDE** - [Download and Install](https://www.arduino.cc/en/software)
- **megaTinyCore Arduino Core** - [Download and Install](https://github.com/SpenceKonde/megaTinyCore/tree/master/megaavr)
- **Hardware**
  - ATtiny3227 or an [ATtiny3227 Dev Board](https://github.com/e-tinkers/attiny3217)
  - Push button x 3
  - Buzzer
  - SSD1306 I2C OLED 128x64
  - SerialUPDI Programmer - Like [tinyUPDI](https://github.com/techstudio-design/tinyUPDI) or [make one with a USB Serial Adaptor](https://github.com/SpenceKonde/AVR-Guidance/blob/master/UPDI/jtag2updi.md)
  - Custom PCB (To be develop)

### Compile and Run 
- Compose the electronic parts, please follow the circult diagram in hardware folder
- Launch Arduino IDE
- Open "tinyGotchi.ino" in the project folder
- Connect your tinyGotchi to with either via USB type-c port or 3.7V LiPo battery
- Connect SerialUPDI programmer
- Select your board
  - Main Menu -> Tools -> Board -> megaTinyCore -> ATtiny3227/...
- Install U8g2 library
  - Main Menu -> Sketch -> Include Library -> Manage Libraries
  - Search "U8g2" and install
- Select SerialUPDI programmer port
  - Main Menu -> Tools -> Ports -> <usb device for SerialUPDI programmer>
- Configure SerialUPDI
  - Main Menu -> Tools -> Programmer -> SerialUPDI: 230400 Baud
- Click the "Upload" button

### Additional notes
- To activate your pet, you have to configure the clock by pressing the middle button. Otherwise, your pet will not alive.
- The emulator will save the game status for every x mintues configured by `#define AUTO_SAVE_MINUTES x`.
- There are a few settings in the main program (**tinyGotchi.ino**) that you can adjust to fit your need:
```
/***** Tama Setting and Features *****/
#define TAMA_DISPLAY_FRAMERATE 3  // 3 is optimal for Arduino UNO
#define ENABLE_AUTO_SAVE_STATUS
#define AUTO_SAVE_MINUTES 60UL    // Auto save for every hour (to preserve EEPROM lifespan)
// #define ENABLE_LOAD_STATE_FROM_EEPROM
#define EEPROM_MAGIC_NUMBER 12
/*************************************/
```

### Hardware
to be updated

### License
ArduinoGotchi is distributed under the GPLv2 license. See the LICENSE file for more information.
