//------------------Rede------------------
const char* ssid     = "embarcados";                  
const char* password = "embarcados";

//------------------Motores------------------                        
const int pma = 14;                     
const int pmb = 13;                     
const int pmc = 2;                    
const int pmd = 5;
int vma = 0;
int vmb = 0;
int vmc = 0; 
int vmd = 0; 
const int canalMa = 0;
const int canalMb = 1;
const int canalMc = 2;
const int canalMd = 3; 

//------------------Joystick------------------
int x = 0;
int y = 0; 
int j = 0; 
int k = 0;  
 
//------------------Acelerômetro------------------
int16_t ax1;
int16_t ay1;
int16_t az1;
float ax2 = 0;
float ay2 = 0;
float az2 = 0;
float ax = 0;
float ay = 0;
float az = 0;


//------------------Giroscópio------------------
int16_t gx1;
int16_t gy1;
int16_t gz1;
float gx2 = 0;
float gy2 = 0;
float gz2 = 0;
float gx3 = 0;
float gy3 = 0;
float gz3 = 0;
float gx = 0;
float gy = 0;
float gz = 0;
float gz_ini = 0; 
const float radToDegr = 57.295795;

//------------------Termometro------------------
int16_t Tmp = 0;              

//------------------SetPoints------------------
                   
float sp_ax = 0; 
float sp_ay = 0;  
float sp_az = 0;  
float sp_gx = 0; 
float sp_gy = 0;  
float sp_gz = 0;
float potencia = 0;  

//------------------Cronometro------------------
unsigned long t_total = 0;
unsigned long t_anterior = 0; 
unsigned long dt = 0;

//------------------Inclinação------------------
const int inclinacaoMinima = -30;
const int inclinacaoMaxima = 30;

//------------------PID------------------
float ex = 0; 
float ey = 0;
float ez = 0;
float ex_ant = 0; 
float ey_ant = 0;
float ez_ant = 0;
float kp = 0.65;
float ki = 0.003; 
float kd = 0.4;
float px = 0; 
float py = 0;
float pz = 0;
float ix = 0;
float iy = 0; 
float iz = 0;
float dx = 0; 
float dy = 0;
float dz = 0;
float pidx = 0;
float pidy = 0;
float pidz = 0;

//------------------I2C------------------

#define MPU 0x68
#define CALIB 16071.82
#define GRAVI 9.81
#define G_GAIN 0.00875






                       
