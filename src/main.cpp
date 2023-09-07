#include "network/Network.h"
#include "gate_server/GateServer.h"
#include "settings/Settings.h"

GateLeaf    left;
GateLeaf    right;
Gate        gate(left, right);
GateServer  server(80, gate);

void setup() {
    Serial.begin(9600);
    LittleFS.begin();
    analogWriteFreq(5000);
    left.configureGateLeaf(Settings::readSettings(), "left");
    right.configureGateLeaf(Settings::readSettings(), "right");
    gate.initPins();
    Network::connectToWifi("TP-LINK_EFDA52", "kul1551luk");
    server.start();
}

void loop() {
    server.handleClient();
    // TODO gate status update
    // TODO gate error detect
}