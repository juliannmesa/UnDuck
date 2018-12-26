/*------------------------------------------------------------------------------
  08/01/2018
  Author: Makerbro
  Platforms: ESP8266
  Language: C++/Arduino
  File: webserver_spiffs.ino
  ------------------------------------------------------------------------------
  Description: 
  Code for YouTube video demonstrating how to use the File System (SPIFFS) in 
  Flash Memory to read and write files containing HTML and JavaScript.
  https://youtu.be/pfJROpQg-Is

  Do you like my videos? You can support the channel:
  https://patreon.com/acrobotic
  https://paypal.me/acrobotic
  ------------------------------------------------------------------------------
  Please consider buying products from ACROBOTIC to help fund future
  Open-Source projects like this! We'll always put our best effort in every
  project, and release all our design files and code for you to use. 

  https://acrobotic.com/
  https://amazon.com/acrobotic
  ------------------------------------------------------------------------------
  License:
  Please see attached LICENSE.txt file for details.
------------------------------------------------------------------------------*/
#include "requests.h"
#include "message.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <DNSServer.h>

ESP8266WebServer server;
const byte DNS_PORT = 53;
DNSServer dnsServer;
uint8_t pin_led = 2; // If you are using a module, keep the value, if you are using a NodeMCU, use 16, otherwise just Google it.
char* ssid = "UnDuck"; //TODO: Config in the SPIFFS
char* password = "g3t_duck3d"; //TODO: Config in the SPIFFS
IPAddress apIP(10, 10, 10, 10);
IPAddress netMask(255, 255, 255, 0);
void setup()

{
  SPIFFS.begin();
  pinMode(pin_led, OUTPUT);
  WiFi.softAPConfig(apIP, apIP, netMask);
  WiFi.softAP(ssid,password);
  Serial.begin(115200);
  Serial.println("30*_STATUS*_ONLINE");
  server.on("/", serveIndex);
  server.on("/index.html", serveIndex);
  server.on("/console.html", serveConsole);
  server.onNotFound(serveNotFound);
  server.begin();
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", apIP);
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}

void serveFile(String path) {
  File file = SPIFFS.open(path ,"r");
  server.streamFile(file, "text/html");
  file.close();
}


void serveNotFound() {
  File file = SPIFFS.open("/notfound.html", "rr");
}

void toggleLED() {
  digitalWrite(pin_led,!digitalRead(pin_led));
}
