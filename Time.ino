//////////// Функция времени
int GetTime() {
  if (c.rtc_check) {
    DateTime now = rtc.getTime();
    hour = now.hour;
    minute = now.minute;
    second = now.second;
    day = now.day;
    month = now.month;
    year = now.year;
    Serial.println((String)hour + ":" + minute + ":" + second);
    return (hour * 100 + minute);
  } else {
    hour = ntp.hour();
    minute = ntp.minute();
    second = ntp.second();
    day = ntp.day();
    month = ntp.month();
    year = ntp.year();
    Serial.println((String)hour + ":" + minute + ":" + second);
    return (hour * 100 + minute);
  }
}
// void clock_time() {
//   tmElements_t tm;
//   hour = tm.Hour;
//   minute = tm.Minute;
//   second = tm.Second;
// }

void TimeToArray() {    // вывод времени на экран
  int Now = GetTime();  // получаем время
  boolean change_color_flag = false;
  for (int i = 1; i <= 4; i++) {  // 4 сегмента
    int digit = Now % 10;         // получаем последнюю цифру в времени
    int cursor = NUM_LEDS - i * LEDS_IN_SEGMENT * 7;
    if (i > 2) {
      cursor -= DOTS_NUM;
    }
    if ((i == 4) & (digit == 0)) Digit(digits[12], cursor);  // если впереди ноль, то выключаем его, например 01:23 будет как 1:23
    else
      Digit(digits[digit], cursor);  // иначе показываем символ
    if (i == c.change_color) {       // как часто менять цвет
      if (digit != last_digit) {
        change_color_flag = true;
        last_digit = digit;
      }
    }
    Now /= 10;
  };
  if (change_color_flag) ledColor = ColorTable[random(NUM_COLORS)];  // случайный цвет из таблицы
};