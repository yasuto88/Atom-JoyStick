#include <M5Core2.h>
#include <WiFi.h>
#include <WebServer.h>
#include "AtomJoyStick.h"

const char* apSSID = "M5CORE2_AP";
const char* apPassword = "";  // open network

AtomJoyStick joystick;
WebServer server(80);
bool ledState = false;

void handleRoot() {
  server.send(200, "text/plain", "M5Core2 joystick server");
}

void handleValues() {
  char json[160];
  snprintf(json, sizeof(json),
           "{\"joy1_x\":%u,\"joy1_y\":%u,\"joy2_x\":%u,\"joy2_y\":%u,\"btnA\":%u}",
           joystick.getJoy1ADCValueX(_12bit),
           joystick.getJoy1ADCValueY(_12bit),
           joystick.getJoy2ADCValueX(_12bit),
           joystick.getJoy2ADCValueY(_12bit),
           joystick.getButtonValue(BUTTON_A));
  server.send(200, "application/json", json);
}

void handleLed() {
  if (!server.hasArg("state")) {
    server.send(400, "text/plain", "use /led?state=on or off");
    return;
  }
  String state = server.arg("state");
  ledState = (state == "on");
  M5.Axp.SetLed(ledState);
  server.send(200, "text/plain", ledState ? "led on" : "led off");
}

void setup() {
  M5.begin();
  joystick.begin(&Wire, ATOM_JOYSTICK_ADDR, 32, 33);
  WiFi.softAP(apSSID, apPassword);
  server.on("/", handleRoot);
  server.on("/values", handleValues);
  server.on("/led", handleLed);
  server.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("AP: M5CORE2_AP");
  M5.Lcd.println("/values /led?state=on");
}

void loop() {
  server.handleClient();
}
