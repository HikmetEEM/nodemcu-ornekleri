#include <ESP8266httpUpdate.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
// To inject firmware info into binary file, You have to use following macro according to let
// OTAdrive to detect binary info automatically
#define ProductKey "b96ca3d1-56c4-46b9-bc88-dcceec1d560d"
#define Version "1.0.0.0"
#define MakeFirmwareInfo(k, v) "&_FirmwareInfo&k=" k "&v=" v "&FirmwareInfo_&"
#define LED D2
#define power D3
void doUpdate();

void setup()
{

  pinMode(LED, OUTPUT);
  pinMode(power, OUTPUT);

  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Blinker version ");
  Serial.println(Version);

  if (WiFi.status() != WL_CONNECTED) {
    Serial.begin(115200);
    WiFiManager wifiManager;
    wifiManager.autoConnect("AutoConnectAP");
    Serial.println("Connected.....");
  }


  Serial.print("Wifi IP:");
  Serial.println(WiFi.localIP());

  // Setup LED GPIO
  pinMode(2, OUTPUT);
}

int updateCheckTimer = 0;
void loop()
{
  if (WiFi.status() == WL_CONNECTED) {
    // Lets blink
    digitalWrite(2, 1);
    delay(50);
    digitalWrite(2, 0);
    delay(50);
  }



  updateCheckTimer++;
  if (updateCheckTimer > 45)
  {
    updateCheckTimer = 0;
    doUpdate();
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
