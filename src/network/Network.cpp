#include "Network.h"

void Network::startSoftAP(const char *ssid, const char *password) {
    WiFi.softAP(ssid, password);
    WiFi.softAPIP();
}

void Network::connectToWifi(const char *ssid, const char *password) {

    Serial.begin(9600);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.end();
}