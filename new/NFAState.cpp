#include "NFAState.h"
#include "token_table.h"
using namespace std;
NFAState::NFAState(int id)
{
    this->id=id;
    acceptingState=false;
    this->tk = token_table::empty_token;
}



void NFAState::setAsAccepting(Token tk)
{
    acceptingState = true;
    this->tk = tk;
}


Token NFAState::getToken() {
    return tk;
}

void NFAState::addTransition(transition t)
{
    transitions.push_back(t);
    moves.push_back({new Pattern(t.first.st,t.first.en),(NFAState*)t.second});
}

NFAState::stateMoves *NFAState::getTransitions()
{
    return &moves;
}

void NFAState::addTransition(move m) {
moves.push_back(m);
transitions.push_back({Entry(m.first->rangeBegin,m.first->rangeEnd),m.second});
}
