/*
 * ArduinoGotchi - A real Tamagotchi emulator for Arduino UNO
 *
 * Copyright (C) 2022 Gary Kwok - Arduino Uno implementation
 * Copyright (C) 2026 Henry Cheung - ATtiny3227 implementation
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <U8g2lib.h>
#include <Wire.h>
#include <EEPROM.h>
#include "tamalib.h"
#include "hw.h"
#include "bitmaps.h"
#include "hardcoded_state.h"

/***** GPIO Pin Defition *****/
#if (defined(__AVR_ATtiny3227__) || defined(__AVR_ATtiny3217__))
#define PIN_LEFT PIN_PC3
#define PIN_MIDDLE PIN_PC2
#define PIN_RIGHT PIN_PC1
#define PIN_BUZZ PIN_PA5
#elif (defined (__AVR_ATmega328P__)) // original pin definitions in ArduinoGotchi
#define PIN_LEFT 2
#define PIN_MIDDLE 3
#define PIN_RIGHT 4
#define PIN_BUZZ 9
#endif
/*****************************/

/***** U8g2 SSD1306 Library Setting *****/
#define DISPLAY_I2C_ADDRESS 0x3C
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
/****************************************/

/***** Tama Setting and Features *****/
#define TAMA_DISPLAY_FRAMERATE 3  // 3 is optimal for Arduino UNO
#define ENABLE_AUTO_SAVE_STATUS
#define AUTO_SAVE_MINUTES 60UL    // Auto save for every hour (to preserve EEPROM lifespan)
<<<<<<< HEAD
<<<<<<< HEAD
#define ENABLE_LOAD_STATE_FROM_EEPROM
/***************************/
=======
// #define ENABLE_LOAD_STATE_FROM_EEPROM
#define EEPROM_MAGIC_NUMBER 12
/*************************************/
>>>>>>> refactor

U8G2_SSD1306_128X64_NONAME_2_HW_I2C display(U8G2_R0);

/**** TamaLib Specific Variables ****/
static uint16_t current_freq = 0;
static bool_t matrix_buffer[LCD_HEIGHT][LCD_WIDTH / 8] = { { 0 } };
static bool_t icon_buffer[ICON_NUM] = { 0 };
=======
// #define ENABLE_LOAD_STATE_FROM_EEPROM
#define EEPROM_MAGIC_NUMBER 12
/*************************************/

/***** Display Constants *****/
#define MENU_ROW 49
#define MENU_PADDING 4
#define ICON_PADDING 3

U8G2_SSD1306_128X64_NONAME_2_HW_I2C display(U8G2_R0);

/**** TamaLib Specific Variables ****/
static uint16_t current_freq = 0;                                    // select buzz freq of {4096, 3279, 2731, 2341, 2048, 1638, 1365, 1170};
static bool_t matrix_buffer[LCD_HEIGHT][LCD_WIDTH / 8] = { { 0 } };  // 32 x (16/8) = 64 of original Tamagochi display buffer
static bool_t icon_buffer[ICON_NUM] = { 0 };                         // an array hold the state of which of the 8 icons is selected
>>>>>>> refactor
static cpu_state_t cpuState;
static unsigned long lastSaveTimestamp = 0;
/************************************/

static void hal_halt(void) {
  // Serial.println("Halt!");
}

static void hal_log(log_level_t level, char *buff, ...) {
<<<<<<< HEAD
<<<<<<< HEAD
  Serial.println(buff);
=======
  // Serial.println(buff);
>>>>>>> refactor
=======
  // Serial.println(buff);
>>>>>>> refactor
}

static void hal_sleep_until(timestamp_t ts) {
  //int32_t remaining = (int32_t) (ts - hal_get_timestamp());
  //if (remaining > 0) {
  //delayMicroseconds(1);
  //delay(1);
  //}
}

static timestamp_t hal_get_timestamp(void) {
  return millis() * 1000;
}

static void hal_update_screen(void) {
  displayTama();
}

static void hal_set_lcd_matrix(u8_t x, u8_t y, bool_t val) {
  uint8_t mask;
  if (val) {
    mask = 0b10000000 >> (x % 8);
    matrix_buffer[y][x / 8] = matrix_buffer[y][x / 8] | mask;
  } else {
    mask = 0b01111111;
    for (byte i = 0; i < (x % 8); i++) {
      mask = (mask >> 1) | 0b10000000;
    }
    matrix_buffer[y][x / 8] = matrix_buffer[y][x / 8] & mask;
  }
}

static void hal_set_lcd_icon(u8_t icon, bool_t val) {
  icon_buffer[icon] = val;
}

static void hal_set_frequency(u32_t freq) {
  current_freq = freq;
}

static void hal_play_frequency(bool_t en) {
  if (en) {
    tone(PIN_BUZZ, current_freq);
  } else {
    noTone(PIN_BUZZ);
  }
}

static int hal_handler(void) {
  if (digitalRead(PIN_LEFT) == LOW) {
    hw_set_button(BTN_LEFT, BTN_STATE_PRESSED);
  } else {
    hw_set_button(BTN_LEFT, BTN_STATE_RELEASED);
  }
  if (digitalRead(PIN_MIDDLE) == LOW) {
    hw_set_button(BTN_MIDDLE, BTN_STATE_PRESSED);
  } else {
    hw_set_button(BTN_MIDDLE, BTN_STATE_RELEASED);
  }
  if (digitalRead(PIN_RIGHT) == LOW) {
    hw_set_button(BTN_RIGHT, BTN_STATE_PRESSED);
  } else {
    hw_set_button(BTN_RIGHT, BTN_STATE_RELEASED);
  }

  return 0;
}

static hal_t hal = {
  .halt = &hal_halt,
  .log = &hal_log,
  .sleep_until = &hal_sleep_until,
  .get_timestamp = &hal_get_timestamp,
  .update_screen = &hal_update_screen,
  .set_lcd_matrix = &hal_set_lcd_matrix,
  .set_lcd_icon = &hal_set_lcd_icon,
  .set_frequency = &hal_set_frequency,
  .play_frequency = &hal_play_frequency,
  .handler = &hal_handler,
};

void drawTriangle(uint8_t x, uint8_t y) {
  display.drawLine(x + 1, y + 1, x + 5, y + 1);
  display.drawLine(x + 2, y + 2, x + 4, y + 2);
  display.drawLine(x + 3, y + 3, x + 3, y + 3);
}

void drawTamaRow(uint8_t tamaLCD_y, uint8_t ActualLCD_y, uint8_t thick) {
  for (uint8_t i = 0; i < LCD_WIDTH; i++) {
    uint8_t mask = 0b10000000;
    mask = mask >> (i % 8);
    if ((matrix_buffer[tamaLCD_y][i / 8] & mask) != 0) {
      display.drawBox(i + i + i + 16, ActualLCD_y, 2, thick);
    }
  }
}

<<<<<<< HEAD
void drawTamaSelection(uint8_t y) {
  uint8_t i;
  for (i = 0; i < 7; i++) {
    if (icon_buffer[i]) drawTriangle(i * 16 + 5, y);
    display.drawXBMP(i * 16 + 4, y + 6, 16, 9, bitmaps + i * 18);
  }
  if (icon_buffer[7]) {
    drawTriangle(7 * 16 + 5, y);
    display.drawXBMP(7 * 16 + 4, y + 6, 16, 9, bitmaps + 7 * 18);
  }
}

void displayTama() {
  uint8_t j;

  display.firstPage();

  for (j = 0; j < LCD_HEIGHT; j++) {
=======
void drawTamaSelection() {
  for (uint8_t icon = 0; icon <= 7; icon++) {
    if (icon_buffer[icon])
      drawTriangle(icon * 16 + MENU_PADDING, MENU_ROW);
    display.drawXBMP(icon * 16 + ICON_PADDING, MENU_ROW + 6, 16, 9, bitmaps + icon * 18);
  }
}

void displayTama() {

  display.firstPage();

  for (uint8_t j = 0; j < LCD_HEIGHT; j++) {
>>>>>>> refactor
    if (j != 5) drawTamaRow(j, j + j + j, 2);
    if (j == 5) {
      drawTamaRow(j, j + j + j, 1);
      display.nextPage();
      drawTamaRow(j, j + j + j + 1, 1);
    }
    if (j == 10) display.nextPage();
  }
  display.nextPage();
<<<<<<< HEAD
  drawTamaSelection(49);
=======
  drawTamaSelection();
>>>>>>> refactor
  display.nextPage();

}

#ifdef ENABLE_AUTO_SAVE_STATUS
void saveStateToEEPROM() {
<<<<<<< HEAD
  int i = 0;
<<<<<<< HEAD
  if (EEPROM.read(0) != 12) {
=======
  if (EEPROM.read(0) != EEPROM_MAGIC_NUMBER) {
>>>>>>> refactor
    // Clear EEPROM
    for (i = 0; i < EEPROM.length(); i++) {
=======
  if (EEPROM.read(0) != EEPROM_MAGIC_NUMBER) {
    // Clear EEPROM
    for (int i = 0; i < EEPROM.length(); i++) {
>>>>>>> refactor
      EEPROM.write(i, 0);
    }
  }
  EEPROM.update(0, EEPROM_MAGIC_NUMBER);
  cpu_get_state(&cpuState);
  EEPROM.put(1, cpuState);
<<<<<<< HEAD
  for (i = 0; i < MEMORY_SIZE; i++) {
=======
  for (int i = 0; i < MEMORY_SIZE; i++) {
>>>>>>> refactor
    EEPROM.update(1 + sizeof(cpu_state_t) + i, cpuState.memory[i]);
  }
  // Serial.println("S");
}
#endif

#ifdef ENABLE_LOAD_STATE_FROM_EEPROM
void loadStateFromEEPROM() {
  cpu_get_state(&cpuState);
  u4_t *memTemp = cpuState.memory;
  EEPROM.get(1, cpuState);
  cpu_set_state(&cpuState);
<<<<<<< HEAD
  int i = 0;
  for (i = 0; i < MEMORY_SIZE; i++) {
=======
  for (int i = 0; i < MEMORY_SIZE; i++) {
>>>>>>> refactor
    memTemp[i] = EEPROM.read(1 + sizeof(cpu_state_t) + i);
  }
  // Serial.println("L");
}
#endif

void setup() {
<<<<<<< HEAD
<<<<<<< HEAD
  Serial.begin(115200);
=======
  // Serial.begin(115200);

>>>>>>> refactor
=======
  // Serial.begin(115200);

>>>>>>> refactor
  pinMode(PIN_LEFT, INPUT_PULLUP);
  pinMode(PIN_MIDDLE, INPUT_PULLUP);
  pinMode(PIN_RIGHT, INPUT_PULLUP);
  pinMode(PIN_BUZZ, OUTPUT);

  display.setI2CAddress(DISPLAY_I2C_ADDRESS * 2);  // required if display does not use default address of 0x3C
  display.begin();                                 // initialize U8g2 graphics library for selected display module

  tamalib_register_hal(&hal);
  tamalib_set_framerate(TAMA_DISPLAY_FRAMERATE);
  tamalib_init(1000000);

#ifdef ENABLE_LOAD_STATE_FROM_EEPROM
<<<<<<< HEAD
<<<<<<< HEAD
  if (EEPROM.read(0) == 12) {
=======
  if (EEPROM.read(0) == EEPROM_MAGIC_NUMBER) {
>>>>>>> refactor
=======
  if (EEPROM.read(0) == EEPROM_MAGIC_NUMBER) {
>>>>>>> refactor
    loadStateFromEEPROM();
  }
#endif

}

void loop() {
  tamalib_mainloop_step_by_step();
#ifdef ENABLE_AUTO_SAVE_STATUS
  if ((millis() - lastSaveTimestamp) > (AUTO_SAVE_MINUTES * 60 * 1000)) {
    lastSaveTimestamp = millis();
    saveStateToEEPROM();
  }
#endif
}
