#include "MinDFA.h"

MinDFA::MinDFA() {

}

MinDFA::table MinDFA::getTransitionTable() {
    return transitionTable;
}

State MinDFA::getStartState() {
    return startState;
}