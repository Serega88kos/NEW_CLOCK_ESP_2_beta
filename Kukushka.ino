
//    Кукушка by Romshteks

//  Определится с Pin_kuku
//  kuku_tick(); - Закинуть в loop
//  В void kuku() может быть что угодно(в разумных пределах) Например для использования совместно с MP3 модулем или ISD1820 достаточно дёрнуть ногой

void kuku_tick() {
  if (r.status_kuku) {
    if (hour >= r.start_kuku && hour <= r.stop_kuku) {
      if (minute == 0 && flag_kuku == 1) {
        kuku();
        flag_kuku = 0;
      }
      if (minute == 59 && flag_kuku == 0) {
        flag_kuku = 1;
      }
    }
  }
}
void kuku() {
  DFPlayer();
};