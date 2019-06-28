void mpu_initialize(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  delay(3000);
  Wire.write(0); 
  Wire.endTransmission(true);
  delay(8000);
}

void read_mpu(){  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true); 

  ax1=Wire.read()<<8|Wire.read();      
  ay1=Wire.read()<<8|Wire.read();  
  az1=Wire.read()<<8|Wire.read();    
  Tmp=Wire.read()<<8|Wire.read();
  gx1=Wire.read()<<8|Wire.read();  
  gy1=Wire.read()<<8|Wire.read();  
  gz1=Wire.read()<<8|Wire.read();  

  ax = ((ax1*GRAVI)/CALIB);
  ay = ((ay1*GRAVI)/CALIB);
  az = ((az1*(GRAVI-AJUSTE))/CALIB);   //depois tirar ajuste

  ax3 = (atan2(ax1, sqrt(pow(ay1,2) + pow(az1,2))))* radToDegr; 
  ay3 = (atan2(ay1, sqrt(pow(ax1,2) + pow(az1,2))))* radToDegr; 
  az3 = (atan2(az1, sqrt(pow(ax1,2) + pow(ay1,2))))* radToDegr; 

  gx2 = gx1 * G_GAIN; 
  gy2 = gy1 * G_GAIN; 
  gz2 = gz1 * G_GAIN; 

  gx3 = gx3 + (gx2 * dt);
  gy3 = gy3 + (gy2 * dt);
  gz3 = gz3 + (gz2 * dt);

  gx= ((0.98 *((gx + gx2) * dt)) + (0.02 * ax3))*50;
  gy= ((0.98 *((gy + gy2) * dt)) + (0.02 * ay3))*50;
  gz= ((0.98 *((gz + gz2) *dt)) + (0.02 * az3))*50;
}

void getDirecaoDecolagem(){
  gz_ini = gz; 
}
