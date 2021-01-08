bool start_stop = true;

void testeDshot(){
  while(start_stop){
      portENTER_CRITICAL_ISR(&mux);
          dshotUserInputValue1 = 47;
          dshotUserInputValue2 = 47;
          dshotUserInputValue3 = 47;
          dshotUserInputValue4 = 47;
      portEXIT_CRITICAL_ISR(&mux);
//  setarValores = true;

  for(int cont = 70; cont < 100; cont++){
      portENTER_CRITICAL_ISR(&mux);
          //dshotUserInputValue1 = cont;
          //dshotUserInputValue2 = cont;
          dshotUserInputValue3 = cont;
          //dshotUserInputValue4 = cont;
      portEXIT_CRITICAL_ISR(&mux);
    Serial.print("cont: "); Serial.println(cont);
    setarValores = true;
    delay(60);
  }
  for(int cont2 = 100; cont2 > 70; cont2--){
   portENTER_CRITICAL_ISR(&mux);
        //dshotUserInputValue1 = cont2;
        //dshotUserInputValue2 = cont2;
        dshotUserInputValue3 = cont2;
        //dshotUserInputValue4 = cont2;
   portEXIT_CRITICAL_ISR(&mux);
  //  setarValores = true;
    delay(60);
  }

  portENTER_CRITICAL_ISR(&mux);
      dshotUserInputValue1 = 47;
      dshotUserInputValue2 = 47;
      dshotUserInputValue3 = 47;
      dshotUserInputValue4 = 47;
  portEXIT_CRITICAL_ISR(&mux);
  //setarValores = true;
  delay(3000);
  }
  bool start_stop = false;
}
