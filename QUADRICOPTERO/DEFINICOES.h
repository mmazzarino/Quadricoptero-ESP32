//--------Porta do webServer-----------------
AsyncWebServer server(80);

//--------Porta do webSocket-----------------
WebSocketsServer webSocket(81);

//--------Dados da rede----------------------
const char *ssid = "embarcados";                  
const char *password = "embarcados";

//------------------Motores------------------                        
volatile int pma = 14;                     
volatile int pmb = 13;                     
volatile int pmc = 2;                    
volatile int pmd = 5;
volatile int vma = 0;
volatile int vmb = 0;
volatile int vmc = 0; 
volatile int vmd = 0; 
volatile int canalMa = 0;
volatile int canalMb = 1;
volatile int canalMc = 2;
volatile int canalMd = 3; 
volatile int resolucao = 8;
volatile int frequencia = 10000;

//------------------Joystick------------------
volatile int x = 0;
volatile int y = 0; 
volatile int j = 0; 
volatile int k = 0;  
 
//------------------Acelerômetro------------------
volatile int16_t ax1;
volatile int16_t ay1;
volatile int16_t az1;
volatile float ax2 = 0;
volatile float ay2 = 0;
volatile float az2 = 0;
volatile float ax = 0;
volatile float ay = 0;
volatile float az = 0;
volatile float ax3 = 0;
volatile float ay3 = 0;
volatile float az3 = 0;


//------------------Giroscópio------------------
volatile int16_t gx1;
volatile int16_t gy1;
volatile int16_t gz1;
volatile float gx2 = 0;
volatile float gy2 = 0;
volatile float gz2 = 0;
volatile float gx3 = 0;
volatile float gy3 = 0;
volatile float gz3 = 0;
volatile float gx = 0;
volatile float gy = 0;
volatile float gz = 0;
volatile float gz_ini = 0; 
volatile float radToDegr = 57.295795;

//------------------Termometro------------------
volatile int16_t Tmp = 0;              

//------------------SetPoints------------------
                   
volatile float sp_ax = 0; 
volatile float sp_ay = 0;  
volatile float sp_az = 0;  
volatile float sp_gx = 0; 
volatile float sp_gy = 0;  
volatile float sp_gz = 0;
volatile float potencia = 0;  

//------------------Cronometro------------------
volatile long t_total = 0;
volatile long t_anterior = 0; 
volatile long dt = 0;

//------------------Inclinação------------------
volatile int inclinacaoMinima = -30;
volatile int inclinacaoMaxima = 30;

//------------------PID------------------
volatile float ex = 0; 
volatile float ey = 0;
volatile float ez = 0;
volatile float ex_ant = 0; 
volatile float ey_ant = 0;
volatile float ez_ant = 0;
volatile float kp = 0.65;
volatile float ki = 0.003; 
volatile float kd = 0.4;
volatile float px = 0; 
volatile float py = 0;
volatile float pz = 0;
volatile float ix = 0;
volatile float iy = 0; 
volatile float iz = 0;
volatile float dx = 0; 
volatile float dy = 0;
volatile float dz = 0;
volatile float pidx = 0;
volatile float pidy = 0;
volatile float pidxAnt = 0;
volatile float pidyAnt = 0;


//------------------I2C------------------

volatile int MPU = 0x68;
volatile float CALIB = 16071.82;
volatile float GRAVI = 9.81;
volatile float AJUSTE = 1.69;
volatile float G_GAIN = 0.00875;








                       
