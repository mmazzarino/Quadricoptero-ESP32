void controle_motores(int *vma, int *vmb, int *vmc, int *vmd){
  motor_a.write(*vma);
  motor_b.write(*vmb);
  motor_c.write(*vmc);
  motor_d.write(*vmd);
}
