//////////// Функция Web страницы
void build() {
  GP.BUILD_BEGIN(GP_LIGHT);
  GP.PAGE_TITLE("WEB Clock");
  GP.UI_BEGIN("Меню", "/,/wifi,/clock,/other,/monitoring,/ota,/faq,/restart", "Начало,Настройки WiFi,Настройки часов,Различные настройки,Мониторинг,Прошивка,Справка,Перезагрузка", GP_GREEN, 400);

  /////WIFI
  if (ui.uri() == "/wifi") {
    //GP.TITLE("Настройки WiFi");
    GP.FORM_BEGIN("/wifi");
    M_BLOCK(GP_THIN, "", "Настройки WIFI",
            M_TABLE("50px,170px", GP_ALS(GP_LEFT, GP_RIGHT),
                    M_TR(GP.LABEL("SSID"), GP.TEXT("ssid", "", w.ssid, "190px"));
                    M_TR(GP.LABEL("PASS"), GP.PASS("pass", "", w.pass, "190px"));););
    GP.SUBMIT("Сохранить");
    GP.FORM_END();
  }

  /////CLOCK
  else if (ui.uri() == "/clock") {
    //GP.TITLE("Настройки часов");
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
    M_BLOCK(GP_THIN, "", "Настройки часов",
            M_BOX(GP.LABEL("Сервер"); GP.TEXT("host", "", c.host, "200px"); GP.HINT("host", "Введите имя сервера"););
            M_BOX(GP.LABEL("GMT зона"); GP.SPINNER("gmt", c.gmt, -9, 9, 1, 0, GP_GREEN, "60px", 0); GP.HINT("gmt", "Введите временную зону"););
            GP.CHECK("rtc_check", c.rtc_check); GP.LABEL("Есть модуль RTC?"); GP.BREAK(););
    M_BLOCK(GP_THIN, "", "Цвета",
            GP.LABEL("Смена цвета?");
            GP.SELECT("change_color", "выключена,раз в минуту,каждые 10 минут,каждый час,каждые 10 часов", c.change_color, 1); GP.BREAK();
            GP.LABEL("Выбор цвета на лету");
            GP.COLOR("ledColor", color); GP.BREAK();
            GP.CHECK("new_god", c.new_god); GP.LABEL("Вкл. новогодний режим?"); GP.BREAK(););
    M_BLOCK(GP_THIN, "", "Символы",
            M_TABLE("15px,170px", GP_ALS(GP_LEFT, GP_LEFT),
                    M_TR(GP.CHECK("prs", c.prs), GP.LABEL("Символ давления?"));
                    M_TR(GP.CHECK("hmd", c.hmd), GP.LABEL("Символ влажности?"));););
    M_BLOCK(GP_THIN, "", "Мигания секунд",
            M_BOX(GP.LABEL("1р/с"); GP.SWITCH("type_sec", c.type_sec); GP.LABEL("2р/с");););
    M_BLOCK(GP_THIN, "", "Режимы часов",
            M_BOX(GP.LABEL("Порядок"); GP.TEXT("orderDisplay", "", arrayToStr(c.orderDisplay), "200px"););
            GP.SPAN("0 - часы, 1 - комнатная температура, 2 - уличная температура, 3 - давление, 4 - влажность");
            M_BOX(GP.LABEL("Время"); GP.TEXT("periodDisplay", "", arrayToStr(c.periodDisplay), "200px"););
            GP.SPAN("сколько по времени выводить каждый режим, сек"););
    GP.SUBMIT("Сохранить");
    GP.FORM_END();
  }

  /////OTHER
  else if (ui.uri() == "/other") {
    //GP.SEND(F("<style>td{border:1px solid}</style>"));
    //GP.TITLE("Различные настройки");
    //GP.NAV_TABS_LINKS("/,/wifi,/clock,/other,/monitoring,/ota,/restart", "Дом,WiFi,Часы,Разное,Мониторинг,OTA,RST");
    GP.FORM_BEGIN("/other");
    M_BLOCK(GP_THIN, "",
            GP.CHECK("auto_bright", o.auto_bright);
            GP.LABEL("Автояркость"););
    M_BLOCK(GP_THIN, "", "Тип датчика",
            M_BOX(GP.LABEL("Аналог"); GP.SWITCH("type_brg", o.type_brg); GP.LABEL("Цифра");););

    M_BLOCK(GP_THIN, "", "Яркость",
            M_TABLE("210px,80px", GP_ALS(GP_LEFT, GP_CENTER),
                    M_TR(GP.LABEL("Текущая"), GP.LABEL(String(new_bright_f)));
                    M_TR(GP.LABEL("Минимальная"), GP.SPINNER("min_bright", o.min_bright, 1, 250, 1, 0, GP_GREEN, "60px", 0));
                    M_TR(GP.LABEL("Максимальная"), GP.SPINNER("max_bright", o.max_bright, 10, 255, 1, 0, GP_GREEN, "60px", 0));
                    M_TR(GP.LABEL("Задержка, сек"), GP.SPINNER("brg", o.brg, 0, 30, 1, 0, GP_GREEN, "60px", 0));););

    M_BLOCK(GP_THIN, "", "Подстройка",
            M_TABLE("210px,80px", GP_ALS(GP_LEFT, GP_CENTER),
                    M_TR(GP.LABEL("Усиление"), GP.SPINNER("bright_constant", o.bright_constant, 0, 1000, 100, 0, GP_GREEN, "60px", 0));
                    M_TR(GP.LABEL("Фильтр"), GP.SPINNER("coef", o.coef, 0, 1, 0.1, 1, GP_GREEN, "60px", 0));););

    M_BLOCK(GP_THIN, "", "Корректировка показаний",
            M_TABLE("130px,30px,80px", GP_ALS(GP_LEFT, GP_RIGHT, GP_CENTER),
                    M_TR(GP.LABEL("Комнатная"), GP.LABEL(String(FtempH)), GP.SPINNER("cor_tempH", o.cor_tempH, -9, 9, 0.1, 1, GP_GREEN, "60px", 0));
                    M_TR(GP.LABEL("Уличная"), GP.LABEL(String(FtempS)), GP.SPINNER("cor_tempS", o.cor_tempS, -9, 9, 0.1, 1, GP_GREEN, "60px", 0));
                    M_TR(GP.LABEL("Давление"), GP.LABEL(String(Fpres)), GP.SPINNER("cor_pres", o.cor_pres, -9, 9, 1, 0, GP_GREEN, "60px", 0));
                    M_TR(GP.LABEL("Влажность"), GP.LABEL(String(hum)), GP.SPINNER("cor_hum", o.cor_hum, -9, 9, 1, 0, GP_GREEN, "60px", 0));););
    GP.SUBMIT("Сохранить");
    GP.FORM_END();
  }

  /////MONITORING
  else if (ui.uri() == "/monitoring") {
    //GP.TITLE("Народный мониторинг.");
    //GP.NAV_TABS_LINKS("/,/wifi,/clock,/other,/monitoring,/ota,/restart", "Дом,WiFi,Часы,Разное,Мониторинг,OTA,RST");
    GP.FORM_BEGIN("/monitoring");
    M_BLOCK(GP_THIN, "",
            GP.LABEL("narodmon.ru");
            GP.BREAK();
            GP.LABEL(WiFi.macAddress()););
    M_BLOCK(GP_THIN, "",
            GP.CHECK("Monitoring", m.Monitoring);
            GP.LABEL("Включить мониторинг"););
    M_BLOCK(GP_THIN, "",
            M_BOX(GP.LABEL("Интервал, в сек"); GP.NUMBER("delay_narod", "", m.delay_narod, "70px"); GP.HINT("delay_narod", "не менее 300! если нет поддержки сервиса");););
    M_BLOCK(GP_THIN, "", "Отправка показаний датчиков",
            M_BOX(GP.LABEL("Комнатная"); GP.SWITCH("nm_tempH", m.nm_tempH););
            M_BOX(GP.LABEL("Уличная"); GP.SWITCH("nm_tempS", m.nm_tempS););
            M_BOX(GP.LABEL("Давление"); GP.SWITCH("nm_pres", m.nm_pres););
            M_BOX(GP.LABEL("Влажность"); GP.SWITCH("nm_hum", m.nm_hum);););
    GP.SUBMIT("Сохранить");
    GP.BREAK();
    GP.FORM_END();
  }
  /////OTA
  else if (ui.uri() == "/ota") {
    //GP.NAV_TABS_LINKS("/,/wifi,/clock,/other,/monitoring,/ota,/restart", "Дом,WiFi,Часы,Разное,Мониторинг,OTA,RST");
    GP.TITLE("Прошивка");
    GP.OTA_FIRMWARE("Файл прошивки");
    //GP.LABEL (String(error()));
  }
  ////FAQ
  else if (ui.uri() == "/faq") {
    GP.TITLE("Важная информация!");
    GP.LABEL("Разное:");
    GP.BREAK();
    GP.SPAN("Усиление: чем меньше константа, тем резче будет прибавляться яркость.");
    GP.BREAK();
    GP.SPAN("Фильтр: чем больше коэффициент, тем медленнее меняется яркость.");
    GP.BREAK();
    GP.LABEL("Мониторинг:");
    GP.SPAN("Интервал: не менее 300 сек, иначе получите бан!");
    GP.SPAN("Правило не действует, если есть поддержка сервиса и получены персональные условия.");

  }
  /////RESTART
  else if (ui.uri() == "/restart") {
    GP.TITLE("Перезагрузить ESP?");
    GP.BREAK();
    GP.FORM_BEGIN("/restart");
    GP.SUBMIT("Да", GP_GREEN_B);
    GP.FORM_END();
    GP.BUTTON_LINK("/", "Нет", GP_RED_B);
  }

  /////INDEX
  else {
    GP.TITLE("Системная информация.");
    //GP.NAV_TABS_LINKS("/,/wifi,/clock,/other,/monitoring,/ota,/restart", "Дом,WiFi,Часы,Разное,Мониторинг,OTA,RST");
    GP.FILE_MANAGER(&LittleFS);  // передать ссылку на свою ф. систему (&LittleFS, &SPIFFS..) выводит список файлов из Flash памяти с кнопками для удаления (нужно настроить delete)
    GP.BREAK();
    GP.SYSTEM_INFO();  // выводит таблицу системной информации
    GP_VERSION;
  }
  GP.UI_END();
  GP.BUILD_END();
}

void action() {


  if (ui.click()) {
    if (ui.click("sync")) {
      rtcCheck();
    }
    if (ui.click("ledColor")) {
      Serial.println(ui.getString());
      GPcolor color1;
      ui.copyColor("ledColor", color1);
      ledColor = CRGB(color1.r, color1.g, color1.b);
      mem5.updateNow();
    }
  }
  if (ui.form()) {
    if (ui.form("/wifi")) {
      ui.copyStr("ssid", w.ssid);
      ui.copyStr("pass", w.pass);
      mem1.updateNow();
      ESP.restart();
    }
    // настройки часов
    if (ui.form("/clock")) {
      ui.copyStr("host", c.host);
      ui.copyInt("gmt", c.gmt);
      ui.copyBool("rtc_check", c.rtc_check);
      ui.copyInt("change_color", c.change_color);
      ui.copyBool("prs", c.prs);
      ui.copyBool("hmd", c.hmd);
      ui.copyBool("type_sec", c.type_sec);
      String prd, ord;
      ui.copyString("periodDisplay", prd);
      ui.copyString("orderDisplay", ord);
      StrToArray(prd, c.periodDisplay, 6);
      StrToArray(ord, c.orderDisplay, 6);
      ui.copyBool("new_god", c.new_god);
      mem2.updateNow();
    }
    // остальные
    if (ui.form("/other")) {
      ui.copyFloat("cor_tempH", o.cor_tempH);
      ui.copyFloat("cor_tempS", o.cor_tempS);
      ui.copyInt("cor_pres", o.cor_pres);
      ui.copyInt("cor_hum", o.cor_hum);
      ui.copyBool("type_brg", o.type_brg);
      ui.copyBool("auto_bright", o.auto_bright);
      ui.copyInt("min_bright", o.min_bright);
      ui.copyInt("max_bright", o.max_bright);
      ui.copyInt("brg", o.brg);
      ui.copyInt("bright_constant", o.bright_constant);
      ui.copyFloat("coef", o.coef);
      mem3.updateNow();
    }
    // мониторинг
    if (ui.form("/monitoring")) {
      ui.copyBool("Monitoring", m.Monitoring);
      ui.copyInt("delay_narod", m.delay_narod);
      ui.copyBool("nm_tempH", m.nm_tempH);
      ui.copyBool("nm_tempS", m.nm_tempS);
      ui.copyBool("nm_pres", m.nm_pres);
      ui.copyBool("nm_hum", m.nm_hum);
      mem4.updateNow();
    }
    if (ui.form("/restart")) {
      ESP.restart();
    }
  }
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