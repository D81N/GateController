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

        doc["leftGateLeafOpenPin"] = server.arg("leftGateLeafOpenPin").toInt();
        doc["leftGateLeafClosePin"] = server.arg("leftGateLeafClosePin").toInt();
        doc["leftGateLeafSpeed"] = server.arg("leftGateLeafSpeed").toInt();
        doc["rightGateLeafOpenPin"] = server.arg("rightGateLeafOpenPin").toInt();
        doc["rightGateLeafClosePin"] = server.arg("rightGateLeafClosePin").toInt();
        doc["rightGateLeafSpeed"] = server.arg("rightGateLeafSpeed").toInt();
        doc["delayBtwGateLeaves"] = server.arg("delayBtwGateLeaves").toInt();

        String settings;
        serializeJsonPretty(doc, settings);

        if (!Settings::saveSettings(settings)) {
            String response;
            doc.clear();
            doc["message"] = "Can`t save settings.";
            serializeJsonPretty(doc, response);
            server.send(423, "application/json", response);
            return;
        }

        server.send(200, "application/json", settings);
    });
}

void GateServer::handleOpenGate() {
    server.on("/open-gate", HTTP_POST, [&]() {

        String jsonResponse;

        StaticJsonDocument<200> doc;

        if (gate.errorIsPresent()) {
            doc["message"] = "Can`t open gate. Error is present.";
            serializeJsonPretty(doc, jsonResponse);
            server.send(503, "application/json", jsonResponse);
            return;
        }

        if (gate.getState() == State::CLOSING_LEAF || gate.getState() == State::OPENING_LEAF ||
            gate.getState() == State::CLOSING || gate.getState() == State::OPENING) {
            doc["message"] = "Can`t open gate. It`s already in action.";
            serializeJsonPretty(doc, jsonResponse);
            server.send(423, "application/json", jsonResponse);
            return;
        }

        if (gate.getState() == State::OPENED) {
            doc["message"] = "Gate is already opened.";
            serializeJsonPretty(doc, jsonResponse);
            server.send(423, "application/json", jsonResponse);
            return;
        }

        gate.open();

        doc["message"] = "Gate is opening...";
        serializeJsonPretty(doc, jsonResponse);
        server.send(200, "application/json", jsonResponse);
    });
}

void GateServer::initRouting() {
    handleOpenGate();
    handleGetSettings();
    handlePostSettings();
}

void GateServer::handleClient() {
    server.handleClient();
}

void GateServer::start() {
    initRouting();
    server.serveStatic("/", LittleFS, "/");
    server.begin();
}






