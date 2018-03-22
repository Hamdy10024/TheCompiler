
/* 
 * File:   NFAState.h
 * Author: Abeer
 *
 * Created on March 21, 2018, 1:02 AM
 */

#ifndef NFASTATE_H
#define NFASTATE_H

#include <vector>
#include "Entry.h"

class NFAState {
public:
    typedef std::pair <Entry, NFAState*>  transition;
    typedef std::vector <transition>  stateTransitions;
    State();
    void setID(int id);
    int getID();
    void setAsAccepting();
    bool isAcceptingState();
    void addTransition(transition);
    stateTransitions getTransitions();

private:
    int id; // 0-based, used for indexing the transition table.
    bool acceptingState;
    stateTransitions transitions;
};

#endif /* NFASTATE_H */

