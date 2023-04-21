#include <EEPROM.h>
#include <WString.h>

struct Period {
  int startHour;
  int startMinute;
  int endHour;
  int endMinute;
};

struct Every {
  int everyHour;
  int everyMinute;
  int forHour;
  int forMinute;

  String toJSON() {
    String result;

    result += "{\n";
    result += "  \"every\": {\n";
    result += "    \"hour\": \"" + String(everyHour) + "\",\n";
    result += "    \"minute\": \"" + String(everyMinute) + "\"\n";
    result += "    },\n";
    result += "  \"for\": {\n";
    result += "    \"hour\": \"" + String(forHour) + "\",\n";
    result += "    \"minute\": \"" + String(forMinute) + "\"\n";
    result += "    }\n";
    result += "}";

    return result;
  }
};

enum StorageOffset {
  mode = 0,
  periodSize = 4,  // maximum size is 255
  every = 12,
  period = 256,
};

class Store {
private:

  int _periodSize = 0;

public:
  int getAsInt(StorageOffset offset) {
    return EEPROM.read(offset);
  }

  void init() {
    EEPROM.begin(512);
    _periodSize = getAsInt(StorageOffset::periodSize);
  }

  Every getEvery() {
    Every result;
    result.everyHour = EEPROM.read(StorageOffset::every);
    result.everyMinute = EEPROM.read(StorageOffset::every + 1);
    result.forHour = EEPROM.read(StorageOffset::every + 2);
    result.forMinute = EEPROM.read(StorageOffset::every + 3);
    return result;
  }

  void setEvery(int everyHour, int everyMinute, int forHour, int forMinute) {
    EEPROM.write(StorageOffset::every    , everyHour);
    EEPROM.write(StorageOffset::every + 1, everyMinute);
    EEPROM.write(StorageOffset::every + 2, forHour);
    EEPROM.write(StorageOffset::every + 3, forMinute);
  }

  Period getPeriod(const int& id) {
    Period result;
    int padding = 4 * _periodSize;
    result.startHour = EEPROM.read(StorageOffset::period + padding);
    result.startMinute = EEPROM.read(StorageOffset::period + padding);
    result.endHour = EEPROM.read(StorageOffset::period + padding);
    result.endMinute = EEPROM.read(StorageOffset::period + padding);
    return result;
  }

  void addPeriod(const Period& config) {
    int padding = 4 * _periodSize;
    EEPROM.write(StorageOffset::period + padding    , config.startHour);
    EEPROM.write(StorageOffset::period + padding + 1, config.startMinute);
    EEPROM.write(StorageOffset::period + padding + 2, config.endHour);
    EEPROM.write(StorageOffset::period + padding + 3, config.endMinute);
    EEPROM.write(StorageOffset::periodSize, ++_periodSize);
  }

  void removePeriod(const int index) {
    if (_periodSize <= 0) {
      return;
    }
    int padding = 4 * _periodSize;
    EEPROM.write(StorageOffset::period + padding    , 0);
    EEPROM.write(StorageOffset::period + padding + 1, 0);
    EEPROM.write(StorageOffset::period + padding + 2, 0);
    EEPROM.write(StorageOffset::period + padding + 3, 0);
    EEPROM.write(StorageOffset::periodSize, --_periodSize);
    
    if (index == _periodSize) { // after -1
      return;
    }

    // move last one to this position

  }
};
