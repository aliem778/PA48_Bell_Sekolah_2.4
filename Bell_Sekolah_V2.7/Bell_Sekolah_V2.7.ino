//created/modified by: Alim Mulyadi
//Powered by: Kamalino Store (Tokepedia)
//Created: 29/06/2022
//Program: Bell Sekolah V2.4
//Inspirasi by: Semesin.com --> Bell Sekolah Bluetooth

/*
  Jika ingin berdonasi untuk traktir saya kopi/mengembangkan projek arduino lainnya:
  https://saweria.co/alimmulyadi

  Terima Kasih Atas Support kalian selama ini.
*/

/*
   Update V2.4 (20/04/2023):
   - Reapeat Bell
   - Pin Busy Low signal
   - Manual Mic Support
   - Amplifier Support
   - Costum 10 mp3 extern
   - Costum Bell Pabrik

   Update V2.5 (27/05/2023):
   - Costum 84 mp3 extern
   - Lcd backlight hemat daya
   - Amplifier Auto/Manual
   - 1 Button Costum in App
   - Mini Amplifier test include

   Update V2.6 (28/05/2023)
   - Fix bug bell
   - Fix bug Costum button bell
   - Fix PCB for audio

   Update V2.7 (12/11/2023)
   - Fix Library button
   - Add & Fix Setting jeda ampli
   - Add size All mp3 (200)
   - Add Reset Jadwal

   Update V2.8 (11/12/2023)
   - Fix Lib dfplayer versi 1.0.6
   variable ver_lib_dfplayer = true;
*/

//---Library Yang Digunakan---//
#include <avr/sleep.h>
#include <Wire.h>
#include <AceButton.h>
#include <LiquidCrystal_I2C.h>
#include "RTC.h"
#include <EEPROM.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "name_of_struct.h"
using namespace ace_button;

//---Pins & Setting Lainnya---//
#define btn_ampli     4
#define btn_backlight 5
#define btn_costum    6
#define buzzer        7
#define pinRelay      8
#define SQWPin        A3
#define relayOn       LOW
#define tokenEEPROM   0x65  //Parameter Setting awal EEPROM
#define namaSekolah   "Nama Sekolah"  //Nama Sekolah

//---Mendefinisikan Library---//
SoftwareSerial mySoftwareSerial(10, 11); // pin RX TX untuk DFPlayer
SoftwareSerial bluetooth(2, 3); // RX, TX bluetooth
DFRobotDFPlayerMini myDFPlayer;
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;
DateTime now;
AceButton button1(btn_ampli);
AceButton button2(btn_backlight);
AceButton button3(btn_costum);

// Forward reference to prevent Arduino compiler becoming confused.
void button_event(AceButton*, uint8_t, uint8_t);

//---Variable yang Digunakan---//
char namaHari[][7] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
char bufWaktu[40];

byte indexMataPelajaran;
byte indexPengaturanJadwal = 0;
byte detikSebelumnya = 60;
byte tanggalSebelumnya = 0;
byte menitBel;
byte jadwalBerikutnyaKegiatan;

volatile bool interupsiDetik;
bool rtcValid;
bool statusBel;
bool statusPengingat;
bool err_rtc = false; //Deteksi Error pada RTC
bool err_df = false;  //Deteksi Error pada Dfplayer
boolean isPlaying = false;  //Memutar File Mp3
bool index_play = false;
bool play_bell = false;
bool play_manual = false;
bool status_manual = false;
bool fix_bell = false;
bool index_2 = true;  //Index Reapeat Bell
bool costum_btnbell = false;
bool backlightcon = false;
bool no_interruptbtn = false;
bool auto_backlight = false;
bool strelay_manual = false;
bool set_ampli = false;
bool notif = false;
bool ver_lib_dfplayer = true; //false:v1.0.5 //true:v1.0.6

int data_play = 0;
int ampli_play = 0;
int repeat = 0;
int ampli = 0;
int lcd_backlight = 0;
int volume_dfplayer = 0;
int costum_nada = 0;
int jeda_ampli = 0;
int count_repeat = 0;

unsigned long ms_notif, ms_repeat, ms_relay, ms_backlight, nilai_backlight, ms_ampli;
//---End Variable---//

void setup() {
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  bluetooth.begin(9600);
  //bluetooth.listen();
  mySoftwareSerial.listen();
  Wire.begin();
  Wire.beginTransmission(0x3F);
  if (Wire.endTransmission())
  {
    lcd = LiquidCrystal_I2C(0x27, 16, 2);
  }
  lcd.begin();
  rtc.begin();
  rtc.writeSqwPinMode(DS3231_SquareWave1Hz);

  //---Mendefinisikan Mode pin yang dipakai---//
  pinMode(btn_ampli, INPUT);  //Input Button Ampli
  pinMode(btn_backlight, INPUT);  //Input Button Backlight
  pinMode(btn_costum, INPUT);  //Input Button Costum
  pinMode(9, INPUT);  //Input Busy
  pinMode(pinRelay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  //pinMode(13, OUTPUT);  //Monitoring data
  digitalWrite(buzzer, LOW);
  digitalWrite(pinRelay, !relayOn);

  // Configure the ButtonConfig with the event handler, and enable all higher
  ButtonConfig* buttonConfig = ButtonConfig::getSystemButtonConfig();
  buttonConfig->setEventHandler(button_event);
  buttonConfig->setFeature(ButtonConfig::kFeatureClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig->setFeature(ButtonConfig::kFeatureRepeatPress);

  lcd.command (0x40 | (0 << 3));
  for (byte i = 0; i < 8; i++)
    lcd.write (karakterDetik1[i]);

  lcd.command (0x40 | (1 << 3));
  for (byte i = 0; i < 8; i++)
    lcd.write (karakterDetik2[i]);

  lcd.command (0x40 | (2 << 3));
  for (byte i = 0; i < 8; i++)
    lcd.write (karakterDetik3[i]);

  lcd.command (0x40 | (3 << 3));
  for (byte i = 0; i < 8; i++)
    lcd.write (karakterDetik2[i]);

  lcd.command (0x40 | (4 << 3));
  for (byte i = 0; i < 8; i++)
    lcd.write (karakterMusik[i]);

  lcd.command (0x40 | (5 << 3));
  for (byte i = 0; i < 8; i++)
    lcd.write (karakterSetting[i]);

  lcd.command (0x40 | (6 << 3));
  for (byte i = 0; i < 8; i++)
    lcd.write (karakterrelay[i]);

  cek_error();
  default_settings();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(F("Bell Sekolah V2"));
  lcd.setCursor(0, 1);
  lcd.print("By: Alim Mulyadi");

  delay(2000);
  lcd.clear();
  delay(50);
  //Serial.println(F("Sistem bel sekolah dimulai"));
}

void loop() {
  button1.check();
  button2.check();
  button3.check();

  if (ver_lib_dfplayer) {
    if (myDFPlayer.available()) {
      printDetail(myDFPlayer.readType(), myDFPlayer.read());
    }
  }

  //---Cek Backlight LCD---//
  if (millis() - ms_backlight >= nilai_backlight && auto_backlight == true) {
    lcd.noBacklight();
    backlightcon = true;
  }
  else {
    backlightcon = false;
    lcd.backlight();
  }

  //---Cek Notif Ampli---//
  if (millis() - ms_notif >= 1500 && notif == true) {
    tanggalSebelumnya = 0;
    notif = false;
  }

  //---Cek Jeda Ampli---//
  if (set_ampli == true) {
    if (millis() - ms_ampli >= jeda_ampli * 1000) {
      isPlaying = true;
    }
  }

  //---Cek Playing Audio---//
  if (isPlaying) {
    if (play_bell == true) {
      play_bell = false;
      data_play = 0;
      myDFPlayer.play(jadwalBerikutnyaKegiatan + 2);
      ms_relay = millis();
      if (repeat == 1 && count_repeat == 0) {
        index_2 = true;
      }
      else {
        index_2 = false;
      }
    }
    else if (play_manual == true) {
      if (costum_btnbell == true) {
        status_manual = true;
        myDFPlayer.play(data_play);
        ms_relay = millis();
        index_play = true;
      }
      else {
        status_manual = true;
        if (ampli_play == 1) {
          myDFPlayer.play(1);
        }
        else if (ampli_play == 2) {
          ms_relay = millis();
          myDFPlayer.play(2);
          index_play = true;
        }
      }
      play_manual = false;
    }
    set_ampli = false;
    isPlaying = false;
  }
  //---End Cek Audio---//

  //---Cek Durasi Audio & Relay---//
  //jadi satu perintah Auto bell dan Manual
  if (index_play == true) {
    if (millis() - ms_relay >= 3000 && digitalRead(9) == HIGH) {
      if (strelay_manual == false) {
        if (index_2 == true) {
          count_repeat = 1;
          isPlaying = true;
          play_bell = true;
        }
        else {
          if (ampli == 1) {
            digitalWrite(pinRelay, !relayOn);
          }
          else {
            digitalWrite(pinRelay, relayOn);
          }

          lcd.backlight();
          ms_backlight = millis();
          count_repeat = 0;
          fix_bell = false;
          index_2 = false;
          no_interruptbtn = false;
          statusBel = false;
          cariJadwal();
          tanggalSebelumnya = 0;
          index_play = false; //set akhir
        }
      }
      else {
        if (status_manual == true) {
          if (costum_btnbell == true) {
            if (fix_bell == true) {
              digitalWrite(pinRelay, relayOn);
            }
            else {
              if (ampli == 1 && ampli_play == 0) {
                digitalWrite(pinRelay, !relayOn);
              }
            }
            data_play = 0;
            strelay_manual = false;
            no_interruptbtn = false;
            play_manual = false;
            status_manual = false;
            costum_btnbell = false;
            index_play = false; //set akhir
          }
          else {
            if (fix_bell == true) {
              digitalWrite(pinRelay, relayOn);
            }
            else {
              if (ampli == 1) {
                digitalWrite(pinRelay, !relayOn);
              }
            }
            ampli_play = 0;
            strelay_manual = false;
            no_interruptbtn = false;
            play_manual = false;
            status_manual = false;
            index_play = false; //set akhir
          }
        }
      }
    }
  }
  //---End Cek Audio dan Relay---//

  //---Cek Bell Otomatis---//
  if (digitalRead(SQWPin)) {
    if (rtcValid) {
      rtcValid = false;

      now = rtc.now();
      uint16_t unixJadwalBerikutnya = (jadwalBerikutnya.jam * 60) + jadwalBerikutnya.menit;
      uint16_t unixWaktu = (now.jam * 60) + now.menit;

      if (jadwalBerikutnyaKegiatan && (unixWaktu == unixJadwalBerikutnya - 1)) {
        statusPengingat = true;
        //Serial.println("Pengingat bel masuk 1 menit lagi");
      }
      else {
        statusPengingat = false;
      }

      if (!now.detik) {
        if (jadwalBerikutnyaKegiatan && (jadwalBerikutnya.jam == now.jam) && (jadwalBerikutnya.menit == now.menit)) {
          lcd.backlight();
          ms_backlight = millis();

          lcd.setCursor(6, 1);
          lcd.print((char)4);
          lcd.setCursor(0, 0);
          lcd.print((__FlashStringHelper *)kegiatanText[jadwalBerikutnyaKegiatan]);
          //Serial.println((__FlashStringHelper *)kegiatanText[jadwalBerikutnyaKegiatan]);
          menitBel = jadwalBerikutnya.menit;
          count_repeat = 0;
          strelay_manual = false;
          index_play = true;
          isPlaying = true;
          play_bell = true;
          statusBel = true;
          no_interruptbtn = true;
          statusPengingat = false;
        }
      }

      if (menitBel != now.menit && digitalRead(9) == HIGH) {
        if (statusBel) {
          lcd.setCursor(6, 1);
          lcd.print(F(" "));
          cariJadwal();
          statusBel = false;
          tanggalSebelumnya = 0;
        }
      }

      //tampilan
      if (statusPengingat) {
        if (now.detik >= 30) {
          digitalWrite(pinRelay, relayOn);
          fix_bell = true;
          lcd.backlight();
          ms_backlight = millis();
          lcd.setCursor(1, 1);

          if (now.detik % 2) {
            sprintf(bufWaktu, "%02d:%02d", jadwalBerikutnya.jam, jadwalBerikutnya.menit);
            lcd.print(bufWaktu);
          }
          else {
            lcd.print(F("     "));
          }
        }
      }

      if (detikSebelumnya != now.detik) {
        sprintf(bufWaktu, "%02d:%02d:%02d", now.jam, now.menit, now.detik);
        lcd.setCursor(8, 1);
        lcd.print(bufWaktu);
        lcd.setCursor(0, 1);
        lcd.print((char)(now.detik % 4));

        sprintf(bufWaktu, "%02d:%02d:%02d %s, %02d/%02d/%02d", now.jam, now.menit, now.detik, namaHari[now.hari - 1], now.tanggal, now.bulan, now.tahun - 2000);
        //Serial.println(bufWaktu);
      }

      if (tanggalSebelumnya != now.tanggal) {
        tanggalSebelumnya = now.tanggal;
        lcd.clear();
        lcd.print(namaHari[now.hari - 1]);
        lcd.print(F(","));
        sprintf(bufWaktu, "%02d/%02d/%02d", now.tanggal, now.bulan, now.tahun - 2000);
        lcd.setCursor(8, 0);
        lcd.print(bufWaktu);

        cariJadwal();
      }
    }
  }
  else {
    rtcValid = true;
  }

  cekBluetooth();
}

void cariJadwal() {
  uint16_t unixWaktu = (now.jam * 60) + now.menit;
  byte hariKeDiTanggal1 = ((now.hari + 7  - (now.tanggal % 7)) % 7) + 1;
  byte SeninKe = ((now.tanggal + ((hariKeDiTanggal1 + 4) % 7)) / 7); //senin pertama
  byte mingguKe = ((now.tanggal + hariKeDiTanggal1 + 6 - 1) / 7);
  //  Serial.print("SeninKe = ");
  //  Serial.println(SeninKe);
  //  Serial.print("mingguKe = ");
  //  Serial.println(mingguKe);

  uint16_t unixTerkecil = UINT16_MAX;
  jadwalBerikutnyaKegiatan = 0;
  Waktu waktuTerkecil;

  for (byte i = 0; i < sizeof(jadwalBelajar) / sizeof(TabelMataPelajaran); i++) {
    if (
      (jadwalBelajar[i].aktif) &&
      (jadwalBelajar[i].hariAktif & (1 << (8 - now.hari)))
    ) {
      uint16_t unixJadwal = (jadwalBelajar[i].waktu.jam * 60) + jadwalBelajar[i].waktu.menit;
      if (unixWaktu < unixJadwal) {
        if (unixTerkecil > unixJadwal) {
          unixTerkecil = unixJadwal;
          jadwalBerikutnya.jam = jadwalBelajar[i].waktu.jam;
          jadwalBerikutnya.menit = jadwalBelajar[i].waktu.menit;
          jadwalBerikutnyaKegiatan = jadwalBelajar[i].kegiatan;
        }
      }
    }
  }
  if (jadwalBerikutnyaKegiatan) {
    Serial.print("Bel berikutnya : ");
    Serial.print((__FlashStringHelper *)kegiatanText[jadwalBerikutnyaKegiatan]);
    Serial.print(" ");
    Serial.print(jadwalBerikutnya.jam);
    Serial.print(":");
    Serial.println(jadwalBerikutnya.menit);

    lcd.setCursor(1, 1);
    sprintf(bufWaktu, "%02d:%02d", jadwalBerikutnya.jam, jadwalBerikutnya.menit);
    lcd.print(bufWaktu);
  }
  else {
    lcd.setCursor(1, 1);
    lcd.print(F("--:--"));
  }
}

void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      //StatusDF="Timeout";
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      //StatusDF="Stack Wrong";
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      //StatusDF="Card Insert";
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      //StatusDF="Card Removed";
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      //StatusDF="Card Online";
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      //StatusDF="Play Finish";
      //intNowTrack=value;
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          //StatusDF="Card Not Found";
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          //StatusDF="Sleeping";
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          //StatusDF="Get Wrong Stack";
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          //StatusDF="Check Sum Not Match";
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          //StatusDF="File Index out of Bound";
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          //StatusDF="Cant Find File";
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          //StatusDF="In Advertise";
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
