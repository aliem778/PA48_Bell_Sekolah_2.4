//---Fungsi Cek Button---//
void button_event(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      if (no_interruptbtn == false) {
        if (button->getPin() == btn_ampli) {
          delay(250);
          if (digitalRead(9) == HIGH && fix_bell == false) {
            lcd.backlight();
            ms_backlight = millis();
            if (ampli_play == 0) {
              ampli_play = 1;
              ms_ampli = millis();
              digitalWrite(pinRelay, relayOn);
              strelay_manual = true;
              play_manual = true;

              if (ampli == 1) {
                set_ampli = true;
              }
              else {
                isPlaying = true;
              }
            }
            else {
              ampli_play = 2;
              strelay_manual = true;
              play_manual = true;
              isPlaying = true;
            }
          }
        }
        if (button->getPin() == btn_costum) {
          if (costum_nada != 1) {
            delay(250);
            if (digitalRead(9) == HIGH && fix_bell == false) {
              lcd.backlight();
              ms_backlight = millis();
              digitalWrite(pinRelay, relayOn);
              //myDFPlayer.play(costum_nada + 1);
              data_play = costum_nada + 1;
              ms_ampli = millis();
              strelay_manual = true;
              no_interruptbtn = true;
              play_manual = true;
              costum_btnbell = true;
              if (ampli == 1) {
                if (ampli_play == 1) {
                  isPlaying = true;
                }
                else {
                  set_ampli = true;
                }
              }
              else {
                isPlaying = true;
              }
            }
          }
        }
      }

      if (button->getPin() == btn_backlight) {
        delay(250);
        if (auto_backlight == true) {
          lcd.backlight();
          ms_backlight = millis();
        }

        if (digitalRead(9) == LOW) {
          if (status_manual == true  && no_interruptbtn == true) {
            lcd.backlight();
            ms_backlight = millis();
            myDFPlayer.pause();

            if (ampli == 1) {
              digitalWrite(pinRelay, !relayOn);
            }
            no_interruptbtn = false;
            costum_btnbell = false;
            play_manual = false;
          }
        }
      }
      break;
  }
}
//---END Cek Button---//
