#include "CONFIGURACAO.h"

void setPointsInclinacao(){ 
  sp_gx = map(x, -100, 100, inclinacaoMinima, inclinacaoMaxima); 
  sp_gy = map(y, -100, 100, inclinacaoMinima, inclinacaoMaxima);  
}

void setPointsGiroZ(){
  if((sp_gx == 0) and (sp_gy == 0)){
    sp_gz = map(j, -100, 100, -180, 180) + gz_ini;          
  } 
  else{
    null;
  }
}

void setPointsPotencia(){
  if((k != 0) and (k > -20)){
    potencia = map(k, -100, 100, 0, 255);
  }else if((k > -99) and (k < -19)){
    potencia = 100;
  }
  else if(k == -100){
    potencia = 0;
  }
  else if(k == 0){
     null; 
  }
}
