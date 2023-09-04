#include <ESP8266WiFi.h>

class Network {
public:
    static void startSoftAP(const char* ssid, const char* password);
    static void connectToWifi(const char* ssid, const char* password);
};