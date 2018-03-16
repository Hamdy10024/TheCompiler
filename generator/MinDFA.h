#ifndef LEXICALANALYZER_MINDFA_H
#define LEXICALANALYZER_MINDFA_H

#include <vector>
#include "State.h"

class MinDFA {
public:
    typedef std::vector<State::stateTransitions> table;

    MinDFA();

    MinDFA::table getTransitionTable();

    State getStartState();

private:
    MinDFA::table transitionTable;
    State startState;
};

#endif
