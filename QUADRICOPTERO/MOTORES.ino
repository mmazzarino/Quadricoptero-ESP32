void setaValoresMotores(){
      portENTER_CRITICAL_ISR(&mux);
          dshotUserInputValue1 = (uint16_t)(potencia - pidx + pidy);
          dshotUserInputValue2 = (uint16_t)(potencia + pidx + pidy);
          dshotUserInputValue3 = (uint16_t)(potencia - pidx - pidy);
          dshotUserInputValue4 = (uint16_t)(potencia + pidx - pidy);
      portEXIT_CRITICAL_ISR(&mux);
}
