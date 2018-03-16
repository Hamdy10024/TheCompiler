#ifndef LEXICALANALYZER_MINDFA_H
#define LEXICALANALYZER_MINDFA_H

#include <vector>
#include "State.h"

typedef std::vector<stateTransitions> table;

class MinDFA {
public:
    MinDFA();

    table getTransitionTable();

    State getStartState();

private:
    table transitionTable;
    State startState;
};

#endif
