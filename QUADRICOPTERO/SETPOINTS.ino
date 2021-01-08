void setPointsPotencia(){
  
  if(k < 1){
    k = 0;
  }
  potencia = map(k, 0, 100, potenciaMinima, potenciaMaxima);
 // Serial.print(potencia);Serial.print("; ");
}

void setPointsInclinacao(){ 
  sp_gx = map(x, -100, 100, inclinacaoMinima, inclinacaoMaxima); 
  sp_gy = map(y, -100, 100, inclinacaoMinima, inclinacaoMaxima);  

 // Serial.print(sp_gx);Serial.print("; ");
 // Serial.print(sp_gy);Serial.print("; ");
  
}
