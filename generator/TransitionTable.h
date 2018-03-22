#ifndef LEXICALANALYZER_TRANSITIONTABLE_H
#define LEXICALANALYZER_TRANSITIONTABLE_H

#include "State.h"
#include "MinDFA.h"

class TransitionTable {
public:
    TransitionTable(MinDFA::table transitionTable, State startState);

    /* Returns the start state of the minimized DFA. */
    State getStartState();

    /* Returns the next state under input "input" applied to the current state.
     * If not found, return PHI state. */
    State getNextState(State current, char *input);

private:
    MinDFA::table transitionTable;

    State startState;
};

#endif

