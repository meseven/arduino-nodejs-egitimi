#include <Adafruit_SleepyDog.h>
#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_FONA.h"

//Kapadokya GSM Shield için pinler
#define FONA_RX  11
#define FONA_TX  10
#define FONA_RST 4
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

#define FONA_APN        "internet"
#define FONA_USERNAME   ""
#define FONA_PASSWORD   ""
#define AIO_SERVER      "157.230.113.66"
#define AIO_SERVERPORT  1883

Adafruit_MQTT_FONA mqtt(&fona, AIO_SERVER, AIO_SERVERPORT);
#define halt(s) { Serial.println(F( s )); while(1); }
boolean FONAconnect(const __FlashStringHelper *apn, const __FlashStringHelper *username, const __FlashStringHelper *password);

Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe(&mqtt, "LED");

uint8_t txfailures = 0;
#define MAXTXFAILURES 3

#include <TinyGPS.h>
TinyGPS gps;
#define ss Serial1

void setup() {
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);

  ss.begin(9600);

  Serial.begin(9600);
  //while (!Serial);
  Serial.println(F("System started."));
  mqtt.subscribe(&led);

  while (! FONAconnect(F(FONA_APN), F(FONA_USERNAME), F(FONA_PASSWORD))) {
    Serial.println("Retrying FONA");
  }
  Serial.println(F("Connected to Cellular!"));
}

uint32_t x = 0;

void loop() {
  MQTT_connect();

  smartdelay(1000);
  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);
  int alt = gps.f_altitude();
  int spd = gps.f_speed_kmph();
  int crs = gps.f_course();

  String locData = String(flat, 6) + "," + String(flon, 6) + "," + String(alt) + "," + String(spd) + "," + String(crs);
  char locData2[100];
  locData.toCharArray(locData2, 100);

  Serial.print(F("\nSending LOCATION val: ")); Serial.print(locData2); Serial.print(F("..."));

#define QoS 1
#define RETAIN 1

  if (!mqtt.publish("LOCATION", locData2, QoS , RETAIN)) {
    Serial.println(F("Failed"));
    txfailures++;
  } else {
    Serial.println(F("OK!"));
    txfailures = 0;
  }

  //  Watchdog.reset();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &led) {
      Serial.print(F("------------------------------------------------Got: "));
      String gelenVeri = String((char *)led.lastread);
      Serial.println(gelenVeri);
      if (gelenVeri == "on") {
        digitalWrite(13, HIGH);
      }
      else if (gelenVeri == "off") {
        digitalWrite(13, LOW);
      }
      else {
        Serial.print(F("------------------------------------------------ELSE: "));
      }
    }
  }
}

void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
  }
  Serial.println("MQTT Connected!");
}

static void smartdelay(unsigned long ms) {
  unsigned long start = millis();
  do  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
