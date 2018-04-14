/*
 * File:   DFAState.cpp
 * Author: Dahlia
 *
 * Created on March 21, 2018, 12:49 AM
 */
#include "DFAState.h"
#include "NFAState.h"
#include <vector>
#include <iostream>
using namespace std;

DFAState::DFAState(int id)
{

    states.clear();
    this->id=id;
    acceptingState=false;
}
void DFAState::resetAccepting() {
acceptingState = false;
}
void DFAState::editAcceptingVal(int value){
    acceptingState = value;
}
void DFAState::addState(NFAState* state)
{
    states.push_back(state);
}
void DFAState::addStateSet(vector <NFAState*> NFAStates)
{
    states.insert(states.end(), NFAStates.begin(), NFAStates.end() );
}
vector <NFAState*> DFAState::getNFAStates ()
{
    return states;
}

void DFAState::setAsAccepting(Token tk)
{
    this->token = tk;
    acceptingState = true;
}
Token DFAState::getToken()
{
    return token;
}
vector <Pattern> DFAState::all_entries()
{

    vector <Pattern> all;
    for(int i = 0; i < this->states.size(); i++ )
    {
        for(int j=0 ; j<this->states[i]->getTransitions()->size(); j++)
        {
            if(this->states[i]->getETransitions()->at(j).first.accept(LAMBDA))
                continue;
            all.push_back(this->states[i]->getETransitions()->at(j).first);
        }
    }
    return all;
}
