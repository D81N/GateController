#include "network/Network.h"
#include "gate_server/GateServer.h"

GateLeaf    left(D0, D1);
GateLeaf    right(D2, D3);
Gate        gate(left, right, 1000);
GateServer  server(80, gate);

void setup() {
    gate.initPins();
    Network::connectToWifi("TP-LINK_EFDA52", "kul1551luk");
    server.start();
}

void loop() {
    server.handleClient();
}