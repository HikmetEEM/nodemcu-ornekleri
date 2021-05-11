#include <ESP8266httpUpdate.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
// To inject firmware info into binary file, You have to use following macro according to let
// OTAdrive to detect binary info automatically
#define ProductKey "b96ca3d1-56c4-46b9-bc88-dcceec1d560d"
#define Version "1.0.0.3"
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
    wifiManager.autoConnect("NETHOUSE");
    Serial.println("Connected.....");
  }


  Serial.print("Wifi IP:");
  Serial.println(WiFi.localIP());

  // Setup LED GPIO
  pinMode(2, OUTPUT);

  Serial.println("calisiyor valla bak");
  doUpdate();
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

  iffsSistem();

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


void iffsSistem() {
  uint32_t realSize = ESP.getFlashChipRealSize();//iffs
  uint32_t ideSize = ESP.getFlashChipSize();//iffs
  FlashMode_t ideMode = ESP.getFlashChipMode();//iffs

  Serial.printf("Flash real id:   %08X\n", ESP.getFlashChipId());//iffs
  Serial.printf("Flash real size: %u\n\n", realSize);//iffs

  Serial.printf("Flash ide  size: %u\n", ideSize);//iffs
  Serial.printf("Flash ide speed: %u\n", ESP.getFlashChipSpeed());//iffs
  Serial.printf("Flash ide mode:  %s\n", (ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT" : ideMode == FM_DIO ? "DIO" : ideMode == FM_DOUT ? "DOUT" : "UNKNOWN"));//iffs

  if (ideSize != realSize) {
    Serial.println("Flash Chip configuration wrong!\n");//iffs
  } else {
    Serial.println("Flash Chip configuration ok.\n");//iffs
  }//iffs

  delay(500);//iffs
}
