#include <ArduinoJson.h>

class GateLeaf {
private:
    uint8_t openPin{};
    uint8_t closePin{};
    uint8_t speed{};

public:
    GateLeaf();
    void initPins() const;
    void configureGateLeaf(const String& json, const String& gateLeaf);
    void configureGateLeaf(uint8_t newOpenPin, uint8_t newClosePin, uint8_t newSpeed);
    void open() const;
    void close() const;
    void stop() const;
};