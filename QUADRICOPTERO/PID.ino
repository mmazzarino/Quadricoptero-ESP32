void pidEixoX(){
  ex = gx - sp_gx;
  px = kp * ex;
  ix += ki * ex;
  dx = (kd * ex)/dt;
  pidx = px + ix + dx;
  ex_ant = ex;
}

void pidEixoY(){
  ey = gy - sp_gy;
  py = kp * ey;
  iy += ki * ey;
  dy = (kd * ey)/dt;
  pidy = py + iy + dy;
  ey_ant = ey;
}
