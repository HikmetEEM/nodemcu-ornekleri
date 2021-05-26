#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define TRIGGERPIN D5
#define ECHOPIN    D6
#define rolePin 0

bool sanalBtn = 0;
int kilit = 0;
bool role = 1;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "OOIf08f_mrjdIzj4KQyFw9GTQiCPsRqt";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "HIKMET";
char pass[] = "1999_XqC_2001";
WidgetLCD lcd(V1);
void setup()
{
  pinMode(rolePin, OUTPUT);
 
  Serial.begin(115200);
  pinMode(TRIGGERPIN, OUTPUT);
  digitalWrite(rolePin, role);
  Blynk.begin(auth, ssid, pass);

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")

}
BLYNK_WRITE(V3)
{
  // You'll get uptime value here as result of syncAll()
  Serial.print("sanal buton: ");
  Serial.println(param.asInt());
  sanalBtn = param.asInt();
  roleKonum();
}
void roleKonum() {
  role = !role;
  digitalWrite(rolePin, role);
  Blynk.virtualWrite (V3, role);
}
void loop()
{
  lcd.clear();
  lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  long duration, distance;
  digitalWrite(TRIGGERPIN, LOW);
  delayMicroseconds(3);
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12);
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print(distance);
  Serial.println("Cm"); 
  lcd.print(7, 1, distance);

  if (distance < 15) {
    if (kilit == 0) {
      role = !role;
      kilit = 1;
    }
  } else if (kilit == 1) {
    kilit = 0;
  }
  digitalWrite(rolePin, role);

  delay (400);
}
