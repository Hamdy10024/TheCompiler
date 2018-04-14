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
typedef std::vector <State::stateTransitions>  NFAstates ;
using namespace std;
class DFA
{
public:
    DFA(NFAState* startState,token_table * toktab);
    std::vector <std::vector <int> > getTransitionTable();
    std::vector<std::pair<int, int> > getStatesGroups();
    TransitionTable*  getTable();

private:
    NFAState* startState;
    int counter;
       vector <NFAState*> epsilonStates2;

    stack <NFAState*> eclosure;

vector<NFAState*> dstates;
 std::set<Pattern > uniq;
        vector <Entry> all_en;
        vector <NFAState*> x;
        TransitionTable::table trans;
        token_table *tktab;
vector<NFAState*> transitions;
State::stateTransitions *st;
    vector <NFAState*> epsilonStates;
    std::vector<DFAState*> DFAStates;
    std::queue<DFAState*> DFAstatesInc;
    std::vector<std::vector<int> > transitionTable;
    TransitionTable *transition_table;
    std::vector<std::pair<int, int> > statesGroups;
    void subsetConstruction();
    void epsilonClosure(DFAState* Dstate);
    bool exists (NFAState* a, DFAState* b);
    bool foundEntry(NFAState* t,std::vector <NFAState*> &epsilonStates,Entry s);
    DFAState* initiateDtransition();
    void setAcceptingState(DFAState* d);
    std::vector <NFAState*> move(DFAState* d, Entry ch);
    bool checkSameStates(std::vector <NFAState*> v1, std::vector<NFAState*> v2) ;
    bool combine(DFAState* d);
    void DFS(NFAState * node,Entry inp , vector<NFAState*> &cals);
    void construct();
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* DFA_H */
