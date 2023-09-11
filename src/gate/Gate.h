#include "gate/gate_leaf/GateLeaf.h"
#include "gate/state/State.h"
#include "gate/error/Error.h"

class Gate {
private:
    GateLeaf& left;
    GateLeaf& right;
    State state;
    Error error;
    uint32_t delayBtwAction;

public:
    Gate(GateLeaf& left, GateLeaf& right, uint32_t delay);
    void setDelayBtwGateLeaves(uint32_t delay);
    void initPins() const;
    GateLeaf& getLeft();
    GateLeaf& getRight();
    State& getState();
    Error& getError();
    bool errorIsPresent();
    bool isPerformingAction();
    void open();
    void close();
    void stop();
    void openSingle();
    void closeSingle();
    static State recognizeAction(bool oL, bool cL, bool oR, bool cR);
};