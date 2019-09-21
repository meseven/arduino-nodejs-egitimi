//YouTube: https://www.youtube.com/ArduinoHaberTV
#include <ArduinoHaberGSM.h> // İlk Türkçe GSM Kütüphanesi
ArduinoHaberGSM GSMr;
String smsMetni, smsNumarasi;
#define gonderilecekTelNumarasi  "+905321231212" // Numarayı değiştirmeyi unutmayın :) 
#define LM35_pin A0

void setup() {
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

      if (smsMetni.indexOf("HAVA KAC DERECE?") != -1) {
        Serial.println("Hava SMSi Geldi");
        String Sicaklik = String(analogRead(LM35_pin) * 0.48828125);
        String Sicaklik2 = "Hava " + Sicaklik + " derece.";
        char SicaklikSMS2[] = "";
        Sicaklik2.toCharArray(SicaklikSMS2, 30);
        Serial.println(SicaklikSMS2);
        GSMr.smsGonder(gonderilecekTelNumarasi, SicaklikSMS2);
      }
      else {
        Serial.println("Tanimsiz SMS............");
      }
      GSMr.tumSmsSil();
    }
  }
}
