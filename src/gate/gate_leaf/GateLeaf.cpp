#include "GateLeaf.h"

GateLeaf::GateLeaf(uint8_t openPin, uint8_t closePin) {
    this->openPin = openPin;
    this->closePin = closePin;
}

void GateLeaf::open() const {
    digitalWrite(openPin, HIGH);
}

void GateLeaf::close() const {
    digitalWrite(closePin, HIGH);
}

void GateLeaf::stop() const {
    digitalWrite(openPin, LOW);
    digitalWrite(closePin, LOW);
}

void GateLeaf::initPins() const {
    pinMode(openPin, OUTPUT);
    pinMode(closePin, OUTPUT);
    digitalWrite(openPin, LOW);
    digitalWrite(closePin, LOW);
}