WiFiServer server(80);                                        // define a porta do web server

void webServerInitialize(){
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
   
   Serial.println("");                                         // Print local IP address and start web server
   Serial.println("WiFi connected.");
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
   server.begin();
}

void comunicacaoWebServer(){
  WiFiClient client = server.available();                      // Listen for incoming clients
  
  if (client) {                                                // If a new client connects,
    Serial.println("New Client.");                             // print a message out in the serial port
    String currentLine = "";                                   // make a String to hold incoming data from the client
    while (client.connected()) {                               // loop while the client's connected
      if (client.available()) {                                // if there's bytes to read from the client,
        char c = client.read();                                // read a byte, then
        Serial.write(c);                                       // print it out the serial monitor
        header += c;
        if (c == '\n') {                                       // if the byte is a newline character
                                                               // if the current line is blank, you got two newline characters in a row.
                                                               // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
                                                               // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                                                               // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
                                                               // turns the GPIOs on and off
          

              if(header.indexOf("GET /subir") >= 0){
                 if(subir < 8){
                  subir += 1;                                                                         
                 }
              }
             
              else if(header.indexOf("GET /decer") >= 0){           
                 if(subir > -8){
                  subir -= 1;
                 }
              }
                 
                  
              else if(header.indexOf("GET /girar/esq") >= 0){
                 if(giro < 1){
                  giro += 1;
                 }
              }

              else if(header.indexOf("GET /girar/dir") >= 0){
                 if(giro > -1){
                  giro -= 1;
                 }    
              } 

              else if(header.indexOf("GET /mov/frente") >= 0){
                 if(movX < 4){
                  movX += 1;          
                 }   
              }              

              else if(header.indexOf("GET /mov/tras") >= 0){
                 if(movX > -4){
                  movX -= 1;
                 }       
              }        

              else if(header.indexOf("GET /mov/esq") >= 0){
                 if(movY < 4){
                  movY += 1;
                 }
              }               

              else if(header.indexOf("GET /mov/dir") >= 0){
                 if(movY > -4){
                  movY -= 1;
                 }
              }               
              
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");;
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");

            client.println("<p><a href=\"/subir\"><button class=\"button\">Subir</button></a></p>");
            client.println("<p><a href=\"/decer\"><button class=\"button button2\">Decer</button></a></p>");
            client.println("<p><a href=\"/girar/esq\"><button class=\"button\">Giro Esquerda</button></a></p>");
            client.println("<p><a href=\"/girar/dir\"><button class=\"button button2\">Giro Direita</button></a></p>");
            client.println("<p><a href=\"/mov/frente\"><button class=\"button\">Movimento Frente</button></a></p>");
            client.println("<p><a href=\"/mov/tras\"><button class=\"button button2\">Movimento Tras</button></a></p>");
            client.println("<p><a href=\"/mov/dir\"><button class=\"button\">Movimento Direita</button></a></p>");
            client.println("<p><a href=\"/mov/esq\"><button class=\"button button2\">Movimento Esquerda</button></a></p>");

            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
