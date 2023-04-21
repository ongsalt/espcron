#include <Ds1302.h>
#include <SoftwareSerial.h>

const static char* WeekDays[] = {
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday",
  "Sunday"
};

class DateTime {
public:

  Ds1302 rtc;

  DateTime(uint8_t a, uint8_t b, uint8_t c)
    : rtc(a, b, c) {
  }

  void init() {
    rtc.init();
    if (rtc.isHalted()) {
      Serial.println("RTC is halted. Setting time...");

      Ds1302::DateTime dt = {
        .year = 23,
        .month = Ds1302::MONTH_APR,
        .day = 20,
        .hour = 14,
        .minute = 28,
        .second = 30,
        .dow = Ds1302::DOW_TUE
      };

      rtc.setDateTime(&dt);
    }
  }

  Ds1302::DateTime print() {
    // get the current time
    Ds1302::DateTime now;
    rtc.getDateTime(&now);

    Serial.print("20");
    Serial.print(now.year);  // 00-99
    Serial.print('-');
    if (now.month < 10) Serial.print('0');
    Serial.print(now.month);  // 01-12
    Serial.print('-');
    if (now.day < 10) Serial.print('0');
    Serial.print(now.day);  // 01-31
    Serial.print(' ');
    Serial.print(WeekDays[now.dow - 1]);  // 1-7
    Serial.print(' ');
    if (now.hour < 10) Serial.print('0');
    Serial.print(now.hour);  // 00-23
    Serial.print(':');
    if (now.minute < 10) Serial.print('0');
    Serial.print(now.minute);  // 00-59
    Serial.print(':');
    if (now.second < 10) Serial.print('0');
    Serial.print(now.second);  // 00-59
    Serial.println();
    return now;
  }

  Ds1302::DateTime get() {
    Ds1302::DateTime now;
    rtc.getDateTime(&now);
    return now;
  }

  bool isInPeriod(Ds1302::DateTime& now) {
    return true;
  }


  void set(Ds1302::DateTime& dt) {
    rtc.setDateTime(&dt);
  }

  void sync() {
    
  }

};
