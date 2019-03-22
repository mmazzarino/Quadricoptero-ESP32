#include "configuration.h"
#include<Wire.h>               
#include <Servo.h>

float ax, ay, az, gx, gy, gz = 0;
float sp_ax, sp_ay, sp_az, sp_gx, sp_gy, sp_gz = 0;  //setpoints
unsigned long t_total, t_anterior, dt = 0;
Servo motor_a, motor_b, motor_c, motor_d;
int vma, vmb, vmc, vmd = 0;

void setup() {
  mpu_initialize();
  config_controles();
  motor_a.attach(pma);
  motor_b.attach(pmb);
  motor_c.attach(pmc);
  motor_d.attach(pmd);
}

void loop() {
  t_total = micros();
  dt = t_total - t_anterior;
  t_anterior = t_total;
  read_mpu(&ax, &ay, &az, &gx, &gy, &gz, &dt);
  read_controls(&vma, &vmb, &vmc, &vmd);
  controle_motores(&vma, &vmb, &vmc, &vmd);
  
