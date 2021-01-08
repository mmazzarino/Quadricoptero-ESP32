void setup() {
    Serial.begin(9600);
    pinMode(13,OUTPUT);

    ledcAttachPin(13, 0);//Atribuimos o pino 2 ao canal 0.
    ledcSetup(0, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.
}


void loop(){
    unsigned char aux = 0;
    if(!Serial.available()){
        aux = Serial.read();     
    }
        ledcWrite(0, aux); 
}
