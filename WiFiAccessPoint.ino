#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "website.h"

// define the SSID and password for the wifi access point
const char *ssid = "RC_Car";
const char *password = "sherwin123";

// create an instance of the ESP8266WebServer and initialize it to listen on port 80
// 80 is the port used for HTTP requests
ESP8266WebServer server(80);

// handle HTTP requests to the root path ("/") of the web server
// http://192.168.4.1 is connected to this access point
void handleRoot() {
  Serial.println("Connected!");
  server.send(200, "text/html", site);
}

// called once when the ESP8266 is powered on or reset
void setup() {
  delay(1000);
  // initialize the serial communication
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");

  // set up the WiFi access point with the defined SSID and password
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // set up the server to handle HTTP requests to the root path 
  server.on("/", handleRoot);

  // start web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}