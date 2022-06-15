#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <ESPmDNS.h>

const char* ssid = "PeaceData";
const char* password = "yqkhr1t8aetk8o";

WebServer server(80);
uint8_t fuckerPin = 8;
bool fuckerStatus = LOW;

void fuck() {
  fuckerStatus = HIGH;
  DynamicJsonDocument doc(64);
  doc["fuck"] = true;
  String buf;
  serializeJson(doc, buf);
  server.send(200, "application/json", buf);
}

void setup() {
  Serial.begin(115200);
  pinMode(fuckerPin, OUTPUT);
  delay(1000);

  Serial.println("Connecting...");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  WiFi.begin(ssid, password);

  WiFi.setTxPower(WIFI_POWER_8_5dBm);

  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (!MDNS.begin("fucker")) {
        Serial.println("Error setting up MDNS responder!");
        while(1) {
            delay(1000);
        }
    }
  server.on("/fuck", fuck);
  server.begin();
  MDNS.addService("http", "tcp", 80);
}

void loop() {
  if(fuckerStatus)
    {
      digitalWrite(fuckerPin, HIGH);
      delay(1000);
      fuckerStatus = LOW;
      }
  else
    {digitalWrite(fuckerPin, LOW);}
  server.handleClient();
}
