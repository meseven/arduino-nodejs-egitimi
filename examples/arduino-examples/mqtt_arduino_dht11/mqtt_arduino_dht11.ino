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

Adafruit_MQTT_Publish tem = Adafruit_MQTT_Publish(&mqtt, "TEMP");
Adafruit_MQTT_Publish loc = Adafruit_MQTT_Publish(&mqtt, "LOCATION");
Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe(&mqtt, "LED");

uint8_t txfailures = 0;
#define MAXTXFAILURES 3

#include "DHT.h"
DHT dht(A1, DHT11);

void setup() {
  dht.begin();

  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);

  Serial.begin(9600);
  Serial.println(F("System started."));
  mqtt.subscribe(&led);

  Watchdog.reset();
  delay(5000);
  Watchdog.reset();

  while (! FONAconnect(F(FONA_APN), F(FONA_USERNAME), F(FONA_PASSWORD))) {
    Serial.println("Retrying FONA");
  }
  Serial.println(F("Connected to Cellular!"));
  Watchdog.reset();
  delay(5000);
  Watchdog.reset();
}

uint32_t x = 0;

void loop() {
  int t = dht.readTemperature();

  Watchdog.reset();
  MQTT_connect();

  //if (digitalRead(A0)) {
  if (false) {
    Serial.println(F("\nButton Pressed ################################"));
    Watchdog.reset();
    Serial.print(F("\nSending LOCATION val ")); Serial.print("...");
    if (!loc.publish("emre,mehmet,udemy")) {
      Serial.println(F("Failed"));
      txfailures++;
    } else {
      Serial.println(F("OK!"));
      txfailures = 0;
    }
  }


  char temp2[4];
  String str = String(t);
  str.toCharArray(temp2, 4);
  Serial.print(F("temp2: ")); Serial.println(temp2);

  Watchdog.reset();
  Serial.print(F("\nSending temp2 val ")); Serial.print("...");
  if (!tem.publish(temp2)) {
    Serial.println(F("Failed"));
    txfailures++;
  } else {
    Serial.println(F("OK!"));
    txfailures = 0;
  }


  Watchdog.reset();

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

  /*
    if (!mqtt.ping()) {
      Serial.println(F("MQTT Ping failed."));
    }
  */
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
