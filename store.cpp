#include <EEPROM.h>
#include <WString.h>

struct Period {
  int startHour;
  int startMinute;
  int endHour;
  int endMinute;

    String toJSON() {
    String result;

    result += "{\n";
    result += "  \"start\": {\n";
    result += "    \"hour\": " + String(startHour) + ",\n";
    result += "    \"minute\": " + String(startMinute) + "\n";
    result += "    },\n";
    result += "  \"end\": {\n";
    result += "    \"hour\": " + String(endHour) + ",\n";
    result += "    \"minute\": " + String(endMinute) + "\n";
    result += "    }\n";
    result += "}";

    return result;
  }
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
    result += "    \"hour\": " + String(everyHour) + ",\n";
    result += "    \"minute\": " + String(everyMinute) + "\n";
    result += "    },\n";
    result += "  \"for\": {\n";
    result += "    \"hour\": " + String(forHour) + ",\n";
    result += "    \"minute\": " + String(forMinute) + "\n";
    result += "    }\n";
    result += "}";

    return result;
  }
};

enum StorageOffset {
  mode = 0,
  periodSize = 4,  // maximum size is 255
  every = 12,
  period = 128,
};

class Store {
public:

  int _periodSize = 0;

  int getAsInt(StorageOffset offset) {
    return EEPROM.read(offset);
  }

  void reset() {
    for (int i = 0; i < 512; i++) { EEPROM.write(i, 0); }
    _periodSize = 0;
  }

  void init() {
    EEPROM.begin(512);
    _periodSize = getAsInt(StorageOffset::periodSize);
    if (_periodSize >= ((512 - 128) / 4)) {
      reset();
    }
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

  Period getPeriod(const int index) {
    Period result;
    int padding = 4 * index;
    result.startHour   = EEPROM.read(StorageOffset::period + padding);
    result.startMinute = EEPROM.read(StorageOffset::period + padding + 1);
    result.endHour     = EEPROM.read(StorageOffset::period + padding + 2);
    result.endMinute   = EEPROM.read(StorageOffset::period + padding + 3);
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
    if (index >= _periodSize || _periodSize <= 0) {
      return;
    }

    EEPROM.write(StorageOffset::periodSize, --_periodSize);

    if (index == _periodSize) { // after -1
      return;
    }

    // move last one to index position
    int padding = 4 * index;
    const auto last = getPeriod(_periodSize);

    EEPROM.write(StorageOffset::period + padding    , last.startHour);
    EEPROM.write(StorageOffset::period + padding + 1, last.startMinute);
    EEPROM.write(StorageOffset::period + padding + 2, last.endHour);
    EEPROM.write(StorageOffset::period + padding + 3, last.endMinute);
  }

  int findPeriod(int startHour, int startMinute, int endHour, int endMinute) {
    int index = 0;
    
    while (index < _periodSize) {
      const auto current = getPeriod(index);
      if (
        current.startHour == startHour && current.endHour == current.endHour &&
        current.startMinute == startMinute && current.endMinute == endMinute
      ) {
        return index;
      }

      index++;
    }

    return -1;
  }

  void setMode(bool mode) {
    EEPROM.write(StorageOffset::mode, mode);
  }

  bool getMode(bool mode) {
    return EEPROM.read(StorageOffset::mode);
  }
};
