#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <Servo.h>
#include "website.h"
Servo steering_servo;
#include "functions.h"
// **************************** CREATE INSTANCES **************************** //
// Create Server instance
ESP8266WebServer server(80); // Use port 80 for the web server

// Create Websocket instance
WebSocketsServer webSocket = WebSocketsServer(81); // Use port 81 for the WebSocket

// Create Servo instance



// **************************** HANDLE REQUESTS TO THE ROOT PATH OF THE WEB SERVER **************************** //
// When a client connects to the server, the server sends the site content (in "website.h") to the client
// http://192.168.4.1 is connected to this access point
void handleRoot() {
  Serial.println("Connected!");
  server.send(200, "text/html", site);
}


// **************************** HANDLE WEBSOCKET EVENTS, SUCH AS CLIENT CONNECTION/DISCONNECTION, RECEIVING DATA, CALLING FUNCTIONS, ETC. **************************** //
// handle websocket for real-time events
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    // If client disconnects
    case WStype_DISCONNECTED: 
      Serial1.printf("[%u] Disconnected!\n", num);
      break;
      // If client connects
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial1.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        // send message to client
        webSocket.sendTXT(num, "Connected");
      }
      break;
    case WStype_TEXT: // Get information about how to move motor and servo motor
      {
      StaticJsonDocument<200> doc;
      deserializeJson(doc, payload);
      int motor_value = doc["y"];
      int servo_value = doc["x"];
      run_motor(motor_value);
      steer(servo_value);
      }
      break;
    case WStype_BIN:
      Serial1.printf("[%u] get binary length: %u\n", num, length);
      hexdump(payload, length);
      break;
  }
}


// **************************** START SERVER AND HOST WIFI NETWORK **************************** //
// called once when the ESP8266 is powered on or reset
void setup() {
  delay(1000);

  // Attach pin specified to Servo motor object
  steering_servo.attach(SERVO_PIN);

  // Set the analogWrite range 
  analogWriteRange(255);

  // Set pin modes
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(EN_PIN, OUTPUT);

  // Initialize the serial communication
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");

  // Set up the WiFi access point with the defined SSID and password
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Set up the server to handle HTTP requests to the root path 
  server.on("/", handleRoot);

  // Start web server
  server.begin();
  Serial.println("HTTP server started!");
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}


// **************************** LOOP TO CHECK FOR NEW USERS CONNECTING AND GETTING INSTRUCTIONS FROM REMOTE **************************** //
void loop() {
  // Handle webserver requests on Arduino
  server.handleClient();
  webSocket.loop();
}