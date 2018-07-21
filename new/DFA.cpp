/*
 * File:   DFA.h
 * Author: Dahlia
 *
 * Created on March 21, 2018, 12:49 AM
 */
#include "DFA.h"
#include "NFAState.h"
#include "dfa/DFAState.h"
#include <stack>
#include <string>
#include <queue>
#include <set>
#include <algorithm>
#include <utility>
#include "token_table.h"
#include <iostream>
using namespace std;
bool comparevec(vector<NFAState *> &a,vector<NFAState *> &b) {
    if(a.size()!=b.size())
        return  false;
    for(int i =0;i<a.size();i++)
    {
        bool t=false;
        for(int j=0;j<b.size();j++)
            t|=a[i]==b[j];
        if(!t)
            return  false;
    }
    return  true;
}
DFA::DFA(NFAState* startState,token_table * toktab)
{
    this->startState = startState;
    counter = 0;
    this->tktab = toktab;
    construct();
}
bool comparator (NFAState* &a, NFAState* &b)
{
    return a->getID()< b->getID();
}
map <NFAState*,bool> visi;
void DFA::DFS(NFAState * node,Pattern inp , vector<NFAState*> &cals){
    if(visi.count(node))
        return;;
    visi[node] = 1;
    State::stateTransitions *ts = node->getETransitions();

    for(int i=0;i<ts->size();i++) {
        if(ts->at(i).first == inp) {
            DFS((NFAState*)ts->at(i).second,Pattern(LAMBDA),cals);
            cals.push_back((NFAState*)ts->at(i).second);
        }
    }
}
vector <Pattern> all_en;
void DFA::construct() {
    vector <NFAState*> epsilonStates;
    set < Pattern> uniq;
    counter = 0;
    DFAState *init = new DFAState(counter++);
    init->setID(0);
    visi.clear();
    DFS(startState,Pattern(LAMBDA),epsilonStates);
    init->addStateSet(epsilonStates);
    queue<DFAState*> alls;
    alls.push(init);
    map<DFAState*,bool>taken;

    while(!alls.empty()) {

        DFAState *curr = alls.front();
        alls.pop();
        if(curr->states.size() ==0 || taken.count(curr))
            continue;
        taken[curr] = 1;
        DFAStates.push_back(curr);
        all_en.clear();
        all_en = curr->all_entries();
        for(int i = 0; i <all_en.size();i++) {
                if(uniq.count(all_en[i]))
                    continue;
                uniq.insert(all_en[i]);
            DFAState* u = new DFAState(counter++);
            u->setID(counter);
            epsilonStates.clear();
            visi.clear();
            for(int k = 0;k<curr->states.size();k++)
                DFS(curr->states[k],all_en[i],epsilonStates);
            u->addStateSet(epsilonStates);
            bool tr = false;
            for(int i=0;i<DFAStates.size();i++) {
                vector<NFAState*> now = u->getNFAStates();
                vector<NFAState*> now2=DFAStates[i]->getNFAStates();
                tr|=comparevec(now,now2);

                if(tr){

                    delete u;
                    u = DFAStates[i];
                    break;
                }
            }
            if(u->states.size()==0 )
            {

                delete u;
                continue;
            }
            curr->addTransition({all_en[i],u});
            alls.push(u);
        }
    }

    for (int i=0;i<DFAStates.size();i++) {
        trans[DFAStates[i]] = *DFAStates[i]->getETransitions();
        string this_token = "";
        for(int j=0;j< DFAStates[i]->states.size();j++)
        {
            Token nt = DFAStates[i]->states[j]->getToken();
            if(tktab->compare_priority(nt,this_token) < 0) {

                DFAStates[i]->setAsAccepting(nt);
            this_token = nt;
            }
        }
    }


    MinDFA * minimizer= new MinDFA();
    transition_table = minimizer->minimize(trans,init);
    delete minimizer;


}
void DFA::freeStates() {

}
TransitionTable* DFA::getTable() {
return transition_table;
}

