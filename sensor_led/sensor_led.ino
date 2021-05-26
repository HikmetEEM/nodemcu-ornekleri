#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define TRIGGERPIN D5
#define ECHOPIN    D6
#define rolePin 0

int sayac = 0;
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
  // Debug console
  Serial.begin(115200);
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  digitalWrite(rolePin, role);
  
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  // Please use timed events when LCD printintg in void loop to avoid sending too many commands
  // It will cause a FLOOD Error, and connection will be dropped
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
  
  if (distance < 15){

    sayac = sayac + 1;
  }
  if (sayac % 2 == 1) {
    digitalWrite(rolePin, HIGH);
  }
  if (sayac % 2 == 0) {
    digitalWrite(rolePin, LOW);
  }
  delay (400);
}  