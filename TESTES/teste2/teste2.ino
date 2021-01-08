#include <HardwareSerial.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "Arduino.h"
#include "esp32-hal.h"

#define MOTOR_POLES 14

TaskHandle_t Task1;

rmt_data_t dshotPacket[16];
rmt_obj_t* rmt_send = NULL;

hw_timer_t * timer = NULL;

HardwareSerial MySerial(1);

uint8_t receivedBytes = 0;
volatile bool requestTelemetry = false;
bool printTelemetry = true;
uint16_t dshotUserInputValue = 0;
uint16_t dshotmin = 48;
uint16_t dshotmax = 2047;
uint16_t dshotidle = dshotmin + round(3.5*(dshotmax-dshotmin)/100); // 3.5%
uint16_t dshot50 =   dshotmin + round(50*(dshotmax-dshotmin)/100); // 50%
uint16_t dshot75 =   dshotmin + round(75*(dshotmax-dshotmin)/100); // 75%
int16_t ESC_telemetrie[5]; // Temperature, Voltage, Current, used mAh, eRpM
bool runMQTBSequence = false;

uint32_t currentTime;
uint8_t temperature = 0;
uint8_t temperatureMax = 0;
float voltage = 0;
float voltageMin = 99;
uint32_t current = 0;
uint32_t currentMax = 0;
uint32_t erpm = 0;
uint32_t erpmMax = 0;
uint32_t rpm = 0;
uint32_t rpmMAX = 0;
uint32_t kv = 0;
uint32_t kvMax = 0;

void gotTouch8(){
    dshotUserInputValue = 0;
    runMQTBSequence = false;
    printTelemetry = true;
    } // DIGITAL_CMD_MOTOR_STOP
void gotTouch9(){
    dshotUserInputValue = 247;
    resetMaxMinValues();
    runMQTBSequence = false;
    printTelemetry = true;
    } // 10%
void gotTouch7(){
    dshotUserInputValue = 447;
    resetMaxMinValues();
    runMQTBSequence = false;
    printTelemetry = true;
    } // 20%
void gotTouch6(){
    dshotUserInputValue = 1047;
    resetMaxMinValues();
    runMQTBSequence = false;
    printTelemetry = true;
    } // 50%
void gotTouch5(){ 
    dshotUserInputValue = 2047;                 
    resetMaxMinValues();
    runMQTBSequence = false;
    printTelemetry = true;
    } // 100%
void gotTouch4(){ 
    temperatureMax = 0;
    voltageMin = 99;
    currentMax = 0;
    erpmMax = 0;
    rpmMAX = 0;
    kvMax = 0;
    runMQTBSequence = false;
    printTelemetry = true;
}
void resetMaxMinValues() {
    gotTouch4();
}

void IRAM_ATTR getTelemetry(){
    requestTelemetry = true;        
}

void startTelemetryTimer() {
    timer = timerBegin(0, 80, true); // timer_id = 0; divider=80; countUp = true;
    timerAttachInterrupt(timer, &getTelemetry, true); // edge = true
    timerAlarmWrite(timer, 20000, true);  //1000 = 1 ms
    timerAlarmEnable(timer);
}

// Second core used to handle dshot packets
void secondCoreTask( void * pvParameters ){
    while(1){
      
        dshotOutput(dshotUserInputValue, requestTelemetry);
    
        if (requestTelemetry) {                
            requestTelemetry = false;
            receivedBytes = 0;
        }
        
        delay(1);
        
    } 
}

void setup() {

    Serial.begin(115200);
    MySerial.begin(115200, SERIAL_8N1, RX, TX);
    
    if ((rmt_send = rmtInit(5, true, RMT_MEM_64)) == NULL) {
        Serial.println("init sender failed\n");
    }
    float realTick = rmtSetTick(rmt_send, 12.5); // 12.5ns sample rate
  
    
    // Output disarm signal while esc initialises and do some display stuff.
    uint8_t xbeep = random(15, 100);
    uint8_t ybeep = random(15, 50);
    uint8_t ibeep = 0;
    while (millis() < 3500) {
        dshotOutput(0, false);
        delay(1);  
        
       
        ibeep++; 
        if (ibeep == 100) {
            ibeep = 0;
            xbeep = random(15, 50);
            ybeep = random(15, 50);
        }
        if (millis() < 500) {         
            Serial.println("Initialising ESC... 4s");
        } else if (millis() < 1500) {   
            Serial.println("Initialising ESC... 3s");
        } else if (millis() < 2500) {  
            Serial.println("Initialising ESC... 2s");
        } else {                
            Serial.println("Initialising ESC... 1s");
        }
    }
    
    touchAttachInterrupt(T4, gotTouch4, 40);
    touchAttachInterrupt(T5, gotTouch5, 40);
    touchAttachInterrupt(T6, gotTouch6, 40);
    touchAttachInterrupt(T7, gotTouch7, 40);
    touchAttachInterrupt(T8, gotTouch8, 40);
    touchAttachInterrupt(T9, gotTouch9, 40);

    // Empty Rx Serial of garbage telemtry
    while(MySerial.available())
        MySerial.read();
    
    requestTelemetry = true;

    startTelemetryTimer(); // Timer used to request tlm continually in case ESC rcv bad packet
    
    xTaskCreatePinnedToCore(secondCoreTask, "Task1", 10000, NULL, 1, &Task1, 0); 

    Serial.print("Time (ms)"); 
    Serial.print(","); 
    Serial.print("dshot"); 
    Serial.print(",");  
    Serial.print("Voltage (V)");
    Serial.print(",");   
    Serial.print("Current (A)");
    Serial.print(",");
    Serial.print("RPM");
    Serial.print(",");  
    Serial.println("Thrust (g)");

#ifdef MINIQUADTESTBENCH   
    dshotUserInputValue = dshotidle;
    runMQTBSequence = true;     
    display.clear();              
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0,  0, "Running MQTB Sequence...");    
    display.display(); 
#endif

}

void loop() {
   
    if(!requestTelemetry) {
         receiveTelemtrie();
    } 
    
#ifdef MINIQUADTESTBENCH
    if(runMQTBSequence) {
        currentTime = millis();
        if(currentTime >= 4000 && currentTime < 6000) {
            dshotUserInputValue = 70;   //dshot50;
        } else if(currentTime >= 6000 && currentTime < 8000) {
            dshotUserInputValue = 147;   // dshotidle;
        } else if(currentTime >= 8000 && currentTime < 10000) {
            dshotUserInputValue = 247;//dshot75;
        } else if(currentTime >= 10000 && currentTime < 12000) {
            dshotUserInputValue = 347;//dshotidle;
        } else{
            dshotUserInputValue = 47;
        }
        
        
        /*else if(currentTime >= 12000 && currentTime < 14000) {
            dshotUserInputValue = dshotmax;
        } else if(currentTime >= 14000 && currentTime < 16000) {
            dshotUserInputValue = dshotmin;
        } else if(currentTime >= 16000 && currentTime < 22000) {      
            dshotUserInputValue = dshotmin + (currentTime-16000)*(dshotmax-dshotmin)/6000.0;        
        } else if(currentTime >= 24000 && currentTime < 26000) {
            dshotUserInputValue = dshotidle;
        } else if(currentTime >= 26000 && currentTime < 28000) {
            printTelemetry = false;
            dshotUserInputValue = 0;
        } */
    }
#endif
}

void receiveTelemtrie(){
    static uint8_t SerialBuf[10];

        if(MySerial.available()){
            SerialBuf[receivedBytes] = MySerial.read();
            receivedBytes++;
        }

        if(receivedBytes > 9){ // transmission complete
          
            uint8_t crc8 = get_crc8(SerialBuf, 9); // get the 8 bit CRC
          
            if(crc8 != SerialBuf[9]) {
//                Serial.println("CRC transmission failure");
                
                // Empty Rx Serial of garbage telemtry
                while(MySerial.available())
                    MySerial.read();
                
                requestTelemetry = true;
            
                return; // transmission failure 
            }
          
            // compute the received values
            ESC_telemetrie[0] = SerialBuf[0]; // temperature
            ESC_telemetrie[1] = (SerialBuf[1]<<8)|SerialBuf[2]; // voltage
            ESC_telemetrie[2] = (SerialBuf[3]<<8)|SerialBuf[4]; // Current
            ESC_telemetrie[3] = (SerialBuf[5]<<8)|SerialBuf[6]; // used mA/h
            ESC_telemetrie[4] = (SerialBuf[7]<<8)|SerialBuf[8]; // eRpM *100
            
            requestTelemetry = true;

            if(!runMQTBSequence) { // Do not update during MQTB sequence.  Slows serial output.
                updateDisplay();
            }
          /*  
          Serial.println("Requested Telemetrie");
          Serial.print("Temperature (C): ");
          Serial.println(ESC_telemetrie[0]); 
          Serial.print("Voltage (V): ");
          Serial.println(ESC_telemetrie[1] / 100.0);   
          Serial.print("Current (mA): ");
          Serial.println(ESC_telemetrie[2] * 100); 
          Serial.print("mA/h: ");
          Serial.println(ESC_telemetrie[3] * 10);   
          Serial.print("eRPM : ");
          Serial.println(ESC_telemetrie[4] * 100);  
          Serial.print("RPM : ");
          Serial.println(ESC_telemetrie[4] * 100 / 7.0);  // 7 = 14 magnet count / 2
          Serial.print("KV : ");
          Serial.println( (ESC_telemetrie[4] * 100 / 7.0) / (ESC_telemetrie[1] / 100.0) );  // 7 = 14 magnet count / 2
          Serial.println(" ");
          Serial.println(" ");
            */
            if(printTelemetry) {
                Serial.print(millis()); 
                Serial.print(","); 
                Serial.print(dshotUserInputValue); 
                Serial.print(",");
                Serial.print("Voltage (V): ");
                Serial.print(ESC_telemetrie[1] / 100.0); 
                Serial.print(",");   
                Serial.print("Current (A): ");
                Serial.print(ESC_telemetrie[2] / 10.0); 
                Serial.print(","); 
                Serial.print("RPM : ");
                Serial.print(ESC_telemetrie[4] * 100 / (MOTOR_POLES / 2)); 
                Serial.println(",");  
                // Thrust

            }
          
            temperature = 0.9*temperature + 0.1*ESC_telemetrie[0];
            if (temperature > temperatureMax) {
                temperatureMax = temperature;
            }
            
            voltage = 0.9*voltage + 0.1*(ESC_telemetrie[1] / 100.0);
            if (voltage < voltageMin) {
                voltageMin = voltage;
            }
            
            current = 0.9*current + 0.1*(ESC_telemetrie[2] * 100);
            if (current > currentMax) {
                currentMax = current;
            }
            
            erpm = 0.9*erpm + 0.1*(ESC_telemetrie[4] * 100);
            if (erpm > erpmMax) {
                erpmMax = erpm;
            }
            
            rpm = erpm / (MOTOR_POLES / 2);
            if (rpm > rpmMAX) {
                rpmMAX = rpm;
            }
            
            if (rpm) {                  // Stops weird numbers :|
                kv = rpm / voltage / ( (float(dshotUserInputValue) - dshotmin) / (dshotmax - dshotmin) );
            } else {
                kv = 0;
            }
            if (kv > kvMax) {
                kvMax = kv;
            }
          
        }

  return;
  
}

void dshotOutput(uint16_t value, bool telemetry) {
    
    uint16_t packet;
    
    // telemetry bit    
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

    // durations are for dshot600
    // https://blck.mn/2016/11/dshot-the-new-kid-on-the-block/
    // Bit length (total timing period) is 1.67 microseconds (T0H + T0L or T1H + T1L).
    // For a bit to be 1, the pulse width is 1250 nanoseconds (T1H – time the pulse is high for a bit value of ONE)
    // For a bit to be 0, the pulse width is 625 nanoseconds (T0H – time the pulse is high for a bit value of ZERO)
    for (int i = 0; i < 16; i++) {
        if (packet & 0x8000) {
              dshotPacket[i].level0 = 1;
              dshotPacket[i].duration0 = 100;
              dshotPacket[i].level1 = 0;
              dshotPacket[i].duration1 = 34;
          } else {
              dshotPacket[i].level0 = 1;
              dshotPacket[i].duration0 = 50;
              dshotPacket[i].level1 = 0;
              dshotPacket[i].duration1 = 84;
          }
        packet <<= 1;
    }
    
    rmtWrite(rmt_send, dshotPacket, 16);
    
    return;

}

uint8_t update_crc8(uint8_t crc, uint8_t crc_seed){
  uint8_t crc_u, i;
  crc_u = crc;
  crc_u ^= crc_seed;
  for ( i=0; i<8; i++) crc_u = ( crc_u & 0x80 ) ? 0x7 ^ ( crc_u << 1 ) : ( crc_u << 1 );
  return (crc_u);
}

uint8_t get_crc8(uint8_t *Buf, uint8_t BufLen){
  uint8_t crc = 0, i;
  for( i=0; i<BufLen; i++) crc = update_crc8(Buf[i], crc);
  return (crc);
}

void updateDisplay() {    
   
  /*            

    Serial.println("Dshot Packet");
    Serial.print("Temp C ");Serial.println(String(temperature));
    Serial.print("Volt ");Serial.println(String(voltage));
    Serial.print("mA ");Serial.println(String(current));
    Serial.print("eRPM ");Serial.println(String(erpm));
    Serial.print("KV ");Serial.println(String(kv));
    


   Serial.println(String(dshotUserInputValue));
    Serial.println(String(temperatureMax));
    Serial.println(String(voltageMin));
    Serial.println(String(currentMax));
    Serial.println(String(erpmMax));
    Serial.println(String(kvMax));
    */
}
