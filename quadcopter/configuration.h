#include<Wire.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>

const char* ssid     = "embarcados";
const char* password = "embarcados";


int vma, vmb, vmc, vmd = 0;

int x, y, j, k;

int16_t ax1,ay1,az1,Tmp,gx1,gy1,gz1;
float ax2,ay2,az2,gx2,gy2,gz2;
float gx3,gy3,gz3;

float erroX = 0;
float erroY = 0;
float erroZ = 0;


float ax, ay, az, gx, gy, gz = 0; 
float gz_ini;                   
float sp_ax, sp_ay, sp_az, sp_gx, sp_gy, sp_gz = 0;  
unsigned long t_total, t_anterior, dt = 0;

int inclinacaoMinima = 45;
int inclinacaoMaxima = 45;

float coeficientePotencia = 0;

#define MPU 0x68  //endere�o I2C do MPU6050
#define CALIB 16071.82
#define GRAVI 9.81
#define G_GAIN 0.00875

#define pma                         //define pinos dos motores
#define pmb                      
#define pmc                      
#define pmd 
                       

#define cp_acl                      //constante de proporcionalidade do acelerômetro
#define cp_gir                      //constante de proporcionalidade do giroscópio    
#define ci_acl                      //constante integrativa do acelerômetro
#define ci_gir                      //constante integratica do giroscópio
#define cd_acl                      //constante derivativa do acelerômetro
#define cd_gir                      //constante derivativa do giroscópio
