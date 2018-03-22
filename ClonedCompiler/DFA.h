
/* 
 * File:   DFA.h
 * Author: Dahlia
 *
 * Created on March 21, 2018, 12:49 AM
 */

#ifndef DFA_H
#define DFA_H
#include "NFAState.h"
#include "DFAState.h"
#include "Entry.h"
#include <string>
#include <vector>
#include <queue>

//typedef std::vector <NFAState::stateTransitions>  NFAstates ;

class DFA{
 public:
     DFA(NFAState* startState, std::string token); 
     std::vector <std::vector <int>> getTransitionTable();
     std::vector<std::pair<int, int> > getStatesGroups();

 private:
     std::string token;
     NFAState* startState;
     int counter;
     std::vector<DFAState*> DFAStates;
     std::queue<DFAState*> DFAstatesInc;
     std::vector<std::vector<int> > transitionTable;
     std::vector<std::pair<int, int> > statesGroups;
     void subsetConstruction();
     void epsilonClosure(DFAState* Dstate);
     bool exists (NFAState* a, DFAState* b);
     bool foundEntry(NFAState* t,std::vector <NFAState*> &epsilonStates,std::string s);
     void initiateDtransition();
     void setAcceptingState(DFAState* d);
     std::vector <NFAState*> move(DFAState* d, char ch);
     bool checkSameStates(std::vector <NFAState*> v1, std::vector<NFAState*> v2) ;
     bool combine(DFAState* d);
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* DFA_H */

