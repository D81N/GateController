#include "Gate.h"

Gate::Gate(GateLeaf& left, GateLeaf& right, uint32_t delay) :
        left(left),
        right(right),
        state(State::STOPPED),
        error(Error::NONE),
        delayBtwAction(delay) { }

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
    right.open();
    delay(delayBtwAction);
    left.open();
}

void Gate::close() {
    state = State::CLOSING;
    left.close();
    delay(delayBtwAction);
    right.close();
}

void Gate::stop() {
    state = State::STOPPED;
    left.stop();
    right.stop();
}

void Gate::openSingle() {
    state = State::OPENING_LEAF;
    right.open();
}

void Gate::closeSingle() {
    state = State::CLOSING_LEAF;
    right.close();
}

Error &Gate::getError() {
    return error;
}

bool Gate::errorIsPresent() {
    return error != Error::NONE;
}

void Gate::setDelayBtwGateLeaves(uint32_t delay) {
    delayBtwAction = delay;
}

State Gate::recognizeAction(bool oL, bool cL, bool oR, bool cR) {

    if (oL && oR)
        return State::OPENING;

    if (cL && cR)
        return State::CLOSING;

    if (oR)
        return State::OPENING_LEAF;

    if (cR)
        return State::CLOSING_LEAF;

    return State::STOPPED;
}

bool Gate::isPerformingAction() {
    return state == State::OPENING ||
            state == State::CLOSING ||
            state == State::OPENING_LEAF ||
            state == State::CLOSING_LEAF;
}

