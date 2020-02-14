//https://github.com/yelvlab/ESP32-Arduino-MPU9250

#INCLUDE "definicoes.h"

MPU9250 IMU(Wire,0x68); //O endereço I2C do MPU-9250 será 0x68 se o pino AD0 estiver aterrado ou 0x69 se o pino AD0 for puxado alto
void setup(){
  int status;
  float gxb;
  float gyb;
  float gzb;
  float axs;
  float ayb;
  float azb;
  float azs;
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
  float hx;
  float hy;
  float hz;
  float temperature;



  
  status = IMU.begin();
  status = IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);         //opcional
  status = IMU.setGyroRange(MPU9250::GYRO_RANGE_250DPS);       //opcional
  status = IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ); //opcional
  status = IMU.setSrd(9);                                      //opcional
  status = IMU.enableDataReadyInterrupt();                     //opcional
  status = IMU.calibrateGyro();                                //opcional 
  status = IMU.calibrateAccel();                               //opcional
  gxb = IMU.getGyroBiasX_rads();                               //opcional
  gyb = IMU.getGyroBiasY_rads();                               //opcional
  gzb = IMU.getGyroBiasZ_rads();                               //opcional
  axs = IMU.getAccelScaleFactorX();
  ayb = IMU.getAccelBiasY_mss();
  azb = IMU.getAccelBiasZ_mss();
  azs = IMU.getAccelScaleFactorZ();

  
  //Essas funções definem a polarização do giroscópio usada para o valor de entrada em unidades de rad / s
  gxb = 0,001 ;       
  IMU.setGyroBiasZ_rads(gxb);                                  //opcional
  gyb = 0,001 ;       
  IMU.setGyroBiasZ_rads(gyb);                                  //opcional
  gzb = 0,001 ;       
  IMU.setGyroBiasZ_rads(gzb);                                  //opcional
}

void loop(){
  IMU.readSensor();
  ax = IMU.getAccelX_mss();
  ay = IMU.getAccelY_mss();
  az = IMU.getAccelZ_mss();
 
  gx = IMU.getGyroX_rads();
  gy = IMU.getGyroY_rads();
  gz = IMU.getGyroZ_rads();

  hx = IMU.getMagX_uT();
  hy = IMU.getMagY_uT();
  hz = IMU.getMagZ_uT();
  
  temperature = IMU.getTemperature_C();

  
}
