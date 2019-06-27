#include "BIBLIOTECAS.h"
#include "DEFINICOES.h"
#include "HTML_CSS_JS.h"
AsyncWebServer server(80);
WebSocketsServer webSocket(81);
void setup() {
  Serial.begin(115200);
  spiffsInitialize();
  //writeFile(SPIFFS, "/joy.html", joystick);
  wifiInitialize();
  startWebSocket();
  serverInitialize();
  mpu_initialize();
  read_mpu();
  getDirecaoDecolagem();
  pinsMotorsInitialize();
}

void loop() {
  tempoCiclo();
  webSocket.loop();
  setPointsPotencia(); 
  setPointsInclinacao();
  setPointsGiroZ();
  read_mpu();
  pidEixoX(); 
  pidEixoY();
  definePWM();

}

  
  
  
