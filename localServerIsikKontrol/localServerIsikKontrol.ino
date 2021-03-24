#include <ESP8266WiFi.h>
int value[4] = {LOW,LOW,LOW,LOW};
int disko = LOW;
int i = 0;
const char* ssid = "Furkan Parlak";
const char* password = "RV7CUUPTJTFC";

int ledPin[4] = {15,13,12,14}; // GPIO13---D7 of NodeMCU
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
for(i=0;i<4;i++)
{
  pinMode(ledPin [i], OUTPUT);
  digitalWrite(ledPin[i], 1);
}
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

void loop() {
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

if(request.indexOf("/disko=on") != -1){
  digitalWrite(ledPin[0], 0);
  delay(300);
  digitalWrite(ledPin[0], 1);
  digitalWrite(ledPin[1], 0);
  delay(300);
  digitalWrite(ledPin[1], 1);
  digitalWrite(ledPin[2], 0);
  delay(300);
  digitalWrite(ledPin[2], 1);
  digitalWrite(ledPin[3], 0);
  delay(300);
  digitalWrite(ledPin[3], 1);
}


  if (request.indexOf("/LED0=ON") != -1)  {
    digitalWrite(ledPin[0], 0);
    value[0] = HIGH;
  }
  if (request.indexOf("/LED0=OFF") != -1)  {
    digitalWrite(ledPin[0], 1);
    value[0]= LOW;
  }
  if (request.indexOf("/LED1=ON") != -1)  {
    digitalWrite(ledPin[1], 0);
    value[1] = HIGH;
  }
  if (request.indexOf("/LED1=OFF") != -1)  {
    digitalWrite(ledPin[1], 1);
    value[1] = LOW;
  } if (request.indexOf("/LED2=ON") != -1)  {
    digitalWrite(ledPin[2], 0);
    value[2] = HIGH;
  }
  if (request.indexOf("/LED2=OFF") != -1)  {
    digitalWrite(ledPin[2], 1);
    value[2] = LOW;
  } if (request.indexOf("/LED3=ON") != -1)  {
    digitalWrite(ledPin[3], 0);
    value[3] = HIGH;
  }
  if (request.indexOf("/LED3=OFF") != -1)  {
    digitalWrite(ledPin[3], 1);
    value[3] = LOW;
  }

  // Set ledPin according to the request
  //digitalWrite(ledPin, value);

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  for(i=0;i<4;i++)
  {
    client.println("<br><br>");
  client.println("<a href=\"/LED");
  client.println(i);
  client.println("=ON\"\"><button>On </button></a>");
  client.println("<a href=\"/LED");
  client.println(i);
  client.println("=Off\"\"><button>Off </button></a>");
  client.println("<br><br>");
  client.print("Ledi is now: ");
  if (value[i] == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  }

  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<a href=\"/disko=on\"\"><button>disko on </button></a><br />");
  
  client.println("</html>");


  Serial.println("Client disonnected");
  Serial.println("");

}
