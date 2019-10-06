#include <Adafruit_SleepyDog.h>
#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_FONA.h"

#define FONA_RX  11
#define FONA_TX  10
#define FONA_RST 4
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

#define FONA_APN       "internet"
#define FONA_USERNAME  ""
#define FONA_PASSWORD  ""
#define AIO_SERVER      "167.71.181.108"
#define AIO_SERVERPORT  1883

Adafruit_MQTT_FONA mqtt(&fona, AIO_SERVER, AIO_SERVERPORT);
#define halt(s) { Serial.println(F( s )); while(1);  }
boolean FONAconnect(const __FlashStringHelper *apn, const __FlashStringHelper *username, const __FlashStringHelper *password);

Adafruit_MQTT_Publish loc = Adafruit_MQTT_Publish(&mqtt, "LOCATION");
Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe(&mqtt, "LED");

uint8_t txfailures = 0;
#define MAXTXFAILURES 3

void setup() {
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

  Watchdog.reset();
  MQTT_connect();

  if (digitalRead(A0) || true) {
    Serial.println(F("\nBUTONA BASILDI ################################"));
    Watchdog.reset();
    Serial.print(F("\nSending LOCATION val ")); Serial.print(x); Serial.print("...");
    //if (!loc.publish(x++)) {
    if (!loc.publish("23.34234354,34.4564564564,4,5,emre,mehmet,udemy,01234567891011121314151617181920")) {
      Serial.println(F("Failed"));
      txfailures++;
    } else {
      Serial.println(F("OK!"));
      txfailures = 0;
    }
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
