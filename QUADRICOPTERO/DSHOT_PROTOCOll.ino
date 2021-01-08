bool vai = false;

void setupDshot(){
  remetenteMotor1 = rmtInit(pinMotor1 , true, RMT_MEM_64);
  rmtSetTick(remetenteMotor1, 12.5); //12.5 = tempo 80MHz^(-1)  
  
  remetenteMotor2 = rmtInit(pinMotor2, true, RMT_MEM_64);
  rmtSetTick(remetenteMotor2, 12.5);

  remetenteMotor3 = rmtInit(pinMotor3 , true, RMT_MEM_64);
  rmtSetTick(remetenteMotor3, 12.5);
  
  remetenteMotor4 = rmtInit(pinMotor4, true, RMT_MEM_64); 
  rmtSetTick(remetenteMotor4, 12.5);

  dshotOutput(0, 0, 0, 0);
  delay(7000); 
  dshotOutput(47, 47, 47, 47);
  delay(3500); 
}


void loopDshot( void * pvParameters ){
    while(1){
    //if(vai){
        portENTER_CRITICAL_ISR(&mux);
        dshotOutput(dshotUserInputValue1,
                    dshotUserInputValue2,
                    dshotUserInputValue3,
                    dshotUserInputValue4);
        portEXIT_CRITICAL_ISR(&mux);
    //}
    delay(1);//precisa??
   } 
}

void dshotOutput(uint16_t value1, uint16_t value2, uint16_t value3, uint16_t value4) {
    vai = false;
    uint16_t packet1 = (value1 << 1);
    uint16_t packet2 = (value2 << 1);
    uint16_t packet3 = (value3 << 1);
    uint16_t packet4 = (value4 << 1);

    int csum1 = 0;
    int csum2 = 0;
    int csum3 = 0;
    int csum4 = 0;
    
    int csum_data1 = packet1;
    int csum_data2 = packet2;
    int csum_data3 = packet3;
    int csum_data4 = packet4;
    
    for (int i = 0; i < 3; i++) {
        csum1 ^=  csum_data1;
        csum2 ^=  csum_data2;
        csum3 ^=  csum_data3;
        csum4 ^=  csum_data4;
        
        csum_data1 >>= 4;
        csum_data2 >>= 4;
        csum_data3 >>= 4;
        csum_data4 >>= 4;
    }
    
    csum1 &= 0xf;
    csum2 &= 0xf;
    csum3 &= 0xf;
    csum4 &= 0xf;
    
    packet1 = (packet1 << 4) | csum1;
    packet2 = (packet2 << 4) | csum2;
    packet3 = (packet3 << 4) | csum3;
    packet4 = (packet4 << 4) | csum4;

    for (int i = 0; i < 16; i++) {
        if (packet1 & 0x8000) {
            dshotPacketMotor1[i].level0 = 1;
            dshotPacketMotor1[i].duration0 = 100;
            dshotPacketMotor1[i].level1 = 0;
            dshotPacketMotor1[i].duration1 = 34;
        } else {
            dshotPacketMotor1[i].level0 = 1;
            dshotPacketMotor1[i].duration0 = 50;
            dshotPacketMotor1[i].level1 = 0;
            dshotPacketMotor1[i].duration1 = 84;
          }
        
        if (packet2 & 0x8000) {
            dshotPacketMotor2[i].level0 = 1;
            dshotPacketMotor2[i].duration0 = 100;
            dshotPacketMotor2[i].level1 = 0;
            dshotPacketMotor2[i].duration1 = 34;
        } else {
            dshotPacketMotor2[i].level0 = 1;
            dshotPacketMotor2[i].duration0 = 50;
            dshotPacketMotor2[i].level1 = 0;
            dshotPacketMotor2[i].duration1 = 84;
          }

          if (packet3 & 0x8000) {
            dshotPacketMotor3[i].level0 = 1;
            dshotPacketMotor3[i].duration0 = 100;
            dshotPacketMotor3[i].level1 = 0;
            dshotPacketMotor3[i].duration1 = 34;
        } else {
            dshotPacketMotor3[i].level0 = 1;
            dshotPacketMotor3[i].duration0 = 50;
            dshotPacketMotor3[i].level1 = 0;
            dshotPacketMotor3[i].duration1 = 84;
          }

          if (packet4 & 0x8000) {
            dshotPacketMotor4[i].level0 = 1;
            dshotPacketMotor4[i].duration0 = 100;
            dshotPacketMotor4[i].level1 = 0;
            dshotPacketMotor4[i].duration1 = 34;
        } else {
            dshotPacketMotor4[i].level0 = 1;
            dshotPacketMotor4[i].duration0 = 50;
            dshotPacketMotor4[i].level1 = 0;
            dshotPacketMotor4[i].duration1 = 84;
          }
        packet1 <<= 1;
        packet2 <<= 1;
        packet3 <<= 1;
        packet4 <<= 1;
    }
    
    rmtWrite(remetenteMotor1, dshotPacketMotor1, 16);
    rmtWrite(remetenteMotor2, dshotPacketMotor2, 16);
    rmtWrite(remetenteMotor3, dshotPacketMotor3, 16);
    rmtWrite(remetenteMotor4, dshotPacketMotor4, 16);

 vai = true;
    return;
}
