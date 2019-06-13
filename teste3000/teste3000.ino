#include <WiFi.h>
#include "index.h"
#include<Wire.h>
// Replace with your network credentials
const char* ssid     = "embarcados";
const char* password = "embarcados";


WiFiServer server(80);
unsigned long t_total, t_anterior, dt = 0;


String header;

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {    
    Serial.print(".");
    delay(500); 
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  
  
}

void loop(){
 
  WiFiClient client = server.available();   // Listen for incoming clients
           String a = MAIN_pageA;
  String b = MAIN_pageB;
  String c = MAIN_pageC;
  String d = MAIN_pageD;
  String e = MAIN_pageE;
  String f = MAIN_pageF;
  String g = MAIN_pageG;
  String h = MAIN_pageH;
  String i = MAIN_pageI;
  String j = MAIN_pageJ;
  String k = MAIN_pageK;
  String l = MAIN_pageL;
  String m = MAIN_pageM;
  String n = MAIN_pageN;
  String o = MAIN_pageO;
    
  if (client) {    
    Serial.println("New Client.");
        client.println(a);
        client.println(b);
        client.println(c);
        client.println(d);
        client.println(e);
        client.println(f);
        client.println(g);
        client.println(h);
        client.println(i);
        client.println(j);
        client.println(k);
        client.println(l);
        client.println(m);
        client.println(n);
        client.println(o);
 
    String currentLine = "";              
    
    while (client.connected()) {           
      if (client.available()) {            
        char c = client.read();            
        Serial.write(c);                    
        header += c;
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
        
            t_total = micros();
            dt = t_total - t_anterior;
            t_anterior = t_total; 
             
              Serial.println(header);                       
              Serial.print(t_total);
              Serial.print("   ");
              Serial.println(dt);
              delay(500);
              
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            
              
            
    
            client.println();

            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }


    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
