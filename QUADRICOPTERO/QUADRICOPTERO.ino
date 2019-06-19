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
  definePWM();
  
  PIDeixoX();
  PIDeixoY();
  
  
  
  
 
  
  
 

  controle_pid_estabilidade(&ax, &ay, &az, &gx, &gy, &gz, &sp_ax, &sp_ay, &sp_az, &sp_gx, &sp_gy, &sp_gz, &vma, &vmb, &vmc, &vmd);
  controle_motores(&vma, &vmb, &vmc, &vmd);
  
  
  
