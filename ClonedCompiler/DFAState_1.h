/*
 * File:  DFAState.h
 * Authors: Dahlia
 *
 * Created on March 21, 2018, 12:59 AM
 */

#ifndef DFASTATE_H
#define DFASTATE_H
#include <vector>
#include "NFAState.h"


class DFAState{
public:
    DFAState(int id);
    void setID(int id);
    int getID();
    void setAsAccepting();
    void resetAccepting();
    void editAcceptingVal(int value);
    bool isAcceptingState();
    void addState(NFAState* state);
    void addStateSet(std::vector <NFAState*> NFAStates);
    std::vector <NFAState*> getNFAStates ();
    int final;
private:
    int id ; 
    bool acceptingState; 
    std::vector <NFAState*> states;
};

#endif /* DFASTATE_H */

