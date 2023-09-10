#include <ESP8266WebServer.h>
#include "gate/Gate.h"

class GateServer {
private:
    ESP8266WebServer server;
    Gate& gate;

    void initRouting();
    void handleGetSettings();
    void handlePostSettings();
    void handlePostGate();

public:
    GateServer(int32_t port, Gate& gate);
    Gate& getGate();
    void handleClient();
    void start();
};