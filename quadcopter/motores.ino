void controle_motores(int *vma, int *vmb, int *vmc, int *vmd){
  analogWrite(pma, *vma);
  analogWrite(pmb, *vmb);
  analogWrite(pmc, *vmc);
  analogWrite(pmd, *vmd);
}

void controle_pid_estabilidade(float *ax, float *ay, float *az, float *gx, float *gy, float *gz, float *sp_ax, float *sp_ay, float *sp_az, float *sp_gx, float *sp_gy, float *sp_gz){
  float erro_ax, erro_ay, erro_az, erro_gx, erro_gy, erro_gz;
  erro_ax = *sp_ax - *ax;
  erro_ay = *sp_ay - *ay;
  erro_az = *sp_az - *az;
  erro_gx = *sp_gx - *gx;
  erro_gy = *sp_gy - *gy;
  erro_gz = *sp_gz - *gz; 
}
