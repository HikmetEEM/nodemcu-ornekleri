
#include <ESP8266httpUpdate.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#define trigger D0
#define LED D2
#define power D3
// To inject firmware info into binary file, You have to use following macro according to let
// OTAdrive to detect binary info automatically
#define ProductKey "b0610a83-1a1d-4ce5-840e-ea9b5d1ec5fe"
#define Version "1.0.0.0"
#define MakeFirmwareInfo(k, v) "&_FirmwareInfo&k=" k "&v=" v "&FirmwareInfo_&"


void doUpdate();

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Blinker version ");
  Serial.println(Version);

  pinMode(trigger, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(power, OUTPUT);
  if (digitalRead(trigger) == HIGH) {
    digitalWrite(power, HIGH);
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    wifiManager.autoConnect("CIRCUIT DIGEST WiFi Manager");
    Serial.println("connected :)");
  }

  
  // Setup LED GPIO
  pinMode(2, OUTPUT);
}

int updateCheckTimer = 0;
void loop()
{
  // Lets blink
  digitalWrite(2, 1);
  delay(50);
  digitalWrite(2, 0);
  delay(50);

  updateCheckTimer++;
  if (updateCheckTimer > 45)
  {
    updateCheckTimer = 0;
    doUpdate();
  }

  if (WiFi.status() == WL_CONNECTED)
        {
          digitalWrite(power,LOW);
          while(WiFi.status() == WL_CONNECTED){           
            digitalWrite(LED,HIGH);
            delay(500);
            digitalWrite(LED,LOW);
            delay(200);   
          }              
        }
        else {
          digitalWrite(LED,LOW);
        }
}

void doUpdate()
{
  String url = "http://otadrive.com/DeviceApi/GetEsp8266Update?";
  WiFiClient client;
  url += "&s=" + String(CHIPID);
  url += MakeFirmwareInfo(ProductKey, Version);

  Serial.println("Get firmware from url:");
  Serial.println(url);

  t_httpUpdate_return ret = ESPhttpUpdate.update(client, url, Version);
  switch (ret)
  {
    case HTTP_UPDATE_FAILED:
      Serial.println("Update faild!");
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("No new update available");
      break;
    // We can't see this, because of reset chip after update OK
    case HTTP_UPDATE_OK:
      Serial.println("Update OK");
      break;

    default:
      break;
  }
}
