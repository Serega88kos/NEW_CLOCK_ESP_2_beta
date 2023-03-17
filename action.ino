void action() {
  if (ui.click()) {
    if (ui.click("sync")) {
      rtcCheck();
    }
    if (ui.click("hi")) {
      mp3.playMP3Folder(26);
      Serial.println("Test click");
    }
    if (ui.click("yes_rst")) {
      ESP.restart();
    }
    if (ui.click("ledColor")) {
      Serial.println(ui.getString());
      GPcolor color1;
      ui.copyColor("ledColor", color1);
      ledColor = CRGB(color1.r, color1.g, color1.b);
      mem5.updateNow();
    }
  }
  // настройки WiFi
  if (ui.form()) {
    if (ui.form("/wifi")) {
      ui.copyStr("ssid", w.ssid);
      ui.copyStr("pass", w.pass);
      mem1.updateNow();
      ESP.restart();
    }
    // if (ui.form("/color")) {
    //   ui.copyStr("portalTheme", portalTheme);
    //   ui.copyStr("colorTheme", colorTheme);
    // }
    // настройки часов
    if (ui.form("/clock")) {
      ui.copyStr("host", c.host);
      ui.copyInt("gmt", c.gmt);
      ui.copyBool("rtc_check", c.rtc_check);
      ui.copyInt("change_color", c.change_color);
      ui.copyBool("prs", c.prs);
      ui.copyBool("hmd", c.hmd);
      ui.copyBool("symbol", c.symbol);
      ui.copyBool("type_sec", c.type_sec);
      String prd, ord;
      ui.copyString("periodDisplay", prd);
      ui.copyString("orderDisplay", ord);
      int t = 0.5 * (ord.length() + 3);
      if (t = 0) t = 2;
      StrToArray(prd, c.periodDisplay, 7);
      StrToArray(ord, c.orderDisplay, 7);
      ui.copyBool("new_god", c.new_god);
      mem2.updateNow();
      ntp.end();
      ntp.setGMT(c.gmt);
      ntp.setHost(c.host);
      ntp.begin();
      rtc.getUnix(c.gmt);
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
    // DFP
    if (ui.form("/dfp")) {
      ui.copyBool("status_kuku", r.status_kuku);
      ui.copyInt("start_kuku", r.start_kuku);
      ui.copyInt("stop_kuku", r.stop_kuku);
      ui.copyBool("kuku_mp3_check", r.kuku_mp3_check);
      ui.copyBool("vrem_mp3_check", r.vrem_mp3_check);
      ui.copyInt("golos", r.golos);
      ui.copyInt("grom_mp3", r.grom_mp3);
      mem6.updateNow();
      mp3.setVolume(r.grom_mp3);
      DFPlayer();
    }
    // if (ui.form("/restart")) {
    //   ESP.restart();
    // }
  }
}
