void setup() {
   Serial.begin(115200);
   
}



void loop() {
  uint16_t packet = ((uint16_t)1046 << 1);
  int csum = 0;
  int csum_data = packet;
  for (int i = 0; i < 3; i++) {
      csum ^=  csum_data;   
      csum_data >>= 4;
    }
/*
10000010110
01101000001
00010110100
01000001011
10110100000
*/    
csum &= 0xf; //0xf = '1111'
  packet = (packet << 4) | csum;
/*
01000001011
*/
  for (int i = 0; i < 16; i++) {
       Serial.print((packet & 0x8000) ? 1 : 0);  // MSB first // 0x8000='1000000000000000'
        packet <<= 1;
    }
   // Serial.print("csum: " + String(csum));
   
    
    Serial.println("");
    delay(2000);

}
