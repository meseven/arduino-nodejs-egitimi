//YouTube: https://www.youtube.com/ArduinoHaberTV
#include <ArduinoHaberGSM.h> // İlk Türkçe GSM Kütüphanesi
ArduinoHaberGSM GSMr;
String smsMetni, smsNumarasi;
#define gonderilecekTelNumarasi  "+905321231212" // Numarayı değiştirmeyi unutmayın :) 
#define LED_pin 13

void setup() {
  pinMode(LED_pin, OUTPUT);
  Serial.begin(9600);
  GSMr.basla();
  GSMr.tumSmsSil();
  Serial.println("Sistem Calisiyor");
  GSMr.smsGonder(gonderilecekTelNumarasi, "Sistem acildi.");
}

void loop() {
  smsMetni = GSMr.smsOku(1);
  if (smsMetni.indexOf("OK") != -1) {
    if (smsMetni.length() > 7) {
      smsNumarasi = GSMr.numaraliSmsOku(1);
      Serial.println(smsNumarasi);
      smsMetni.toUpperCase();
      
      if (smsMetni.indexOf("LEDAC") != -1) {
        Serial.println("LED ACILDI");
        digitalWrite(LED_pin, HIGH);
        GSMr.smsGonder(gonderilecekTelNumarasi, "LED Acildi");
      }
      else if (smsMetni.indexOf("LEDKAPAT") != -1) {
        Serial.println("LED KAPATILDI");
        digitalWrite(LED_pin, LOW);
        GSMr.smsGonder(gonderilecekTelNumarasi, "LED Kapatildi");
      }
      else {
        Serial.println("Tanimsiz SMS............");
      }
      GSMr.tumSmsSil();
    }
  }
}
