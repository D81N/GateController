#include <LittleFS.h>

class Settings {
public:
    static int saveSettings(const String& settings) ;
    static String readSettings();
};