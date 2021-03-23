#include <ESP8266WiFi.h>
int value0 = LOW;
int value1 = LOW;
int value2 = LOW;
int value3 = LOW;
int disko = LOW;
const char* ssid = "Furkan Parlak";
const char* password = "RV7CUUPTJTFC";

int ledPin0 = 15; // GPIO13---D7 of NodeMCU
int ledPin1 = 13; // GPIO13---D7 of NodeMCU
int ledPin2 = 12; // GPIO13---D7 of NodeMCU
int ledPin3 = 14; // GPIO13---D7 of NodeMCU
WiFiServer server(80);

void setup() {
  Serial.begin(115200);


  pinMode(ledPin0, OUTPUT);
  digitalWrite(ledPin0, 1);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, 1);
  pinMode(ledPin3, OUTPUT);
  digitalWrite(ledPin3, 1);
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, 1);

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
  digitalWrite(ledPin0, 0);
  delay(300);
  digitalWrite(ledPin0, 1);
  digitalWrite(ledPin1, 0);
  delay(300);
  digitalWrite(ledPin1, 1);
  digitalWrite(ledPin2, 0);
  delay(300);
  digitalWrite(ledPin2, 1);
  digitalWrite(ledPin3, 0);
  delay(300);
  digitalWrite(ledPin3, 1);
}


  if (request.indexOf("/LED0=ON") != -1)  {
    digitalWrite(ledPin0, 0);
    value0 = HIGH;
  }
  if (request.indexOf("/LED0=OFF") != -1)  {
    digitalWrite(ledPin0, 1);
    value0 = LOW;
  }
  if (request.indexOf("/LED1=ON") != -1)  {
    digitalWrite(ledPin1, 0);
    value1 = HIGH;
  }
  if (request.indexOf("/LED1=OFF") != -1)  {
    digitalWrite(ledPin1, 1);
    value1 = LOW;
  } if (request.indexOf("/LED2=ON") != -1)  {
    digitalWrite(ledPin2, 0);
    value2 = HIGH;
  }
  if (request.indexOf("/LED2=OFF") != -1)  {
    digitalWrite(ledPin2, 1);
    value2 = LOW;
  } if (request.indexOf("/LED3=ON") != -1)  {
    digitalWrite(ledPin3, 0);
    value3 = HIGH;
  }
  if (request.indexOf("/LED3=OFF") != -1)  {
    digitalWrite(ledPin3, 1);
    value3 = LOW;
  }

  // Set ledPin according to the request
  //digitalWrite(ledPin, value);

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");








  client.print("Led1 is now: ");
  if (value0 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED0=ON\"\"><button>On </button></a>");
  client.println("<a href=\"/LED0=OFF\"\"><button>Off </button></a><br />");
  client.println("<br><br>");
  client.print("Led2 is now: ");
  if (value1 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED1=ON\"\"><button>On </button></a>");
  client.println("<a href=\"/LED1=OFF\"\"><button>Off </button></a><br />");
  client.println("<br><br>");

  client.print("Led3 is now: ");
  if (value2 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED2=ON\"\"><button>On </button></a>");
  client.println("<a href=\"/LED2=OFF\"\"><button>Off </button></a><br />");
  client.println("<br><br>");
  client.print("Led4 is now: ");
  if (value3 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED3=ON\"\"><button>On </button></a>");
  client.println("<a href=\"/LED3=OFF\"\"><button>Off </button></a><br />");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<a href=\"/disko=on\"\"><button>disko on </button></a><br />");
  
  client.println("</html>");


  Serial.println("Client disonnected");
  Serial.println("");

}
