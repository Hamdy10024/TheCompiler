/* 
 * File:   DFA.h
 * Author: Dahlia
 *
 * Created on March 21, 2018, 12:49 AM
 */
#include "DFA.h"
#include "NFAState.h"
#include "DFAState.h"
#include "Entry.h"
#include <stack>
#include <string>
#include <queue>
#include <set>
#include <algorithm>
#include <utility>
using namespace std;

DFA::DFA(NFAState* startState, string token) {
    this->startState = startState;
    this->token=token;
    counter = 0;
    subsetConstruction();
}
vector<vector<int>> DFA::getTransitionTable() {
	return transitionTable;
}
vector<pair<int, int> > DFA::getStatesGroups() {
	return statesGroups;
}
void DFA::epsilonClosure(DFAState* Dstate){
    stack <NFAState*> eclosure;
    vector <NFAState*> list = Dstate -> getNFAStates();
    for (int i=0;i <list.size();i++){
        eclosure.push(list[i]);
    }
    while (eclosure.size()){
        NFAState* top =eclosure.top();
        eclosure.pop();
        vector <NFAState*> epsilonStates;
        if (!foundEntry(top,epsilonStates,"$")) continue;
        for (int i=0;i<epsilonStates.size();i++){
            if (!exists(epsilonStates[i],Dstate)){
                NFAState* x = epsilonStates[i];
		Dstate->addState(x);
		eclosure.push(x);
            }   
        }
    }
}
bool DFA::exists (NFAState* a, DFAState* b){
    for (int i=0;i< b->getNFAStates().size();i++)
        if (a-> getID()== b-> getNFAStates()[i]-> getID())
            return true;
    return false;
}
bool DFA::foundEntry(NFAState* t,vector <NFAState*> &epsilonStates,string s){
     NFAState::stateTransitions trans = t->getTransitions();
     for (int i=0;i<trans.size();i++) {
         if (trans[i].first.entry == s){
             epsilonStates.push_back(trans[i].second);
         }    
     }
     return epsilonStates.size();
}
void DFA:: initiateDtransition(){
    DFAState* init = new DFAState(counter ++);
    init->addState(startState);
    vector <NFAState*> epsilonStates;
    if (foundEntry(startState,epsilonStates,"$")) {
        init->addStateSet(epsilonStates);
        epsilonClosure(init);
    }
    DFAstatesInc.push(init);
    DFAStates.push_back(init);
    setAcceptingState(init);
    statesGroups.push_back(make_pair(init->getID(), init->isAcceptingState()));
    
    vector <int> vec(token.size());
    transitionTable.push_back(vec);
    
}
void DFA::setAcceptingState(DFAState* d){
    vector <NFAState*> states= d -> getNFAStates();
    vector <int> vec;
    for (int i=0;i<states.size();i++){
        if (states[i]->isAcceptingState())
            vec.push_back((int)states[i]->isAcceptingState());
    }
    if (vec.empty()) d->resetAccepting();
    else {
        sort (vec.begin(),vec.end());
        d->editAcceptingVal(vec[0]);
    }
}
bool comparator (NFAState* &a, NFAState* &b){
    return a->getID()< b->getID();
}
vector <NFAState*> DFA::move(DFAState* d, char ch) {
        vector<NFAState*> dstates =d->getNFAStates();
        vector<NFAState*> sameEntryStates;
	vector<NFAState*> transitions;
	for (int i = 0; i < dstates.size(); i++) {
	    if (!foundEntry(dstates[i],sameEntryStates,string (1,ch)))continue;
            transitions.insert(transitions.end(), sameEntryStates.begin(), sameEntryStates.end());
	}
	set <NFAState*> duplicateRemoval (transitions.begin(), transitions.end());
	transitions.assign(duplicateRemoval.begin(), duplicateRemoval.end());
 	sort(transitions.begin(),transitions.end(),comparator);
	return transitions;
}
bool DFA::checkSameStates(vector <NFAState*> v1, vector<NFAState*> v2) {
	vector<int> t1,t2;
        if (v1.size()!= v2.size())return false;
	for (int i = 0; i < v1.size(); i++) {
		t1.push_back(v1[i]->getID());
		t2.push_back(v2[i]->getID());
	    }
	sort(t1.begin(), t1.end());
	sort(t2.begin(), t2.end());
	return(equal(t1.begin(), t1.end(), t2.begin()));		
}
bool DFA::combine(DFAState* d) {
	for (int i = 0; i < DFAStates.size(); i++) {
            vector <NFAState*> u=d->getNFAStates(),
                               v=DFAStates[i]->getNFAStates();   
		if (checkSameStates(u,v)) {
		  d->setID(DFAStates[i]->getID());
	          return true;
		}
	}
	return false;
}
void DFA::subsetConstruction() {
   initiateDtransition();
   while (DFAstatesInc.size()){
       DFAState*d = DFAstatesInc.front();
       DFAstatesInc.pop();
       for (int i=0;i<token.size();i++){
           char ch = token[i];
           vector <NFAState*> x = move(d,ch);
           DFAState* u =new DFAState(0);
           u->addStateSet(x);
           epsilonClosure(u);
           if (u->getNFAStates().size() && !combine(u)){
                u->setID(counter++);
		setAcceptingState(u);
		transitionTable.push_back(vector<int> (token.size()));
		DFAstatesInc.push(u);
		DFAStates.push_back(u);
		statesGroups.push_back(make_pair(u->getID(), u->isAcceptingState()));
	    }
           
	    if (u->getNFAStates().size())
		transitionTable[d->getID()][i] = u->getID();
	    else
		transitionTable[d->getID()][i] = -1;
       }
   }
}