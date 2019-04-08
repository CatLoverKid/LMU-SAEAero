#include <SoftwareSerial.h>

SoftwareSerial XBee(52, 50); // RX, TX

void setup(){
  Serial.begin(9600);
  XBee.begin(9600);
}

// Receiver Code
void loop() {
  if(XBee.available()){
    Serial.print((char)XBee.read());
  }
    if(Serial.available()){
    XBee.print((char)Serial.read());
  }
}
