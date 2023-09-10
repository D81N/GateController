#include "GateLeaf.h"

GateLeaf::GateLeaf() = default;

void GateLeaf::open() const {
    analogWrite(openPin, speed);
}

void GateLeaf::close() const {
    analogWrite(closePin, speed);
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

void GateLeaf::configureGateLeaf(uint8_t newOpenPin, uint8_t newClosePin, uint8_t newSpeed) {
    this->openPin = newOpenPin;
    this->closePin = newClosePin;
    this->speed = newSpeed;
}

void GateLeaf::configureGateLeaf(const String& json, const String& gateLeaf) {
    StaticJsonDocument<255> doc;
    deserializeJson(doc, json);
    configureGateLeaf(doc[gateLeaf + "GateLeafOpenPin"],
                      doc[gateLeaf + "GateLeafClosePin"],
                      doc[gateLeaf + "GateLeafSpeed"]);
}