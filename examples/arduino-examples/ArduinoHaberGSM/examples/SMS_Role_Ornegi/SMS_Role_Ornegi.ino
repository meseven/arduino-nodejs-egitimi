//YouTube: https://www.youtube.com/ArduinoHaberTV#include <ArduinoHaberGSM.h> // İlk Türkçe GSM Kütüphanesi
ArduinoHaberGSM GSMr;
String smsMetni, smsNumarasi;
#define gonderilecekTelNumarasi  "+905321231212" // Numarayı değiştirmeyi unutmayın :) 
#define LED_pin 13
#define role1 2
#define role2 3

void setup() {
  pinMode(LED_pin, OUTPUT);
  pinMode(role1, OUTPUT);
  pinMode(role2, OUTPUT);
  digitalWrite(role1, HIGH);
  digitalWrite(role2, HIGH);
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
      ///////////////////////////////LED///////////////////////////////
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

      ///////////////////////////////RÖLE1///////////////////////////////
      else if (smsMetni.indexOf("ROLE1AC") != -1) {
        Serial.println("Role1 Acildi");
        digitalWrite(role1, !HIGH);
        GSMr.smsGonder(gonderilecekTelNumarasi, "Role1 Acildi");
      }
      else if (smsMetni.indexOf("ROLE1KAPAT") != -1) {
        Serial.println("Role1 Kapatildi");
        digitalWrite(role1, !LOW);
        GSMr.smsGonder(gonderilecekTelNumarasi, "Role1 Kapatildi");
      }

      ///////////////////////////////RÖLE2///////////////////////////////
      else if (smsMetni.indexOf("ROLE2AC") != -1) {
        Serial.println("Role2 Acildi");
        digitalWrite(role2, !HIGH);
        GSMr.smsGonder(gonderilecekTelNumarasi, "Role2 Acildi");
      }
      else if (smsMetni.indexOf("ROLE2KAPAT") != -1) {
        Serial.println("Role2 Kapatildi");
        digitalWrite(role2, !LOW);
        GSMr.smsGonder(gonderilecekTelNumarasi, "Role2 Kapatildi");
      }

      ///////////////////////////////TEST MESAJI///////////////////////////////
      else if (smsMetni.indexOf("NBR") != -1) {
        Serial.println("nbr mesajı geldi");
        GSMr.smsGonder(gonderilecekTelNumarasi, "iyilik senden naber");
      }

      ///////////////////////////////TANIMLI OLMAYAN MESAJ///////////////////////////////
      else {
        Serial.println("Tanimsiz SMS............");
      }
      GSMr.tumSmsSil();
    }
  }
}
