//////////// Настройка точек
void Dots(boolean Dot_On) {
  if (c.new_god) {
    if (DOTS_NUM == 2) {
      leds[dot_1] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_2] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
    } else if (DOTS_NUM == 4) {
      leds[dot_1] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_2] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_3] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_4] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
    } else if (DOTS_NUM == 6) {
      leds[dot_1] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_2] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_3] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_4] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_5] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_6] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
    } else if (DOTS_NUM == 8) {
      leds[dot_1] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_2] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_3] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_4] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_5] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_6] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_7] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
      leds[dot_8] = (Dot_On) ? ColorTable[random(NUM_COLORS)] : CRGB(0, 0, 0);
    }
  } else {
    if (DOTS_NUM == 2) {
      leds[dot_1] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_2] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
    } else if (DOTS_NUM == 4) {
      leds[dot_1] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_2] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_3] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_4] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
    } else if (DOTS_NUM == 6) {
      leds[dot_1] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_2] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_3] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_4] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_5] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_6] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
    } else if (DOTS_NUM == 8) {
      leds[dot_1] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_2] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_3] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_4] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_5] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_6] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_7] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
      leds[dot_8] = (Dot_On) ? ledColor : CRGB(0, 0, 0);
    }
  }
}