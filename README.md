# orientation-firmware-rc-car
This is the Firmware used for the RC Car

## Setup
You will need:
#### Software
- Arduino IDE, which you can install on https://www.arduino.cc/en/software 
#### Hardware
- D1 Mini Pro 
- USB-C/Micro-USB Cable
- A Phone to connect to Websocket

## Introduction
The ESP8266 creates a Joystick website server, that allows a user to send Analog values to the ESP8266.

To do so, open the Arduino IDE and follow these steps:
1. Go to File > Preferences > Additional Board Managers URLs, and copy and paste http://arduino.esp8266.com/stable/package_esp8266com_index.json
2. Go to Tools > Board > Board Manager and search for esp8266 by ESP8266 Community. Install that package!
3. Go to Library Manager on the left hand side, and search "websockets". You should see a library called "WebSockets" by Markus Sattler. Install that!
4. Open WiFiAccessPoint.ino and select LOLIN(WEMOS) D1 mini Pro as your Microcontroller. Plug in your Microcontoller to the computer, and run the code. 
5. From there, connect to the website and watch you move the analog stick!
6. For hardware instructions follow: [some link here]
