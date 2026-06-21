#include <ESP8266WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID "**********"
#define WIFI_PASS "**********"
#define APP_KEY "************"
#define APP_SECRET "*********"
#define device_ID_1 "********"

// Callback function triggered when SinricPro state changes
bool onPowerState(String deviceId, bool &state) {
  if (state == true) {
    Serial.println("turn on");  // Sends 'turn on\r\n' over Serial to the Arduino
  } else {
    Serial.println("turn off"); // Sends 'turn off\r\n' over Serial to the Arduino
  }
  return true; 
}

void setupSinricPro() {
  SinricProSwitch &mySwitch = SinricPro[device_ID_1];
  mySwitch.onPowerState(onPowerState);

  SinricPro.begin(APP_KEY, APP_SECRET);
  SinricPro.restoreDeviceStates(true);
}

void setup() {
  // Serial baud rate must perfectly match the Arduino's baud rate
  Serial.begin(9600);
  
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}
