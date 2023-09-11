enum class State {
    OPENING,
    OPENING_LEAF,
    OPENED,
    CLOSING,
    CLOSING_LEAF,
    CLOSED,
    STOPPED
};

static const String stateToString[] ={
        "OPENING",
        "OPENING_LEAF",
        "OPENED",
        "CLOSING",
        "CLOSING_LEAF",
        "CLOSED",
        "STOPPED",
};