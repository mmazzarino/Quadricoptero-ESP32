void setPointsInclinacao(){ 
  switch(movX){
    case -4: sp_gx = ; break;
    case -3: sp_gx = ; break;
    case -2: sp_gx = ; break;
    case -1: sp_gx = ; break;
    case 0:  sp_gx = ; break;
    case 1:  sp_gx = ; break;
    case 2:  sp_gx = ; break;
    case 3:  sp_gx = ; break;
    case 4:  sp_gx = ; break;
    default: break;
    }

  switch(movY){
    case -4: sp_gy = ; break;
    case -3: sp_gy = ; break;
    case -2: sp_gy = ; break;
    case -1: sp_gy = ; break;
    case 0:  sp_gy = ; break;
    case 1:  sp_gy = ; break;
    case 2:  sp_gy = ; break;
    case 3:  sp_gy = ; break;
    case 4:  sp_gy = ; break;
    default: break;
    }
}

void setPointsGiroZ(){
  switch(giro){
    case -1: sp_gz -= ; giro = 0; break;
    case 1:  sp_gz += ; giro = 0; break;
    case 0:  null; break;
    default: break;              
  } 
}

void setPointsPotencia(){  
}
