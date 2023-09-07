#include "Settings.h"

int Settings::saveSettings(const String& settings) {
    File file = LittleFS.open("/settings.json", "w");
    if (!file) {
        Serial.println("Error opening file");
        return 0;
    }

    if (!file.print(settings)) {
        Serial.println("Error writing file");
        return 0;
    }

    file.close();
    return 1;
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