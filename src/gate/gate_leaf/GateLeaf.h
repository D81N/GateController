#include <Arduino.h>

class GateLeaf {
private:
    int openPin;
    int closePin;

public:
    GateLeaf(uint8_t openPin, uint8_t closePin);
    void initPins() const;
    void open() const;
    void close() const;
    void stop() const;
};