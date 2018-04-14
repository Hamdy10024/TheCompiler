#ifndef LEXICALANALYZER_TRANSITIONTABLE_H
#define LEXICALANALYZER_TRANSITIONTABLE_H

#include "State.h"
#include <map>
#include <vector>
class TransitionTable
{
public:
    //std::map<State , vector < pair <Entry, State > > > table;
    typedef std::map<State*,State::stateTransitions> table;
    TransitionTable(TransitionTable::table &transitionTable, State *startState);

    /* Returns the start state of the minimized DFA. */
    State *getStartState();

    /* Returns the next state under input "input" applied to the current state.
     * If not found, return PHI state. */
    State *getNextState(State *current, char input);

    int size();
    void print();
private:
    TransitionTable::table transitionTable;
    State *startState;
};

#endif

