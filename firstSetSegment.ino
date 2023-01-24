//////////// настройка сегментов и точек
void firstSetSegment() {

  segment_4 = (NUM_LEDS - DOT_TEMP) - LEDS_IN_SEGMENT * 7;
  segment_3 = (NUM_LEDS - DOT_TEMP) - LEDS_IN_SEGMENT * 14;
  segment_2 = (NUM_LEDS - DOT_TEMP) - LEDS_IN_SEGMENT * 21 - DOTS_NUM;
  segment_1 = (NUM_LEDS - DOT_TEMP) - LEDS_IN_SEGMENT * 28 - DOTS_NUM;

  if (DOTS_NUM == 2) {
    dot_1 = LEDS_IN_SEGMENT * 14;
    dot_2 = (LEDS_IN_SEGMENT * 14) + 1;
  } else if (DOTS_NUM == 4) {
    dot_1 = LEDS_IN_SEGMENT * 14;
    dot_2 = (LEDS_IN_SEGMENT * 14) + 1;
    dot_3 = (LEDS_IN_SEGMENT * 14) + 2;
    dot_4 = (LEDS_IN_SEGMENT * 14) + 3;
  } else if (DOTS_NUM == 6) {
    dot_1 = LEDS_IN_SEGMENT * 14;
    dot_2 = (LEDS_IN_SEGMENT * 14) + 1;
    dot_3 = (LEDS_IN_SEGMENT * 14) + 2;
    dot_4 = (LEDS_IN_SEGMENT * 14) + 3;
    dot_5 = (LEDS_IN_SEGMENT * 14) + 4;
    dot_6 = (LEDS_IN_SEGMENT * 14) + 5;
  } else if (DOTS_NUM == 8) {
    dot_1 = LEDS_IN_SEGMENT * 14;
    dot_2 = (LEDS_IN_SEGMENT * 14) + 1;
    dot_3 = (LEDS_IN_SEGMENT * 14) + 2;
    dot_4 = (LEDS_IN_SEGMENT * 14) + 3;
    dot_5 = (LEDS_IN_SEGMENT * 14) + 4;
    dot_6 = (LEDS_IN_SEGMENT * 14) + 5;
    dot_7 = (LEDS_IN_SEGMENT * 14) + 6;
    dot_8 = (LEDS_IN_SEGMENT * 14) + 7;
  }
}