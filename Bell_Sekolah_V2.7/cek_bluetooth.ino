//---Cek Pengiriman Bluetooth---//
void cekBluetooth() {
  bluetooth.listen();
  uint8_t tokenMulai;
  uint8_t perintah;
  uint8_t parameter;
  uint8_t panjang1;
  uint8_t panjang2;
  char c;
  uint8_t i, j;
  uint8_t tokenSelesai;
  byte bufferSerial[100];
  byte *alamat;
  uint8_t nilai_data = 0;
  uint8_t nilai_data2[6];

  if (bluetooth.available()) {
    tokenMulai = bluetoothRead();
    if (tokenMulai == 0xFD) {
      panjang1 = bluetoothRead();
      panjang2 = bluetoothRead();

      if (panjang2 == 254 - panjang1) {
        if (panjang1 >= sizeof(bufferSerial)) {
          panjang1 = sizeof(bufferSerial);
        }

        uint16_t timeOut = 0xFFF;
        i = 0;
        do {
          if (bluetooth.available()) {
            c = bluetoothRead();
            bufferSerial[i++] = c;
          }
        }
        while ((i < panjang1 + 3) && (timeOut--));

        perintah = bufferSerial[0];
        parameter = bufferSerial[1];
        tokenSelesai = bufferSerial[i - 1];

        if (tokenSelesai == 0x00) {
          lcd.backlight();
          ms_backlight = millis();
          delay(10);
          bluetooth.write(254);
          switch (perintah) {
            case cekAses:
              bluetooth.write(1);
              bluetooth.write(254);
              break;
            case pengaturanJadwal:
              lcd.setCursor(6, 1);
              lcd.print((char)5);
              memcpy((byte*)&jadwalBelajar[parameter], bufferSerial + 2, sizeof(TabelMataPelajaran));
              if (parameter == (sizeof(jadwalBelajar) / sizeof(TabelMataPelajaran)) - 1) {
                digitalWrite(buzzer, HIGH);
                EEPROM.put(0, jadwalBelajar);
                //Serial.println("Jadwal diterima");

                lcd.setCursor(6, 1);
                lcd.print(F(" "));
                delay(50);
                tanggalSebelumnya = 0;
                digitalWrite(buzzer, LOW);
                //cekJadwalHariIni();
              }
              break;
            case pengaturanWaktu:
              memcpy((byte*)&now, bufferSerial + 2, sizeof(DateTime));
              rtc.adjust(now);
              //lcd.setCursor(6, 1);
              //lcd.print(F(" "));
              digitalWrite(buzzer, HIGH);
              delay(50);
              digitalWrite(buzzer, LOW);
              tanggalSebelumnya = 0;
              //Serial.println("Setting waktu diterima");
              break;
            case testMp3:
              memcpy((byte*)&nilai_data, bufferSerial + 2, 4);
              //Serial.println(nilai_data);

              if (parameter == 1) {
                if (digitalRead(pinRelay) == !relayOn) {
                  lcd.setCursor(0, 0);
                  lcd.print(F("!Hidupkan Ampli "));
                  notif = true;
                  ms_notif = millis();
                }
                else {
                  myDFPlayer.play(nilai_data + 2);
                }
              }
              else if (parameter == 2) {
                myDFPlayer.pause();
              }
              else if (parameter == 3) {
                EEPROM.write(sizeof(jadwalBelajar) + 1, nilai_data); //daat volume dfplayer
                delay(50);
                volume_dfplayer = EEPROM.read(sizeof(jadwalBelajar) + 1);
                myDFPlayer.volume(volume_dfplayer);
              }
              else if (parameter == 4) {
                EEPROM.write(sizeof(jadwalBelajar) + 2, nilai_data); //daat costum nada
                delay(50);
                costum_nada = EEPROM.read(sizeof(jadwalBelajar) + 2);
              }
              else if (parameter == 5) {
                for (int k = 0; k < (sizeof(jadwalBelajar) / sizeof(TabelMataPelajaran)); k++) {
                  jadwalBelajar[k] = {TidakAktif, _waktu(  0, 0 ), _hariAktif(0, 0, 0, 0, 0, 0, 0), TidakAda};
                }
                //jadwalBelajar = 0;
                EEPROM.put(0, jadwalBelajar);
                delay(50);
                tanggalSebelumnya = 0;
              }
              digitalWrite(buzzer, HIGH);
              delay(50);
              digitalWrite(buzzer, LOW);
              break;

            case settings:
              memcpy((byte*)&nilai_data2[parameter], bufferSerial + 2, 4);
              lcd.setCursor(6, 1);
              lcd.print((char)5);

              if (parameter == sizeof(nilai_data2) - 1) {
                for (int k = 1; k < sizeof(nilai_data2); k++) {
                  //Serial.print(nilai_data2[k]);
                  if (k != 3) {
                    if (k >= 4) {
                      EEPROM.write(sizeof(jadwalBelajar) + (k + 10) - 1, nilai_data2[k]); //data amplifier
                    } else {
                      EEPROM.write(sizeof(jadwalBelajar) + (k + 10), nilai_data2[k]); //data amplifier
                    }
                  }
                }

                digitalWrite(buzzer, HIGH);
                delay(50);
                eeprom_setting_read();
                digitalWrite(buzzer, LOW);
                lcd.setCursor(6, 1);
                lcd.print(F(" "));
                //Serial.println("");
              }

              //              if (parameter == 1) {
              //                EEPROM.write(sizeof(jadwalBelajar) + 11, nilai_data); //data amplifier
              //              }
              //              else if (parameter == 2) {
              //                EEPROM.write(sizeof(jadwalBelajar) + 12, nilai_data); //data Repeat
              //              }
              //              else if (parameter == 3) {
              //                EEPROM.write(sizeof(jadwalBelajar) + 13, nilai_data); //data lcd backlight
              //              }
              //              else if (parameter == 4) {
              //                EEPROM.write(sizeof(jadwalBelajar) + 14, nilai_data); //data jeda ampli
              //                digitalWrite(buzzer, HIGH);
              //                delay(50);
              //                digitalWrite(buzzer, LOW);
              //                eeprom_setting_read();
              //                lcd.setCursor(6, 1);
              //                lcd.print(F(" "));
              //                Serial.println("");
              //              }
              break;
          }
        }
        else
        {
          bluetooth.write(252);//data tidak benar
        }
      }
    }
  }
}

byte bluetoothRead() {
  uint16_t timeOut = 0xFFF;
  while (!bluetooth.available() && timeOut--);
  return bluetooth.read();
}

//---END Cek Pengiriman Bluetooth---//
