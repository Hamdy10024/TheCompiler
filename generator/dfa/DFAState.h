/*
 * File:  DFAState.h
 * Authors: Dahlia
 * Created on March 21, 2018, 12:59 AM
 */

#ifndef DFASTATE_H
#define DFASTATE_H
#include <vector>
#include "NFAState.h"


class DFAState : public State
{
public:
    DFAState(int id);
    void setAsAccepting(Token tk);
    Token getToken();
    void addState(NFAState* state);
    void resetAccepting();
    void editAcceptingVal(int value);
    void addStateSet(std::vector <NFAState*> NFAStates);
    std::vector <NFAState*> getNFAStates ();
    std::vector <Pattern> all_entries();
    int id ;
    bool acceptingState;
    Token token;
    std::vector <NFAState*> states;
private:

};

#endif /* DFASTATE_H */
