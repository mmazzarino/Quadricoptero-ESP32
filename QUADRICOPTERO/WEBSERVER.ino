void serverInitialize(){ // handshake 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/joy.html", "text/html");
  });

  server.begin();
  Serial.println("HTTP server started.");
}
                   
