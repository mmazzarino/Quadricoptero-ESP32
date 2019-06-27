//#include "BIBLIOTECAS.h"
#include "DEFINICOES.h"

void wifiInitialize(){
  const char *ssid = "embarcados";                  
  const char *password = "embarcados";
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println(WiFi.localIP());
}
