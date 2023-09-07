#include <LittleFS.h>

class Settings {
public:
    static bool saveSettings(const String& settings) ;
    static String readSettings();
};