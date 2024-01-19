void cek_error() {
  now = rtc.now();
  if (now.jam == 165) {
    err_rtc = true;
  }

  if (rtc.lostPower()) {
    //Serial.println(F("RTC lost power, lets set the time!"));
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  if (now.tahun < 2022) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  //---Cek DFrobotDFplayer---//
  //Serial.begin(9600);
  //mySoftwareSerial.begin(9600);
  //Serial.println();
  //Serial.println("DFPlayer Mini Demo");
  //Serial.println("Initializing DFPlayer...");

  if (!myDFPlayer.begin(mySoftwareSerial)) {
    err_df = true;
    //Serial.println("Unable to begin:");
    //Serial.println("1.Please recheck the connection!");
    //Serial.println("2.Please insert the SD card!");
    //while (true);
  }
  //Serial.println(F("DFPlayer Mini online."));

  //  myDFPlayer.setTimeOut(500);

  //----Set volume----
  //myDFPlayer.volume(30); //Set volume value (0~30).
  //myDFPlayer.volumeUp(); //Volume Up
  //myDFPlayer.volumeDown(); //Volume Down

  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  //  myDFPlayer.EQ(DFPLAYER_EQ_POP);
  //  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
  //  myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
  //  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
  //  myDFPlayer.EQ(DFPLAYER_EQ_BASS);

  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  //---Stop Scan---//

  //---Deteksi Error Pada RTC dan Dfplayer---//
  if (err_rtc || err_df) {
    if (err_rtc && err_df) {
      lcd.setCursor(4, 0);
      lcd.print("err0x10");
    }
    else if (err_rtc == false && err_df) {
      lcd.setCursor(4, 0);
      lcd.print("err0x20");
    }
    else if (err_rtc && err_df == false) {
      lcd.setCursor(4, 0);
      lcd.print("err0x30");
    }
    while (true);
  }
  //---End Deteksi Error---//
}

void nilaiAwal() {
  byte i = 0;
  jadwalBelajar[i++] = {Aktif, _waktu(  6, 45 ), hariAktifSenin                 , Upacara};
  jadwalBelajar[i++] = {Aktif, _waktu(  6, 45 ), _hariAktif(0, 1, 1, 1, 1, 0, 0), JamPelajaran1};

  jadwalBelajar[i++] = {Aktif, _waktu(  7, 30 ), _hariAktif(1, 1, 1, 1, 0, 0, 0), JamPelajaran2};
  jadwalBelajar[i++] = {Aktif, _waktu(  8, 15 ), _hariAktif(1, 1, 1, 1, 0, 0, 0), JamPelajaran3};
  jadwalBelajar[i++] = {Aktif, _waktu(  9, 0  ), _hariAktif(1, 1, 1, 1, 0, 0, 0), JamPelajaran4};
  jadwalBelajar[i++] = {Aktif, _waktu(  9, 45 ), _hariAktif(1, 1, 1, 1, 0, 0, 0), Istirahat};
  jadwalBelajar[i++] = {Aktif, _waktu( 10, 15 ), _hariAktif(1, 1, 1, 1, 0, 0, 0), JamPelajaran5};
  jadwalBelajar[i++] = {Aktif, _waktu( 11, 0  ), _hariAktif(1, 1, 1, 1, 0, 0, 0), JamPelajaran6};
  jadwalBelajar[i++] = {Aktif, _waktu( 11, 45 ), _hariAktif(1, 1, 1, 1, 0, 0, 0), Istirahat};
  jadwalBelajar[i++] = {Aktif, _waktu( 12, 30 ), _hariAktif(1, 1, 1, 1, 0, 0, 0), JamPelajaran7};
  jadwalBelajar[i++] = {Aktif, _waktu( 13, 15 ), _hariAktif(1, 1, 1, 1, 0, 0, 0), JamPelajaran8};
  jadwalBelajar[i++] = {Aktif, _waktu( 14, 0  ), _hariAktif(1, 1, 1, 1, 0, 0, 0), JamPelajaran9};
  jadwalBelajar[i++] = {Aktif, _waktu( 14, 45 ), _hariAktif(1, 1, 1, 1, 0, 0, 0), Pulang};

  jadwalBelajar[i++] = {Aktif, _waktu(  7, 25 ), hariAktifJumat, JamPelajaran2};
  jadwalBelajar[i++] = {Aktif, _waktu(  8, 5  ), hariAktifJumat, JamPelajaran3};
  jadwalBelajar[i++] = {Aktif, _waktu(  8, 45 ), hariAktifJumat, JamPelajaran4};
  jadwalBelajar[i++] = {Aktif, _waktu(  9, 25 ), hariAktifJumat, Istirahat};
  jadwalBelajar[i++] = {Aktif, _waktu(  9, 55 ), hariAktifJumat, JamPelajaran5};
  jadwalBelajar[i++] = {Aktif, _waktu( 10, 35 ), hariAktifJumat, JamPelajaran6};
  jadwalBelajar[i++] = {Aktif, _waktu( 11, 15 ), hariAktifJumat, PulangAkhPekan};

  EEPROM.put(0, jadwalBelajar);
}

void default_settings() {
  if (EEPROM.read(sizeof(jadwalBelajar)) != tokenEEPROM) {
    nilaiAwal();
    EEPROM.write(sizeof(jadwalBelajar), tokenEEPROM);
    EEPROM.write(sizeof(jadwalBelajar) + 1, 30); //Volume
    EEPROM.write(sizeof(jadwalBelajar) + 2, 1); //costum nada
    EEPROM.write(sizeof(jadwalBelajar) + 11, 1);  //amplifier repeat
    EEPROM.write(sizeof(jadwalBelajar) + 12, 1); //auto off ampli
    EEPROM.write(sizeof(jadwalBelajar) + 13, 1); //auto off lcd
    EEPROM.write(sizeof(jadwalBelajar) + 14, 1);  //jada ampli
    Serial.println("setting awal");
  }
  eeprom_setting_read();
  cekJadwalHariIni(); //Print Jadwal to Serial Monitor
}

void eeprom_setting_read() {
  EEPROM.get(0, jadwalBelajar);
  volume_dfplayer = EEPROM.read(sizeof(jadwalBelajar) + 1);
  costum_nada = EEPROM.read(sizeof(jadwalBelajar) + 2);
  
  repeat = EEPROM.read(sizeof(jadwalBelajar) + 11);
  ampli = EEPROM.read(sizeof(jadwalBelajar) + 12);
  lcd_backlight = EEPROM.read(sizeof(jadwalBelajar) + 13);
  jeda_ampli = EEPROM.read(sizeof(jadwalBelajar) + 14);

  myDFPlayer.volume(volume_dfplayer);

  if (lcd_backlight == 1) {
    auto_backlight = false;
    lcd.backlight();
  }
  else {
    auto_backlight = true;
    if (lcd_backlight == 2) {
      nilai_backlight = 60000;
    }
    else if (lcd_backlight == 3) {
      nilai_backlight = 120000;
    }
    else if (lcd_backlight == 4) {
      nilai_backlight = 300000;
    }
    else if (lcd_backlight == 5) {
      nilai_backlight = 600000;
    }
  }

  if (ampli == 1) {
    ampli_play = 0;
    digitalWrite(pinRelay, !relayOn);
  }
  else {
    digitalWrite(pinRelay, relayOn);
  }
  //  Serial.println(repeat);
  //  Serial.println(ampli);
  //  Serial.println(ms_backlight);
  //  Serial.println(volume_dfplayer);
}

void cekJadwalHariIni() {
  Serial.println("Jadwal hari ini");
  for (byte i = 0; i < sizeof(jadwalBelajar) / sizeof(TabelMataPelajaran); i++) {
    if (i + 1 == 2) {
      Serial.println("DATA (x2) ini Erorr tidak digunakan ---");
    }
    else {
      if (i == 0) {
        Serial.print(i + 1);
      }
      else {
        Serial.print(i);
      }

      Serial.print('\t');
      Serial.print(jadwalBelajar[i].aktif);
      Serial.print('\t');
      Serial.print(jadwalBelajar[i].waktu.jam);
      Serial.print('\t');
      Serial.print(jadwalBelajar[i].waktu.menit);
      Serial.print('\t');
      Serial.print(jadwalBelajar[i].hariAktif, HEX);
      Serial.print('\t');
      //Serial.print(jadwalBelajar[i].mingguAktif, HEX);
      //Serial.print('\t');
      Serial.print(jadwalBelajar[i].kegiatan);
      Serial.print('\t');
      char buf[20];
      memcpy_P(buf, kegiatanText[jadwalBelajar[i].kegiatan], sizeof(kegiatanText[0]));
      Serial.print(buf);
      Serial.println();
    }
  }
}
