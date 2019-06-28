void startWebSocket() {  
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("WebSocket server started.");
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
    
      break;
    case WStype_CONNECTED: {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      }
      break;
    case WStype_TEXT:{
      Serial.printf("[%u] get Text: %s", num, payload);
      x = atoi((const char *)&payload[3]);
      y = atoi((const char *)&payload[9]);
      j = atoi((const char *)&payload[15]);
      k = atoi((const char *)&payload[21]);
      Serial.printf("         %d, %d, %d, %d \n", x, y, j, k);
    }
      break;
  }
}
