#include <stdlib.h>
#include "TransitionTable.h"

TransitionTable::TransitionTable(MinDFA::table transitionTable, State startState) {
    this->transitionTable = transitionTable;
    this->startState = startState;
}

State TransitionTable::getStartState() {
    return startState;
}

State TransitionTable::getNextState(State current, char *input) {
    return State();
}