#include <ESP8266WiFi.h>
#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
#define DHT11PIN 5 // DHT11PIN olarak Dijital 2"yi belirliyoruz.
const char* ssid = "Furkan Parlak";
const char* password = "RV7CUUPTJTFC";
dht11 DHT11;
WiFiServer server(80);
void setup()
{
  Serial.begin(115200); // Seri iletişimi başlatıyoruz.
  Serial.println("isi olcer test");
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop()
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {

  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request
  // Bir satır boşluk bırakıyoruz serial monitörde.
  Serial.println();
  // Sensörün okunup okunmadığını konrol ediyoruz.
  // chk 0 ise sorunsuz okunuyor demektir. Sorun yaşarsanız
  // chk değerini serial monitörde yazdırıp kontrol edebilirsiniz.
  int chk = DHT11.read(DHT11PIN);

  // Sensörden gelen verileri serial monitörde yazdırıyoruz.

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Nem (%): ");
  client.println((float)DHT11.humidity, 2);
  client.println("<br><br>");
  client.print("Sicaklik (Celcius): ");
  client.println((float)DHT11.temperature, 2);
  client.println("<br><br>");
  client.print("Sicaklik (Fahrenheit): ");
  client.println(DHT11.fahrenheit(), 2);
  client.println("<br><br>");
  client.print("Sicaklik (Kelvin): ");
  client.println(DHT11.kelvin(), 2);
  client.println("<br><br>");
  // Çiğ Oluşma Noktası, Dew Point
  client.print("Cig Olusma Noktasi: ");
  client.println(DHT11.dewPoint(), 2);

  client.println("</html>");
  Serial.println("Client disonnected");
  Serial.println("");



}
