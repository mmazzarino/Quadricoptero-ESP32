#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
 
const char* ssid = "embarcados";
const char* password = "embarcados";
 
AsyncWebServer server(80);
WebSocketsServer webSocket(81);
 
void setup(){
  Serial.begin(115200);
  
  wifiInitialize();
  spiffsInitialize();
  
  
  startWebSocket();   
  serverInitialize();
}

 
void loop(){
  webSocket.loop(); 
  }
