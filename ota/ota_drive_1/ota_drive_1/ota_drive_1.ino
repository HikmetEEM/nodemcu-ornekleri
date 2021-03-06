#include <ESP8266httpUpdate.h>

// To inject firmware info into binary file, You have to use following macro according to let
// OTAdrive to detect binary info automatically
#define ProductKey "00000000-0000-0000-0000-000000000000"
#define Version "1.0.0.0"
#define MakeFirmwareInfo(k, v) "&_FirmwareInfo&k=" k "&v=" v "&FirmwareInfo_&"

char SSID[33] = "SohaDevice";
char PASS[33] = "DamkpKCk";
void doUpdate();

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Blinker version ");
  Serial.println(Version);

  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(".");
    delay(150);
  }

  Serial.print("Wifi IP:");
  Serial.println(WiFi.localIP());

  // Setup LED GPIO
  pinMode(2,OUTPUT);
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
  if(updateCheckTimer > 45)
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
