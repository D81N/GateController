#include <ESP8266WebServer.h>
#include "gate/Gate.h"

class GateServer {
private:
    ESP8266WebServer server;
    Gate gate;

    void initRouting();
    void handleOpenGate();

public:
    GateServer(int32_t port, Gate& gate);
    void handleClient();
    void start();
};