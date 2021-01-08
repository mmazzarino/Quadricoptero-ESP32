void pidEixoX(){
  ex = gx4 - sp_gx;
  px = kp * ex;
  ix += ki * ex;
  dx = (kd * ex)/dt_micro_s;
  pidx = px + ix + dx;
  ex_ant = ex;
 // Serial.print(pidx);Serial.print("; ");
}

void pidEixoY(){
  ey = gy4 - sp_gy;
  py = kp * ey;
  iy += ki * ey;
  dy = (kd * ey)/dt_micro_s;
  pidy = py + iy + dy;
  ey_ant = ey;
  //Serial.print(pidy);Serial.print("; ");
}
