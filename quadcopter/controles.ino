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
  if(c_sub == HIGH and *vma < 179 and *vmb < 179 and *vmc < 179 and *vmd < 179){
    *vma += 9;
    *vmb += 9;
    *vmc += 9;
    *vmd += 9;
    delay(tempo_press);
  }
}
