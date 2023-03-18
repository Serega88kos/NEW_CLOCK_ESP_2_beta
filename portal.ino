//////////// Функция Web страницы
void build() {
  GP.BUILD_BEGIN(portalTheme);
  GP.PAGE_TITLE("WEB Clock");
  GP.UI_BEGIN("Меню", "/,/wifi,/clock,/other,/monitoring,/dfp,/ota,/restart", "Начало,Настройки WiFi,Настройки часов,Различные настройки,Мониторинг,Настройки DFP,Прошивка,Перезагрузка", colorTheme, 400);

  /////WIFI
  if (ui.uri() == "/wifi") {
    GP.FORM_BEGIN("/wifi");
    M_BLOCK(GP_THIN, "", "Настройки WIFI", colorTheme,
            M_TABLE("50px,170px", GP_ALS(GP_LEFT, GP_RIGHT),
                    M_TR(GP.LABEL("SSID"), GP.TEXT("ssid", "", w.ssid, "190px"));
                    M_TR(GP.LABEL("PASS"), GP.PASS("pass", "", w.pass, "190px"));););
    GP.SUBMIT("Сохранить", colorTheme);
    GP.FORM_END();
  }

  /////CLOCK
  else if (ui.uri() == "/clock") {
    GP.ICON_SUPPORT();
    GP.JQ_SUPPORT();
    GP.JQ_UPDATE_BEGIN(1000);
    if (!c.rtc_check) {
      M_TABLE("10px,70px,10px", GP_ALS(GP_RIGHT, GP_CENTER, GP_LEFT), "80%",
              M_TR(GP.LABEL("ntp"), GP.LABEL(ntp.timeString()); GP.LABEL(ntp.dateString());, GP.ICON_BUTTON("sync", "refresh")););
    }
    if (c.rtc_check) {
      M_TABLE("10px,70px,10px", GP_ALS(GP_RIGHT, GP_CENTER, GP_LEFT), "80%",
              M_TR(GP.LABEL("rtc"), GP.LABEL(rtc.getTimeString()); GP.LABEL(rtc.getDateString());, GP.ICON_BUTTON("sync", "refresh")););
    }
    GP.JQ_UPDATE_END();
    GP.FORM_BEGIN("/clock");
    M_BLOCK(GP_THIN, "", "Настройки часов", colorTheme,
            M_BOX(GP.LABEL("Сервер"); GP.TEXT("host", "", c.host, "200px"););
            M_BOX(GP.LABEL("GMT зона"); GP.SPINNER("gmt", c.gmt, -9, 9, 1, 0, colorTheme, "60px", 0););
            GP.SPAN("Требуется перезагрузка!");
            GP.CHECK("rtc_check", c.rtc_check, colorTheme); GP.LABEL("Есть модуль RTC?"); GP.BREAK(););
    M_BLOCK(GP_THIN, "", "Цвета", colorTheme,
            GP.LABEL("Смена цвета?");
            GP.SELECT("change_color", "выключена,раз в минуту,каждые 10 минут,каждый час,каждые 10 часов", c.change_color, 1); GP.BREAK();
            GP.LABEL("Выбор цвета на лету");
            GP.COLOR("ledColor", color); GP.BREAK();
            GP.CHECK("new_god", c.new_god, colorTheme); GP.LABEL("Вкл. новогодний режим?"););
    M_BLOCK(GP_THIN, "", "Символы", colorTheme,
            M_TABLE("15px,170px", GP_ALS(GP_LEFT, GP_LEFT),
                    M_TR(GP.CHECK("prs", c.prs, colorTheme), GP.LABEL("Символ давления?"));
                    M_TR(GP.CHECK("hmd", c.hmd, colorTheme), GP.LABEL("Символ влажности?"));
                    M_TR(GP.CHECK("symbol", c.symbol, colorTheme), GP.LABEL("Первый ноль в часах?"));););
    M_BLOCK(GP_THIN, "", "Мигания секунд", colorTheme,
            M_BOX(GP.LABEL("1р/с"); GP.SWITCH("type_sec", c.type_sec, colorTheme); GP.LABEL("2р/с");););
    M_BLOCK(GP_THIN, "", "Режимы часов", colorTheme,
            M_BOX(GP.LABEL("Порядок"); GP.TEXT("orderDisplay", "", arrayToStr(c.orderDisplay), "200px"););
            GP.SPAN("0 - часы, 1 - комн. темп, 2 - ул. темп, 3 - давление, 4 - влажность, 5 - дата");
            M_BOX(GP.LABEL("Время"); GP.TEXT("periodDisplay", "", arrayToStr(c.periodDisplay), "200px"););
            GP.SPAN("сколько по времени выводить каждый режим, сек"););
    GP.SUBMIT("Сохранить", colorTheme);
    GP.FORM_END();
  }

  /////OTHER
  else if (ui.uri() == "/other") {
    GP.FORM_BEGIN("/other");
    M_BLOCK(GP_THIN, "", "", colorTheme,
            GP.CHECK("auto_bright", o.auto_bright, colorTheme);
            GP.LABEL("Автояркость"););
    M_BLOCK(GP_THIN, "", "Тип датчика", colorTheme,
            M_BOX(GP.LABEL("Аналог"); GP.SWITCH("type_brg", o.type_brg, colorTheme); GP.LABEL("Цифра");););
    M_BLOCK(GP_THIN, "", "Яркость", colorTheme,
            M_TABLE("210px,80px", GP_ALS(GP_LEFT, GP_CENTER),
                    M_TR(GP.LABEL("Текущая"), GP.LABEL(String(new_bright_f)));
                    M_TR(GP.LABEL("Минимальная"), GP.SPINNER("min_bright", o.min_bright, 1, 250, 1, 0, colorTheme, "60px", 0));
                    M_TR(GP.LABEL("Максимальная"), GP.SPINNER("max_bright", o.max_bright, 10, 255, 1, 0, colorTheme, "60px", 0));
                    M_TR(GP.LABEL("Задержка, сек"), GP.SPINNER("brg", o.brg, 0, 30, 1, 0, colorTheme, "60px", 0));););
    M_BLOCK(GP_THIN, "", "Подстройка", colorTheme,
            M_TABLE("210px,80px", GP_ALS(GP_LEFT, GP_CENTER),
                    M_TR(GP.LABEL("Усиление"), GP.SPINNER("bright_constant", o.bright_constant, 0, 1000, 100, 0, colorTheme, "60px", 0)););
            M_TABLE("290px", GP_ALS(GP_LEFT),
                    M_TR(GP.SPAN("чем меньше константа, тем резче будет прибавляться яркость.");););
            M_TABLE("210px,80px", GP_ALS(GP_LEFT, GP_CENTER),
                    M_TR(GP.LABEL("Фильтр"), GP.SPINNER("coef", o.coef, 0, 1, 0.1, 1, colorTheme, "60px", 0)););
            M_TABLE("290px", GP_ALS(GP_LEFT),
                    M_TR(GP.SPAN("чем больше коэффициент, тем медленнее меняется яркость."););););
    M_BLOCK(GP_THIN, "", "Корректировка показаний", colorTheme,
            M_TABLE("130px,30px,80px", GP_ALS(GP_LEFT, GP_RIGHT, GP_CENTER),
                    M_TR(GP.LABEL("Комнатная"), GP.LABEL(String(FtempH)), GP.SPINNER("cor_tempH", o.cor_tempH, -9, 9, 0.1, 1, colorTheme, "60px", 0));
                    M_TR(GP.LABEL("Уличная"), GP.LABEL(String(FtempS)), GP.SPINNER("cor_tempS", o.cor_tempS, -9, 9, 0.1, 1, colorTheme, "60px", 0));
                    M_TR(GP.LABEL("Давление"), GP.LABEL(String(Fpres)), GP.SPINNER("cor_pres", o.cor_pres, -9, 9, 1, 0, colorTheme, "60px", 0));
                    M_TR(GP.LABEL("Влажность"), GP.LABEL(String(hum)), GP.SPINNER("cor_hum", o.cor_hum, -9, 9, 1, 0, colorTheme, "60px", 0));););
    GP.SUBMIT("Сохранить", colorTheme);
    GP.FORM_END();
  }

  /////MONITORING
  else if (ui.uri() == "/monitoring") {
    GP.FORM_BEGIN("/monitoring");
    M_BLOCK(GP_THIN, "", "", colorTheme,
            GP.LABEL("narodmon.ru");
            GP.BREAK(); GP.LABEL(WiFi.macAddress()););
    M_BLOCK(GP_THIN, "", "", colorTheme,
            GP.CHECK("Monitoring", m.Monitoring, colorTheme);
            GP.LABEL("Включить мониторинг"););
    M_BLOCK(GP_THIN, "", "", colorTheme,
            M_TABLE("210px,80px", GP_ALS(GP_LEFT, GP_CENTER),
                    M_TR(GP.LABEL("Интервал, в сек"), GP.NUMBER("delay_narod", "", m.delay_narod, "70px")););
            M_TABLE("290px", GP_ALS(GP_LEFT),
                    M_TR(GP.SPAN("не менее 300 сек, иначе получите блок!");););
            M_TABLE("290px", GP_ALS(GP_LEFT),
                    M_TR(GP.SPAN("<strong>Исключение: </strong>правило не действует, если есть поддержка сервиса и получены персональные условия."););););
    M_BLOCK(GP_THIN, "", "Отправка показаний датчиков", colorTheme,
            M_BOX(GP.LABEL("Комнатная"); GP.SWITCH("nm_tempH", m.nm_tempH, colorTheme););
            M_BOX(GP.LABEL("Уличная"); GP.SWITCH("nm_tempS", m.nm_tempS, colorTheme););
            M_BOX(GP.LABEL("Давление"); GP.SWITCH("nm_pres", m.nm_pres, colorTheme););
            M_BOX(GP.LABEL("Влажность"); GP.SWITCH("nm_hum", m.nm_hum, colorTheme);););
    GP.SUBMIT("Сохранить", colorTheme);
    GP.FORM_END();
  }

  /////DFP
  else if (ui.uri() == "/dfp") {
    GP.ICON_SUPPORT();
    GP.FORM_BEGIN("/dfp");
    M_BLOCK(GP_THIN, "", "Настройки DFP", colorTheme,
            M_TABLE("10px,70px,10px", GP_ALS(GP_RIGHT, GP_CENTER, GP_LEFT), "80%",
                    M_TR(GP.CHECK("status_kuku", r.status_kuku, colorTheme), GP.LABEL("Включить модуль"), GP.ICON_BUTTON("hi", "music"));););
    M_BLOCK(GP_THIN, "", "Часы работы", colorTheme,
            GP.LABEL("с");
            GP.SELECT("start_kuku", "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23", r.start_kuku);
            GP.LABEL("до");
            GP.SELECT("stop_kuku", "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23", r.stop_kuku););
    M_BLOCK(GP_THIN, "", "Режимы", colorTheme,
            M_TABLE("10px,170px", GP_ALS(GP_LEFT, GP_LEFT),
                    M_TR(GP.CHECK("kuku_mp3_check", r.kuku_mp3_check, colorTheme), GP.LABEL("Кукушка"));
                    M_TR(GP.CHECK("vrem_mp3_check", r.vrem_mp3_check, colorTheme), GP.LABEL("Время"));););
    M_BLOCK(GP_THIN, "", "Голос", colorTheme,
            M_TABLE("10px,170px", GP_ALS(GP_LEFT, GP_LEFT),
                    M_TR(GP.RADIO("golos", 0, r.golos, colorTheme), GP.LABEL("Алиса"));
                    M_TR(GP.RADIO("golos", 1, r.golos, colorTheme), GP.LABEL("Женский"));
                    M_TR(GP.RADIO("golos", 2, r.golos, colorTheme), GP.LABEL("Мужской"));););
    M_BLOCK(GP_THIN, "", "Громкость", colorTheme,
            GP.SLIDER("grom_mp3", r.grom_mp3, 0, 30, 1, 0, colorTheme));
    GP.SUBMIT("Сохранить", colorTheme);
    GP.FORM_END();
  }

  /////OTA
  else if (ui.uri() == "/ota") {
    M_BLOCK(GP_THIN, "", "Прошивка", colorTheme,
            GP.OTA_FIRMWARE("Выбрать файл", colorTheme);
            GP.LABEL((String)ui.OTA.error()););
  }

  /////RESTART
  else if (ui.uri() == "/restart") {
    M_BLOCK(GP_THIN, "", "Перезагрузить ESP?", colorTheme,
            GP.BUTTON("yes_rst", "Да", "yes_rst", colorTheme, "170px"););
  }

  /////INDEX
  else {
    GP.TITLE("Системная информация.");
    GP.SYSTEM_INFO(Version_Firmware);  // + версия вашей программы (в таблице появится строка Version с указанным текстом), [строка]
  }
  GP.UI_END();
  GP.BUILD_END();
}

/*
   (с) DAK, ноябрь, 2022 год.
*/
String arrayToStr(uint8_t* inp) {
  uint8_t i = 0;
  String s;
  while (inp[i] != 255) {
    s += inp[i];
    i++;
    if (inp[i] != 255) s += ",";
  }
  return s;
}

void StrToArray(const String& str, uint8_t* outArr, int length) {
  String s;
  s += str;
  s += ", ";
  for (int i = 0; i < length - 1; i++) {
    if (s.length() > 2) {
      outArr[i] = s.substring(0, s.indexOf(",")).toInt();
      // Serial.print(i);
      // Serial.print(" - ");
      // Serial.println(outArr[i]);
      s = s.substring(s.indexOf(",") + 1);
    } else {
      outArr[i] = 255;
      // Serial.print(i);
      // Serial.print(" - ");
      // Serial.println(outArr[i]);
    }
  }
  outArr[length - 1] = 255;
  // Serial.print(length - 1);
  // Serial.print(" - ");
  // Serial.println(outArr[length - 1]);
}