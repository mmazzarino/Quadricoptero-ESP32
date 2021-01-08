#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h> 

uint16_t sinal = 0;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void TaskRunningOnAppCore(void *arg) {
    while(1){  
       //portENTER_CRITICAL_ISR(&mux);
       Serial.println("sinal task: " + String(sinal));
       //portEXIT_CRITICAL_ISR(&mux);
       delay(1);
    }
}
 
void setup(){
    Serial.begin(115200);
   // xMutex = xSemaphoreCreateMutex();
    
    xTaskCreatePinnedToCore(TaskRunningOnAppCore, 
                            "TaskCoreZero",             
                            2048,                     
                            NULL,                    
                            4,                        
                            NULL,                     
                            0);            
}
 
void loop(){
  //portENTER_CRITICAL_ISR(&mux);
  Serial.println("sinal loop: " + String(sinal));
 // portEXIT_CRITICAL_ISR(&mux);
  delay(1);
}
