#include "configuration.h"

void tempoCiclo(){
  t_total = micros();
  dt = t_total - t_anterior;
  t_anterior = t_total;
}
