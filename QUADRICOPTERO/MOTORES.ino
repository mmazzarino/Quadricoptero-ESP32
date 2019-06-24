#include "CONFIGURACAO.h"

void pinsMotorsInitialize(){
   pinMode(pma, OUTPUT);
   pinMode(pmb, OUTPUT);
   pinMode(pmc, OUTPUT);
   pinMode(pmd, OUTPUT);

  ledcSetup(canalMa, freq, resolucao);
  ledcSetup(canalMb, freq, resolucao);
  ledcSetup(canalMc, freq, resolucao);
  ledcSetup(canalMd, freq, resolucao);    

  ledcAttachPin(pma, canalMa);
  ledcAttachPin(pmb, canalMb);
  ledcAttachPin(pmc, canalMc);
  ledcAttachPin(pmd, canalMd);
}


void definePWM(){
   if(potencia != 0){
    vma = potencia + pidx - pidy;
    vmc = potencia + pidx + pidy;
    vmb = potencia - pidx - pidy;
    vmd = potencia - pidx + pidy;
   
    if(vma > 254){
      vma = 255;
     }
    else if(vma < 100){
      vma = 100;
     }
   
    if(vmb > 254){
      vmb = 255;
    }
    else if(vmb < 100){
      vmb = 100;
    }
   
    if(vmc > 254){
      vmc = 255;
    }
    else if(vmc < 100){
      vmc = 100;
    }  
   
    if(vmd > 254){
      vmd = 255;
    }
    else if(vmd < 100){
      vmd = 100;
    }
  }
  else if(potencia == 0){
    vma = potencia;
    vmb = potencia;
    vmc = potencia;
    vmd = potencia;
  }
   
   ledcWrite(canalMa, vma);
   ledcWrite(canalMb, vmb);
   ledcWrite(canalMc, vmc);
   ledcWrite(canalMd, vmd);
}


  
 
  
  /*
//---------------------movimento para frente-----------------------
  if(sp_gx > gx){
    erroX = sp_gx - gx;
    px = ex * cpx;
    ix = (cix * ex) * dt;
    dx = (cdx * ex) / dt;
    pidx = px + ix + dx;
    if((vma > vmc) and (vmd > vmb)){
      vma--;
      vmd--;
    }
    else if((vma <= vmc) and (vmd <= vmb){
      vmc++;
      vmb++;
    }
  }
  
//---------------------movimento para trás-------------------------
  if(sp_gx < gx){
    if((vmc > vma) and (vmb > vmd)){
      vmc--;
      vmb--;
    }
    else if((vmc <= vma) and (vmb <= vmd){
      vma++;
      vmd++;
    }
  }

//---------------------movimento para esquerda---------------------
  if(sp_gy > gy){
    if((vmd > vma) and (vmb > vmc)){
      vmd--;
      vmb--;
    } 
    else if((vmd <= vma) and (vmb <= vmc)){
      vma++;
      vmc++; 
  }

//---------------------movimento para direita----------------------
  if(sp_gy < gy){
    if((vma > vmd) and (vmc > vmb)){
      vma--;
      vmc--;
    } 
    else if((vma <= vmd) and (vmc <= vmb)){
      vmd++;
      vmb++; 
    }
  }



     if(sp_gy > gy){
    if(()and()){
    } 
  }
  
    
     
  }
}*/
