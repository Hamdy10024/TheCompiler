/*
 * File:   DFA.h
 * Author: Dahlia
 *
 * Created on March 21, 2018, 12:49 AM
 */

#ifndef DFA_H
#define DFA_H

#include "NFAState.h"
#include "State.h"
#include "dfa/DFAState.h"
#include "Pattern.h"
#include "MinDFA.h"
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include "TransitionTable.h"
#include "token_table.h"

typedef std::vector<State::stateTransitions> NFAstates;
using namespace std;

class DFA {
public:
    DFA(NFAState *startState, token_table *toktab);

    TransitionTable *getTable();

    void freeStates();

private:
    NFAState *startState;
    int counter;
    vector<DFAState *> DFAStates;
    TransitionTable::table trans;
    token_table *tktab;
    TransitionTable *transition_table;
    void DFS(NFAState *node, Pattern inp, vector<NFAState *> &cals);
    void construct();
};


#endif /* DFA_H */
