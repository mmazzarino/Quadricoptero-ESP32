#include "CONFIGURACAO.h"

void tempoCiclo(){
  t_total = micros();
  dt = (t_total - t_anterior)/1000000;
  t_anterior = t_total;
}
