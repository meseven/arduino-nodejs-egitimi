String saat = "";    // hhmmss.00
String enlem = "";   // DDMM.MMMM Kuzey/Güney N/S
String boylam = "";  // DDMM.MMMM Doğu/Batı E/W
String irtifa = "";  // metre

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {

  GPSdinle();

  Serial.print("Saat: ");
  Serial.println(saat);
  Serial.print("Enlem: ");
  Serial.println(enlem);
  Serial.print("Boylam: ");
  Serial.println(boylam);
  Serial.print("irtifa: ");
  Serial.println(irtifa);
  Serial.println();
}

void GPSdinle() {

  // $GPGGA arıyoruz
  if ( Serial1.find("$GPGGA,") ) {

    // Gelen veriyi parçalıyoruz
    saat = Serial1.readStringUntil(',');
    enlem = Serial1.readStringUntil(',');
    enlem.concat(Serial1.readStringUntil(','));
    boylam = Serial1.readStringUntil(',');
    boylam.concat(Serial1.readStringUntil(','));

    // irtifaya kadar olan kısmı atlıyoruz
    for ( int i = 0; i < 3; i++ ) {
      Serial1.readStringUntil(',');
    }

    // irtifa verisini parçalıyoruz
    irtifa = Serial1.readStringUntil(',');
    irtifa.concat(Serial1.readStringUntil(','));

    // Verinin geri kalanını atlıyoruz
    Serial1.readStringUntil('\r');
  }
}
