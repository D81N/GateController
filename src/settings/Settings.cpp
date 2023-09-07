#include "Settings.h"

bool Settings::saveSettings(const String& settings) {
    File file = LittleFS.open("/settings.json", "w");
    if (!file) {
        Serial.println("Error opening file");
        return false;
    }

    if (!file.print(settings)) {
        Serial.println("Error writing file");
        return false;
    }

    file.close();
    return true;
}

String Settings::readSettings() {

    File file = LittleFS.open("/settings.json", "r");
    if (!file) {
        Serial.println("Failed to open file for reading");
        return "";
    }

    String settings;
    while (file.available()) {
        settings += (char)file.read();
    }
    file.close();

    return settings;
}