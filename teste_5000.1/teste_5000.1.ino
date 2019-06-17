#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
 
const char* ssid = "WAYSYSNET24G";
const char* password = "a6f7010601";
 
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
