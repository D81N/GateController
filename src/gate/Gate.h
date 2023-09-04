#include "gate/gate_leaf/GateLeaf.h"
#include "gate/state/State.h"
#include "gate/error/Error.h"

class Gate {
private:
    GateLeaf left;
    GateLeaf right;
    State state;
    Error error;
    uint32_t delayBtwAction;
    uint8_t currentSensorPin;
    float minCurrent;
    float maxCurrent;

public:
    Gate(uint8_t currentSensorPin, float minCurrent, float maxCurrent,
         uint8_t leftOpenPin, uint8_t leftClosePin,
         uint8_t rightOpenPin, uint8_t rightClosePin,
         uint32_t delayBtwAction);
    void initPins() const;
    GateLeaf& getLeft();
    GateLeaf& getRight();
    State& getState();
    void open();
    void close();
    void stop();
    void openSingle();
    void closeSingle();
};