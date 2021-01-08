#include "BIBLIOTECAS.h"
#include "DEFINICOES.h"

void setup() {
   Serial.begin(115200);
   //main_scanner();
   spiffsInitialize(); 
   wifiInitialize();
   startWebSocket();
   serverInitialize();
   mpu_initialize();
   setupDshot();
   //Serial.println("Pot;sp_gx;sp_gy;dt_s;mili_s;micro_s;giro x;giro y;pidx;pidy;m_1;m_2;m_3;m_4;");
   
   xTaskCreatePinnedToCore(
      loopCorePadrao,   //Função para implementar a tarefa
      "TaskCorePadrao", //Nome da tarefa
      10000,            //Tamanho da pilha em palavras
      NULL,             //Parâmetro de entrada de tarefa
      1,                //Prioridade da tarefa
      &TaskCorePadrao,  //Identificador de tarefa
      1);               //Núcleo onde a tarefa deve ser executada
      
   xTaskCreatePinnedToCore(
      loopDshot, 
      "TaskSegundoCore", 
      10000, 
      NULL, 
      1, 
      &TaskSegundoCore, 
      0);
  
}


void loopCorePadrao( void * pvParameters ) { 
   while(1){
      //writeFile(SPIFFS, "/joy.html", joyHtml);
      webSocket.loop();
      setPointsPotencia(); 
      setPointsInclinacao();
      tempoCiclo();
      read_mpu();
      
      pidEixoX(); 
      pidEixoY();
      setaValoresMotores();   
      //testeDshot();
      //scanner();
      //delayMicroseconds(50000);
      delay(70);
    }
}

void loop(){ 
  
}
  
  
