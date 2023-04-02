// ArduinoJson - Version: 6.14.1
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <Servo.h>

#include "website.h"

// --------------------------- TODO ---------------------------
// Define which pins you want to use for the motor, you need at least 3 with motor driver
#define MOTOR_IN1 5
#define MOTOR_IN2 4
#define EN_PIN 2
// --------------------------- TODO ---------------------------
// Define which pins you want to use for the Servo, you need 1 
#define SERVO_PIN 12
// --------------------------- TODO ---------------------------
// Define what your SSID and Password is for your personal server! (Team name preferred :))
const char *ssid = "";
const char *password = "";

// Create Server instances
ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81); // Use port 81 for the WebSocket

// Create Servo instances
Servo steering_servo;

// handle HTTP requests to the root path ("/") of the web server
// http://192.168.4.1 is connected to this access point
void handleRoot() {
  Serial.println("Connected!");
  server.send(200, "text/html", site);
}
void run_motor(int y){
  if (y < 0){  // To run RC Car Forward
    y = map(y, -200, 0, -255, -102);
    analogWrite(EN_PIN, abs(y));
  //  --------------------------- TODO ---------------------------
  // Digital write to MOTOR_IN1 and MOTOR_IN2 pins to go forwards
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);  
  } else if (y > 0){ // To run RC Car backwards
    y = map(y, 0, 200, 102, 255);
    analogWrite(EN_PIN, abs(y));
  //  --------------------------- TODO ---------------------------
  // Digital write to MOTOR_IN1 and MOTOR_IN2 pins to go backwards
    digitalWrite(MOTOR_IN2, HIGH);
    digitalWrite(MOTOR_IN1, LOW);  
  } else if (y == 0){
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, LOW);
  }
  
}
void steer(int x){
//  --------------------------- TODO ---------------------------
// Turn x which is a number between -200 to 200 into a nubmer between 0 to 180
  x = map(x, -200, 200, 0, 180);
//  --------------------------- TODO ---------------------------
// Write to the servo motor the degrees it should be
  steering_servo.write(x);
}
// handle websocket for real-time events
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  // Handle the event here
  switch(type) {
    case WStype_DISCONNECTED: // Print message if client disconnects
      Serial1.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: // Print message if client connects
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

// called once when the ESP8266 is powered on or reset
void setup() {
  delay(1000);
  // Attach pin specified to Servo motor object
  steering_servo.attach(SERVO_PIN);
  // Init analogWrites  
  analogWriteRange(255);
  // Init pins
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(EN_PIN, OUTPUT);

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
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  // Handle webserver requests on Arduino
  server.handleClient();
  webSocket.loop();
}