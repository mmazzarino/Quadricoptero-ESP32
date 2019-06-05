#include<Wire.h>
#include <WiFi.h>

const char* ssid     = "embarcados";
const char* password = "embarcados";
int subir = 0;
int giro = 0;
int movX = 0;
int movY = 0;

#define MPU 0x68  //endere�o I2C do MPU6050
#define CALIB 16071.82
#define GRAVI 9.81
#define G_GAIN 0.00875
#define pma                         //define pinos dos motores
#define pmb                      
#define pmc                      
#define pmd 
                       
#define c_sub                       //botões de controle
#define c_dec                       
#define c_gir_esq                  
#define c_gir_dir                  
#define c_mov_fre                  
#define c_mov_tra                   
#define c_mov_esq                  
#define c_mov_dir
#define tempo_press
#define cp_acl                      //constante de proporcionalidade do acelerômetro
#define cp_gir                      //constante de proporcionalidade do giroscópio    
#define ci_acl                      //constante integrativa do acelerômetro
#define ci_gir                      //constante integratica do giroscópio
#define cd_acl                      //constante derivativa do acelerômetro
#define cd_gir                      //constante derivativa do giroscópio
