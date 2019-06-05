#include "configuration.h"
               
float ax, ay, az, gx, gy, gz = 0;                    
float sp_ax, sp_ay, sp_az, sp_gx, sp_gy, sp_gz = 0;  //setpoints
unsigned long t_total, t_anterior, dt = 0;

int vma, vmb, vmc, vmd = 0;

void setup() {
 Serial.begin(115200); 
 pinsMotorsInitialize();
 webServerInitialize();
 mpuInitialize(); 
}

void loop() {
  t_total = micros();
  dt = t_total - t_anterior;
  t_anterior = t_total;

  comunicacaoWebServer();
  setPointsInclinacao();
  setPointsPotencia();
  
  
  read_mpu(&ax, &ay, &az, &gx, &gy, &gz, &dt);
 
  read_controls(&vma, &vmb, &vmc, &vmd, &sp_ax, &sp_ay, &sp_az, &sp_gx, &sp_gy, &sp_gz);
  controle_pid_estabilidade(&ax, &ay, &az, &gx, &gy, &gz, &sp_ax, &sp_ay, &sp_az, &sp_gx, &sp_gy, &sp_gz, &vma, &vmb, &vmc, &vmd);
  controle_motores(&vma, &vmb, &vmc, &vmd);
  
  
  
