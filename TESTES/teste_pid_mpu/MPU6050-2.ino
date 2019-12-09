/*#include "BIBLIOTECAS.h"
#include "DEFINICOES.h"

void mpu_initialize2(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0); 
  Wire.endTransmission(true);
}

void read_mpu(){  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);                               

  ax1=Wire.read()<<8|Wire.read();      
  ay1=Wire.read()<<8|Wire.read();  
  az1=Wire.read()<<8|Wire.read();    


  Acceleration_angle[0] = atan((ay1/16384.0)/sqrt(pow((ax1/16384.0),2) + pow((az1/16384.0),2)))*radToDegr;
  Acceleration_angle[1] = atan(-1*(ax1/16384.0)/sqrt(pow((ay1/16384.0),2) + pow((az1/16384.0),2)))*radToDegr;

  Wire.beginTransmission(0x68);
  Wire.write(0x43); //Gyro data first adress
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,4,true);

  gx1=Wire.read()<<8|Wire.read();  
  gy1=Wire.read()<<8|Wire.read();  

  Gyro_angle[0] = gx1/131.0; 
  Gyro_angle[1] = gy1/131.0;

  Total_angle[0] = 0.98 *(Total_angle[0] + Gyro_angle[0]*dt) + 0.02*Acceleration_angle[0];
  Total_angle[1] = 0.98 *(Total_angle[1] + Gyro_angle[1]*dt) + 0.02*Acceleration_angle[1];
}

void getDirecaoDecolagem2(){
  gz_ini = gz; 
}*/
