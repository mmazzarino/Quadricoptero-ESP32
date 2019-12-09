#include <Wire.h>
#include <SPIFFS.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>

const char* ssid     = "embarcados";                  
const char* password = "embarcados";


int vma, vmb, vmc, vmd = 0;                           //pwm dos motores



int x, y, j, k;                                       //coordenadas do joystick

int16_t ax1,ay1,az1,Tmp,gx1,gy1,gz1;                  
float ax2,ay2,az2,gx2,gy2,gz2;
float gx3,gy3,gz3;
float radToDegr = 180/3.141592654;

float ax, ay, az, gx, gy, gz = 0; 
float gz_ini;                   
float sp_ax, sp_ay, sp_az, sp_gx, sp_gy, sp_gz = 0;  
unsigned long t_total, t_anterior, dt = 0;

int inclinacaoMinima = -30;
int inclinacaoMaxima = 30;

float ex, ey, ez;
float ex_ant, ey_ant, ez_ant;
float kp = 0.065, ki = 0.003, kd = 0.04;
float px, py, pz = 0;
float ix, iy, iz = 0;
float dx, dy, dz = 0;
float pidx, pidy, pidz = 0;

float potencia = 0;

#define MPU 0x68  //endere�o I2C do MPU6050
#define CALIB 16071.82
#define GRAVI 9.81
#define G_GAIN 0.00875

#define pma = 14;                     
#define pmb = 13;                     
#define pmc = 2;                    
#define pmd = 5;

const int canalMa = 0;
const int canalMb = 1;
const int canalMc = 2;
const int canalMd = 3;

const int freq = 10000;

const int resolucao = 8;
                       
float Acceleration_angle[2];
float Gyro_angle[2];
float Total_angle[2];

#define cp_acl                      //constante de proporcionalidade do acelerômetro
#define cp_gir                      //constante de proporcionalidade do giroscópio    
#define ci_acl                      //constante integrativa do acelerômetro
#define ci_gir                      //constante integratica do giroscópio
#define cd_acl                      //constante derivativa do acelerômetro
#define cd_gir                      //constante derivativa do giroscópio
