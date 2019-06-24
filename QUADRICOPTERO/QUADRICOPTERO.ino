#include "CONFIGURACAO.h"
#include "HTML_CSS_JS.h"

void setup() {
  Serial.begin(115200);
  spiffsInitialize();
  //writeFile(SPIFFS, "/joy.html", joystick);
  wifiInitialize();
  startWebSocket();
  serverInitialize();
  mpuInitialize();
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

  
  
  
