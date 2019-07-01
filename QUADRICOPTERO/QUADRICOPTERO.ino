#include "BIBLIOTECAS.h"
#include "DEFINICOES.h"
#include "HTML_CSS_JS.h"

void setup() {
  Serial.begin(115200);
  spiffsInitialize();
  //writeFile(SPIFFS, "/joy.html", joystick);
  wifiInitialize();
  startWebSocket();
  serverInitialize();
  mpu_initialize();
  pinsMotorsInitialize();
}

void loop() {
  tempoCiclo();
  webSocket.loop();
  setPointsPotencia(); 
  setPointsInclinacao();
  read_mpu();
  pidEixoX(); 
  pidEixoY();
  definePWM();
}

  
  
  
