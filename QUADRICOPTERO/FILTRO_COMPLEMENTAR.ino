void filtroComplementar(){
  ax2 = ((ax1 * GRAVI)/CALIB);
  ay2 = ((ay1 * GRAVI)/CALIB);
  az2 = ((az1 /** GRAVI*/)/CALIB);   

  //Converte valor do acelerometro com base nos 3 eixos
  ax3 = (atan2(ax1, sqrt(pow(ay1, 2) + pow(az1, 2))))* radToDegr; 
  ay3 = (atan2(ay1, sqrt(pow(ax1, 2) + pow(az1, 2))))* radToDegr; 
  az3 = (atan2(az1, sqrt(pow(ax1, 2) + pow(ay1, 2))))* radToDegr; 

  // Converte valor do giro em graus por seg multiplicando uma contante relacionada à taxa de amostragem do sensor
  gr_por_seg_x = gx1 * SENSE_GYRO_2000; 
  gr_por_seg_y = gy1 * SENSE_GYRO_2000; 
  gr_por_seg_z = gz1 * SENSE_GYRO_2000; 

  // Calcula a distância percorrida por integração simples
  gx3 += (gr_por_seg_x * dt_s);
  gy3 += (gr_por_seg_y * dt_s);
  gz3 += (gr_por_seg_z * dt_s);

  // Fusão dos dados: giro + accel

  Serial.print("inicio;");Serial.print(xTaskGetTickCount());Serial.print(";");

//mais rápido, mas com mais ruido
 /* gx4= ((0.98 *((gx4 + gr_por_seg_x) * dt_s)) + (0.02 * ax3))*50;
  gy4= ((0.98 *((gy4 + gr_por_seg_y) * dt_s)) + (0.02 * ay3))*50;
  gz4= ((0.98 *((gz4 + gr_por_seg_z) * dt_s)) + (0.02 * az3))*50;
*/

//menos ruido e bem mais lento

  gx4 = ((0.98 *(gx4 + (gr_por_seg_x * dt_s))) + (0.02 * ax3));
  gy4 = ((0.98 *(gy4 + (gr_por_seg_y * dt_s))) + (0.02 * ay3));
  gz4 = ((0.98 *(gz4 + (gr_por_seg_z * dt_s))) + (0.02 * az3));

/*
  gx4 = ((0.90 *(gx4 + (gr_por_seg_x * dt_s))) + (0.1 * ax3));
  gy4 = ((0.90 *(gy4 + (gr_por_seg_y * dt_s))) + (0.1 * ay3));
  gz4 = ((0.90 *(gz4 + (gr_por_seg_z * dt_s))) + (0.1 * az3));
  */
/*
  Serial.print("dt_s: ;");Serial.print(dt_s);Serial.print("; ");
  Serial.print("dt_mili_s: ;");Serial.print(dt_mili_s);Serial.print("; ");
  Serial.print("ax3: ;");Serial.print(ax3);Serial.print("; ");
  Serial.print("ay3: ;");Serial.print(ay3);Serial.print("; ");
  Serial.print("az3: ;");Serial.print(az3);Serial.print("; ");
  Serial.print("gx: ;");Serial.print(gx4);Serial.print("; ");
  Serial.print("gy: ;");Serial.print(gy4);Serial.print("; ");
  Serial.print("gz: ;");Serial.print(gz4);Serial.print("; ");

  
  

  Serial.print("fim;");Serial.print(xTaskGetTickCount());Serial.println(";");*/
}
