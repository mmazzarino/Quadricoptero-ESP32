void mpu_initialize(){
  Wire.begin();

  // Reseta os registros internos e restaura as configurações padrão.
  write_byte(MPU9250_ADDRESS, PWR_MGMT_1, 0b10000000);
  delay(100);

  // Ativa todos sensores
  write_byte(MPU9250_ADDRESS, PWR_MGMT_2, 0x00); 

  // Ativa o desvio para acessar o magnetômetro
  write_byte(MPU9250_ADDRESS, INT_PIN_CFG, 0x02);

  // Le os dados de ajuste de fábrica
  write_byte(AK8963_ADDRESS, AK8963_CNTL, 0x00);
  delay(10);

   // Entra no modo de acesso à ROM do fusível
  write_byte(AK8963_ADDRESS, AK8963_CNTL, 0x0F); 
  delay(10);

  // Le os valores de calibração dos eixos x, y e z
  read_bytes(AK8963_ADDRESS, AK8963_ASAX, 3);

  // Retornar valores de ajuste de sensibilidade do eixo x, etc.
  MagAdjustment[0] =  (float)(Wire.read() - 128)/256. + 1.;
  MagAdjustment[1] =  (float)(Wire.read() - 128)/256. + 1.;
  MagAdjustment[2] =  (float)(Wire.read() - 128)/256. + 1.;
 
  //Desligue o magnetômetro
  write_byte(AK8963_ADDRESS, AK8963_CNTL, 0x00); 
  delay(10);

  // Definir a resolução de dados do magnetômetro e obter amostra de ODR
  write_byte(AK8963_ADDRESS, AK8963_CNTL, 0b00010110);
  delay(10);

  set_accel_range(RANGE_2G);
  set_gyro_range(RANGE_GYRO_2000);
}

void read_mpu(){  
   read_bytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 14);
 
   ay1=Wire.read()<<8|Wire.read();      
   ax1=Wire.read()<<8|Wire.read();  
   az1=Wire.read()<<8|Wire.read();    
   Tmp=Wire.read()<<8|Wire.read();
   gy1=Wire.read()<<8|Wire.read();  
   gx1=Wire.read()<<8|Wire.read();  
   gz1=Wire.read()<<8|Wire.read();  

   filtroComplementar();
}

void set_accel_range(accel_range range){
    uint8_t reg = read_byte(MPU9250_ADDRESS, ACCEL_CONFIG);
    write_byte(MPU9250_ADDRESS, ACCEL_CONFIG, ((reg & 0b11100111)|(range<<3)));
}

void set_gyro_range(gyro_range range){
    uint8_t reg = read_byte(MPU9250_ADDRESS, GYRO_CONFIG);
    write_byte(MPU9250_ADDRESS, GYRO_CONFIG, ((reg & 0b11100111)|(range<<3)));
}

void write_byte(uint8_t adress, uint8_t reg, uint8_t value){
    Wire.beginTransmission(adress);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

uint8_t read_byte(uint8_t adress, uint8_t reg){
    Wire.beginTransmission(adress);
    Wire.write(reg);
    Wire.endTransmission(false); 
    Wire.requestFrom(adress, 1);   
    return Wire.read();
}
void read_bytes(uint8_t adress, uint8_t reg, int numBytes){
    Wire.beginTransmission(adress);
    Wire.write(reg);
    Wire.endTransmission(false); 
    Wire.requestFrom(adress, numBytes);   
}
