//////////// функция освещенности
void BrightnessCheck() {
  static uint32_t last_br = millis();
  if ((millis() - last_br) < o.brg) return;
  last_br = millis();
  if (o.auto_bright) {                                                                             // если включена адаптивная яркость
    if (millis() - bright_timer > 100) {                                                           // каждые 100 мс
      bright_timer = millis();                                                                     // сбросить таймер
      if (o.type_brg) {                                                                            // выбор типа датчика, аналог или цифра
        new_bright = map(digitalRead(BRI_PIN), 0, o.bright_constant, o.min_bright, o.max_bright);  // считать показания с фоторезистора, перевести диапазон
      } else {
        new_bright = map(analogRead(BRI_PIN), 0, o.bright_constant, o.min_bright, o.max_bright);  // считать показания с фоторезистора, перевести диапазон
      }
      //Serial.println((String)"Освещенность: " + new_bright);
      new_bright = constrain(new_bright, o.max_bright, o.min_bright);
      new_bright_f = new_bright_f * o.coef + new_bright * (1 - o.coef);
      LEDS.setBrightness(new_bright_f);  // установить новую яркость
      //Serial.println((String)"Новая освещенность: " + new_bright_f);
    }
  } else {
    LEDS.setBrightness(100);
  }
}