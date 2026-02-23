# tinyGotchi - A real Tamagotchi emulator for ATtiny3227

## Synopsis

**tinyGotchi** is based on [ArduinoGotchi](https://github.com/GaryZ88/ArduinoGotchi) created by Gary Kwok and modified/optimized to run on an ATtiny3227. **ArduinoGotchi** itself is a real [Tamagotchi P1](https://tamagotchi.fandom.com/wiki/Tamagotchi_(1996_Pet)) emulator running in Arduino UNO hardware. The emulation core is based on [TamaLib](https://github.com/jcrona/tamalib) with intensive optimization to make it fit into UNO's hardware that only comes with 32K Flash 2K RAM.

![Tamagotchi P1 Actual Devices](../main/images/TamaP1_devices.jpg)

## Fork Changes and Improvements
The repo adds a few changes and improvements over the original repo [GaryZ88/ArduinoGotchi](https://github.com/GaryZ88/ArduinoGotchi):
- `TamaRomConvert` is removed from the repo, `rom_12bit.h` is obtained from another fork [analolyc/Tamagotchi](https://github.com/anabolyc/Tamagotchi).
- Other changes to be updated soon.

## How to build

### Prerequisites

- **Git** - command line tool, please follows [Getting started installing Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git)
- **Arduino IDE** - [Download and Install](https://www.arduino.cc/en/software)
- **megaTinyCore Arduino Core** - [Download and Install](https://github.com/SpenceKonde/megaTinyCore/tree/master/megaavr)
- **Hardware**
  - ATtiny3227
  - Push button x 3
  - Buzzer
  - SSD1306 I2C OLED 128x64
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
/***** U8g2 SSD1306 Library Setting *****/
#define DISPLAY_I2C_ADDRESS 0x3C
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
/****************************************/

/***** Tama Setting and Features *****/
#define TAMA_DISPLAY_FRAMERATE  3   // 3 is optimal for Arduino UNO
#define ENABLE_TAMA_SOUND
#define ENABLE_AUTO_SAVE_STATUS
#define AUTO_SAVE_MINUTES 60    // Auto save for every hour (to preserve EEPROM lifespan)
#define ENABLE_LOAD_STATE_FROM_EEPROM 
//#define ENABLE_DUMP_STATE_TO_SERIAL_WHEN_START
//#define ENABLE_SERIAL_DEBUG_INPUT
//#define ENABLE_LOAD_HARCODED_STATE_WHEN_START
/***************************/
```

### Hardware
to be updated

### License
ArduinoGotchi is distributed under the GPLv2 license. See the LICENSE file for more information.
