#include<Wire.h>
#include "ArduinoJson-v5.13.5.h"
  
const int MPU=0x68;  //Endereco I2C do MPU6050
const float CALIB = 16071.82;
const float GRAVI = 9.81;
const float G_GAIN = 0.00875; 
unsigned long T_TOTAL = 0;          //variáveis para calcular o tempo decorrido de cada medição do MPU 
unsigned long T_ANTERIOR = 0;       
unsigned long VARIACAO_TEMPO = 0;

int16_t AX1,AY1,AZ1,Tmp,GX1,GY1,GZ1;
float AX2,AY2,AZ2,GX2,GY2,GZ2;
float AX3,AY3,AZ3,GX3,GY3,GZ3;
float GX4,GY4,GZ4;
void setup()  
{
  Serial.begin(115200);

 
  Wire.begin();
  delay(1000);
  Wire.beginTransmission(MPU);
 delay(1000);
  Wire.write(0x6B); 
   delay(1000);
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);
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
  Wire.requestFrom(MPU,14,true);  
  
  //Armazena o valor dos sensores nas variaveis correspondentes
  AX1=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AY1=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AZ1=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GX1=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GY1=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GZ1=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  AX2 = ((AX1*GRAVI)/CALIB);
  AY2 = ((AY1*GRAVI)/CALIB);
  AZ2 = ((AZ1*GRAVI)/CALIB);

  AX3 = (atan2(AX1, sqrt(pow(AY1,2) + pow(AZ1,2)))*180) / 3.14; 
  AY3 = (atan2(AY1, sqrt(pow(AX1,2) + pow(AZ1,2)))*180) / 3.14; 
  AZ3 = (atan2(AZ1, sqrt(pow(AX1,2) + pow(AY1,2)))*180) / 3.14; 

  GX2 = GX1 * G_GAIN; 
  GY2 = GY1 * G_GAIN; 
  GZ2 = GZ1 * G_GAIN; 

  GX3 = GX3 + (GX2 * VARIACAO_TEMPO);
  GY3 = GY3 + (GY2 * VARIACAO_TEMPO);
  GZ3 = GZ3 + (GZ2 * VARIACAO_TEMPO);

  GX4= ((0.98 *((GX4 + GX2) *(VARIACAO_TEMPO/1000000))) + (0.02 * AX3));
  GY4= ((0.98 *((GY4 + GY2) *(VARIACAO_TEMPO/1000000))) + (0.02 * AY3));
  GZ4= ((0.98 *((GZ4 + GZ2) *(VARIACAO_TEMPO/1000000))) + (0.02 * AZ3));

/* Serial.print(" | AX = "); Serial.print(AX2);
 Serial.print(" | AY = "); Serial.print(AY2);
 Serial.print(" | AZ = "); Serial.print(AZ2);
 Serial.print(" | GX = "); Serial.print(GX4);
 Serial.print(" | GY = "); Serial.print(GY4);
 Serial.print(" | GZ = "); Serial.println(GZ4);
*/
DynamicJsonBuffer jBuffer;
JsonObject& root = jBuffer.createObject();
root["ax"] = AX2;
root["ay"] = AY2;
root["az"] = AZ2;
root["gx"] = GX4;
root["gy"] = GY4;
root["gz"] = GZ4; 

root.prettyPrintTo(Serial);
Serial.println();
delay(100);
}
