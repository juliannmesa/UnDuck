#include <ESP8266WebServer.h>
#include <FS.h>

ESP8266WebServer server;

void serveFile(String path) {
  File file = SPIFFS.open(path ,"r");
  server.streamFile(file, "text/html");
  file.close();
}

void serveIndex() {serveFile("/index.html");}
void serveScripts() {serveFile("/scripts.html");}
void serveShell() {serveFile("/shell.html");}
void serveConsole() {serveFile("/console.html");}
void serveNotFound() {serveFile("/notfound.html");}
void serveStatus() {server.send(200,"text/plain", "WIP");} //TODO: status checking
void configureServer() {
  server.on("/", serveIndex);
  server.on("/index.html", serveIndex);
  server.on("/scripts.html", serveScripts);
  server.on("/shell.html", serveShell);
  server.on("/console.html", serveConsole);
  server.on("/status", serveStatus);
  server.onNotFound(serveNotFound);
}
