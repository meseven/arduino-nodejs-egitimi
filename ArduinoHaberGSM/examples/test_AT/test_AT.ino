//YouTube: https://www.youtube.com/ArduinoHaberTV
#include <SoftwareSerial.h>
SoftwareSerial gsm(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  while (!Serial);
  gsm.begin(9600);
}

void loop() {
  if (gsm.available()) {
    Serial.write(gsm.read());
  }
  if (Serial.available()) {
    gsm.write(Serial.read());
  }
}
