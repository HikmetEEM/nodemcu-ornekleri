#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
bool sayac1 = 0 ;
bool sayac2 = 0 ;
bool sayac3 = 0 ;
#ifndef STASSID
#define STASSID "HIKMET"
#define STAPSK  "1999_XqC_2001"
#define Led1 16
#define Led2 0
#define Led3 12
#define Buton 4
#endif

unsigned long lastTime1 = 0;
unsigned long lastTime2 = 0;
unsigned long lastTime3 = 0;
const char* ssid = STASSID;
const char* password = STAPSK;

void setup() {
  pinMode(Buton, INPUT);
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();

  }

  // Port defaults to 8266
  ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("hikmetOda");

  // No authentication by default
  ArduinoOTA.setPassword("123");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();

  if (millis() - lastTime3 > 5000)
  {
    digitalWrite(Led3, HIGH);
    sayac3 = !sayac3;


    digitalWrite(Led3, sayac3);

    lastTime3 = millis();
  }
  if (millis() - lastTime2 > 3000)
  {
    digitalWrite(Led2, HIGH);
    sayac2 = !sayac2;


    digitalWrite(Led2, sayac2);

    lastTime2 = millis();
  }
  if (millis() - lastTime1 > 1000)
  {
    digitalWrite(Led1, HIGH);
    sayac1 = !sayac1;


    digitalWrite(Led1, sayac1);

    lastTime1 = millis();
  }

}
