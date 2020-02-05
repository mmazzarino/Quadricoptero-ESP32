/*Exemplo de execução de 1 tarefa em cada core -> :https://randomnerdtutorials.com/esp32-dual-core-arduino-ide/ */
/*Exemplo de uso de telemetria no protocolo DSHOT ->https://github.com/JyeSmith/dshot-esc-tester/blob/master/dshot-esc-tester.ino*/
/*Entendimento do protocolo DSHOT 600 -> https://blck.mn/2016/11/dshot-the-new-kid-on-the-block/ */


kHandle_t TaskDSHOT;


// ESC pins
const int escA = ;
const int escB = ;
const int escC = ;
const int escD = ;

uint16_t dshotMin = 48;
uint16_t dshotMax = 2047;

uint16_t vma   /*valores de 1 a 2000 definidos para cada esc*/ 
uint16_t vmb
uint16_t vmc
uint16_t vmd

uint16_t frameA = dshotMin + vma
uint16_t frameB = dshotMin + vmb
uint16_t frameC = dshotMin + vmc
uint16_t frameD = dshotMin + vmd

int contClockBit = 0;

void setup() {

  setCpuFrequencyMhz(200);  /* pesquisa rapida sobre como setar a frequência corretamente p/ 200MHz*/ 
  Serial.begin(115200); 
  pinMode(escA, OUTPUT);
  pinMode(escB, OUTPUT);
  pinMode(escC, OUTPUT);
  pinMode(escD, OUTPUT);


  xTaskCreatePinnedToCore(
                    Task1code,    /* Task function. */
                    "TaskDSHOT",  /* name of task. */
                    10000,        /* Stack size of task */
                    NULL,         /* parameter of the task */
                    1,            /* priority of the task */
                    &TaskDSHOT,   /* Task handle to keep track of created task */
                    0);           /* pin task to core 0 */                  
  delay(500); 
}

void Task1code( void * pvParameters ){
  
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
 
  for(;;){   
    
    for(contBit = 15; contBit >= 0; ){       
      while(contClockBit <= 334){
        switch(contClockBit){       
          case 0: escA = HIGH; 
                  escB = HIGH; 
                  escC = HIGH; 
                  escD = HIGH;
                  break; 
                  
          case 125: if(bitRead(escA, contBit) == '0'){ escA = LOW;}
                    if(bitRead(escB, contBit) == '0'){ escB = LOW;}
                    if(bitRead(escC, contBit) == '0'){ escC = LOW;}
                    if(bitRead(escD, contBit) == '0'){ escD = LOW;}
                    break;
          
          case 250: if(bitRead(escA, contBit) == '1'){ escA = LOW;}
                    if(bitRead(escB, contBit) == '1'){ escB = LOW;}
                    if(bitRead(escC, contBit) == '1'){ escC = LOW;}
                    if(bitRead(escD, contBit) == '1'){ escD = LOW;}
                    break;
          
          case 334: if(contBit > 0){ zeraContClockBit = true;
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

    if(contClockBit == 400){
       zeraContClockBit = true;
      } 
    }
  } 

void loop() {
  
}
