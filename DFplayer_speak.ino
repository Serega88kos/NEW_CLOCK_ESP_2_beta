//////////// Функция DFPlayer_setup и DFPlayer_loop
/*
  //Подключен ли модуль DFPlayer?, может быть привинчен к веб-интерфейсу!
  bool DFPlayer_check = 1; // 1 - есть модуль DFPlayer, 0 - нет

  // выполняется, если DFPlayer_check - 1
  if (DFPlayer_check) { DFPlayer_setup(); } //нужно поместить в setup 

  // выполняется, если DFPlayer_check - 1
  if (DFPlayer_check) { DFPlayer_loop(); } //нужно поместить в loop 
*/

/*
[*]автор Maxx1200
[*]Каждый час будет говорить время!
[*]есть только один НО, если, скажем, в 22:59:59 будет запущен опрос датчиков, то, возможно, звука "23 часа" не будет и с этим нужно что-то делать!
[*]добавил будильник!, есть только один НО, если, скажем, в 10:59:59 будет запущен опрос датчиков, то, возможно, будильник не сработает, и с этим нужно что-то делать!
*/

/***************************************************************************************************/
/*
   исходный код: https://github.com/enjoyneering/DFPlayer

   Возможности DFPlayer Mini:
    - 3,2В..5,0В, обычно 4,2В
    - microSD-карта до 32 ГБ (FAT16, FAT32)
    - USB-диск до 32 ГБ (FAT16, FAT32)
    - поддерживает частоту дискретизации mp3 8кГц, 11,025кГц, 12кГц, 16кГц, 22,05кГц, 24кГц, 32кГц, 44,1кГц, 48кГц
    - поддерживает до 100 папок, каждая папка может быть назначена на 001..255 песен
    - встроенный моноусилитель мощностью 3 Вт, NS8002 AB-класса с функцией ожидания
    - UART для связи, 9600 бит/с (четность: нет, биты данных: 8, стоповые биты: 1, управление потоком: нет)

    ПРИМЕЧАНИЕ:
    - добавьте резистор 1K последовательно с выводом DFPlayer TX

   Фреймворки и библиотеки:
   ESP8266 Core      -  https://github.com/esp8266/Arduino
   EspSoftwareSerial -  https://github.com/plerup/espsoftwareserial
*/
/***************************************************************************************************/

// Установка будильника!
#define  alarm_clock_hours 23   //час   //без "0" 1 час
#define  alarm_clock_minutes 48 //минут //без "0" 9 минут

  //Переменные
  int Hor, Min, Sec;
  //unsigned long timing2; // Переменная для хранения точки отсчета

/*********************здесь мы выбираем тип модуля*********************/
/*
    DFPlayer_setup()

    Main setup

    ПРИМЕЧАНИЕ:
    - тип модуля:
      - DFPLAYER_MINI:
        - DFPlayer Mini module
        - MP3-TF-16P module
        - FN-M16P module
        - YX5200 chip
        - YX5300 chip
        - JL AAxxxx chip
      - DFPLAYER_FN_X10P:
        - FN-M10P module
        - FN-S10P module
        - FN6100 chip
      - DFPLAYER_HW_247A:
        - HW-247A module
        - GD3200B chip
        - MH2024K-24SS
      - DFPLAYER_NO_CHECKSUM:
        - нет вычисления контрольной суммы (не рекомендуется для MCU без внешнего кварцевого генератора)
*/
/**************************************************************************/
  //  DFPlayer_setup(); //нужно поместить в setup
void DFPlayer_setup() {

  Serial.println("Инициализация DFPlayer... (может занять 3~5 секунд)"); //для отладки

  mp3Serial.begin(MP3_SERIAL_SPEED, SWSERIAL_8N1, MP3_RX_PIN, MP3_TX_PIN, false, MP3_SERIAL_BUFFER_SIZE, 0); //false=сигнал не инвертирован, 0=размер буфера ISR/RX (общий с последовательным буфером TX)

  mp3.begin(mp3Serial, MP3_SERIAL_TIMEOUT, DFPLAYER_HW_247A, false); //"DFPLAYER_HW_247A" см. ПРИМЕЧАНИЕ, false = нет обратной связи от модуля после команды

  mp3.stop();                             //если плеер работал во время перезагрузки ESP8266

  mp3.reset();                            //сбросить все настройки по умолчанию

  mp3.setSource(2);                       //1=USB-диск, 2=TF-карта, 3=Aux, 4=спящий режим, 5=NOR Flash

  mp3.setEQ(0);                           //0=Выкл., 1=Поп, 2=Рок, 3=Джаз, 4=Классика, 5=Бас
  mp3.setVolume(20);                      //0..30, модуль сохраняет громкость при сбое питания

  mp3.sleep();                            //переход в спящий режим, 24 мА

  mp3.wakeup(2);                          //выйти из спящего режима и инициализировать источник 1=USB-диск, 2=TF-карта, 3=Aux, 5=NOR Flash

  mp3Serial.enableRx(true);               //включить прерывания на выводе RX для лучшего обнаружения ответа, меньше накладных расходов, чем mp3Serial.listen()

  Serial.print("getStatus: ");  //для отладки, Получить статус
  Serial.println(mp3.getStatus());        //0=стоп, 1=воспроизведение, 2=пауза, 3=спящий режим или режим ожидания, 4=ошибка связи, 5=неизвестное состояние
  Serial.print("getVolume: ");  //для отладки, Получить громкость
  Serial.println(mp3.getVolume());        //0..30
  Serial.print("getCommandStatus: ");  //для отладки, Получить статус команд
  Serial.println(mp3.getCommandStatus()); //1=модуль занят, 2=модуль в спящем режиме, 3=запрос получен не полностью, 4=не совпадает контрольная сумма
                                          //5=запрошенная папка/трек вне допустимого диапазона, 6=запрошенная папка/трек не найдена
                                          //7=реклама доступна во время воспроизведения трека, 8=SD-карта не найдена, 9=???, 10=спящий модуль
                                          //11=ОК команда принята, 12=ОК воспроизведение завершено, 13=ОК модуль готов после перезагрузки

  mp3Serial.enableRx(false);              //отключить прерывания на RX-контакте, меньше накладных расходов, чем mp3Serial.listen()

    //Чтобы при включении был звук как пример звук! 005.mp3
     mp3.playFolder(2, 5); //2=папка/5=дорожка, имя папки должно быть 01..99, а файлы в папке должны начинаться с 3 десятичных цифр с ведущими нулями // проигрываем файл 02/005.mp3
     Serial.println ("track_Folder2: 5"); //для отладки
     delay(2000); // задержку лучше заменить на миллис
	   mp3.pause(); // пауза
     Serial.print("getStatus: ");  //для отладки, Получить статус
     Serial.println(mp3.getStatus());  //0=стоп, 1=воспроизведение, 2=пауза, 3=спящий режим или режим ожидания, 4=ошибка связи, 5=неизвестное состояние
}



  //  DFPlayer_loop(); //нужно поместить в loop
void DFPlayer_loop() {


  Hor = ntp.hour();
  Min = ntp.minute();
  Sec = ntp.second();

  if(Min == 0 && Sec == 0) {
    switch (Hor) { // Каждый час будет говорить время
     case 0:
     mp3.playMP3Folder(24); // проигрываем файл mp3/0024.mp3
     Serial.println ("track: 24"); //для отладки 
     break;
     case 1:
     mp3.playMP3Folder(1); // проигрываем файл mp3/0001.mp3
     Serial.println ("track: 1"); //для отладки  
     break;
     case 2:
     mp3.playMP3Folder(2); // проигрываем файл mp3/0002.mp3
     Serial.println ("track: 2"); //для отладки  
     break;
     case 3:
     mp3.playMP3Folder(3); // проигрываем файл mp3/0003.mp3
     Serial.println ("track: 3"); //для отладки  
     break; 
     case 4:
     mp3.playMP3Folder(4); // проигрываем файл mp3/0004.mp3
     Serial.println ("track: 4"); //для отладки  
     break;
     case 5:
     mp3.playMP3Folder(5); // проигрываем файл mp3/0005.mp3
     Serial.println ("track: 5"); //для отладки  
     break; 
     case 6:
     mp3.playMP3Folder(6); // проигрываем файл mp3/0006.mp3
     Serial.println ("track: 6"); //для отладки  
     break;
     case 7:
     mp3.playMP3Folder(7); // проигрываем файл mp3/0007.mp3
     Serial.println ("track: 7"); //для отладки  
     break;
     case 8:
     mp3.playMP3Folder(8); // проигрываем файл mp3/0008.mp3
     Serial.println ("track: 8"); //для отладки  
     break;
     case 9:
     mp3.playMP3Folder(9); // проигрываем файл mp3/0009.mp3
     Serial.println ("track: 9"); //для отладки  
     break;
     case 10:
     mp3.playMP3Folder(10); // проигрываем файл mp3/0010.mp3
     Serial.println ("track: 10"); //для отладки  
     break; 
     case 11:
     mp3.playMP3Folder(11); // проигрываем файл mp3/0011.mp3
     Serial.println ("track: 11"); //для отладки  
     break; 
     case 12:
     mp3.playMP3Folder(12); // проигрываем файл mp3/0012.mp3
     Serial.println ("track: 12"); //для отладки  
     break;
     case 13:
     mp3.playMP3Folder(13); // проигрываем файл mp3/0013.mp3
     Serial.println ("track: 13"); //для отладки  
     break;  
     case 14:
     mp3.playMP3Folder(14); // проигрываем файл mp3/0014.mp3
     Serial.println ("track: 14"); //для отладки  
     break;  
     case 15:
     mp3.playMP3Folder(15); // проигрываем файл mp3/0015.mp3
     Serial.println ("track: 15"); //для отладки  
     break;  
     case 16:
     mp3.playMP3Folder(16); // проигрываем файл mp3/0016.mp3
     Serial.println ("track: 16"); //для отладки  
     break;
     case 17:
     mp3.playMP3Folder(17); // проигрываем файл mp3/0017.mp3
     Serial.println ("track: 17"); //для отладки  
     break;  
     case 18:
     mp3.playMP3Folder(18); // проигрываем файл mp3/0018.mp3 
     Serial.println ("track: 18"); //для отладки  
     break;
     case 19:
     mp3.playMP3Folder(19); // проигрываем файл mp3/0019.mp3
     Serial.println ("track: 19"); //для отладки  
     break;
     case 20:
     mp3.playMP3Folder(20); // проигрываем файл mp3/0020.mp3
     Serial.println ("track: 20"); //для отладки  
     break; 
     case 21:
     mp3.playMP3Folder(21); // проигрываем файл mp3/0021.mp3
     Serial.println ("track: 21"); //для отладки  
     break;
     case 22:
     mp3.playMP3Folder(22); // проигрываем файл mp3/0022.mp3
     Serial.println ("track: 22"); //для отладки  
     break;  
     case 23:
     mp3.playMP3Folder(23); // проигрываем файл mp3/0023.mp3
     Serial.println ("track: 23"); //для отладки  
     break;

    }


    delay(2000); // задержку лучше заменить на миллис
    mp3.pause(); // пауза
    //Serial.println ("track"); //для отладки


    /*аналог задержки
    if (millis() - timing2 > 3000){ // Вместо 3000 подставьте нужное вам значение паузы
     timing2 = millis();
     Serial.println ("3 seconds");
    }

     mp3.pause(); // пауза
    */

  }


 //Будильник, длительность воспроизведения звука составит 60 секунд
 if(Hor == alarm_clock_hours && Min == alarm_clock_minutes) {
  mp3.playFolder(2, 2); //2=папка/2=дорожка, имя папки должно быть 01..99, а файлы в папке должны начинаться с 3 десятичных цифр с ведущими нулями // проигрываем файл 02/002.mp3
  Serial.println ("alarm_track_Folder2: 2"); //для отладки

  Serial.print("getCommandStatus: ");  //для отладки, Получить статус команд
  Serial.println(mp3.getCommandStatus()); //1=модуль занят, 2=модуль в спящем режиме, 3=запрос получен не полностью, 4=не совпадает контрольная сумма
                                          //5=запрошенная папка/трек вне допустимого диапазона, 6=запрошенная папка/трек не найдена
                                          //7=реклама доступна во время воспроизведения трека, 8=SD-карта не найдена, 9=???, 10=спящий модуль
                                          //11=ОК команда принята, 12=ОК воспроизведение завершено, 13=ОК модуль готов после перезагрузки
  
  delay(60000); // задержку лучше заменить на миллис
  mp3.pause(); // пауза
  Serial.print("getStatus: ");  //для отладки, Получить статус
  Serial.println(mp3.getStatus());  //0=стоп, 1=воспроизведение, 2=пауза, 3=спящий режим или режим ожидания, 4=ошибка связи, 5=неизвестное состояние
  }
 



}




