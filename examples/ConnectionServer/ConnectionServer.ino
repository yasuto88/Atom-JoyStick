/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#include <M5AtomS3.h>
#include <WiFi.h>
#include "WebServer.h"
#include "AtomJoyStick.h"

const char* apSSID = "M5JOY";           // Access point SSID
const char* apPassword = "";            // No password

WebServer server(80);
AtomJoyStick joystick;

void handleRoot() {
  String s = "<html><body>";
  s += "<h1>Atom JoyStick</h1>";
  s += "<p><a href=\"/values\">Read Values</a></p>";
  s += "</body></html>";
  server.send(200, "text/html", s);
}

void handleValues() {
  char buf[128];
  snprintf(buf, sizeof(buf),
           "{\"joy1_x\":%d,\"joy1_y\":%d,\"joy2_x\":%d,\"joy2_y\":%d}",
           joystick.getJoy1ADCValueX(_12bit),
           joystick.getJoy1ADCValueY(_12bit),
           joystick.getJoy2ADCValueX(_12bit),
           joystick.getJoy2ADCValueY(_12bit));
  server.send(200, "application/json", buf);
}

void setup() {
  M5.begin();
  joystick.begin(&Wire, ATOM_JOYSTICK_ADDR, 38, 39, 400000U);

  WiFi.softAP(apSSID, apPassword);
  IPAddress ip = WiFi.softAPIP();
  M5.Lcd.printf("AP: %s\nIP: %s\n", apSSID, ip.toString().c_str());

  server.on("/", handleRoot);
  server.on("/values", handleValues);
  server.begin();
}

void loop() {
  server.handleClient();
  delay(2);
}
