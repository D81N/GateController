#include "Gate.h"

Gate::Gate(GateLeaf& left, GateLeaf& right, uint32_t delayBtwAction) :
        left(left),
        right(right),
        state(State::STOPPED),
        error(Error::NONE),
        delayBtwAction(delayBtwAction) {}

void Gate::initPins() const {
    right.initPins();
    left.initPins();
}

GateLeaf &Gate::getLeft() {
    return left;
}

GateLeaf &Gate::getRight() {
    return right;
}

State &Gate::getState() {
    return state;
}

void Gate::open() {
    state = State::OPENING;
    left.open();
    delay(delayBtwAction);
    right.open();
}

void Gate::close() {
    state = State::CLOSING;
    right.close();
    delay(delayBtwAction);
    left.close();
}

void Gate::stop() {
    state = State::STOPPED;
    left.stop();
    right.stop();
}

void Gate::openSingle() {
    state = State::OPENING_LEAF;
    left.open();
}

void Gate::closeSingle() {
    state = State::CLOSING_LEAF;
    left.close();
}

Error &Gate::getError() {
    return error;
}

bool Gate::errorIsPresent() {
    return error != Error::NONE;
}
