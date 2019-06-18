#include "configuration.h"

void pinsMotorsInitialize(){
   pinMode(pma, OUTPUT);
   pinMode(pmb, OUTPUT);
   pinMode(pmc, OUTPUT);
   pinMode(pmd, OUTPUT);
}

void definePWM(){
/*---------------------movimento para frente-----------------------*/
  if(sp_gx > gx){
    if((vma > vmc) and (vmd > vmb)){
      vma--;
      vmd--;
    }
    else if((vma <= vmc) and (vmd <= vmb){
      vmc++;
      vmb++;
    }
  }
  
/*---------------------movimento para trás-------------------------*/
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

/*---------------------movimento para esquerda---------------------*/
  if(sp_gy > gy){
    if((vmd > vma) and (vmb > vmc)){
      vmd--;
      vmb--;
    } 
    else if((vmd <= vma) and (vmb <= vmc)){
      vma++;
      vmc++; 
  }

/*---------------------movimento para direita----------------------*/
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
}
