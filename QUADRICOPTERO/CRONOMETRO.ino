void tempoCiclo(){
  t_total = xTaskGetTickCount();  
  dt_s = (t_total - t_anterior)/1000;
  dt_mili_s = (t_total - t_anterior);
  dt_micro_s = (t_total - t_anterior);
  t_anterior = t_total;
 
}
