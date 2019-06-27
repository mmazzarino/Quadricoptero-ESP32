#include <Wire.h>
const int MPU = 0x68;  //Endereco I2C do MPU6050
const int teste = 0x6B;
const int teste2 = 0x3B; 
uint8_t catorze = 14;
const float CALIB = 16071.82;
const float GRAVI = 9.81;
const float G_GAIN = 0.007633; //0.00875; 
unsigned long T_TOTAL = 0;          //variáveis para calcular o tempo decorrido de cada medição do MPU 
unsigned long T_ANTERIOR = 0;       
unsigned long VARIACAO_TEMPO = 0;
float Gyro_angle[2];
float Total_angle[2];
float Acceleration_angle[2];


uint16_t ax1,ay1,az1,Tmp,gx1,gy1,gz1;
float AX2,AY2,AZ2,GX2,GY2,GZ2;
float AX3,AY3,AZ3,GX3,GY3,GZ3;
float GX4,GY4,GZ4;
float radToDegr = 180/3.14;
void setup()  
{
  Serial.begin(115200);

 
  Wire.begin();
  Wire.beginTransmission(MPU);

  Wire.write(0x6B); 
 delay(3000);
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);
    delay(8000);
}
void loop()
{
  T_TOTAL = micros();
  VARIACAO_TEMPO = T_TOTAL - T_ANTERIOR;
  T_ANTERIOR = T_TOTAL;
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,6,true);  
  
  //Armazena o valor dos sensores nas variaveis correspondentes
  ax1 = Wire.read () << 8 | Wire.read ();      
  ay1 = Wire.read () << 8 | Wire.read ();  
  az1 = Wire.read () << 8 | Wire.read ();

  
  Acceleration_angle [0] = atan ((ay1 / 16384.0) / sqrt (pow ((ax1 / 16384.0), 2) + pow ((az1 / 16384.0), 2))) * radToDegr;
  Acceleration_angle [1] = atan (-1 * (ax1 / 16384.0) / sqrt (pow ((ay1 / 16384.0), 2) + pow ((az1 / 16384.0), 2))) * radToDegr;
  Wire.beginTransmission (0x68);
  Wire.write (0x43); // primeiro endereço de dados giroscópicos
  Wire.endTransmission (false);
  Wire.requestFrom (0x68,4, true);
  gx1 = Wire.read () << 8 | Wire.read ();  
  gy1 = Wire.read () << 8 | Wire.read ();  
  Gyro_angle [0] = gx1 / 131,0; 
  Gyro_angle [1] = gy1 / 131,0;
  Total_angle [0] = 0,98 * (Total_angle [0] + Gyro_angle [0] * VARIACAO_TEMPO) + 0,02 * Acceleration_angle [0];
  Total_angle [1] = 0,98 * (Total_angle [1] + Gyro_angle [1] * VARIACAO_TEMPO) + 0,02 * Acceleration_angle [1];


 Serial.print(" | GX = "); Serial.print(Total_angle [0]);
 Serial.print(" | GY = "); Serial.println(Total_angle [1]);

delay(300);
}
