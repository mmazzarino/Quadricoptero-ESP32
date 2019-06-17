#include "configuration.h"

void setup() {
  Serial.begin(115200); 
  spiffsInitialize();
  wifiInitialize();
  startWebSocket();
  serverInitialize();
  mpuInitialize();
  getDirecaoDecolagem(); 
  pinsMotorsInitialize();
}

void loop() {
  tempoCiclo();
  comunicacaoWebServer();
  setPointsInclinacao();
  setPointsGiroZ();
  setPointsPotencia();
  
  
  read_mpu();
 

  controle_pid_estabilidade(&ax, &ay, &az, &gx, &gy, &gz, &sp_ax, &sp_ay, &sp_az, &sp_gx, &sp_gy, &sp_gz, &vma, &vmb, &vmc, &vmd);
  controle_motores(&vma, &vmb, &vmc, &vmd);
  
  
  
