//Автор ASM
//Обсуждение работы на форуме https://community.alexgyver.ru/threads/bolshie-chasy-na-ws2812-esp8266-narodnyj-monitoring.5067
//Поблагодарить за труд, можно на Яндекс 410014148046232
#include "Constants.h"
#include "ESP8266WiFi.h"
#include <LittleFS.h>
#include <GyverPortal.h>
GyverPortal ui(&LittleFS);
#include <GyverNTP.h>
GyverNTP ntp(c.gmt);
#include <WiFiClient.h>

#include <EEManager.h>
EEManager mem1(w);
EEManager mem2(c);
EEManager mem3(o);
EEManager mem4(m);
EEManager mem6(r);
#include <microDS3231.h>
MicroDS3231 rtc;

#include <SoftwareSerial.h>
#include <DFPlayer.h>
SoftwareSerial mp3Serial;
DFPlayer mp3;

#include "FastLED.h"
#include <Wire.h>
#include "SparkFunBME280.h"
BME280 bmp280;
#include "OneWire.h"
#include "DallasTemperature.h"
// настроим библиотеку 1-Wire для связи с датчиком
OneWire oneWire_out(ONE_WIRE_BUS_2);
// создадим объект для работы с библиотекой DallasTemperature
DallasTemperature sensors(&oneWire_out);                       //уличный ds18b20
#define NUM_LEDS (LEDS_IN_SEGMENT * 28 + DOTS_NUM + DOT_TEMP)  // вычисляем кол-во светодиодов
CRGB leds[NUM_LEDS];                                           // определение СД ленты

bool flag_kuku;

bool Dot = true;                    // переменная для точек
uint8_t last_digit = 0;             // последний символ равен нулю
byte set_light;                     // переменная для освещенности
byte brightness;                    // переменная для освещенности
uint16_t new_bright, new_bright_f;  // переменная для освещенности
uint32_t bright_timer, off_timer;   // переменная для освещенности
float FtempH, FtempS, Fpres;
int8_t tempH, tempS;
uint16_t pres;
uint8_t hum;
uint8_t hour, minute, second, day, month;
int year;

byte segment_1, segment_2, segment_3, segment_4, dot_1, dot_2, dot_3, dot_4, dot_5, dot_6, dot_7, dot_8;
GPcolor color(0, 255, 255);
CRGB ledColor = CRGB(color.r, color.g, color.b);
EEManager mem5(ledColor);

CRGB ColorTable[NUM_COLORS] = {  // Таблица цветов
  CRGB::Amethyst, CRGB::Aqua, CRGB::Blue, CRGB::Chartreuse, CRGB::DarkGreen, CRGB::DarkMagenta, CRGB::DarkOrange, CRGB::DeepPink,
  CRGB::Fuchsia, CRGB::Gold, CRGB::GreenYellow, CRGB::LightCoral, CRGB::Tomato, CRGB::Salmon, CRGB::Red, CRGB::Orchid
};

/////////////////////////////////////////////
void setup() {
  if (!LittleFS.begin()) Serial.println("FS Error");
  Serial.begin(115200);
  EEPROM.begin(2000);
  mem1.begin(0, 'a');
  mem2.begin(mem1.nextAddr(), 'a');
  mem3.begin(mem2.nextAddr(), 'a');
  mem4.begin(mem3.nextAddr(), 'a');
  mem5.begin(mem4.nextAddr(), 'a');
  mem6.begin(mem5.nextAddr(), 'a');

  Wire.begin();
  bmp280.setI2CAddress(0x76);  //Подключение датчика
  if (bmp280.beginI2C() == false) Serial.println("Не удалось подключиться к датчику");
  //  LEDS.setBrightness(50);
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);  // подключение ленты
  FastLED.setMaxPowerInVoltsAndMilliamps(5, milliamp);
  firstSetSegment();
  wifi_connected();
  rtcCheck();
  if (DFPlayer_check) { DFPlayer_setup(); }
}

/////////////////////////////////////////////
void loop() {
  //BrightnessCheck();//перенес в body
  kuku_tick();
  mem1.tick();
  mem2.tick();
  mem3.tick();
  mem4.tick();
  mem5.tick();
  mem6.tick();
  ui.tick();
  ntp.tick();
  body();
  if (DFPlayer_check) { kuku_tick(); }
  static uint32_t timing;
  if (m.Monitoring) {
    if ((millis() - timing) > (m.delay_narod * 1000)) {
      timing = millis();
      narod();
    }
  }
}