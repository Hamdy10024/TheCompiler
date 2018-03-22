/* 
 * File:   DFAState.cpp
 * Author: Dahlia
 *
 * Created on March 21, 2018, 12:49 AM
 */
#include "DFAState.h"
#include "NFAState.h"
#include <vector>

using namespace std;

DFAState::DFAState(int id) {
    states.clear();
    this->id=id;
    acceptingState=false;
}
void DFAState::setID(int id) {
    this->id=id;
}
int DFAState::getID() {
    return id;
}
void DFAState::setAsAccepting() {
   acceptingState = true;
}
void DFAState::resetAccepting(){
    acceptingState = false;
}
void DFAState::editAcceptingVal(int value){
    acceptingState = value;
}
bool DFAState::isAcceptingState() {
    return acceptingState;
}
void DFAState::addState(NFAState* state){
    states.push_back(state);
}
void DFAState::addStateSet(vector <NFAState*> NFAStates){
    states.insert(states.end(), NFAStates.begin(), NFAStates.end() );
}
vector <NFAState*> DFAState::getNFAStates (){
    return states;
}