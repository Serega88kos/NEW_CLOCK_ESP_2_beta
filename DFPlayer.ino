//////////// Функция DFPlayer
/*
[*]автор Maxx1200
[*]Каждый час будет говорить время!
*/
//========ВЫБОР-ТИПА-МОДУЛЯ========
//#define DFPlayer_type DFPLAYER_MINI         // Раскоментируйте эту строчку, если такой, DFPlayer Mini module, MP3-TF-16P module, FN-M16P module, YX5200 chip, YX5300 chip, JL AAxxxx chip
//#define DFPlayer_type DFPLAYER_FN_X10P      // Раскоментируйте эту строчку, если такой, FN-M10P module, FN-S10P module, FN6100 chip
#define DFPlayer_type DFPLAYER_HW_247A  // Закомментируйте эту строку,  если используеися плеер с чипом, отличным от, HW-247A module, GD3200B chip, MH2024K-24SS
//#define DFPlayer_type DFPLAYER_NO_CHECKSUM  // Раскоментируйте эту строчку, если такой, нет вычисления контрольной суммы (не рекомендуется)
//=================================
/***************************************************************************************************/
/*
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
   DFPlayer          -  https://github.com/enjoyneering/DFPlayer
   ESP8266 Core      -  https://github.com/esp8266/Arduino
   EspSoftwareSerial -  https://github.com/plerup/espsoftwareserial
*/
/***************************************************************************************************/
void DFPlayer_setup() {

  Serial.println("Инициализация DFPlayer... (может занять 3~5 секунд)");                                      //для отладки
  mp3Serial.begin(MP3_SERIAL_SPEED, SWSERIAL_8N1, MP3_RX_PIN, MP3_TX_PIN, false, MP3_SERIAL_BUFFER_SIZE, 0);  //false=сигнал не инвертирован, 0=размер буфера ISR/RX (общий с последовательным буфером TX)
  mp3.begin(mp3Serial, MP3_SERIAL_TIMEOUT, DFPlayer_type, false);                                             //"DFPLAYER_HW_247A" см. ПРИМЕЧАНИЕ, false = нет обратной связи от модуля после команды
  mp3.stop();                                                                                                 //если плеер работал во время перезагрузки ESP8266
  mp3.reset();                                                                                                //сбросить все настройки по умолчанию
  mp3.setSource(2);                                                                                           //1=USB-диск, 2=TF-карта, 3=Aux, 4=спящий режим, 5=NOR Flash
  mp3.setEQ(0);                                                                                               //0=Выкл., 1=Поп, 2=Рок, 3=Джаз, 4=Классика, 5=Бас
  mp3.setVolume(r.grom_mp3);                                                                                  //0..30, модуль сохраняет громкость при сбое питания

  Serial.print(" ♫ Громкость: ");   //для отладки, Получить громкость
  Serial.println(mp3.getVolume());  //0..30

  mp3Serial.enableRx(false);  //отключить прерывания на RX-контакте, меньше накладных расходов, чем mp3Serial.listen()

  mp3.playMP3Folder(26);
  Serial.println(" ♫ Приветствие");  // Музыкальное приветствие
}

void DFPlayer() {            // Функция срабатывающая раз в час
  if (r.status_kuku) {       // Если кукушка включена(проверка второй раз для корректной работы портала)
    if (r.kuku_mp3_check) {  // Если включено воспроизведение кукушки
      Serial.println(" ♫ Ку-Ку");
      mp3.playMP3Folder(25);  // проигрываем файл c кукушкой
    }
    if (r.kuku_mp3_check && r.vrem_mp3_check) delay(2500);
    if (r.vrem_mp3_check) {  // Если включено воспроизведение времени
      switch (hour) {        // Взависимости от часа будет говорить время
        case 0:
          mp3.playMP3Folder(24);         // проигрываем файл mp3/0024.mp3
          Serial.println(" ♫ 0 часов");  //для отладки
          break;
        case 1:
          mp3.playMP3Folder(1);        // проигрываем файл mp3/0001.mp3
          Serial.println(" ♫ 1 час");  //для отладки
          break;
        case 2:
          mp3.playMP3Folder(2);         // проигрываем файл mp3/0002.mp3
          Serial.println(" ♫ 2 часа");  //для отладки
          break;
        case 3:
          mp3.playMP3Folder(3);         // проигрываем файл mp3/0003.mp3
          Serial.println(" ♫ 3 часа");  //для отладки
          break;
        case 4:
          mp3.playMP3Folder(4);         // проигрываем файл mp3/0004.mp3
          Serial.println(" ♫ 4 часа");  //для отладки
          break;
        case 5:
          mp3.playMP3Folder(5);          // проигрываем файл mp3/0005.mp3
          Serial.println(" ♫ 5 часов");  //для отладки
          break;
        case 6:
          mp3.playMP3Folder(6);          // проигрываем файл mp3/0006.mp3
          Serial.println(" ♫ 6 часов");  //для отладки
          break;
        case 7:
          mp3.playMP3Folder(7);          // проигрываем файл mp3/0007.mp3
          Serial.println(" ♫ 7 часов");  //для отладки
          break;
        case 8:
          mp3.playMP3Folder(8);          // проигрываем файл mp3/0008.mp3
          Serial.println(" ♫ 8 часов");  //для отладки
          break;
        case 9:
          mp3.playMP3Folder(9);          // проигрываем файл mp3/0009.mp3
          Serial.println(" ♫ 9 часов");  //для отладки
          break;
        case 10:
          mp3.playMP3Folder(10);          // проигрываем файл mp3/0010.mp3
          Serial.println(" ♫ 10 часов");  //для отладки
          break;
        case 11:
          mp3.playMP3Folder(11);          // проигрываем файл mp3/0011.mp3
          Serial.println(" ♫ 11 часов");  //для отладки
          break;
        case 12:
          mp3.playMP3Folder(12);          // проигрываем файл mp3/0012.mp3
          Serial.println(" ♫ 12 часов");  //для отладки
          break;
        case 13:
          mp3.playMP3Folder(13);          // проигрываем файл mp3/0013.mp3
          Serial.println(" ♫ 13 часов");  //для отладки
          break;
        case 14:
          mp3.playMP3Folder(14);          // проигрываем файл mp3/0014.mp3
          Serial.println(" ♫ 14 часов");  //для отладки
          break;
        case 15:
          mp3.playMP3Folder(15);          // проигрываем файл mp3/0015.mp3
          Serial.println(" ♫ 15 часов");  //для отладки
          break;
        case 16:
          mp3.playMP3Folder(16);          // проигрываем файл mp3/0016.mp3
          Serial.println(" ♫ 16 часов");  //для отладки
          break;
        case 17:
          mp3.playMP3Folder(17);          // проигрываем файл mp3/0017.mp3
          Serial.println(" ♫ 17 часов");  //для отладки
          break;
        case 18:
          mp3.playMP3Folder(18);          // проигрываем файл mp3/0018.mp3
          Serial.println(" ♫ 18 часов");  //для отладки
          break;
        case 19:
          mp3.playMP3Folder(19);          // проигрываем файл mp3/0019.mp3
          Serial.println(" ♫ 19 часов");  //для отладки
          break;
        case 20:
          mp3.playMP3Folder(20);          // проигрываем файл mp3/0020.mp3
          Serial.println(" ♫ 20 часов");  //для отладки
          break;
        case 21:
          mp3.playMP3Folder(21);        // проигрываем файл mp3/0021.mp3
          Serial.println(" ♫ 21 час");  //для отладки
          break;
        case 22:
          mp3.playMP3Folder(22);         // проигрываем файл mp3/0022.mp3
          Serial.println(" ♫ 22 часа");  //для отладки
          break;
        case 23:
          mp3.playMP3Folder(23);         // проигрываем файл mp3/0023.mp3
          Serial.println(" ♫ 23 часа");  //для отладки
          break;
      }
    }
  }
}