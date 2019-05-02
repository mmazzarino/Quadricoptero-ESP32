void controle_motores(int *vma, int *vmb, int *vmc, int *vmd){
  analogWrite(pma, *vma);
  analogWrite(pmb, *vmb);
  analogWrite(pmc, *vmc);
  analogWrite(pmd, *vmd);
}
