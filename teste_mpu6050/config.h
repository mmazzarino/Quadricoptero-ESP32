const int MPU = 0x68;  //Endereco I2C do MPU6050
const int teste = 0x6B;
const int teste2 = 0x3B; 
uint8_t catorze = 14;
const float CALIB = 16071.82;
const float AJUSTE = 1.69;
const float GRAVI = 9.81;
const float G_GAIN = 0.00875; 
unsigned long T_TOTAL = 0;          //variáveis para calcular o tempo decorrido de cada medição do MPU 
unsigned long T_ANTERIOR = 0;       
unsigned long VARIACAO_TEMPO = 0;

int16_t AX1,AY1,AZ1,Tmp,GX1,GY1,GZ1;
float AX2,AY2,AZ2,GX2,GY2,GZ2;
float AX3,AY3,AZ3,GX3,GY3,GZ3;
float GX4,GY4,GZ4;
