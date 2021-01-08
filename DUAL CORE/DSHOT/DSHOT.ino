/*Exemplo de execução de 1 tarefa em cada core -> :https://randomnerdtutorials.com/esp32-dual-core-arduino-ide/ */
/*Exemplo de uso de telemetria no protocolo DSHOT ->https://github.com/JyeSmith/dshot-esc-tester/blob/master/dshot-esc-tester.ino*/
/*Entendimento do protocolo DSHOT 600 -> https://blck.mn/2016/11/dshot-the-new-kid-on-the-block/ */
//soma de verificação : https://github.com/cleanflight/cleanflight/blob/bd523ced7cc3a8c000068cca08da96eff43716a1/src/main/drivers/pwm_output.c#L405
//dshot wxample https://github.com/betaflight/betaflight/blob/30f31525251fd08f69e61dad1ce454d630851de1/src/main/drivers/pwm_output.h#L40


//kHandle_t TaskDSHOT;


// ESC pins
volatile const int escA = ;
volatile const int escB = ;
volatile const int escC = ;
volatile const int escD = ;

volatile uint16_t dshotMin = 48;
volatile uint16_t dshotMax = 2047;

volatile uint16_t vma   /*valores de 1 a 2000 definidos para cada esc*/ 
volatile uint16_t vmb
volatile uint16_t vmc
volatile uint16_t vmd

volatile uint16_t frameA = dshotMin + vma
volatile uint16_t frameB = dshotMin + vmb
volatile uint16_t frameC = dshotMin + vmc
volatile uint16_t frameD = dshotMin + vmd

volatile int contClockBit = 0;

void setup() {

 // setCpuFrequencyMhz(240);  /* pesquisa rapida sobre como setar a frequência corretamente p/ 200MHz*/ 
  Serial.begin(115200); 
  pinMode(escA, OUTPUT);
  pinMode(escB, OUTPUT);
  pinMode(escC, OUTPUT);
  pinMode(escD, OUTPUT);

/*
  xTaskCreatePinnedToCore(
                    Task1code,    // Task function. 
                    "TaskDSHOT",  // name of task. 
                    10000,        // Stack size of task 
                    NULL,         // parameter of the task 
                    1,            // priority of the task 
                    &TaskDSHOT,   // Task handle to keep track of created task 
                    0);           // pin task to core 0                   
  */
  delay(500); 
}
/*
void Task1code( void * pvParameters ){
  
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
 
  for(;;){   
    
    for(contBit = 15; contBit >= 0; ){       
      while(contClockBit <= 401){
        switch(contClockBit){       
          case 0: escA = HIGH; 
                  escB = HIGH; 
                  escC = HIGH; 
                  escD = HIGH;
                  break; 
                  
          case 150: if(bitRead(escA, contBit) == '0'){ escA = LOW;}
                    if(bitRead(escB, contBit) == '0'){ escB = LOW;}
                    if(bitRead(escC, contBit) == '0'){ escC = LOW;}
                    if(bitRead(escD, contBit) == '0'){ escD = LOW;}
                    break;
          
          case 300: if(bitRead(escA, contBit) == '1'){ escA = LOW;}
                    if(bitRead(escB, contBit) == '1'){ escB = LOW;}
                    if(bitRead(escC, contBit) == '1'){ escC = LOW;}
                    if(bitRead(escD, contBit) == '1'){ escD = LOW;}
                    break;
          
          case 401: if(contBit > 0){ zeraContClockBit = true;
                                     contBit--;  
                                     break;
                                    }
                    else{ zeraContClockBit = false;                           
                           break; }
          
          default: break;
        }
      }
      contBit--;
    }

    if(contClockBit == 881){
       zeraContClockBit = true;
      } 
    }
  } */

void loop() {
   uint16_t packet = ((uint16_t)1046 << 1);
  int csum = 0;
  int csum_data = packet;
  for (int i = 0; i < 3; i++) {
      csum ^=  csum_data;   
      csum_data >>= 4;
    }
  
   for(contBit = 15; contBit >= 0; ){       
      while(contClockBit <= 401){
        switch(contClockBit){       
          case 0: escA = HIGH; 
                  escB = HIGH; 
                  escC = HIGH; 
                  escD = HIGH;
                  break; 
                  
          case 150: if(bitRead(escA, contBit) == '0'){ escA = LOW;}
                    if(bitRead(escB, contBit) == '0'){ escB = LOW;}
                    if(bitRead(escC, contBit) == '0'){ escC = LOW;}
                    if(bitRead(escD, contBit) == '0'){ escD = LOW;}
                    break;
          
          case 300: if(bitRead(escA, contBit) == '1'){ escA = LOW;}
                    if(bitRead(escB, contBit) == '1'){ escB = LOW;}
                    if(bitRead(escC, contBit) == '1'){ escC = LOW;}
                    if(bitRead(escD, contBit) == '1'){ escD = LOW;}
                    break;
          
          case 401: if(contBit > 0){ zeraContClockBit = true;
                                     contBit--;  
                                     break;
                                    }
                    else{ zeraContClockBit = false;                           
                           break; }
          
          default: break;
        }
      }
      contBit--;
    }

    if(contClockBit == 881){
       zeraContClockBit = true;
      } 
}
