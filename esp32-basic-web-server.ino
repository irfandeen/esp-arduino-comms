#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "my wifi";
const char* password = "my wifi password";

// Create an HTTP server object
WebServer server(80);

// Define LED pin
const int ledPin = 2; // Use the built-in LED (GPIO 2 on most ESP32 boards)

// blink
bool blink = false;
void blinker() {
  if (blink) {
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
  }
}

// Handle the /on route
void handleTurnOn() {
  blink = 0;
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/plain", "LED is ON");
}

// Handle the /off route
void handleTurnOff() {
  blink = 0;
  digitalWrite(ledPin, LOW);
  server.send(200, "text/plain", "LED is OFF");
}

// Handle root request
void handleRoot() {
  server.send(200, "text/html", "<h1>ESP32 LED Control</h1><p>Use /on to turn on the LED and /off to turn it off.</p>");
}

// Handle Blink
void handleBlink() {
  blink = 1;
  server.send(200, "text/plain", "Should be blinking...");
}

// Handle 404 (Not Found)
void handleNotFound() {
  server.send(404, "text/plain", "404: Not found");
}

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);

  // Set up LED pin as output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Turn off LED initially

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");
  Serial.println(WiFi.localIP());

  // Define server routes
  server.on("/", handleRoot);
  server.on("/on", handleTurnOn);
  server.on("/off", handleTurnOff);
  server.on("/blink", handleBlink);
  server.onNotFound(handleNotFound);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle incoming HTTP requests
  server.handleClient();
  
  // blink if needed
  blinker();
}
