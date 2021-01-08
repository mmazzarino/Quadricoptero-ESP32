//--------Definição das tarefas-----------------
TaskHandle_t TaskCorePadrao;
TaskHandle_t TaskSegundoCore;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;


//--------Porta do webServer-----------------
AsyncWebServer server(80);

//--------Porta do webSocket-----------------
WebSocketsServer webSocket(81);

//--------Dados da rede----------------------
const char *ssid = "Luciane";                  
const char *password = "celio20012000";

//------------------Joystick------------------
volatile int x = 0;
volatile int y = 0; 
volatile int j = 0; 
volatile int k = 0;  

//------------------Motores------------------
volatile int potenciaMaxima = 247;
volatile int potenciaMinima = 70;

//------------------Acelerômetro------------------
volatile int16_t ax1;
volatile int16_t ay1;
volatile int16_t az1;
volatile float ax2 = 0;
volatile float ay2 = 0;
volatile float az2 = 0;
volatile float ax3 = 0;
volatile float ay3 = 0;
volatile float az3 = 0;

//------------------Giroscópio------------------
volatile int16_t gx1;
volatile int16_t gy1;
volatile int16_t gz1;
volatile float gr_por_seg_x = 0;
volatile float gr_por_seg_y = 0;
volatile float gr_por_seg_z = 0;
volatile float gx3 = 0;
volatile float gy3 = 0;
volatile float gz3 = 0;
volatile float gx4 = 0;
volatile float gy4 = 0;
volatile float gz4 = 0;
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
volatile int potencia = 0;  

//------------------Cronometro------------------
volatile long t_total = 0;
volatile long t_anterior = 0; 
volatile long dt_micro_s = 0;
volatile double dt_mili_s = 0;
volatile double dt_s = 0;

//------------------Inclinação------------------
volatile float inclinacaoMinima = -30;//graus
volatile float inclinacaoMaxima = 30;

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


//------------------GY-91------------------

#define MPU9250_ADDRESS  0x68  // Change to 0x69 if AD0 is in high state
#define PWR_MGMT_1       0x6B
#define PWR_MGMT_2       0x6C
#define INT_PIN_CFG      0x37
#define AK8963_ADDRESS   0x0C  // MPU9250 must bypass to access the AK8963 in INT_PIN_CFG
#define AK8963_CNTL      0x0A  // Power down (0000), Continuous measurement mode 1 (0010), CMM2 (0110), Fuse ROM (1111) on bits 3:0
#define AK8963_ASAX      0x10  // Fuse ROM x-axis sensitivity adjustment value
#define ACCEL_XOUT_H     0x3B  // 1º dado
#define GYRO_CONFIG      0x1B
#define ACCEL_CONFIG     0x1C
float MagAdjustment[3] = {0, 0, 0};
volatile float CALIB = 16071.82;
volatile float GRAVI = 9.81;
volatile float AJUSTE = 1.69;
volatile float G_GAIN = 0.0164;//0.00875;

volatile float SENSE_GYRO_2000 = 0.0164;
volatile float SENSE_GYRO_1000 = 0.0328;
volatile float SENSE_GYRO_500 = 0.0655;
volatile float SENSE_GYRO_250 = 0.131;

typedef enum{
  RANGE_16G          = 0b11,
  RANGE_8G           = 0b10,
  RANGE_4G           = 0b01,
  RANGE_2G           = 0b00
} accel_range;
typedef enum{
  RANGE_GYRO_2000    = 0b11,
  RANGE_GYRO_1000    = 0b10,
  RANGE_GYRO_500     = 0b01,
  RANGE_GYRO_250     = 0b00
} gyro_range;
typedef enum{
  SCALE_14_BITS      = 0,
  SCALE_16_BITS      = 1
} mag_scale;
typedef enum{
  MAG_8_Hz           = 0,
  MAG_100_Hz         = 1
} mag_speed;

//------------------DSHOT------------------

#define pinMotor1 13
#define pinMotor2 23
#define pinMotor3 2
#define pinMotor4 4

bool setarValores = false;
bool setandoValores = false;

rmt_data_t dshotPacketMotor1[16];
rmt_data_t dshotPacketMotor2[16];
rmt_data_t dshotPacketMotor3[16];
rmt_data_t dshotPacketMotor4[16];

rmt_obj_t* remetenteMotor1 = NULL;
rmt_obj_t* remetenteMotor2 = NULL;
rmt_obj_t* remetenteMotor3 = NULL;
rmt_obj_t* remetenteMotor4 = NULL;

uint16_t dshotUserInputValue1 = 0;
uint16_t dshotUserInputValue2 = 0;
uint16_t dshotUserInputValue3 = 0;
uint16_t dshotUserInputValue4 = 0;

uint16_t antes1;
uint16_t antes2;
uint16_t antes3;
uint16_t antes4;



                       
