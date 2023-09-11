#include "GateServer.h"
#include "settings/Settings.h"
#include <ArduinoJson.h>
#include <LittleFS.h>

GateServer::GateServer(int32_t port, Gate &gate) :
        server(port),
        gate(gate) {}

void GateServer::handleGetSettings() {
    server.on("/settings", HTTP_GET, [&]() {
        StaticJsonDocument<255> doc;
        String settings = Settings::readSettings();

        if (settings.isEmpty()) {
            String jsonResponse;
            doc["message"] = "Can`t read settings.";
            serializeJsonPretty(doc, jsonResponse);
            server.send(423, "application/json", jsonResponse);
            return;
        }

        server.send(200, "application/json", settings);
    });
}

void GateServer::handlePostSettings() {
    server.on("/settings", HTTP_POST, [&]() {
        StaticJsonDocument<255> doc;

        if (gate.getState() == State::OPENED || gate.getState() == State::CLOSED || gate.getState() == State::STOPPED) {
            doc["leftGateLeafOpenPin"] = server.arg("leftGateLeafOpenPin").toInt();
            doc["leftGateLeafClosePin"] = server.arg("leftGateLeafClosePin").toInt();
            doc["leftGateLeafSpeed"] = server.arg("leftGateLeafSpeed").toInt();
            doc["rightGateLeafOpenPin"] = server.arg("rightGateLeafOpenPin").toInt();
            doc["rightGateLeafClosePin"] = server.arg("rightGateLeafClosePin").toInt();
            doc["rightGateLeafSpeed"] = server.arg("rightGateLeafSpeed").toInt();
            doc["delayBtwGateLeaves"] = server.arg("delayBtwGateLeaves").toInt();

            gate.setDelayBtwGateLeaves(doc["delayBtwGateLeaves"]);
            gate.getLeft().configureGateLeaf(doc["leftGateLeafOpenPin"],
                                             doc["leftGateLeafClosePin"],
                                             doc["leftGateLeafSpeed"]);
            gate.getRight().configureGateLeaf(doc["rightGateLeafOpenPin"],
                                              doc["rightGateLeafClosePin"],
                                              doc["rightGateLeafSpeed"]);
            gate.initPins();

            String settings;
            serializeJsonPretty(doc, settings);

            if (!Settings::saveSettings(settings)) {
                String response;
                doc.clear();
                doc["message"] = "Error occurred while saving settings.";
                serializeJsonPretty(doc, response);
                server.send(423, "application/json", response);
                return;
            }

            server.send(200, "application/json", settings);
            return;
        }

        String response;
        doc["message"] = "Not allowed change settings while gate is already in action.";
        serializeJsonPretty(doc, response);
        server.send(423, "application/json", response);
    });
}

void GateServer::handlePostGate() {
    server.on("/gate", HTTP_POST, [&]() {
        StaticJsonDocument<64> doc;
        String jsonResponse;

        if (gate.errorIsPresent()) {
            doc["message"] = "Can`t perform action. Error is present.";
            serializeJsonPretty(doc, jsonResponse);
            server.send(503, "application/json", jsonResponse);
            return;
        }

        bool leftOpen = server.arg("leftOpen").equalsIgnoreCase("true");
        bool leftClose = server.arg("leftClose").equalsIgnoreCase("true");
        bool rightOpen = server.arg("rightOpen").equalsIgnoreCase("true");
        bool rightClose = server.arg("rightClose").equalsIgnoreCase("true");

        State action = Gate::recognizeAction(leftOpen, leftClose, rightOpen, rightClose);

        if (action == State::STOPPED) {
            doc["message"] = "Gate stopped.";
            serializeJsonPretty(doc, jsonResponse);
            gate.stop();
            server.send(200, "application/json", jsonResponse);
            return;
        }

        if (gate.isPerformingAction()) {
            doc["message"] = "Can`t perform action. Gate is already in action.";
            serializeJsonPretty(doc, jsonResponse);
            server.send(423, "application/json", jsonResponse);
            return;
        }

        switch (action) {
            case State::OPENING:
                gate.open();
                doc["message"] = "Gate opening...";
                break;
            case State::CLOSING:
                gate.close();
                doc["message"] = "Gate closing...";
                break;
            case State::OPENING_LEAF:
                gate.openSingle();
                doc["message"] = "Gate leaf opening...";
                break;
            case State::CLOSING_LEAF:
                gate.closeSingle();
                doc["message"] = "Gate leaf closing...";
                break;
        }

        serializeJsonPretty(doc, jsonResponse);
        server.send(200, "application/json", jsonResponse);
    });
}

void GateServer::handleGetState() {
    server.on("/state", HTTP_GET, [&]() {
        StaticJsonDocument<32> doc;
        String jsonResponse;
        doc["state"] = stateToString[(int )gate.getState()];
        serializeJsonPretty(doc, jsonResponse);
        server.send(200, "application/json", jsonResponse);
    });
}

void GateServer::handleGetError() {
    server.on("/error", HTTP_GET, [&]() {
        StaticJsonDocument<32> doc;
        String jsonResponse;
        doc["error"] = errorToString[(int )gate.getError()];
        serializeJsonPretty(doc, jsonResponse);
        server.send(200, "application/json", jsonResponse);
    });
}

void GateServer::initRouting() {
    handlePostGate();
    handleGetSettings();
    handlePostSettings();
    handleGetState();
    handleGetError();
}

void GateServer::handleClient() {
    server.handleClient();
}

void GateServer::start() {
    initRouting();
    server.serveStatic("/", LittleFS, "/");
    server.begin();
}

Gate &GateServer::getGate() {
    return gate;
}