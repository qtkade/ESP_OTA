#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

#include <iostream>

#define LED 2
const char* version = "1.2";
const char* ssid = "WifiName";
const char* password = "xxxxxxxx";
const std::string firmwareUrl = std::string("http://192.168.1.107:3000/upgrade?key=123456&currentVersion=") + version;
void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH); //Truned OFF for default

  WiFi.begin(ssid, password);
  int8_t counter = 10;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf("Connecting to ssid=%s password=%s Network..\n", ssid, password);
    delay(1000);
    counter--;
    if (counter <= 0) {
      Serial.printf("Failed To Connect(%s)!\n", ssid);
      break;
    }
  }
  if (counter > 0) {
    Serial.printf("Wifi Connected To %s Successful!\nNETWORK IP:%s\n", ssid, WiFi.localIP().toString().c_str());
    OTA_Proccess();
  }
  Serial.printf("STARTED! current version=%s\n", version);
}

void OTA_Proccess() {
  Serial.println("Starting OTA update...");
  t_httpUpdate_return ret = ESPhttpUpdate.update(firmwareUrl.c_str());
  int8_t ErrorCode = ESPhttpUpdate.getLastError();
  String ErrorMsg = ESPhttpUpdate.getLastErrorString();
  switch (ret) {
    case HTTP_UPDATE_OK:
      Serial.println("Warn: You should not to see this!(Update Has Been Successfuly Finished!)");
      break;
    case HTTP_UPDATE_FAILED:
      if (ErrorCode == -106) {
        Serial.printf("Warn:You have already the lastest Version.\n");
      } else {
        Serial.printf("Warn: Update Failed! ErrorCode=%d ErrorMsg=%s\n", ErrorCode, ErrorMsg.c_str());
      }
      break;
    default:
      Serial.printf("Error: Update Failed! ErrorCode=%d ErrorMsg=%s\n", ErrorCode, ErrorMsg.c_str());
      break;
  }
}


void loop() {
  digitalWrite(LED, LOW); //on
  delay(1000);
  digitalWrite(LED, HIGH); //off
  delay(1000);
}
