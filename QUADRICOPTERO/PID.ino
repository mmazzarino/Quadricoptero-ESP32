//#include "BIBLIOTECAS.h"
#include "DEFINICOES.h"

void pidEixoX(){
  ex = gx - sp_gx;
  px = kp * ex;
  ix += ki * ex;
  dx = (kd * ex)/dt;
  pidx = px + ix + dx;                            //testar também sem a ação derivativa
  ex_ant = ex;
}

void pidEixoY(){
  ey = gy - sp_gy;
  py = kp * ey;
  iy += ki * ey;
  dy = (kd * ey)/dt;
  pidy = py + iy + dy;                            //testar também sem a ação derivativa
  ey_ant = ey;
}
