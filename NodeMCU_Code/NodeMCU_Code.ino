#include <ESP8266WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"
#include <map>

#define WIFI_SSID "iPhone 15 Pro Max"
#define WIFI_PASS "rredf8smpc"
#define APP_KEY "095a3177-edc8-424f-9773-57c186dd6554"
#define APP_SECRET "d20dce22-064f-4b9a-afa7-655eb2edbfbe-90339a18-dff7-47aa-a8f5-be252f340e4c"
#define device_ID_1 "6547763b2c602d1b7795b028"
#define RelayPin2 D2

typedef struct {
  int relayPIN;
} deviceConfig_t;


std::map<String, deviceConfig_t> devices = {
  { device_ID_1, { RelayPin2 } },
};

bool onPowerState(String deviceId, bool &state) {
  if (state == true) {
    int relayPIN = devices[deviceId].relayPIN;
    Serial.println("turn on");
    digitalWrite(RelayPin2, !state);
    return true;
  } else {
    int relayPIN = devices[deviceId].relayPIN;
    Serial.println("turn off");
    digitalWrite(RelayPin2, !state);
    return true;
  }
}

void setupSinricPro() {
  for (auto &device : devices) {
    const char *deviceId = device.first.c_str();
    SinricProSwitch &mySwitch = SinricPro[deviceId];
    mySwitch.onPowerState(onPowerState);
  }

  SinricPro.begin(APP_KEY, APP_SECRET);
  SinricPro.restoreDeviceStates(true);
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf("Connecting to %s", WIFI_SSID);
    delay(100);
  }
  Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}