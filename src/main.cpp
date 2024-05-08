/**
 *    _____                      __     _    __           __
 *   / ___/____ ___  ____ ______/ /_   | |  / /__  ____  / /_
 *   \__ \/ __ `__ \/ __ `/ ___/ __/   | | / / _ \/ __ \/ __/
 *  ___/ / / / / / / /_/ / /  / /_     | |/ /  __/ / / / /_
 * /____/_/ /_/ /_/\__,_/_/   \__/     |___/\___/_/ /_/\__/
 *
 * @file    main.cpp
 * @author  Team 8:
 *            Abdulaziz Alateeqi,
 *            Meshal Almutairi,
 *            Fawzan Alfahad,
 *            Michael Fontaine,
 *            John Michael Mertz.
 * @brief   Smart Vent capstone project source code.
 * @copyright Copyright (c) 2024
 *
 */

#include <Arduino.h>
#include <DHTesp.h>
#include <TickTwo.h>
#include <U8g2lib.h>
#include "dashboard.h"
#include "fans.h"
#include "mhz19b.h"
#include "oled.h"
#include "webserver.h"

#define OLED_SCL 22
#define OLED_SDA 23

/* global variables */
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, OLED_SCL, OLED_SDA);
extern AsyncWebServer server;  // defined in dashboard.h
WebServer webserver(&server);
MHZ19B mhz19b;

void setup() {
  Serial.begin(9600);

  init_oled();
  display_splash_screen();
  init_fans();
  webserver.init();
  mhz19b.init();
  init_dashboard();
  delay(2000);
}

void loop() {
  if (oled_enabled) {
    display_main_screen(mhz19b.get_temperature(), 0, mhz19b.get_co2());
  } else {
    u8g2.clearBuffer();
    u8g2.sendBuffer();
  }

  webserver.loop();
  mhz19b.loop();
  update_dashboard();
  // update_buttons();
}
