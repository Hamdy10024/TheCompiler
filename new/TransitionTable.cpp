#include <stdlib.h>
#include <vector>
#include <iostream>
#include "TransitionTable.h"
#include "State.h"
#include "dfa/DFAState.h"

using namespace std;
TransitionTable::TransitionTable(TransitionTable::table &transitionTable, State *startState)
{
    this->transitionTable = transitionTable;
    this->startState = startState;
    cout<<"error leeh " <<startState->getID()<<endl;
}

State *TransitionTable::getStartState()
{
    return startState;
}

State *TransitionTable::getNextState(State *current, char input)
{
    State::stateTransitions &tst = transitionTable[current];
    for(std::vector<State::transition>::iterator trans =tst.begin();trans!=tst.end();trans++)
    {
        if(trans->first ==input)
        {
            return trans->second;
        }
    }
    return  NULL;
}
int TransitionTable::size() {
return transitionTable.size();
}
void TransitionTable::print() {
    cout<<"printin the table "<<transitionTable.size()<<endl;
    TransitionTable::table::iterator it;
    for (it = this->transitionTable.begin();it!=transitionTable.end();it++) {
            cout<<it->first->getID()<<" "<<((DFAState*)(it->first))->getToken()<<" ";
        for(int i=0;i<transitionTable[it->first].size();i++) {
            cout <<transitionTable[it->first][i].first.inp << " " <<transitionTable[it->first][i].second->getID();
        }
    cout<<endl;
    }

}
