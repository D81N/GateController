#include "GateServer.h"

GateServer::GateServer(int32_t port, Gate &gate) :
        server(port),
        gate(gate) {}

void GateServer::handleOpenGate() {
    server.on("/open-gate", HTTP_POST, [&]() {

        if (gate.errorIsPresent()) {
            server.send(503,
                        "application/json",
                        R"({"message":"Can`t open gate. Error is present."})");
            return;
        }

        if (gate.getState() == State::CLOSING_LEAF || gate.getState() == State::OPENING_LEAF ||
            gate.getState() == State::CLOSING || gate.getState() == State::OPENING) {
            server.send(423,
                        "application/json",
                        R"({"message":"Can`t open gate. It`s already in action"})");
            return;
        }

        if (gate.getState() == State::OPENED) {
            server.send(423,
                        "application/json",
                        R"({"message":"Can`t open gate. It`s already opened"})");
            return;
        }

        gate.open();
        server.send(200, "application/json", R"({"message":"Gate is opening"})");
    });
}

void GateServer::initRouting() {
    handleOpenGate();
}

void GateServer::handleClient() {
    server.handleClient();
}

void GateServer::start() {
    initRouting();
    server.begin();
}






