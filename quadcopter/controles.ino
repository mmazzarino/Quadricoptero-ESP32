#define tempo_aceleracao
#define f_peso;

void config_controles(){
  pinMode(c_sub, INPUT);                     
  pinMode(c_dec, INPUT);                      
  pinMode(c_gir_esq, INPUT);                   
  pinMode(c_gir_dir, INPUT);                   
  pinMode(c_mov_fre, INPUT);                    
  pinMode(c_mov_tra, INPUT);                    
  pinMode(c_mov_esq, INPUT);                   
  pinMode(c_mov_dir, INPUT);
}

void read_controls(int *vma, int *vmb, int *vmc, int *vmd){
  if(c_sub == HIGH and *vma = 0 and *vmb = 0 and *vmc = 0 and *vmd = 0){
    while((*vma < f_peso) and (*vmb < f_peso) and (*vmc < f_peso) and (*vmd < f_peso)){
      *vma += 1;
      *vmb += 1;
      *vmc += 1;
      *vmd += 1;
    } 
    delay(tempo_aceleracao);
  }
  if(c_mov_fre = HIGH){
    *sp_gx += 1;
    delay(tempo_aceleracao);
  }
  
}
