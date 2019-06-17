void startWebSocket() { // Start a WebSocket server
  webSocket.begin();                          // start the websocket server
  webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  Serial.println("WebSocket server started.");
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) { // When a WebSocket message is received
  switch (type) {
    case WStype_DISCONNECTED:{             // if the websocket is disconnected
      Serial.printf("[%u] Disconnected!\n", num);
    }
      break;
    case WStype_CONNECTED:{               // if a new websocket connection is established
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        //rainbow = false;                  // Turn rainbow off when a new connection is established
  }
      break;
    case WStype_TEXT:{                     // if new text data is received
      Serial.printf("[%u] get Text: %s\n", num, payload);
      int x = atoi((const char *)&payload[3]);
      int y = atoi((const char *)&payload[9]);
      int j = atoi((const char *)&payload[15]);
      int k = atoi((const char *)&payload[21]);
      Serial.printf("%d, %d, %d, %d", x+1, y+2, j+3, k);
    }
      break;
  }
}
