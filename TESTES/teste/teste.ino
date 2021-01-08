//baseado em https://github.com/JyeSmith/dshot-esc-tester/blob/master/dshot-esc-tester.ino
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "Arduino.h"
#include "esp32-hal.h"


TaskHandle_t taskDshot;

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

bool start_stop = true;
bool manda = false;
void dshotSecondCoreTask( void * pvParameters ){
    while(1){
     // if(manda){
        dshotOutput(dshotUserInputValue1,
                    dshotUserInputValue2,
                    dshotUserInputValue3,
                    dshotUserInputValue4);  
      //}
        delay(1);        
    } 
}

void setup() {
    Serial.begin(115200);
    
    if ((remetenteMotor1 = rmtInit(13  , true, RMT_MEM_64)) == NULL) {
        Serial.println("init sender failed\n");
    }
    if ((remetenteMotor2 = rmtInit(23, true, RMT_MEM_64)) == NULL) {
        Serial.println("init sender failed\n");
    }
    if ((remetenteMotor3 = rmtInit(2  , true, RMT_MEM_64)) == NULL) {
        Serial.println("init sender failed\n");
    }
    if ((remetenteMotor4 = rmtInit(4, true, RMT_MEM_64)) == NULL) {
        Serial.println("init sender failed\n");
    }
    float realTick1 = rmtSetTick(remetenteMotor1, 12.5);
    float realTick2 = rmtSetTick(remetenteMotor2, 12.5);
    float realTick3 = rmtSetTick(remetenteMotor3, 12.5);
    float realTick4 = rmtSetTick(remetenteMotor4, 12.5);
    
    dshotOutput(47, 47, 47, 47);
    delay(3500);
    
    xTaskCreatePinnedToCore(dshotSecondCoreTask, "taskDshot", 10000, NULL, 1, &taskDshot, 0); 
}

void loop() {

while(start_stop){
  
  dshotUserInputValue1 = 47;
  dshotUserInputValue2 = 47;
  dshotUserInputValue3 = 47;
  dshotUserInputValue4 = 47;

  for(int cont = 47; cont < 150; cont++){
    dshotUserInputValue1 = cont;
    dshotUserInputValue2 = cont;
    dshotUserInputValue3 = cont;
    dshotUserInputValue4 = cont;
    delay(20);
  }
  for(int cont2 = 150; cont2 > 47; cont2--){
    dshotUserInputValue1 = cont2;
    dshotUserInputValue2 = cont2;
    dshotUserInputValue3 = cont2;
    dshotUserInputValue4 = cont2;
    delay(20);
  }
  dshotUserInputValue1 = 47;
  dshotUserInputValue2 = 47;
  dshotUserInputValue3 = 47;
  dshotUserInputValue4 = 47;

  delay(3500);
  }
}


void dshotOutput(uint16_t value1, uint16_t value2, uint16_t value3, uint16_t value4) {
    
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
     
    return;
}

/*void dshotOutput2(uint16_t value, bool telemetry) {
    
    uint16_t packet;
       
    if (telemetry) {
        packet = (value << 1) | 1;
    } else {
        packet = (value << 1) | 0;
    }

    // https://github.com/betaflight/betaflight/blob/09b52975fbd8f6fcccb22228745d1548b8c3daab/src/main/drivers/pwm_output.c#L523
    int csum = 0;
    int csum_data = packet;
    for (int i = 0; i < 3; i++) {
        csum ^=  csum_data;
        csum_data >>= 4;
    }
    csum &= 0xf;
    packet = (packet << 4) | csum;

  for (int i = 0; i < 16; i++) {
        if (packet & 0x8000) {
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
        packet <<= 1;
    }
    
    rmtWrite(remetenteMotor2, dshotPacketMotor2, 16); 
    return;
}

void dshotOutput3(uint16_t value, bool telemetry) {   
    uint16_t packet;
    
    if (telemetry) {
        packet = (value << 1) | 1;
    } else {
        packet = (value << 1) | 0;
    }
    
    int csum = 0;
    int csum_data = packet;
    
    for (int i = 0; i < 3; i++) {
        csum ^=  csum_data;
        csum_data >>= 4;
    }
    csum &= 0xf;
    
    packet = (packet << 4) | csum;
    for (int i = 0; i < 16; i++) {
        if (packet & 0x8000) {
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
        packet <<= 1;
    }
    
    rmtWrite(remetenteMotor3, dshotPacketMotor3, 16); 
    return;
}

void dshotOutput4(uint16_t value, bool telemetry) {   
    uint16_t packet;
    
    if (telemetry) {
        packet = (value << 1) | 1;
    } else {
        packet = (value << 1) | 0;
    }
    
    int csum = 0;
    int csum_data = packet;
    
    for (int i = 0; i < 3; i++) {
        csum ^=  csum_data;
        csum_data >>= 4;
    }
    csum &= 0xf;
    
    packet = (packet << 4) | csum;
    for (int i = 0; i < 16; i++) {
        if (packet & 0x8000) {
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
        packet <<= 1;
    }
    
    rmtWrite(remetenteMotor4, dshotPacketMotor4, 16); 
    return;
}*/
