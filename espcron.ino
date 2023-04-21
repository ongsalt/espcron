#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <Ticker.h>

#include <uri/UriRegex.h>
#include <uri/UriBraces.h>

#include "datetime.cpp"
#include "store.cpp"

#include "web/dist/webbuiltin.hpp"

#define TRACE(...) Serial.printf(__VA_ARGS__)


const char *ssid = "Mi 11 lite";
const char *password = "";

const int offsetTime = 25200;



Ticker timeTicker;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "1.th.pool.ntp.org", offsetTime);

ESP8266WebServer server(80);

DateTime dateTime(D0, D2, D1);
Store store;



void handleSysInfo() {
  TRACE("[WebServer] Get /sysinfo\n");
  String result;

  result += "{\n";
  result += "  \"flashSize\": " + String(ESP.getFlashChipSize()) + ",\n";
  result += "  \"freeHeap\": " + String(ESP.getFreeHeap()) + ",\n";
  result += "  \"chipId\": " + String(ESP.getChipId()) + ",\n";
  result += "  \"version\": {\n";
  result += "  \"full\": \"" + String(ESP.getFullVersion()) + "\",\n";
  result += "  \"core\": \"" + String(ESP.getCoreVersion()) + "\"\n";
  result += "  }\n";
  result += "}";

  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "application/json; charset=utf-8", result);
} 

void serverSetup() { 

  // Serve static page
  server.on("/", HTTP_GET, [] () {
    TRACE("[WebServer] Get /\n");
    server.send(200, "text/html; charset=utf-8", FPSTR(WebBuiltin::indexHtml));
  });

  server.on("/sysinfo", HTTP_GET, handleSysInfo);

  server.on("/app.css", HTTP_GET, [] () {
    TRACE("[WebServer] get /app.css\n");
    server.send(200, "text/css", FPSTR(WebBuiltin::appCss));
  });

  server.on("/main.1.js", HTTP_GET, [] () {
    TRACE("[WebServer] get /main.1.js\n");
    server.send(200, "text/javascript", FPSTR(WebBuiltin::main1));
  });

  server.on("/main.2.js", HTTP_GET, [] () {
    TRACE("[WebServer] get /main.2.js\n");
    server.send(200, "text/javascript", FPSTR(WebBuiltin::main2));
  });

    server.on("/main.3.js", HTTP_GET, [] () {
    TRACE("[WebServer] get /main.3.js\n");
    server.send(200, "text/javascript", FPSTR(WebBuiltin::main3));
  });

  server.on("/api.js", HTTP_GET, [] () {
    TRACE("[WebServer] get /api.js\n");
    server.send(200, "text/javascript", FPSTR(WebBuiltin::apiJs));
  });

  server.onNotFound([] () {
    TRACE("[WebServer] Not found\n");
    server.send(404, "text/html", FPSTR(WebBuiltin::notfoundHtml));
  });

  // API route

  // server.on(UriRegex("^\\/api/on\\/([0-9]+){4}\\/to\\/([0-9]+){4}$"), HTTP_GET, [] () {
  server.on(UriBraces("/api/on/{}/to/{}"), HTTP_GET, [] () {
    int on = server.pathArg(0).toInt();
    int duration = server.pathArg(1).toInt();

    int onHour = on / 100;
    int onMinute = on % 100;

    int durationHour = duration / 100;
    int durationMinute = duration % 100;

    // add -> just fucking add
    store.addPeriod(Period { onHour, onMinute, durationHour, durationMinute });

    TRACE("[WebServer] Get /api/on/");
    TRACE(server.pathArg(0).c_str());
    TRACE("/to/");
    TRACE(server.pathArg(1).c_str());
    TRACE("\n");

    server.send(200, "text/html; charset=utf-8", "{ \"ok\": true, \"index\": " + String(store._periodSize - 1) + " }");
  });

  // server.on(UriRegex("^\\/api/remove\\/([0-9]+){4}\\/to\\/([0-9]+){4}$"), HTTP_GET, [] () {
  server.on(UriBraces("/api/remove/{}/to/{}"), HTTP_GET, [] () {
    int on = server.pathArg(0).toInt();
    int duration = server.pathArg(1).toInt();

    int onHour = on / 100;
    int onMinute = on % 100;

    int durationHour = duration / 100;
    int durationMinute = duration % 100;

    TRACE("[WebServer] Get /api/remove/");
    TRACE(server.pathArg(0).c_str());
    TRACE("/to/");
    TRACE(server.pathArg(1).c_str());
    TRACE("\n");

    const int index = store.findPeriod(onHour, onMinute, durationHour, durationMinute);
    if (index == -1) {
      server.send(404, "text/html; charset=utf-8", "{ \"ok\": false, \"message\": \"not exist\" }");
    }

    server.send(200, "text/html; charset=utf-8", "{ \"ok\": true }");
  });

  // server.on(UriRegex("^\\/api/every\\/([0-9]+){4}\\/for\\/([0-9]+){4}$"), HTTP_GET, [] () {
  server.on(UriBraces("/api/every/{}/for/{}"), HTTP_GET, [] () {
    int every = server.pathArg(0).toInt();
    int duration = server.pathArg(1).toInt();

    int everyHour = every / 100;
    int everyMinute = every % 100;

    int durationHour = duration / 100;
    int durationMinute = duration % 100;

    store.setEvery(everyHour, everyMinute, durationHour, durationMinute);

    Serial.print("[fehvjhe,kn]");
    Serial.print(every);
    Serial.print(":");
    Serial.println(duration);

    TRACE("[WebServer] Get /api/every/");
    TRACE(server.pathArg(0).c_str());
    TRACE("/for/");
    TRACE(server.pathArg(1).c_str());
    TRACE("\n");

    server.send(200, "text/html; charset=utf-8", "{ \"ok\": true }");
  });

  server.on(UriRegex("^\\/api/mode\\/([0-1]+)$"), HTTP_GET, [] () {
    int mode = server.pathArg(0).toInt();

    TRACE("[WebServer] Get /api/mode/");
    TRACE(server.pathArg(0).c_str());
    TRACE("\n");

    store.setMode(mode);

    server.send(200, "application/json; charset=utf-8", "{ \"ok\": true }");
  });

  server.on("/api/store/reset", HTTP_GET, [] () {

    TRACE("[WebServer] Get /api/store/reset");  

    store.reset();

    server.send(200, "text/html; charset=utf-8", "{ \"ok\": true }");
  });

  server.on("/api/get/every", HTTP_GET, [] () {

    TRACE("[WebServer] Get /api/get/every");  

    const auto result = store.getEvery().toJSON();

    server.send(200, "text/html; charset=utf-8", result);
  });

  server.on("/api/get/period", HTTP_GET, [] () {

    TRACE("[WebServer] Get /api/get/period");  

    String result;

    result += "{";
    result += " \"size\": " + String(store._periodSize) + ",\n";
    result += " \"data\": [";
    for (int i = 0; i < store._periodSize; i++) {
      result += store.getPeriod(i).toJSON();
      result += ",\n";
    }
    result += "]";
    result += "}";

    server.send(200, "text/html; charset=utf-8", result);
  });

}

void setup() {
  Serial.begin(115200);

  dateTime.init();
  store.init();

  WiFi.mode(WiFiMode::WIFI_AP_STA);
  WiFi.softAP("ESP8266", "4405208266");
  WiFi.begin(ssid, password);

  WiFi.setHostname("espconfig");

  TRACE("Connect to wifi...\n");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    TRACE(".");
  }

  TRACE("Setting up NTP...\n");
  timeClient.begin();

  TRACE("Preparing the server...\n");
  serverSetup();
  server.begin();
  TRACE("Done\n");

  // timeTicker.attach(1, [] () {
    // 10.00 - 11.30 & 13.00 - 14.30
    // timeClient.update();

    // Serial.print(timeClient.getHours());
    // Serial.print(":");
    // Serial.println(timeClient.getMinutes());
  // });
}

void loop() {

  server.handleClient();
  // delay(1000);
}
